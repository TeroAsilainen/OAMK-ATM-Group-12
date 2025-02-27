#ifndef AMOUNT_H
#define AMOUNT_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <qnetworkreply.h>
#include <qnetworkaccessmanager.h>
#include <withdrawal.h>

#include <QDialog>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>

namespace Ui {
class Amount;
}

class Amount : public QDialog
{
    Q_OBJECT

public:
    explicit Amount(withdrawal *parent = nullptr);
    ~Amount();

    void setAmountTimerCount(int newAmountTimerCount);

    void setMyToken(const QByteArray &newMyToken);

    void setIdaccount(const QString &newIdaccount);

    void setCreditLimit(bool newCreditLimit);

    void setParentPointer(withdrawal *newParentPointer);

private slots:

    void AmountTimerTick();

    void digitClicked(int digit);

    void on_btnBack_clicked();

    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

    void on_btn0_clicked();

    void on_btnErase_clicked();

    void on_btnEmpty_clicked();

    void on_btnOk_clicked();

    void on_btnJatka_clicked();

    void enteredAmountSlot(QNetworkReply *reply);


private:
    Ui::Amount *ui;
    QString enteredAmount;
    QTimer *AmountTimer;
    int AmountTimerCount;

    bool creditLimit;
    QByteArray myToken;
    QString idaccount;

    QNetworkAccessManager *enteredAmountManager;
    QNetworkReply *reply;
    QByteArray response_data;
    withdrawal *parentPointer;
};

#endif // AMOUNT_H
