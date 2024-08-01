#ifndef STACK_H
#define STACK_H

#include <QListWidgetItem>
#include <QWidget>

#include "../../Model/model.h"

namespace Ui {
class Stack;
}

class Stack : public QWidget
{
    Q_OBJECT

public:
    explicit Stack(QWidget *parent = nullptr);
    Stack(std::vector<Model::StepStack>&& items, QWidget* parent = nullptr);
    ~Stack();
    std::vector<Model::StepStack>* getStackWordsPointer() { return &steps; }
public slots:
    void receiveNewIndex(int index);

signals:
    void sendDockState(bool docked);

private slots:
    void on_pushButton_dock_clicked();

    void on_pushButton_expand_clicked();

    void on_listWidget_stack_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::Stack *ui;

    bool docked;
    int currentIndex;
    size_t maxStackSize;
    std::vector<Model::StepStack> steps;

    void fillSecondaryStack();
};

#endif // STACK_H
