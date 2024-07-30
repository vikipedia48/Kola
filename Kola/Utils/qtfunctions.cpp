#include "qtfunctions.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QInputDialog>

void Gui::ThrowError(const QString& msg)
{
    QMessageBox messageBox;
    messageBox.critical(nullptr, "Error",msg);
    messageBox.setFixedSize(500,200);
}

QString Gui::GetSavePath()
{
    return QFileDialog::getSaveFileName(nullptr,"Save file",QDir::homePath());
}

QString Gui::GetInputPath(const QString& windowName, const QString &tip)
{
    return QFileDialog::getOpenFileName(nullptr,windowName,QDir::homePath(),tip);
}

void Gui::PrintMessage(const QString &title, const QString &msg)
{
    QMessageBox messageBox;
    messageBox.information(nullptr,title,msg);
    messageBox.setFixedSize(500,200);
}

QString Gui::GetStringValueFromInputDialog(const QString &title, const QString &desc)
{
    bool ok;
    QString text = QInputDialog::getText(nullptr, title, desc, QLineEdit::Normal, "", &ok);
    if (!ok || text.isEmpty()) {
        Gui::ThrowError("Invalid input.");
        return "";
    }
    return text;
}

bool Gui::GiveQuestion(const QString &question)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Question", question, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) return true;
    else return false;
}

double Gui::GetNumberValueFromInputDialog(const QString &title, const QString &desc)
{
    double rv;
    bool ok;
    QString text = QInputDialog::getText(nullptr, title, desc, QLineEdit::Normal);
    rv = text.toDouble(&ok);
    if (!ok) {
        Gui::ThrowError("Invalid input.");
        return 0;
    }
    return rv;
}

