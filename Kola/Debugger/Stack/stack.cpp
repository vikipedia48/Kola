#include "stack.h"
#include "ui_stack.h"

Stack::Stack(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Stack)
{
    ui->setupUi(this);
}

Stack::Stack(std::vector<Model::StepStack> &&items, QWidget *parent) : QWidget(parent), ui(new Ui::Stack), docked(true), currentIndex(0), steps(items), maxStackSize(0)
{
    ui->setupUi(this);
    setWindowTitle("Stack");
    ui->listWidget_stack->setStyleSheet(
        "QListWidget::item:hover {"
        "   background-color: rgba(127, 25, 25, 255);"
        "}"
        "QListWidget::item:selected {"
        "   background-color: rgba(127, 25, 25, 255);"
        "   color: inherit;"
        "}"
        "QListWidget::item:selected:active {"
        "   background-color: rgba(127, 25, 25, 255);"
        "   color: inherit;"
        "}"
        );

    for(auto& v : this->steps) maxStackSize = std::max(maxStackSize, v._slots.size());

    for(int i = 0; i < 17; ++i) ui->listWidget_stack->addItem("");
    if (maxStackSize > 17) {
        for(int i = 0; i < maxStackSize - 17; ++i) {
            ui->listWidget_entireStack->addItem("");
        }
    }
    ui->listWidget_entireStack->setVisible(false);

}

Stack::~Stack()
{
    delete ui;
}

void Stack::receiveNewIndex(int index)
{
    auto currentStep = steps[currentIndex];
    for (int i = 0; i < currentStep.numberOfPops; ++i) {
        ui->listWidget_stack->item(i)->setBackground(QBrush());
    }
    if (currentStep.ofNotice.has_value()) {
        ui->listWidget_stack->item(currentStep.ofNotice.value())->setBackground(QBrush());
    }

    auto step = steps[index];
    int stackSize = step._slots.size();
    int primaryStackSize = std::min<int>(17, stackSize);

    {
        auto iter = step._slots.rbegin();
        for(int i = 0; i < primaryStackSize; ++i) {
            ui->listWidget_stack->item(i)->setText(*(iter++));
        }
        for(int i = primaryStackSize; i < 17; ++i) {
            if (ui->listWidget_stack->item(i)->text().isEmpty()) break;
            ui->listWidget_stack->item(i)->setText("");
        }
    }

    {
        auto orangeBackground = QBrush(QColor(204, 102, 0));
        for (int i = 0; i < step.numberOfPops; ++i) {
            ui->listWidget_stack->item(i)->setBackground(orangeBackground);
        }
        if (step.ofNotice.has_value()) {
            ui->listWidget_stack->item(step.ofNotice.value())->setBackground(QBrush(QColor(0, 102, 255)));
        }
    }

    currentIndex = index;

    if (ui->listWidget_entireStack->isVisible()) fillSecondaryStack();

}

void Stack::on_pushButton_dock_clicked()
{
    docked = !docked;
    emit sendDockState(docked);
}


void Stack::on_pushButton_expand_clicked()
{
    bool secondaryStackVisible = ui->listWidget_entireStack->isVisible();
    if (secondaryStackVisible) {
        ui->pushButton_expand->setText("Show less");
        ui->listWidget_entireStack->setVisible(false);
        return;
    }

    ui->pushButton_expand->setText("Show more");
    ui->listWidget_entireStack->setVisible(true);
    fillSecondaryStack();
}

void Stack::fillSecondaryStack()
{
    auto stackSize = steps[currentIndex]._slots.size();
    int beginClearIndex = 0;
    if (stackSize > 17) {
        for(; beginClearIndex < stackSize - 17; ++beginClearIndex) {
            auto item = ui->listWidget_entireStack->item(beginClearIndex);
            auto slot = steps[currentIndex]._slots[17+beginClearIndex];
            item->setText(slot);
        }
    }
    for(int i = beginClearIndex; i < ui->listWidget_entireStack->count(); ++i) {
        if (ui->listWidget_entireStack->item(i)->text().isEmpty()) break;
        ui->listWidget_entireStack->item(i)->setText("");
    }
}


