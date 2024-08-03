#include "step.h"
#include "ui_step.h"

#include "../../Utils/hextooltip.h"

Step::Step(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Step)
{
    ui->setupUi(this);
}

Step::Step(std::vector<Model::StepInfo> &&steps, QWidget *parent) : QWidget(parent), ui(new Ui::Step), steps(steps), docked(true), currentIndex(0)
{
    ui->setupUi(this);
    setWindowTitle("Step");
    paramWidgets = {Param(ui->widget_param1, ui->label_param1Name, ui->label_param1Value ),
                    Param(ui->widget_param2, ui->label_param2Name, ui->label_param2Value),
                    Param(ui->widget_param3, ui->label_param3Name, ui->label_param3Value),
                    Param(ui->widget_param4, ui->label_param4Name, ui->label_param4Value),
                    Param(ui->widget_param5, ui->label_param5Name, ui->label_param5Value),
                    Param(ui->widget_param6, ui->label_param6Name, ui->label_param6Value),
                    Param(ui->widget_param7, ui->label_param7Name, ui->label_param7Value)};
    for(auto& v : paramWidgets) v.parent->setVisible(false);
    receiveNewIndex(0);
}

Step::~Step()
{
    delete ui;
}

void Step::receiveNewIndex(int index)
{
    auto step = steps[index];

    ui->label_indexValue->setText(step.indexStr);
    ui->label_pcValue->setText(step.pcStr);
    ui->label_gasValue->setText(step.gasLeftStr);
    ui->label_gasCostValue->setText(step.gasCostStr);

    if (step.errorReason.has_value()) {
        ui->textBrowser_error->setVisible(true);
        ui->textBrowser_error->setText(step.errorReason.value());
        ui->textBrowser_error->setToolTip(step.reverted ? HexTooltip::hexUtf8(step.errorReason.value()) : "");
    }
    else {
        ui->textBrowser_error->setVisible(false);
    }

    ui->label_opcode->setText(step.opcode);
    ui->label_opcode->setToolTip(step.description);

    auto paramsCount = step.params.size();
    for(int i = 0; i < paramsCount; ++i) {
        auto param = paramWidgets[i];
        param.parent->setVisible(true);
        param.name->setText(step.params[i].name);
        param.value->setText(step.params[i].value);
        param.value->setToolTip(step.params[i].tooltip);
    }

    for(int i = paramsCount; i < 7; ++i) {
        paramWidgets[i].parent->setVisible(false);
    }

    currentIndex = index;
}

void Step::on_pushButton_dock_clicked()
{
    docked = !docked;
    emit sendDockState(docked);
}

