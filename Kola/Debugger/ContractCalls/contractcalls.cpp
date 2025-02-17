#include "contractcalls.h"
#include "ui_contractcalls.h"

ContractCalls::ContractCalls(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ContractCalls)
{
    ui->setupUi(this);
}

ContractCalls::ContractCalls(std::vector<Model::ExecutingContract>&& contracts, QWidget *parent)
    : QWidget(parent), ui(new Ui::ContractCalls), docked(true), currentIndex(0), currentContractIndex(0), contractCalls(contracts)
{
    ui->setupUi(this);
    setWindowTitle("Contract Calls");
    ui->listWidget_calls->setStyleSheet(
        "QListWidget::item:hover {"
        "   background-color: rgba(127, 25, 25, 128);"
        "}"
        "QListWidget::item:selected {"
        "   background-color: rgba(127, 25, 25, 128);"
        "   color: inherit;"
        "}"
        "QListWidget::item:selected:active {"
        "   background-color: rgba(127, 25, 25, 128);"
        "   color: inherit;"
        "}"
        );
    for(int i = 0; i < this->contractCalls.size(); ++i) {
        auto item = new QListWidgetItem(QString::number(i) + " - " + this->contractCalls[i].title);
        if (this->contractCalls[i].failed) item->setBackground(QBrush(QColor(250,7,7)));
        ui->listWidget_calls->addItem(item);
    }

    selectContract(0);
}

ContractCalls::~ContractCalls()
{
    delete ui;
}

void ContractCalls::receiveNewIndex(int index)
{
    for(auto i = 0; i < contractCalls.size(); ++i) {
        auto contract = contractCalls[i];
        if (index >= contract.firstOperationIndex && index <= contract.lastOperationIndex) {
            if (i == currentContractIndex) return;
            selectContract(i);
            currentIndex = index;
        }
    }
}

void ContractCalls::on_pushButton_dock_clicked()
{
    docked = !docked;
    emit sendDockState(docked);
}

void ContractCalls::selectContract(int contractIndex)
{
    ui->listWidget_calls->item(currentContractIndex)->setBackground(contractCalls[currentContractIndex].failed ? QBrush(QColor(250,7,7)) : QBrush());
    auto selectedItem = ui->listWidget_calls->item(contractIndex);
    selectedItem->setBackground(QBrush(contractCalls[contractIndex].failed ? QColor(255,51,51) : QColor(148, 133, 22)));
    ui->listWidget_calls->scrollToItem(selectedItem);
    ui->textBrowser_calldata->setText(contractCalls[contractIndex].calldata.stringRepresentation);
    currentContractIndex = contractIndex;
}



void ContractCalls::on_listWidget_calls_itemDoubleClicked(QListWidgetItem *item)
{
    auto indexInItem = ui->listWidget_calls->indexFromItem(item).row();
    emit sendOperationIndex(contractCalls[indexInItem].firstOperationIndex);
}

