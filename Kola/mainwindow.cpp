#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Utils/qtfunctions.h"
#include "Model/model.h"
#include "Opcode/opcode.h"

#include "InputMethodPick/inputmethodpick.h"
#include "Debugger/Interface/debugger.h"
#include "Debugger/Transaction/transaction.h"


#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <unordered_set>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    currentWindow(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Kola");
    displayInputMethodPick();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete currentWindow;
}

void MainWindow::on_actionReset_triggered()
{
    displayInputMethodPick();
}


void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::displayInputMethodPick()
{
    closeCurrentWindow();
    auto inputMethodPick = new InputMethodPick();
    connect(inputMethodPick, &InputMethodPick::sendStackTraceJson, this, &MainWindow::receiveStackTraceJson, Qt::DirectConnection);
    currentWindow = inputMethodPick;
    ui->widgetWindow->addWidget(currentWindow, 0, Qt::AlignmentFlag::AlignVCenter);
    currentWindow->show();
}

void MainWindow::closeCurrentWindow()
{
    if (currentWindow == nullptr) return;
    currentWindow->close();
    currentWindow = nullptr;
}

void MainWindow::receiveStackTraceJson(QJsonObject &json)
{
        auto structLogsArr = json["structLogs"];
        if (!structLogsArr.isArray()) {
            Gui::ThrowError("invalid stack trace");
            return;
        }

        auto structLogs = structLogsArr.toArray();
        auto opCount = structLogs.count();

        Transaction* transactionWindow;
        {
            bool failed = json["failed"].toBool(false);

            QString returnValue;
            auto value = json["returnValue"];
            switch (value.type()) {
            case QJsonValue::Null:
                returnValue = "null";
            case QJsonValue::Bool:
                returnValue = value.toBool() ? "true" : "false";
            case QJsonValue::Double:
                returnValue = QString::number(value.toDouble());
            case QJsonValue::String:
                returnValue = value.toString();
            case QJsonValue::Array:
                returnValue = QString::fromUtf8(QJsonDocument(value.toArray()).toJson(QJsonDocument::Indented));
            case QJsonValue::Object:
                returnValue = QString::fromUtf8(QJsonDocument(value.toObject()).toJson(QJsonDocument::Indented));
            default:
                returnValue = "";
            }

            transactionWindow = new Transaction(opCount, failed, returnValue);
        }

        std::vector<Model::StepInfo> steps;
        steps.reserve(opCount);
        std::vector<Model::StepStack> stacks;
        stacks.reserve(opCount);
        std::vector<Model::StepMemory> memories;
        memories.reserve(opCount);
        std::vector<Model::StepStorage> storages;
        storages.reserve(opCount);

        std::vector<Model::ExecutingContract> calls = { Model::ExecutingContract("this", 0, 1) };
        Model::Calldata mainCalldata;

        std::unordered_map<QString, std::unordered_set<Model::StorageSlot>> inferredStorage;

        for(size_t i = 0; i < opCount; ++i) {
            auto op = structLogs[i].toObject();

            std::optional<QString> errorReason;
            auto errorObj = op["error"];
            if (errorObj.isArray()) {
                QString errorMsg = "Failed due to errors : ";
                auto errors = errorObj.toArray();
                for(auto val : errors) {
                    errorMsg += val.toString("") + ", ";
                }
                errorMsg += ".";
                errorReason = errorMsg;
            }
            else if (errorObj.isString()) {
                auto error = errorObj.toString();
                errorReason = "Failed due to error : " + error + ".";
            }
            else {
                auto reason = op["reason"].toString();
                if (!reason.isEmpty()) errorReason = "Failed due to : " + reason + ".";
            }

            auto opcode = Opcode::fromName(op["op"].toString());

            auto stack = getStringVectorFromJsonArray(op["stack"].toArray());

            std::vector<QString> memory;
            if (opcode->editsMemory() && i > 0) {
                memory = getStringVectorFromJsonArray(structLogs[i-1].toObject()["memory"].toArray());
            }
            else {
                memory = getStringVectorFromJsonArray(op["memory"].toArray());
            }

            if (i < opCount-1) { // update ExecutingContracts
                if (errorReason.has_value() || opcode->decreasesDepth()) {
                    auto callSize = calls.size();
                    if (callSize > 1) {
                        auto lastCall = calls[callSize-1];
                        lastCall.lastOperationIndex = i;
                        if (errorReason.has_value()) lastCall.failed = true;
                        calls.push_back(calls[callSize-2]);
                    }
                }
                else {
                    auto addr = opcode->callsContract(stack, QString::number(i));
                    if (!addr.isEmpty()) {

                        calls[calls.size()-1].lastOperationIndex = i;

                        auto nextOp = structLogs[i+1].toObject();
                        auto nextDepth = nextOp["depth"].toInt();

                        auto calldata = opcode->calldata(stack, memory);
                        calls.emplace_back(Model::ExecutingContract(addr,i, nextDepth, calldata));
                        if (inferredStorage.find(addr) == inferredStorage.end()) {
                            inferredStorage[addr] = {};
                        }
                    }
                }
            }

            { // StepInfo
                std::vector<Model::OperationArgument> functionArgs;
                if (opcode->pushSize() > 0) {
                    if (i+1 < opCount) {
                        auto nextOp = structLogs[i+1].toObject();
                        auto nextStack = nextOp["stack"].toArray();
                        auto lastStackElement = nextStack.last().toString();
                        auto arguments = opcode->functionArgs(stack, lastStackElement.right(opcode->pushSize() * 2));
                        functionArgs = { Model::OperationArgument(arguments[0].first, arguments[0].second) };
                    }
                    else {
                        auto arguments = opcode->functionArgs(stack, "?");
                        functionArgs = { Model::OperationArgument(arguments[0].first, arguments[0].second) };
                    }
                }
                else {
                    auto arguments = opcode->functionArgs(stack);
                    functionArgs.reserve(arguments.size());
                    for (auto&& v : arguments) {
                        functionArgs.emplace_back(Model::OperationArgument(v.first, v.second));
                    }
                }

                std::optional<QString> newValuePushed;
                if (opcode->pushesNewValue() && i+1 < opCount) {
                    auto nextOp = structLogs[i+1].toObject();
                    auto nextStack = nextOp["stack"].toArray();
                    auto lastStackElement = nextStack.last().toString();
                    newValuePushed = lastStackElement;
                }

                auto pcDouble = op["pc"].toDouble(0);
                auto pc = static_cast<uint64_t>(pcDouble);

                auto gasLeftDouble = op["gas"].toDouble();
                auto gasLeft = static_cast<uint64_t>(gasLeftDouble);

                auto gasCostDouble = op["gasCost"].toDouble();
                auto gasCost = static_cast<uint64_t>(gasCostDouble);

                std::optional<QString> errorReason;
                auto errorObj = op["error"];
                if (errorObj.isArray()) {
                    QString errorMsg = "Failed due to errors : ";
                    auto errors = errorObj.toArray();
                    for(auto val : errors) {
                        errorMsg += val.toString("") + ", ";
                    }
                    errorMsg += ".";
                    errorReason = errorMsg;
                }
                else if (errorObj.isString()) {
                    auto error = errorObj.toString();
                    errorReason = "Failed due to error : " + error + ".";
                }
                else {
                    auto reason = op["reason"].toString();
                    if (!reason.isEmpty()) errorReason = "Failed due to : " + reason + ".";
                }

                steps.emplace_back(Model::StepInfo(opcode->name(), opcode->description(), std::move(functionArgs), i, pc, gasLeft, gasCost, calls.size()-1, errorReason, newValuePushed));
            }

            { // assign memory and reconstruct calldata
                auto memorySlotsToBeChanged = opcode->memorySlotsToBeChanged(stack);

                auto memorySlotsChanged = i > 0 ? memories[i-1].willBeChanged : std::nullopt;

                if (calls[calls.size()-1].isMain) {
                    if (opcode->isCallDataLoad() && i+1 < opCount && stack.size() > 0) {
                        auto nextOp = structLogs[i+1].toObject();
                        auto nextStack = nextOp["stack"].toArray();
                        auto loadedFromCalldata = nextStack.last().toString();
                        bool ok;
                        auto offset = stack[stack.size()-1].toUInt(&ok, 16);
                        if (!loadedFromCalldata.isEmpty() && ok) {
                            for(int index = 0; index < 64; ++index) {
                                mainCalldata.setByte(offset * 2 + index, loadedFromCalldata.at(index));
                            }
                        }
                    }
                    else if (opcode->isCallDataCopy() && i+1 < opCount && memorySlotsToBeChanged.has_value() && stack.size() >= 3) {
                        auto iter = stack.rbegin();
                        bool ok1, ok2, ok3;
                        auto _destOffset = *iter;
                        auto _offset = *(++iter);
                        auto _length = *(++iter);
                        auto destOffset = _destOffset.toUInt(&ok1, 16);
                        auto offset = _offset.toUInt(&ok2, 16);
                        auto length = _length.toUInt(&ok3, 16);
                        if (ok1 && ok2 && ok3)  {
                            auto memoryInThisJsonObject = getStringVectorFromJsonArray(op["memory"].toArray());
                            for(int index = 0; index < length; ++index) {
                                int absoluteMemoryIndex = destOffset + index;
                                int memorySlotIndex = absoluteMemoryIndex / 32;
                                int stringIndex = (absoluteMemoryIndex%32) * 2;
                                mainCalldata.setByte(offset*2+index, memoryInThisJsonObject[memorySlotIndex].at(stringIndex));
                                mainCalldata.setByte(offset*2+index+1, memoryInThisJsonObject[memorySlotIndex].at(stringIndex+1));
                            }
                        }
                    }
                    else if (opcode->isCallDataSize() && i + 1 < opCount) {
                        auto nextOp = structLogs[i+1].toObject();
                        auto nextStack = nextOp["stack"].toArray();
                        auto callDataSize = nextStack.last().toString();
                        bool ok;
                        auto calldataSize = callDataSize.toUInt(&ok, 16);
                        if (ok) mainCalldata.size = calldataSize;
                    }
                }

                memories.emplace_back(Model::StepMemory(std::move(memory), memorySlotsChanged, memorySlotsToBeChanged));
            }


            { // storage
                auto currentCall = calls[calls.size()-1];

                std::vector<Model::StorageSlot> storage;
                std::optional<int> willBeChanged;

                if (opcode->isSStore() && i > 0) {
                    auto previousOp = structLogs[i-1].toObject();
                    auto previousStorage = previousOp["storage"].toObject();
                    storage = getStorageFromJsonObject(previousStorage);
                }
                else {
                    storage = getStorageFromJsonObject(op["storage"].toObject());
                }

                // update willBeChanged
                if (opcode->isSStore() || opcode->isSLoad()) {
                    auto address = stack[stack.size()-1];
                    auto iter = std::find_if(storage.begin(), storage.end(), [&address](Model::StorageSlot el) { return el.address == address; });
                    if (iter != storage.end()) {
                        auto index = iter - storage.begin();
                        willBeChanged = index;
                    }
                    else {
                        willBeChanged = storage.size();
                    }
                }

                // add inferred storage
                for(auto& v : inferredStorage[currentCall.title]) {
                    if (std::find(storage.begin(), storage.end(), v) == storage.end()) {
                        storage.push_back(v);
                    }
                }

                // update inferred storage if SLOAD
                if (opcode->isSLoad() && i+1 < opCount) {
                    auto nextOp = structLogs[i+1].toObject();
                    auto nextStack = nextOp["stack"].toArray();
                    auto address = stack[stack.size()-1];
                    inferredStorage[currentCall.title].insert(Model::StorageSlot(address, nextStack.last().toString(), false));
                }

                auto storageSlotsChanged = i > 0 ? storages[i-1].willBeChanged : std::nullopt;

                storages.emplace_back(Model::StepStorage(std::move(storage), storageSlotsChanged, willBeChanged));
            }

            { // StepStack
                std::optional<int> ofNotice;
                int numberOfPops = 0;
                if (opcode->dupSize() > 0) {
                    ofNotice = opcode->dupSize() - 1;
                }
                else if (opcode->swapSize() > 0) {
                    ofNotice = opcode->swapSize();
                }
                else if (!opcode->isPush()) {
                    numberOfPops = steps[i].params.size();
                }

                stacks.emplace_back(Model::StepStack(std::move(stack), ofNotice, numberOfPops));
            }
        }

        mainCalldata.setStringRepresentation();
        for(auto& v : calls) if(v.isMain) v.calldata = mainCalldata;

        auto contractsWindow = new ContractCalls(std::move(calls));
        auto memoryWindow = new Memory(std::move(memories));
        auto stackWindow = new Stack(std::move(stacks));
        auto stepWindow = new Step(std::move(steps));
        auto storageWindow = new Storage(std::move(storages));
        auto lookupWindow = new Lookup(contractsWindow->getContractsPointer(), memoryWindow->getSlotsPointer(), stackWindow->getStackWordsPointer(), stepWindow->getStepsPointer(), storageWindow->getLayoutsPointer());

        auto debugger = new Debugger(opCount, contractsWindow, lookupWindow, memoryWindow, stackWindow, stepWindow, storageWindow, transactionWindow);

    closeCurrentWindow();
    currentWindow = debugger;
    ui->widgetWindow->addWidget(currentWindow);
    currentWindow->show();
    currentWindow->setFocus();
}

std::vector<QString> MainWindow::getStringVectorFromJsonArray(const QJsonArray &arr)
{
    auto arraySize = arr.count();
    std::vector<QString> stringVector;
    stringVector.reserve(arraySize);
    for(uint64_t i = 0; i < arraySize; ++i) {
        auto wordObj = arr[i];
        if (!wordObj.isString()) throw std::exception();
        auto word = wordObj.toString();
        stringVector.push_back(word);
    }
    return stringVector;
}

std::vector<Model::StorageSlot> MainWindow::getStorageFromJsonObject(const QJsonObject &obj)
{
    if (obj.isEmpty()) return {};
    std::vector<Model::StorageSlot> rv;
    for (auto& key : obj.keys()) {
        auto valueObj = obj[key];
        auto value = valueObj.toString("?");
        rv.push_back(Model::StorageSlot(key, value, true));
    }
    return rv;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QApplication::quit();
}
