#include "memory.h"
#include "ui_memory.h"

Memory::Memory(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Memory)
{
    ui->setupUi(this);
}

Memory::Memory(std::vector<Model::StepMemory> &&memoryArrays, QWidget *parent) : QWidget(parent), ui(new Ui::Memory), docked(true), currentIndex(0), items(memoryArrays), maxMemorySize(0)
{
    for(auto& memory : items) {
        maxMemorySize = std::max(memory.blocks.size(), maxMemorySize);
    }

    ui->setupUi(this);
    setWindowTitle("Memory");
    ui->tableWidget_memory->setColumnCount(2);
    ui->tableWidget_memory->setRowCount(maxMemorySize);
    for(int i = 0; i < maxMemorySize; ++i) {
        QString addr = "00";
        if (i > 0) addr.setNum(i * 32, 16);
        auto addrItem = new QTableWidgetItem(addr);
        auto valueItem = new QTableWidgetItem("");
        ui->tableWidget_memory->setItem(i, 0, addrItem);
        ui->tableWidget_memory->setItem(i, 1, valueItem);
    }

    receiveNewIndex(0);
}

Memory::~Memory()
{
    delete ui;
}

void Memory::receiveNewIndex(int index)
{
    auto currentLayout = items[currentIndex];
    if (currentLayout.willBeChanged.has_value()) {
        auto range = currentLayout.willBeChanged.value();
        auto emptyBackground = QBrush();
        for(int i = range.start; i <= range.start + range.end; ++i) {
            // we can safely assume it's not nullptr
            ui->tableWidget_memory->item(i, 0)->setBackground(emptyBackground);
            ui->tableWidget_memory->item(i, 1)->setBackground(emptyBackground);
        }
    }
    if (currentLayout.hasBeenChanged.has_value()) {
        auto range = currentLayout.hasBeenChanged.value();
        auto emptyBackground = QBrush();
        for(int i = range.start; i <= range.start + range.end; ++i) {
            // we can safely assume it's not nullptr
            ui->tableWidget_memory->item(i, 0)->setBackground(emptyBackground);
            ui->tableWidget_memory->item(i, 1)->setBackground(emptyBackground);
        }
    }

    auto layout = items[index];
    auto currentMemorySize = currentLayout.blocks.size();
    auto memorySize = layout.blocks.size();
    for(int i = 0; i < memorySize; ++i) {
        auto block = layout.blocks[i];
        if (i < currentMemorySize) {
            if (block == currentLayout.blocks[i]) {
                continue;
            }
        }
        ui->tableWidget_memory->item(i, 1)->setText(block.title);
    }
    for(int i = memorySize; i < maxMemorySize; ++i) {
        auto item = ui->tableWidget_memory->item(i, 1);
        if (item->text().isEmpty()) break; // if the row is empty, it's the end of array (guaranteed no elements after it)
        item->setText("");
    }

    if (layout.willBeChanged.has_value()) {
        auto range = layout.willBeChanged.value();
        auto yellowBackground = QBrush(QColor(230, 230, 0));
        for(int i = range.start; i <= range.start + range.end; ++i) {
            if (i < ui->tableWidget_memory->rowCount()) ui->tableWidget_memory->item(i, 0)->setBackground(yellowBackground);
            if (i < ui->tableWidget_memory->rowCount()) ui->tableWidget_memory->item(i, 1)->setBackground(yellowBackground);
        }
    }
    if (layout.hasBeenChanged.has_value()) {
        auto range = layout.hasBeenChanged.value();
        auto greenBackground = QBrush(QColor(41, 163, 41));
        for(int i = range.start; i <= range.start + range.end; ++i) {
            ui->tableWidget_memory->item(i, 0)->setBackground(greenBackground);
            ui->tableWidget_memory->item(i, 1)->setBackground(greenBackground);
        }
        ui->tableWidget_memory->scrollToItem(ui->tableWidget_memory->item(range.start, 1));
    }

    currentIndex = index;
}

void Memory::on_pushButton_dock_clicked()
{
    emit sendDockState(docked);
    docked = !docked;
}

