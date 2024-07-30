#include "debugger.h"
#include "qevent.h"
#include "ui_debugger.h"

#include "undockedwindow.h"

Debugger::Debugger(QWidget *parent)
    : QWidget(parent), ui(new Ui::Debugger),
    contractCallsWindow(nullptr), undockedContractCallsWindow(nullptr),
    lookupWindow(nullptr), undockedLookupWindow(nullptr),
    memoryWindow(nullptr), undockedMemoryWindow(nullptr),
    stackWindow(nullptr), undockedStackWindow(nullptr),
    stepWindow(nullptr), undockedStepWindow(nullptr),
    storageWindow(nullptr), undockedStorageWindow(nullptr),
    transactionWindow(nullptr), undockedTransactionWindow(nullptr),
    currentIndex(0), stepCount(1)
{
    ui->setupUi(this);
}

Debugger::Debugger(int stepCount, ContractCalls *contractCalls, Lookup *lookup, Memory *memory, Stack *stack, Step *step, Storage *storage, Transaction *transaction, QWidget *parent)
    : QWidget(parent), ui(new Ui::Debugger),
    undockedContractCallsWindow(nullptr),
    undockedLookupWindow(nullptr),
    undockedMemoryWindow(nullptr),
    undockedStackWindow(nullptr),
    undockedStepWindow(nullptr),
    undockedStorageWindow(nullptr),
    undockedTransactionWindow(nullptr),
    currentIndex(0), stepCount(stepCount)
{
    ui->setupUi(this);
    assignContractsWindow(contractCalls);
    assignLookupWindow(lookup);
    assignMemoryWindow(memory);
    assignStackWindow(stack);
    assignStepWindow(step);
    assignStorageWindow(storage);
    assignTransactionWindow(transaction);
}

Debugger::~Debugger()
{
    delete ui;
    delete undockedContractCallsWindow;
    delete undockedLookupWindow;
    delete undockedMemoryWindow;
    delete undockedStackWindow;
    delete undockedStepWindow;
    delete undockedStorageWindow;
    delete undockedTransactionWindow;
}

void Debugger::assignContractsWindow(ContractCalls *window)
{
    this->contractCallsWindow = window;
    ui->verticalLayout_contractCalls->addWidget(window);
    connect(this, &Debugger::sendNewIndex, this->contractCallsWindow, &ContractCalls::receiveNewIndex);
    connect(this->contractCallsWindow, &ContractCalls::sendDockState, this, &Debugger::dockContractCallsWindow);
}

void Debugger::assignLookupWindow(Lookup *window)
{
    this->lookupWindow = window;
    ui->verticalLayout_lookup->addWidget(window);
    connect(this, &Debugger::sendNewIndex, this->lookupWindow, &Lookup::receiveNewIndex);
    connect(this, &Debugger::sendResultOffset, this->lookupWindow, &Lookup::receiveResultOffset);
    connect(this->lookupWindow, &Lookup::sendNewIndex, this, &Debugger::receiveNewIndex);
    connect(this->lookupWindow, &Lookup::sendDockState, this, &Debugger::dockLookupWindow);
}

void Debugger::assignMemoryWindow(Memory *window)
{
    this->memoryWindow = window;
    ui->verticalLayout_memory->addWidget(window);
    connect(this, &Debugger::sendNewIndex, this->memoryWindow, &Memory::receiveNewIndex);
    connect(this->memoryWindow, &Memory::sendDockState, this, &Debugger::dockMemoryWindow);
}

void Debugger::assignStackWindow(Stack *window)
{
    this->stackWindow = window;
    ui->verticalLayout_stack->addWidget(window);
    connect(this, &Debugger::sendNewIndex, this->stackWindow, &Stack::receiveNewIndex);
    connect(this->stackWindow, &Stack::sendDockState, this, &Debugger::dockStackWindow);
}

void Debugger::assignStepWindow(Step *window)
{
    this->stepWindow = window;
    ui->verticalLayout_step->addWidget(window);
    connect(this, &Debugger::sendNewIndex, this->stepWindow, &Step::receiveNewIndex);
    connect(this->stepWindow, &Step::sendDockState, this, &Debugger::dockStepWindow);
}

void Debugger::assignStorageWindow(Storage *window)
{
    this->storageWindow = window;
    ui->verticalLayout_storage->addWidget(window);
    connect(this, &Debugger::sendNewIndex, this->storageWindow, &Storage::receiveNewIndex);
    connect(this->storageWindow, &Storage::sendDockState, this, &Debugger::dockStorageWindow);
}

void Debugger::assignTransactionWindow(Transaction *window)
{
    this->transactionWindow = window;
    ui->verticalLayout_transaction->addWidget(window);
    connect(this->transactionWindow, &Transaction::sendNewIndex, this, &Debugger::receiveNewIndex);
    connect(this, &Debugger::sendNewIndex, this->transactionWindow, &Transaction::receiveNewIndexChange);
    connect(this->transactionWindow, &Transaction::sendDockedState, this, &Debugger::dockTransactionWindow);
}

