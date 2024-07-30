#ifndef UNDOCKEDWINDOW_H
#define UNDOCKEDWINDOW_H

#include "qevent.h"
#include <QWidget>

#include "../Transaction/transaction.h"
#include "../Lookup/lookup.h"
#include "debugger.h"

namespace Ui {
class UndockedWindow;
}

class UndockedWindow : public QWidget
{
    Q_OBJECT

public:
    //explicit UndockedWindow(QWidget *parent = nullptr);
    UndockedWindow(QWidget* widget, QString windowTitle);
    ~UndockedWindow();

private:
    Ui::UndockedWindow *ui;
};

class UndockedTransactionWindow : public UndockedWindow {
    Q_OBJECT
public:
    UndockedTransactionWindow(Transaction* widget, Debugger* parentWidget) : UndockedWindow(widget, "Transaction") {
        connect(this, &UndockedTransactionWindow::sendIndexOffset, parentWidget, &Debugger::receiveIndexOffset);
    }
signals:
    void sendIndexOffset(int offset);
protected:
    void keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_A) {
            if (event->modifiers() & Qt::ControlModifier) {
                emit sendIndexOffset(-50);
            }
            else if (event->modifiers() & Qt::ShiftModifier) {
                emit sendIndexOffset(-10);
            }
            else {
                emit sendIndexOffset(-1);
            }
        }
        else if (event->key() == Qt::Key_D) {
            if (event->modifiers() & Qt::ControlModifier) {
                emit sendIndexOffset(50);
            }
            else if (event->modifiers() & Qt::ShiftModifier) {
                emit sendIndexOffset(10);
            }
            else {
                emit sendIndexOffset(1);
            }
        }
    }
};

class UndockedLookupWindow : public UndockedWindow {
    Q_OBJECT
public:
    UndockedLookupWindow(Lookup* widget) : UndockedWindow(widget, "Lookup") {
        connect(this, &UndockedLookupWindow::sendResultOffset, widget, &Lookup::receiveResultOffset);
    }
signals:
    void sendResultOffset(int offset);
protected:
    void keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_W) {
            if (event->modifiers() & Qt::ControlModifier) {
                emit sendResultOffset(-50);
            }
            else if (event->modifiers() & Qt::ShiftModifier) {
                emit sendResultOffset(-10);
            }
            else {
                emit sendResultOffset(-1);
            }
        }
        else if (event->key() == Qt::Key_S) {
            if (event->modifiers() & Qt::ControlModifier) {
                emit sendResultOffset(50);
            }
            else if (event->modifiers() & Qt::ShiftModifier) {
                emit sendResultOffset(10);
            }
            else {
                emit sendResultOffset(1);
            }
        }
    }
};

#endif // UNDOCKEDWINDOW_H
