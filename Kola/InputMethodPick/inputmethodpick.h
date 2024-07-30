#ifndef INPUTMETHODPICK_H
#define INPUTMETHODPICK_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class InputMethodPick;
}

class InputMethodPick : public QWidget
{
    Q_OBJECT

public:
    explicit InputMethodPick(QWidget *parent = nullptr);
    ~InputMethodPick();

signals:
    void sendStackTraceJson(QJsonObject& json);


private slots:
    void on_pushButton_chooseFile_clicked();

    void on_pushButton_web_send_clicked();

    void handleResponse(QNetworkReply* reply);
private:
    Ui::InputMethodPick *ui;
    QNetworkAccessManager* requestManager;

    void showLoadingText(bool show);
};

#endif // INPUTMETHODPICK_H
