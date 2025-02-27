#ifndef PAYMENT_H
#define PAYMENT_H

#include "mainmenu.h"

#include <QDialog>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>

namespace Ui {
class Payment;
}

class Payment : public QDialog
{
    Q_OBJECT

public:
    explicit Payment(Mainmenu *parent = nullptr);
    ~Payment();

    void setPaymentTimerCount(int newPaymentTimerCount);


    void setMyToken(const QByteArray &newMyToken);

    void setIdaccount(const QString &newIdaccount);

    void setPaymentAmount(const QString &newPaymentAmount);

    void setFormattedPaymentAmount(double newFormattedPaymentAmount);

    void setParentPointer(Mainmenu *newParentPointer);

private slots:

    void PaymentTimerTick();

    void digitClicked(int digit);

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

    void on_btnClear_clicked();

    void on_btnPaluu_clicked();

    void on_btnMaksa_clicked();

    void on_btnSwitch_clicked();

    void paymentSlot(QNetworkReply *reply);
    void creditLimitSlot(QNetworkReply *reply);

    void on_btnCon_clicked();

private:
    Ui::Payment *ui;
    QString enteredSum;
    QString enteredAccount;
    bool enteringSum;
    QString formattedSum;
    QTimer *PaymentTimer;

    Mainmenu *parentPointer;

    int PaymentTimerCount;
    QByteArray myToken;
    QString idaccount;

    bool creditLimit;
    void payment(bool creditLimit);
    QNetworkAccessManager *paymentManager;
    QNetworkAccessManager *creditLimitManager;
    QNetworkReply *reply;
    QByteArray response_data;

    void responseForbidden();
    void responseDbError();
    void responseServerError();


};

#endif // PAYMENT_H
