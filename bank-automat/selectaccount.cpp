#include "mainmenu.h"
#include "selectaccount.h"
#include "ui_selectaccount.h"

SelectAccount::SelectAccount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SelectAccount)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowFullScreen);

    setSelectAccountTimerCount(0);
    selectAccountTimer = new QTimer(this);
    connect(selectAccountTimer, SIGNAL(timeout()), this, SLOT(selectAccountTimerTick()));
    selectAccountTimer->start(2000);
}

SelectAccount::~SelectAccount()
{
    delete ui;
}

void SelectAccount::setIdDebitAccount(const QString &newIdDebitAccount)
{
    idDebitAccount = newIdDebitAccount;
}

void SelectAccount::setIdCreditAccount(const QString &newIdCreditAccount)
{
    idCreditAccount = newIdCreditAccount;
}

void SelectAccount::on_btnDebit_clicked()
{
    qDebug()<<"Valittu tili "+this->idDebitAccount;
    Mainmenu *objMainmenu=new Mainmenu(this);
    objMainmenu->setIdcard(idcard);
    objMainmenu->setMyToken(myToken);
    objMainmenu->setIdaccount(idDebitAccount);
    objMainmenu->iduserCheck();
    objMainmenu->open();

    selectAccountTimer->stop();
    this->close();
}

void SelectAccount::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
}

void SelectAccount::setIdcard(const QString &newIdcard)
{
    idcard = newIdcard;
}


void SelectAccount::on_btnCredit_clicked()
{
    qDebug()<<"Valittu tili "+this->idCreditAccount;
    Mainmenu *objMainmenu=new Mainmenu(this);
    objMainmenu->setIdcard(idcard);
    objMainmenu->setMyToken(myToken);
    objMainmenu->setIdaccount(idCreditAccount);
    objMainmenu->iduserCheck();
    objMainmenu->open();

    selectAccountTimer->stop();
    this->close();
}

void SelectAccount::selectAccountTimerTick()
{
    // qDebug()<<"tick";
    this->setSelectAccountTimerCount(selectAccountTimerCount+1);
    qDebug()<<selectAccountTimerCount;
    if(selectAccountTimerCount==5){
        ui->labelWarning->setText(tr("Yhteyden aikakatkaisu pian"));
    } else if(selectAccountTimerCount<5 && ui->labelWarning->text()==tr("Yhteyden aikakatkaisu pian")){
        ui->labelWarning->setText("");
    } else if(selectAccountTimerCount==7){
        this->close();
        selectAccountTimer->stop();
    }
}

void SelectAccount::setSelectAccountTimerCount(int newSelectAccountTimerCount)
{
    selectAccountTimerCount = newSelectAccountTimerCount;
}

