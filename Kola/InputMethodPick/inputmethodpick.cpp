#include "inputmethodpick.h"
#include "ui_inputmethodpick.h"
#include "../Utils/qtfunctions.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

InputMethodPick::InputMethodPick(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InputMethodPick)
{
    ui->setupUi(this);
    ui->label_loading->setVisible(false);
    requestManager = new QNetworkAccessManager();
}

InputMethodPick::~InputMethodPick()
{
    delete ui;
    delete requestManager;
}

void InputMethodPick::on_pushButton_chooseFile_clicked()
{
    auto absolutePath = Gui::GetInputPath("Select file", "All files (*)");
    if (absolutePath.isEmpty()) return;


    QFile file(absolutePath);
    if (!file.open(QIODevice::ReadOnly)) {
        Gui::ThrowError("file could not be read");
        return;
    }

    showLoadingText(true);

    auto data = file.readAll();
    QJsonParseError err;
    auto jsonDoc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError) {
        Gui::ThrowError("file is not valid JSON");
        showLoadingText(false);
        return;
    }
    if (!jsonDoc.isObject()) {
        Gui::ThrowError("file is not a valid JSON object");
        showLoadingText(false);
        return;
    }
    auto jsonObj = jsonDoc.object();
    auto resultObj = jsonObj["result"];
    if (!resultObj.isObject()) {
        emit sendStackTraceJson(jsonObj);
        showLoadingText(false);
    }
    else {
        auto traceObj = resultObj.toObject();
        emit sendStackTraceJson(traceObj);
        showLoadingText(false);
    }
}


void InputMethodPick::on_pushButton_web_send_clicked()
{
    if (ui->lineEdit_rpcAddress->text().isEmpty() || ui->lineEdit_txHash->text().isEmpty()) {
        Gui::ThrowError("please input the RPC URL and the transaction hash");
        return;
    }

    showLoadingText(true);

    auto request = QNetworkRequest(QUrl(ui->lineEdit_rpcAddress->text()));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/json");
    auto requestBody = "{\"jsonrpc\":\"2.0\",\"method\":\"debug_traceTransaction\",\"params\":[\"" + ui->lineEdit_txHash->text() + "\"],\"id\":1}";
    connect(requestManager, &QNetworkAccessManager::finished, this, &InputMethodPick::handleResponse);
    requestManager->post(request, requestBody.toUtf8());
}

void InputMethodPick::handleResponse(QNetworkReply *reply)
{
    disconnect(requestManager, &QNetworkAccessManager::finished, this, &InputMethodPick::handleResponse);
    if (reply->error() != QNetworkReply::NoError) {
        Gui::ThrowError("an error occured while requesting the RPC : " + reply->errorString());
    }
    else {
        auto bytes = reply->readAll();
        auto jsonDoc = QJsonDocument::fromJson(bytes);
        if (!jsonDoc.isObject()) {
            Gui::ThrowError("bad response from RPC");
        }
        else {
            auto jsonObj = jsonDoc.object();
            auto result = jsonObj["result"];
            if (!result.isObject()) {
                Gui::ThrowError("bad response from RPC");
            }
            auto resultObj = result.toObject();
            emit sendStackTraceJson(resultObj);
        }
    }
    showLoadingText(false);
    reply->deleteLater();
}

void InputMethodPick::showLoadingText(bool show)
{
    ui->label_loading->setVisible(show);
    ui->pushButton_chooseFile->setEnabled(!show);
    ui->pushButton_web_send->setEnabled(!show);
    QApplication::processEvents();
}
