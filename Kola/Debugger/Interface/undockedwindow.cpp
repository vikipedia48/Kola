#include "undockedwindow.h"
#include "ui_undockedwindow.h"

UndockedWindow::UndockedWindow(QWidget *widget, QString title) : QWidget(nullptr), ui(new Ui::UndockedWindow)
{
    ui->setupUi(this);
    setWindowTitle(title);
    ui->widgetWindow->addWidget(widget);
}

UndockedWindow::~UndockedWindow()
{
    delete ui;
}
