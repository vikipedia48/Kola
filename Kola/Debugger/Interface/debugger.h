#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QWidget>

#include "../ContractCalls/contractcalls.h"
#include "../Lookup/lookup.h"
#include "../Memory/memory.h"
#include "../Stack/stack.h"
#include "../Step/step.h"
#include "../Storage/storage.h"
#include "../Transaction/transaction.h"



namespace Ui {
class Debugger;
}

class Debugger : public QWidget
{
    Q_OBJECT

public:
    explicit Debugger(QWidget *parent = nullptr);
    Debugger(int stepCount, ContractCalls* contractCalls, Lookup* lookup, Memory* memory, Stack* stack, Step* step, Storage* storage, Transaction* transaction, QWidget *parent = nullptr);
    ~Debugger();
    void assignContractsWindow(ContractCalls* window);
    void assignLookupWindow(Lookup* window);
    void assignMemoryWindow(Memory* window);
    void assignStackWindow(Stack* window);
    void assignStepWindow(Step* window);
    void assignStorageWindow(Storage* window);
    void assignTransactionWindow(Transaction* window);
public slots:
    void dockContractCallsWindow(bool docked);
    void dockLookupWindow(bool docked);
    void dockMemoryWindow(bool docked);
    void dockStackWindow(bool docked);
    void dockStepWindow(bool docked);
    void dockStorageWindow(bool docked);
    void dockTransactionWindow(bool docked);
    void receiveNewIndex(int index);
    void receiveIndexOffset(int offset);
signals:
    void sendNewIndex(int index);
    void sendResultOffset(int offset);

private:
    Ui::Debugger *ui;

    ContractCalls* contractCallsWindow;
    Lookup* lookupWindow;
    Memory* memoryWindow;
    Stack* stackWindow;
    Step* stepWindow;
    Storage* storageWindow;
    Transaction* transactionWindow;
    QWidget* undockedContractCallsWindow;
    QWidget* undockedLookupWindow;
    QWidget* undockedMemoryWindow;
    QWidget* undockedStackWindow;
    QWidget* undockedStepWindow;
    QWidget* undockedStorageWindow;
    QWidget* undockedTransactionWindow;

    int currentIndex;
    int stepCount;

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // DEBUGGER_H
