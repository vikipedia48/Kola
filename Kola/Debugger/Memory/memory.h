#ifndef MEMORY_H
#define MEMORY_H

#include <QTableWidgetItem>
#include <QWidget>

#include "../../Model/model.h"

namespace Ui {
class Memory;
}

class Memory : public QWidget
{
    Q_OBJECT

public:
    explicit Memory(QWidget *parent = nullptr);
    Memory(std::vector<Model::StepMemory>&& memoryArrays, QWidget* parent = nullptr);
    ~Memory();
    std::vector<Model::StepMemory>* getSlotsPointer() { return &items; };
public slots:
    void receiveNewIndex(int index);
signals:
    void sendDockState(bool docked);
private slots:
    void on_pushButton_dock_clicked();

    void on_tableWidget_memory_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::Memory *ui;

    bool docked;
    int currentIndex;
    size_t maxMemorySize;
    std::vector<Model::StepMemory> items;

};

#endif // MEMORY_H
