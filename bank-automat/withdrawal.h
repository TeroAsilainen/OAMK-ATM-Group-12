#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include "mainmenu.h"
#include <QLineEdit>
#include <qnetworkaccessmanager.h>

#include <QDialog>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>

namespace Ui {
class withdrawal;
}

class withdrawal : public QDialog
{
    Q_OBJECT

public:
    explicit withdrawal(Mainmenu *parent = nullptr);
    ~withdrawal();

    void setWithdrawalTimerCount(int newWithdrawalTimerCount);

    void setMyToken(const QByteArray &newMyToken);

    void setIdaccount(const QString &newIdaccount);

    void checkCreditLimit();

    void setParentPointer(Mainmenu *newParentPointer);

    QTimer *WithdrawalTimer;
    Mainmenu *parentPointer;

private slots:

    void WithdrawalTimerTick();

    void on_btnpaluu_clicked();

    void on_btnmuu_clicked();

    void on_btn200_clicked();

    void on_btn100_clicked();

    void on_btn80_clicked();

    void on_btn50_clicked();

    void on_btn20_clicked();

    void on_btn10_clicked();

    void withdrawalSlot(QNetworkReply *reply);
    void creditLimitSlot(QNetworkReply *reply);

    void on_btnCont_clicked();

private:
    Ui::withdrawal *ui;
    int WithdrawalTimerCount;

    int amount;
    int *amountPointer = &amount;

    QByteArray myToken;
    QString idaccount;
    bool creditLimit;
    void Withdrawal(int amount);

    QNetworkAccessManager *withdrawalManager;
    QNetworkAccessManager *creditLimitManager;
    QNetworkReply *reply;
    QByteArray response_data;

    void responseForbidden();
    void responseDbError();
    void responseServerError();

};

#endif // WITHDRAWAL_H
