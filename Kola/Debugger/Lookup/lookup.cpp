#include "lookup.h"
#include "ui_lookup.h"

#include "../../Utils/qtfunctions.h"
#include "lookupbutton.h"
#include "../../sol.hpp"

#include <QKeyEvent>

Lookup::Lookup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Lookup)
{
    ui->setupUi(this);
}

Lookup::Lookup(std::vector<Model::ExecutingContract> *contracts,
               std::vector<Model::StepMemory> *memoryBlocks,
               std::vector<Model::StepStack> *stackWords,
               std::vector<Model::StepInfo> *steps,
               std::vector<Model::StepStorage> *storageSlots,
               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lookup),
    luaFilterWindow(nullptr), luaSeekWindow(nullptr),
    _contracts(contracts),
    _memoryBlocks(memoryBlocks),
    _stackWords(stackWords),
    _steps(steps),
    _storageSlots(storageSlots),
    docked(true), currentIndex(0), currentResultIndex(0), luaFilterBody(""), luaSeekBody(""), results({})
{
    ui->setupUi(this);
    setWindowTitle("Lookup");
    ui->listWidget_steps->setStyleSheet(
        "QListWidget::item:hover {"
        "   background-color: rgba(127, 25, 25, 255);"
        "}"
        "QListWidget::item:selected {"
        "   background-color: rgba(127, 25, 25, 255);"
        "   color: inherit;"
        "}"
        "QListWidget::item:selected:active {"
        "   background-color: rgba(127, 25, 25, 255);"
        "   color: inherit;"
        "}"
        );
    showAll();
}

Lookup::~Lookup()
{
    delete ui;
    delete luaFilterWindow;
    delete luaSeekWindow;
}

void Lookup::receiveNewIndex(int index)
{
    currentIndex = index;
}

void Lookup::receiveLuaBodyBeforeClose(QString lua, bool filterOrSeek)
{
    if (filterOrSeek) {
        luaFilterBody = lua;
        luaFilterWindow->close();
        luaFilterWindow = nullptr;
        filter();
    }
    else {
        luaSeekBody = lua;
        luaSeekWindow->close();
        luaSeekWindow = nullptr;
        seek();
    }
}

void Lookup::receiveLuaBodyAndRun(QString lua, bool filterOrSeek)
{
    if (filterOrSeek) {
        luaFilterBody = lua;
        filter();
    }
    else {
        luaSeekBody = lua;
        seek();
    }
}

void Lookup::on_pushButton_filter_clicked()
{
    if (luaFilterWindow != nullptr) {
        Gui::PrintMessage("Filter", "Window is already opened");
        return;
    }

    luaFilterWindow = new LuaInput(true, luaFilterBody);
    connect(luaFilterWindow, &LuaInput::sendLua, this, &Lookup::receiveLuaBodyAndRun);
    connect(luaFilterWindow, &LuaInput::sendLuaBeforeClose, this, &Lookup::receiveLuaBodyBeforeClose);
    luaFilterWindow->show();
}


void Lookup::on_pushButton_dock_clicked()
{
    docked = !docked;
    emit sendDockState(docked);
}

void Lookup::on_pushButton_reset_clicked()
{
    luaFilterBody = "";
    showAll();
}