void Debugger::dockContractCallsWindow(bool docked)
{
    if (undockedContractCallsWindow != nullptr) {
        if (docked) {
            ui->verticalLayout_contractCalls->addWidget(contractCallsWindow);
            undockedContractCallsWindow->close();
            undockedContractCallsWindow = nullptr;
        }
        return;
    }

    ui->verticalLayout_contractCalls->removeWidget(contractCallsWindow);
    undockedContractCallsWindow = new UndockedWindow(contractCallsWindow, "Contract Calls");
    undockedContractCallsWindow->show();
}

void Debugger::dockLookupWindow(bool docked)
{
    if (undockedLookupWindow != nullptr) {
        if (docked) {
            ui->verticalLayout_lookup->addWidget(lookupWindow);
            undockedLookupWindow->close();
            undockedLookupWindow = nullptr;
        }
        return;
    }
    ui->verticalLayout_contractCalls->removeWidget(lookupWindow);
    undockedLookupWindow = new UndockedLookupWindow(lookupWindow);
    undockedLookupWindow->show();
}

void Debugger::dockMemoryWindow(bool docked)
{
    if (undockedMemoryWindow != nullptr) {
        if (docked) {
            ui->verticalLayout_memory->addWidget(memoryWindow);
            undockedMemoryWindow->close();
            undockedMemoryWindow = nullptr;
        }
        return;
    }
    ui->verticalLayout_contractCalls->removeWidget(memoryWindow);
    undockedMemoryWindow = new UndockedWindow(memoryWindow, "Memory");
    undockedMemoryWindow->show();
}

void Debugger::dockStackWindow(bool docked)
{
    if (undockedStackWindow != nullptr) {
        if (docked) {
            ui->verticalLayout_stack->addWidget(stackWindow);
            undockedStackWindow->close();
            undockedStackWindow = nullptr;
        }
        return;
    }
    ui->verticalLayout_contractCalls->removeWidget(stackWindow);
    undockedStackWindow = new UndockedWindow(stackWindow, "Stack");
    undockedStackWindow->show();
}

void Debugger::dockStepWindow(bool docked)
{
    if (undockedStepWindow != nullptr) {
        if (docked) {
            ui->verticalLayout_step->addWidget(stepWindow);
            undockedStepWindow->close();
            undockedStepWindow = nullptr;
        }
        return;
    }
    ui->verticalLayout_contractCalls->removeWidget(stepWindow);
    undockedStepWindow = new UndockedWindow(stepWindow, "Step");
    undockedStepWindow->show();
}

void Debugger::dockStorageWindow(bool docked)
{
    if (undockedStorageWindow != nullptr) {
        if (docked) {
            ui->verticalLayout_storage->addWidget(storageWindow);
            undockedStorageWindow->close();
            undockedStorageWindow = nullptr;
        }
        return;
    }
    ui->verticalLayout_contractCalls->removeWidget(storageWindow);
    undockedStorageWindow = new UndockedWindow(storageWindow, "Storage");
    undockedStorageWindow->show();
}

void Debugger::dockTransactionWindow(bool docked)
{
    if (undockedTransactionWindow != nullptr) {
        if (docked) {
            ui->verticalLayout_transaction->addWidget(transactionWindow);
            undockedTransactionWindow->close();
            undockedTransactionWindow = nullptr;
        }
        return;
    }
    ui->verticalLayout_contractCalls->removeWidget(transactionWindow);
    undockedTransactionWindow = new UndockedTransactionWindow(transactionWindow, this);
    undockedTransactionWindow->show();
}

void Debugger::receiveNewIndex(int index)
{
    currentIndex = index;
    emit sendNewIndex(index);
}

void Debugger::receiveIndexOffset(int offset)
{
    currentIndex = std::max(std::min(stepCount-1, currentIndex + offset), 0);
    emit sendNewIndex(currentIndex);
}

void Debugger::keyPressEvent(QKeyEvent *event)
{
    if (undockedTransactionWindow == nullptr) {
        if (event->key() == Qt::Key_A) {
            if (event->modifiers() & Qt::ControlModifier) {
                receiveIndexOffset(-50);
            }
            else if (event->modifiers() & Qt::ShiftModifier) {
                receiveIndexOffset(-10);
            }
            else {
                receiveIndexOffset(-1);
            }
        }
        else if (event->key() == Qt::Key_D) {
            if (event->modifiers() & Qt::ControlModifier) {
                receiveIndexOffset(50);
            }
            else if (event->modifiers() & Qt::ShiftModifier) {
                receiveIndexOffset(10);
            }
            else {
                receiveIndexOffset(1);
            }
        }
    }
    if (undockedLookupWindow == nullptr) {
        if (event->key() == Qt::Key_W) {
            if (event->modifiers() & Qt::ControlModifier) emit sendResultOffset(-50);
            else if (event->modifiers() & Qt::ShiftModifier) emit sendResultOffset(-10);
            else emit sendResultOffset(-1);
        }
        else if (event->key() == Qt::Key_S) {
            if (event->modifiers() & Qt::ControlModifier) emit sendResultOffset(50);
            else if (event->modifiers() & Qt::ShiftModifier) emit sendResultOffset(10);
            else emit sendResultOffset(1);
        }
    }

    else {
        QWidget::keyPressEvent(event);
    }
}

