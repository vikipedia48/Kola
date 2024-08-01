#ifndef CONTRACTCALLS_H
#define CONTRACTCALLS_H

#include "../../Model/model.h"

#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class ContractCalls;
}

class ContractCalls : public QWidget
{
    Q_OBJECT

public:
    explicit ContractCalls(QWidget *parent = nullptr);
    ContractCalls(std::vector<Model::ExecutingContract>&& contracts, QWidget* parent = nullptr);
    ~ContractCalls();
    std::vector<Model::ExecutingContract>* getContractsPointer() { return &contractCalls; }
signals:
    void sendDockState(bool docked);
    void sendOperationIndex(int index);

public slots:
    void receiveNewIndex(int index);

private slots:
    void on_pushButton_dock_clicked();

    void on_listWidget_calls_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ContractCalls *ui;

    bool docked;
    int currentIndex;
    int currentContractIndex;
    std::vector<Model::ExecutingContract> contractCalls;

    void selectContract(int contractIndex);
};

#endif // CONTRACTCALLS_H