void Lookup::filter()
{
    results.clear();
    currentResultIndex = 0;
    ui->listWidget_steps->clear();

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::table);
    lua.script(QString("function filter()\n\t--more info on github\n" + luaFilterBody + "\nend").toStdString());

    try {
        auto stepCount = _steps->size();
        for(int i = 0; i < stepCount; ++i) {

            auto step = _steps->at(i);
            lua["match"] = false;
            lua["opcode"] = step.opcode.toStdString();
            lua["pushes_new_value"] = step.newValuePushed.value_or("").toStdString();
            lua["index"] = i;
            lua["thread_index"] = step.threadIndex;
            lua["thread_name"] = (*_contracts).at(step.threadIndex).title;

            lua.create_named_table("sets_memory_value");
            lua.create_named_table("sets_memory_slot");
            lua["sets_storage_slot"] = "";
            lua["sets_storage_value"] = "";
            if (i+1 < stepCount) {
                auto memory = _memoryBlocks->at(i+1);
                auto storage = _storageSlots->at(i+1);
                if (memory.hasBeenChanged.has_value()) {
                    auto range = memory.hasBeenChanged.value();
                    for (int memoryIndex = range.start; memoryIndex < range.end; ++memoryIndex) {
                        lua["sets_memory_value"][memory.blocks[memoryIndex].title.toStdString()] = true;
                        lua["sets_memory_slot"][memoryIndex] = true;
                        auto hexSlot = memoryIndex == 0 ? "0x00" : "0x" + QString::number(memoryIndex*32, 16);
                        lua["sets_memory_slot"][hexSlot.toStdString()] = true;
                    }
                }
                if (storage.hasBeenChanged.has_value()) {
                    auto slot = storage.hasBeenChanged.value();
                    lua["sets_storage_slot"] = storage._slots[slot].address.toStdString();
                    lua["sets_storage_value"] = storage._slots[slot].word.toStdString();
                }
            }

            lua["filter"]();
            if (lua["match"] == true) {
                auto item = new LookupButton(step.indexStr + " - " + step.opcode, i);
                ui->listWidget_steps->addItem(item);
            }
        }
    } catch(sol::error ex) {
        QString error = ex.what();
        Gui::ThrowError("lua function error has occured : " + error + ".");
    } catch(std::exception ex) {
        QString error = ex.what();
        Gui::ThrowError("error has occured : " + error + ".");
    }
}

void Lookup::seek()
{
    for(auto v : results) {
        ui->listWidget_steps->item(v)->setBackground(QBrush());
    }
    results.clear();
    currentResultIndex = 0;

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::math);
    lua.script(QString("function seek()\n\t--more info on github\n" + luaSeekBody + "\nend").toStdString());

    auto filterCount = ui->listWidget_steps->count();
    try {
        for(int i = 0; i < filterCount; ++i) {
            auto lookupItem = dynamic_cast<LookupButton*>(ui->listWidget_steps->item(i));
            auto index = lookupItem->index;
            auto stepCount = _steps->size();

            auto step = _steps->at(index);
            lua["match"] = false;
            lua["opcode"] = step.opcode.toStdString();
            lua["pushes_new_value"] = step.newValuePushed.value_or("").toStdString();
            lua["index"] = index;
            lua["thread_index"] = step.threadIndex;
            lua["thread_name"] = (*_contracts).at(step.threadIndex).title;

            lua.create_named_table("sets_memory_value");
            lua.create_named_table("sets_memory_slot");
            lua["sets_storage_slot"] = "";
            lua["sets_storage_value"] = "";
            if (index+1 < stepCount) {
                auto memory = _memoryBlocks->at(index+1);
                auto storage = _storageSlots->at(index+1);
                if (memory.hasBeenChanged.has_value()) {
                    auto range = memory.hasBeenChanged.value();
                    for (int memoryIndex = range.start; memoryIndex < range.end; ++memoryIndex) {
                        lua["sets_memory_value"][memory.blocks[memoryIndex].title.toStdString()] = true;
                        lua["sets_memory_slot"][memoryIndex] = true;
                        auto hexSlot = memoryIndex == 0 ? "0x00" : "0x" + QString::number(memoryIndex*32, 16);
                        lua["sets_memory_slot"][hexSlot.toStdString()] = true;
                    }
                }
                if (storage.hasBeenChanged.has_value()) {
                    auto slot = storage.hasBeenChanged.value();
                    lua["sets_storage_slot"] = storage._slots[slot].address.toStdString();
                    lua["sets_storage_value"] = storage._slots[slot].word.toStdString();
                }
            }


            lua["seek"]();

            bool matched = lua["match"];

            if (matched) {
                results.push_back(i);
            }
        }
    } catch(sol::error ex) {
        QString error = ex.what();
        Gui::ThrowError("lua function error has occured : " + error + ".");
        return;
    } catch(std::exception ex) {
        QString error = ex.what();
        Gui::ThrowError("error has occured : " + error + ".");
        return;
    }

    if (results.empty()) {
        Gui::PrintMessage("Seek", "no matches found");
        return;
    }
    for(auto v : results) {
        ui->listWidget_steps->item(v)->setBackground(QBrush(QColor(204, 153, 0)));
    }
    auto firstMatch = ui->listWidget_steps->item(results[0]);
    firstMatch->setBackground(QBrush(QColor(0, 204, 0)));
    ui->listWidget_steps->scrollToItem(firstMatch);
}

