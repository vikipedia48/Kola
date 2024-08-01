#include "storage.h"
#include "ui_storage.h"

Storage::Storage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Storage)
{
    ui->setupUi(this);
}

Storage::Storage(std::vector<Model::StepStorage> &&storageLayouts, QWidget *parent) : QWidget(parent), ui(new Ui::Storage),
    currentIndex(0), docked(true), layouts(storageLayouts), maxLayoutSize(0)
{
    ui->setupUi(this);
    setWindowTitle("Storage");

    for(auto& v : this->layouts) maxLayoutSize = std::max<int>(maxLayoutSize, v._slots.size());
    ui->tableWidget_storage->setColumnCount(2);
    ui->tableWidget_storage->setRowCount(maxLayoutSize);
    for(int i = 0; i < maxLayoutSize; ++i) {
        auto addr = new QTableWidgetItem("");
        auto word = new QTableWidgetItem("");
        ui->tableWidget_storage->setItem(i, 0, addr);
        ui->tableWidget_storage->setItem(i, 1, word);
    }
}

Storage::~Storage()
{
    delete ui;
}

void Storage::receiveNewIndex(int index)
{
    auto currentLayout = layouts[currentIndex];
    if (currentLayout.hasBeenChanged.has_value()) {
        ui->tableWidget_storage->item(currentLayout.hasBeenChanged.value(), 1)->setBackground((QBrush()));
    }
    if (currentLayout.willBeChanged.has_value()) {
        ui->tableWidget_storage->item(currentLayout.willBeChanged.value(), 1)->setBackground(QBrush());
    }

    auto newLayout = layouts[index];
    auto newLayoutSlotCount = newLayout._slots.size();
    for(int i = 0; i < newLayoutSlotCount; ++i) {
        auto newSlot = newLayout._slots[i];
        if (i < currentLayout._slots.size()) {
            auto currentSlot = currentLayout._slots[i];
            if (newSlot.hash != currentSlot.hash) {
                ui->tableWidget_storage->item(i, 0)->setText(newSlot.address);
                ui->tableWidget_storage->item(i, 1)->setText(newSlot.word);
                ui->tableWidget_storage->item(i, 1)->setToolTip(newSlot.tooltip);
            }
            if (newSlot.hasBeenAltered != currentSlot.hasBeenAltered) {
                ui->tableWidget_storage->item(i, 0)->setBackground(newSlot.hasBeenAltered ? QBrush(QColor(255, 102, 0)) : QBrush());
            }
        }
        else {
            ui->tableWidget_storage->item(i, 0)->setText(newSlot.address);
            ui->tableWidget_storage->item(i, 1)->setText(newSlot.word);
            ui->tableWidget_storage->item(i, 1)->setToolTip(newSlot.tooltip);
            ui->tableWidget_storage->item(i, 0)->setBackground(newSlot.hasBeenAltered ? QBrush(QColor(255, 102, 0)) : QBrush());
        }
    }
    for(int i = newLayoutSlotCount; i < maxLayoutSize; ++i) {
        if (ui->tableWidget_storage->item(i, 0)->text().isEmpty()) break;
        ui->tableWidget_storage->item(i, 0)->setText("");
        ui->tableWidget_storage->item(i, 1)->setText("");
    }

    if (newLayout.hasBeenChanged.has_value()) {
        auto item = ui->tableWidget_storage->item(newLayout.hasBeenChanged.value(), 1);
        item->setBackground(QBrush(QColor(41, 163, 41)));
        ui->tableWidget_storage->scrollToItem(item);
    }
    if (newLayout.willBeChanged.has_value()) {
        if (newLayout.willBeChanged.value() < ui->tableWidget_storage->rowCount())
            ui->tableWidget_storage->item(newLayout.willBeChanged.value(), 1)->setBackground(QBrush(QColor(230, 230, 0)));
    }

    currentIndex = index;
}

void Storage::on_pushButton_dock_clicked()
{
    docked = !docked;
    emit sendDockState(docked);
}

