#ifndef STEP_H
#define STEP_H

#include <QLabel>
#include <QWidget>

#include "../../Model/model.h"

namespace Ui {
class Step;
}

class Step : public QWidget
{
    Q_OBJECT

public:
    explicit Step(QWidget *parent = nullptr);
    Step(std::vector<Model::StepInfo>&& steps, QWidget* parent = nullptr);
    ~Step();
    std::vector<Model::StepInfo>* getStepsPointer() { return &steps; }
signals:
    void sendDockState(bool docked);
public slots:
    void receiveNewIndex(int index);
private slots:
    void on_pushButton_dock_clicked();

private:
    struct Param {
        QWidget* parent;
        QLabel* name;
        QLabel* value;
        Param(QWidget* parent, QLabel* name, QLabel* value) : parent(parent), name(name), value(value) {}
    };

    Ui::Step *ui;

    bool docked;
    int currentIndex;
    std::vector<Model::StepInfo> steps;
    std::vector<Param> paramWidgets;
};

#endif // STEP_H
