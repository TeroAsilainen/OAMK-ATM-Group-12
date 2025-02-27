#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


namespace Ui {
class Mainmenu;
}

class Mainmenu : public QDialog
{
    Q_OBJECT

public:
    explicit Mainmenu(QWidget *parent = nullptr);
    ~Mainmenu();

    void setIdcard(const QString &newIdcard);

    void setMyToken(const QByteArray &newMyToken);

    void setIdaccount(const QString &newIdaccount);

    void setIduser(const QString &newIduser);

    void iduserCheck();

    void setFname(const QString &newFname);

    void setMainMenuTimerCount(int newMainMenuTimerCount);

    QTimer *mainMenuTimer;

private slots:

    void getIdUserSlot(QNetworkReply *reply);
    void userNameSlot(QNetworkReply *reply);
    void multipleAccountSlot(QNetworkReply *reply);

    void getBalanceSlot(QNetworkReply *reply);

    void on_btnTransactions_clicked();
    void showTransactionsSlot(QNetworkReply *reply);

    void on_btnLogout_clicked();

    void on_btnWithdraw_clicked();

    void on_btnBalance_clicked();

    void on_btnTransfer_clicked();

    void on_btnPay_clicked();

    void mainMenuTimerTick();

private:
    Ui::Mainmenu *ui;
    QString idcard;
    QByteArray myToken;
    QString idaccount;
    QString iduser;
    QString fname;

    QStringList userAccountList;

    QNetworkAccessManager *getIdUserManager;
    QNetworkAccessManager *userNameManager;
    QNetworkAccessManager *multipleAccountManager;
    QNetworkAccessManager *getTransactionsManager;
    QNetworkReply *reply;
    QByteArray response_data;

    void balanceCheck();
    void nameCheck();
    void multipleAccountCheck();

    QNetworkAccessManager *getBalanceManager;

    int mainMenuTimerCount;

    void responseForbidden();
    void responseDbError();
    void responseServerError();
};

#endif // MAINMENU_H
