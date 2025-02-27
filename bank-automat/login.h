#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QLineEdit>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    void setMyToken(const QByteArray &newMyToken);

    void setIdaccount(const QString &newIdaccount);

    void setIdaccount2(const QString &newIdaccount2);

    void setWrongAttempts(int newWrongAttempts);

    void setLoginTimerCount(int newLoginTimerCount);

private slots:
    void on_btnKirjaudu_clicked();
    void wrongAttemptsSlot (QNetworkReply *reply);
    void loginSlot (QNetworkReply *reply);
    void cardAccountSlot (QNetworkReply *reply);
    void accountLimitSlot (QNetworkReply *reply);
    void wrongAttemptsUpdateSlot (QNetworkReply *reply);

    void loginTimerTick();

    void on_btnNext_clicked();

    void on_btnPrevious_clicked();

    void on_btnNum1_clicked();

    void on_btnNum2_clicked();

    void on_btnNum3_clicked();

    void on_btnNum4_clicked();

    void on_btnNum5_clicked();

    void on_btnNum6_clicked();

    void on_btnNum7_clicked();

    void on_btnNum8_clicked();

    void on_btnNum9_clicked();

    void on_btnNum0_clicked();

    void on_btnBackspace_clicked();

    void on_btnClear_clicked();

    void on_btnClose_clicked();

private:
    Ui::login *ui;
    QByteArray myToken;

    QString idaccount;
    QString idaccount2;
    int wrongAttempts;
    QTimer *loginTimer;

    QNetworkAccessManager *wrongAttemptsManager;
    QNetworkAccessManager *wrongAttemptsUpdateManager;
    QNetworkAccessManager *loginManager;
    QNetworkReply *reply;
    QByteArray response_data;

    QNetworkAccessManager *cardAccountManager;
    // QNetworkReply *replyCardAccount;
    // QByteArray response_cardAccount;

    QNetworkAccessManager *accountLimitManager;

    QLineEdit *lineEditPointer;
    void digitClicked(int);

    void wrongAttemptsCheck(QString);
    void loginTry();
    void wrongAttemptsUpdate(QString);
    void cardAccountCheck(QString, QByteArray);
    void accountLimitCheck(QString, QByteArray);

    int loginTimerCount;
};

#endif // LOGIN_H
