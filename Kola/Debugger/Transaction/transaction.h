#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QWidget>

namespace Ui {
class Transaction;
}

class Transaction : public QWidget
{
    Q_OBJECT

public:
    explicit Transaction(QWidget *parent = nullptr);
    Transaction(int stepCount, bool failed, QString returnValue, QWidget* parent = nullptr);
    ~Transaction();
signals:
    void sendDockedState(bool docked);
    void sendNewIndex(int index);
public slots:
    void receiveNewIndexChange(int index);

private slots:
    void on_pushButton_dock_clicked();
    void on_horizontalSlider_step_valueChanged(int value);

private:
    Ui::Transaction *ui;

    bool docked;
    bool failed;
    QString returnValue;
};

#endif // TRANSACTION_H
