#ifndef TRANSFER_H
#define TRANSFER_H


#include <QDialog>
#include <QTimer>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class Mainmenu;

namespace Ui {
class Transfer;
}

class Transfer : public QDialog
{
    Q_OBJECT

public:
    explicit Transfer(Mainmenu *parent = nullptr);
    ~Transfer();



    void setUserAccountList(const QStringList &newUserAccountList);

    void setTransferTimerCount(int newTransferTimerCount);

    void setTransferAmountInput(const QString &newTransferAmountInput);

    void setFormattedTransferAmount(double newFormattedTransferAmount);

    void setParentPointer(Mainmenu *newParentPointer);

    void setMyToken(const QByteArray &newMyToken);

private slots:
    void on_btnCancel_clicked();
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
    void on_btnContinue_clicked();
    void on_btnTransfer_clicked();

    void transferTimerTick();

    void on_comboAccount1_highlighted(int index);
    void on_comboAccount2_highlighted(int index);
    void on_comboAccount1_activated(int index);
    void on_comboAccount2_activated(int index);
    void on_comboAccount1_currentTextChanged(const QString &arg1);
    void on_comboAccount2_currentTextChanged(const QString &arg1);

    void isCreditSlot(QNetworkReply *reply);
    void transferSlot(QNetworkReply *reply);

private:
    Ui::Transfer *ui;

    QStringList userAccountList;

    QString transferAmountInput;
    double formattedTransferAmount;

    void digitClicked(int);

    QTimer *transferTimer;
    int transferTimerCount;

    Mainmenu *parentPointer;

    bool isCredit;
    QByteArray myToken;

    QNetworkAccessManager *isCreditManager;
    QNetworkAccessManager *transferManager;
    QNetworkReply *reply;
    QByteArray response_data;
    void transfer(bool isCredit);

    void responseForbidden();
    void responseDbError();
    void responseServerError();
};

#endif // TRANSFER_H
