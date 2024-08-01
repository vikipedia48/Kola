#include "transaction.h"
#include "ui_transaction.h"

Transaction::Transaction(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Transaction)
{
    ui->setupUi(this);
}

Transaction::Transaction(int stepCount, bool failed, QString returnValue, QWidget *parent) : QWidget(parent), ui(new Ui::Transaction), docked(true),
    failed(failed), returnValue(returnValue)
{
    ui->setupUi(this);
    setWindowTitle("Transaction");

    ui->horizontalSlider_step->setMinimum(0);
    ui->horizontalSlider_step->setMaximum(stepCount - 1);

    if (failed) {
        ui->label_returnValue->setVisible(false);
    }
    else {
        ui->label_failed->setVisible(false);
        if (!returnValue.isEmpty()) ui->label_returnValue->setText("Returned : " + returnValue);
        else ui->label_returnValue->setVisible(false);
    }
}

Transaction::~Transaction()
{
    delete ui;
}

void Transaction::receiveNewIndexChange(int index)
{
    ui->horizontalSlider_step->setValue(index);
}

void Transaction::on_pushButton_dock_clicked()
{
    docked = !docked;
    emit sendDockedState(docked);
}

void Transaction::on_horizontalSlider_step_valueChanged(int value)
{
    emit sendNewIndex(value);
}

