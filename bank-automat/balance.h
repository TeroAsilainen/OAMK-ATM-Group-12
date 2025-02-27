#ifndef BALANCE_H
#define BALANCE_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QJsonDocument>
#include "environment.h"
#include "mainmenu.h"

class Mainmenu;

namespace Ui {
class Balance;
}

class Balance : public QDialog
{
    Q_OBJECT

public:
    explicit Balance(Mainmenu *parent = nullptr);
    ~Balance();

    void setIdaccount(const QString &newIdaccount);

    void setMyToken(const QByteArray &newMyToken);

    void setBalance(const QString &newBalance);

    void setLimit(const QString &newLimit);

    void setIduser(const QString &newIduser);

    void setFname(const QString &newFname);

    void setLname(const QString &newLname);

    void setPhonenumber(const QString &newPhonenumber);

    void setAddress(const QString &newAddress);

    void userDataCheck();

    void setIdcard(const QString &newIdcard);

    void setBalanceTimerCount(int newBalanceTimerCount);

    void setParentPointer(Mainmenu *newParentPointer);

private slots:

    void userDataSlot(QNetworkReply *reply);

    void on_btnUserData_clicked();

    void on_btnBack_clicked();

    void balanceTimerTick();

    void on_btnContinue_clicked();

private:
    Ui::Balance *ui;
    void balanceCheck();

    QString balance;

    QString limit;

    QString idcard;

    QString idaccount;
    QString iduser;
    QString fname;
    QString lname;
    QString phonenumber;
    QString address;

    QByteArray myToken;

    QNetworkAccessManager *userDataManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QTimer *balanceTimer;
    int balanceTimerCount;

    Mainmenu *parentPointer;


};

#endif // BALANCE_H
