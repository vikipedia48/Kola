#ifndef LOOKUP_H
#define LOOKUP_H

#include "luainput.h"
#include "../../Model/model.h"

#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class Lookup;
}

class Lookup : public QWidget
{
    Q_OBJECT

public:
    explicit Lookup(QWidget *parent = nullptr);
    Lookup(std::vector<Model::ExecutingContract>* contracts,
           std::vector<Model::StepMemory>* memoryBlocks,
           std::vector<Model::StepStack>* stackWords,
           std::vector<Model::StepInfo>* steps,
           std::vector<Model::StepStorage>* storageSlots,
           QWidget* parent = nullptr);
    ~Lookup();
signals:
    void sendDockState(bool docked);
    void sendNewIndex(int index);
public slots:
    void receiveNewIndex(int index);
    void receiveResultOffset(int offset);
private slots:
    void receiveLuaBodyBeforeClose(QString lua, bool filterOrSeek);
    void receiveLuaBodyAndRun(QString lua, bool filterOrSeek);

    void on_pushButton_filter_clicked();

    void on_pushButton_dock_clicked();

    void on_pushButton_reset_clicked();

    void on_pushButton_seek_clicked();

    void on_pushButton_findPrevious_clicked();

    void on_pushButton_findNext_clicked();

    void on_pushButton_seekReset_clicked();

    void on_listWidget_steps_itemDoubleClicked(QListWidgetItem *item);

protected:
    //void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::Lookup *ui;
    LuaInput* luaFilterWindow;
    LuaInput* luaSeekWindow;
    std::vector<Model::ExecutingContract>* _contracts;
    std::vector<Model::StepMemory>* _memoryBlocks;
    std::vector<Model::StepStack>* _stackWords;
    std::vector<Model::StepInfo>* _steps;
    std::vector<Model::StepStorage>* _storageSlots;

    bool docked;
    int currentIndex;
    QString luaFilterBody;
    QString luaSeekBody;

    int currentResultIndex;
    std::vector<int> results;

    void filter();
    void seek();
    void showAll();

    void goToResult(int index);


};

#endif // LOOKUP_H
