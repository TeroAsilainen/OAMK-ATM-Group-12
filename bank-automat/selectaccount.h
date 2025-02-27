#ifndef SELECTACCOUNT_H
#define SELECTACCOUNT_H

#include <QDialog>

namespace Ui {
class SelectAccount;
}

class SelectAccount : public QDialog
{
    Q_OBJECT

public:
    explicit SelectAccount(QWidget *parent = nullptr);
    ~SelectAccount();

    void setIdDebitAccount(const QString &newIdDebitAccount);

    void setIdCreditAccount(const QString &newIdCreditAccount);

    void setIdcard(const QString &newIdcard);

    void setMyToken(const QByteArray &newMyToken);

    void setSelectAccountTimerCount(int newSelectAccountTimerCount);

private slots:
    void on_btnDebit_clicked();

    void on_btnCredit_clicked();

    void selectAccountTimerTick();

private:
    Ui::SelectAccount *ui;
    QString idcard;
    QString idDebitAccount;
    QString idCreditAccount;
    QByteArray myToken;

    QTimer *selectAccountTimer;
    int selectAccountTimerCount;
};

#endif // SELECTACCOUNT_H