void Lookup::showAll()
{
    ui->listWidget_steps->clear();
    auto steps = *_steps;
    for(auto& v : steps) {
        auto item = new LookupButton(v.indexStr + " - " + v.opcode, v.index);
        ui->listWidget_steps->addItem(item);
    }
}

void Lookup::goToResult(int index)
{
    auto item = ui->listWidget_steps->item(results[index]);
    ui->listWidget_steps->scrollToItem(item);
    currentResultIndex = index;
}

void Lookup::on_pushButton_seek_clicked()
{

    if (luaSeekWindow != nullptr) {
        Gui::PrintMessage("Filter", "Window is already opened");
        return;
    }

    luaSeekWindow = new LuaInput(false, luaSeekBody);
    connect(luaSeekWindow, &LuaInput::sendLua, this, &Lookup::receiveLuaBodyAndRun);
    connect(luaSeekWindow, &LuaInput::sendLuaBeforeClose, this, &Lookup::receiveLuaBodyBeforeClose);
    luaSeekWindow->show();
}


void Lookup::on_pushButton_findPrevious_clicked()
{
    if (results.size() < 2) return;
    if (currentResultIndex == 0) goToResult(results.size()-1);
    goToResult(--currentResultIndex);
}


void Lookup::on_pushButton_findNext_clicked()
{
    if (results.size() < 2) return;
    if (currentResultIndex == results.size()-1) goToResult(0);
    goToResult(++currentResultIndex);
}


void Lookup::on_pushButton_seekReset_clicked()
{
    for(auto& v : results) {
        ui->listWidget_steps->item(v)->setBackground(QBrush());
    }
    results.clear();
}

void Lookup::receiveResultOffset(int offset)
{
    if (results.size() > 1) {
        int nextIndex = currentResultIndex + offset;
        if (nextIndex >= results.size()) goToResult(0);
        else if (nextIndex < 0) goToResult(results.size()-1);
        else goToResult(nextIndex);
    }
}

/*void Lookup::keyPressEvent(QKeyEvent *event)
{

    if (results.size() > 1) {
        if (event->key() == Qt::Key_S) {
            int nextIndex = currentResultIndex;
            if (event->modifiers() & Qt::ShiftModifier) {
                nextIndex += 5;
            }
            else if (event->modifiers() & Qt::AltModifier) {
                nextIndex += 10;
            }
            else {
                ++nextIndex;
            }
            if (nextIndex >= results.size()) goToResult(0);
            else goToResult(nextIndex);
        }
        else if (event->key() == Qt::Key_W) {
            int nextIndex = currentResultIndex;
            if (event->modifiers() & Qt::ShiftModifier) {
                nextIndex -= 5;
            }
            else if (event->modifiers() & Qt::AltModifier) {
                nextIndex -= 10;
            }
            else {
                --nextIndex;
            }
            if (nextIndex < 0) goToResult(results.size()-1);
            else goToResult(nextIndex);
        }
    }
    else QWidget::keyPressEvent(event);
}
*/

void Lookup::on_listWidget_steps_itemDoubleClicked(QListWidgetItem *item)
{
    auto lookupItem = dynamic_cast<LookupButton*>(item);
    emit sendNewIndex(lookupItem->index);
}

