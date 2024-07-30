#ifndef STORAGE_H
#define STORAGE_H

#include <QWidget>

#include "../../Model/model.h"

namespace Ui {
class Storage;
}

class Storage : public QWidget
{
    Q_OBJECT

public:
    explicit Storage(QWidget *parent = nullptr);
    Storage(std::vector<Model::StepStorage>&& storageLayouts, QWidget* parent = nullptr);
    ~Storage();
    std::vector<Model::StepStorage>* getLayoutsPointer() { return &layouts; }
signals:
    void sendDockState(bool docked);
public slots:
    void receiveNewIndex(int index);

private slots:
    void on_pushButton_dock_clicked();

private:
    Ui::Storage *ui;

    bool docked;
    int currentIndex;
    int maxLayoutSize;
    std::vector<Model::StepStorage> layouts;
};

#endif // STORAGE_H
