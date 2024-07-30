#ifndef LUAINPUT_H
#define LUAINPUT_H

#include <QWidget>

namespace Ui {
class LuaInput;
}

class LuaInput : public QWidget
{
    Q_OBJECT

public:
    explicit LuaInput(QWidget *parent = nullptr);
    LuaInput(bool filterOrSeek, QString lua, QWidget* parent = nullptr);
    ~LuaInput();
signals:
    void sendLua(QString lua, bool filterOrSeek);
    void sendLuaBeforeClose(QString lua, bool filterOrSeek);

private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_apply_clicked();

private:
    Ui::LuaInput *ui;

    bool isFilter;

    QString luaFunction();
};

#endif // LUAINPUT_H
