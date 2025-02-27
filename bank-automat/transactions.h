#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <qnetworkaccessmanager.h>
#include <QNetworkAccessManager>
#include <QtNetwork>
#include <qstandarditemmodel.h>
#include "mainmenu.h"

namespace Ui {
class Transactions;
}

class Transactions : public QDialog
{
    Q_OBJECT

public:
    explicit Transactions(Mainmenu *parent = nullptr);
    ~Transactions();
    void showTable(QByteArray);
    void showNextPage();

    void setMyToken(const QByteArray &newMyToken);

    void setIdaccount(const QString &newIdaccount);

    void setTransactionsTimerCount(int newTransactionsTimerCount);

    void setParentPointer(Mainmenu *newParentPointer);

private slots:
    void on_btnCloseTransactions_clicked();

    void on_btnNextTransactions_clicked();

    void on_btnPreviousTransactions_clicked();

    void on_btnContinue_clicked();

    void showNextPageSlot(QNetworkReply *reply);

    void transactionsTimerTick();

private:
    Ui::Transactions *ui;
    QNetworkAccessManager *nextPageManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QByteArray myToken;
    QString idaccount;
    int offset = 0;
    int limit = 5;

    QTimer *transactionsTimer;
    int transactionsTimerCount;

    Mainmenu *parentPointer;

};

#endif // TRANSACTIONS_H
