#include "luainput.h"
#include "ui_luainput.h"

#include "../../sol.hpp"
#include "../../Utils/qtfunctions.h"

LuaInput::LuaInput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LuaInput)
{
    ui->setupUi(this);
}

LuaInput::LuaInput(bool filterOrSeek, QString lua, QWidget *parent) : QWidget(parent), ui(new Ui::LuaInput), isFilter(filterOrSeek)
{
    ui->setupUi(this);
    setWindowTitle("Lua");
    ui->plainTextEdit_body->setPlainText(lua);

    ui->label_title->setText(isFilter ? "Lua filter script" : "Lua seek script");
    ui->label_signature->setText(isFilter ? "function filter()\n\t--more info on github" : "function seek()\n\t--more info on github");
}

LuaInput::~LuaInput()
{
    delete ui;
}

void LuaInput::on_pushButton_close_clicked()
{
    emit sendLuaBeforeClose(ui->plainTextEdit_body->toPlainText(), isFilter);
}

void LuaInput::on_pushButton_apply_clicked()
{
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::table, sol::lib::math);
    try {
        auto result = lua.script(luaFunction().toStdString());
        if (result.valid()) {
            sol::function fx = lua[isFilter ? "filter" : "seek"];
            if (!fx.valid()) {
                throw sol::error("invalid function");
            }
        }
        else {
            throw sol::error("invalid function");
        }
    } catch(sol::error ex) {
        Gui::ThrowError(ex.what());
        return;
    }

    emit sendLua(ui->plainTextEdit_body->toPlainText(), isFilter);
}

QString LuaInput::luaFunction()
{
    return isFilter ? "function filter()\n\t--more info on github\n" + ui->plainTextEdit_body->toPlainText() + "\nend" : "function seek()\n\t--more info on github\n" + ui->plainTextEdit_body->toPlainText() + "\nend";
}

