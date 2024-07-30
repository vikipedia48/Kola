#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Model/model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void receiveStackTraceJson(QJsonObject& obj);
    
private slots:
    void on_actionReset_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QWidget* currentWindow;
    
    void closeCurrentWindow();
    void displayInputMethodPick();

    std::vector<QString> getStringVectorFromJsonArray(const QJsonArray& arr);
    std::vector<Model::StorageSlot> getStorageFromJsonObject(const QJsonObject& obj);
};
#endif // MAINWINDOW_H
