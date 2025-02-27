#include "environment.h"
#include "mainmenu.h"
#include "payment.h"
#include "transactions.h"
#include "transfer.h"
#include "ui_mainmenu.h"
#include "withdrawal.h"

#include <QStandardItemModel>
#include "balance.h"
#include <qnetworkrequest.h>
#include <QTableView>
#include <QMessageBox>


Mainmenu::Mainmenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Mainmenu)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowFullScreen);

    setMainMenuTimerCount(0);
    mainMenuTimer = new QTimer(this);
    connect(mainMenuTimer, SIGNAL(timeout()), this, SLOT(mainMenuTimerTick()));
    mainMenuTimer->start(2000);
}

Mainmenu::~Mainmenu()
{
    delete ui;
}

void Mainmenu::setIdcard(const QString &newIdcard)
{
    idcard = newIdcard;
    //ui->labelCard->setText(idcard);
}

void Mainmenu::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
}

void Mainmenu::setIdaccount(const QString &newIdaccount)
{
    idaccount = newIdaccount;
}

void Mainmenu::setIduser(const QString &newIduser)
{
    iduser = newIduser;
}

void Mainmenu::setFname(const QString &newFname)
{
    fname = newFname;
    ui->labelTervehdys->setText(ui->labelTervehdys->text()+fname+"!");
}

void Mainmenu::setMainMenuTimerCount(int newMainMenuTimerCount)
{
    mainMenuTimerCount = newMainMenuTimerCount;
}



void Mainmenu::iduserCheck()
{
    QString site_url=Environment::base_url()+"/card/"+idcard;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getIdUserManager = new QNetworkAccessManager(this);

    connect(getIdUserManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getIdUserSlot(QNetworkReply*)));

    reply = getIdUserManager->get(request);
}

void Mainmenu::getIdUserSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    if (response_data=="Forbidden") {
        responseForbidden();
    }
    else if (response_data=="-11"){
        responseDbError();
    }
    else if ((response_data.length()<1)||response_data.contains("Unavailable")){
        responseServerError();
    }
    else {
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    //QJsonArray json_array = json_doc.array();

    this->setIduser(QString::number(json_doc["iduser"].toInt()));
    qDebug()<<"käyttäjätunnus "+this->iduser;

    this->nameCheck();

    reply->deleteLater();
    getIdUserManager->deleteLater();
    }
}



void Mainmenu::nameCheck()
{
    QString site_url=Environment::base_url()+"/user/"+iduser;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    userNameManager = new QNetworkAccessManager(this);

    connect(userNameManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(userNameSlot(QNetworkReply*)));

    reply = userNameManager->get(request);
}

void Mainmenu::userNameSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    if (response_data=="Forbidden") {
        responseForbidden();
    }
    else if (response_data=="-11"){
        responseDbError();
    }
    else if ((response_data.length()<1)||response_data.contains("Unavailable")){
        responseServerError();
    }
    else {
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    //QJsonObject json_obj = json_doc.object();

    this->setFname(json_doc["fname"].toString());
    this->multipleAccountCheck();

    reply->deleteLater();
    userNameManager->deleteLater();
    }
}



void Mainmenu::multipleAccountCheck()
{
    QString site_url=Environment::base_url()+"/account_user/"+iduser;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    multipleAccountManager = new QNetworkAccessManager(this);

    connect(multipleAccountManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(multipleAccountSlot(QNetworkReply*)));

    reply = multipleAccountManager->get(request);
}

void Mainmenu::multipleAccountSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    if (response_data=="Forbidden") {
        responseForbidden();
    }
    else if (response_data=="-11"){
        responseDbError();
    }
    else if ((response_data.length()<1)||response_data.contains("Unavailable")){
        responseServerError();
    }
    else {
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    if(json_array.size()==1){
        this->ui->btnTransfer->setDisabled(true);
    } else {
        foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            userAccountList.append(json_obj["idaccount"].toString());
        }
        qDebug()<<"Käyttäjän tilit "<<userAccountList;
        this->ui->btnTransfer->setEnabled(true);
    }

    reply->deleteLater();
    multipleAccountManager->deleteLater();
    }
}



void Mainmenu::on_btnTransactions_clicked()
{
    setMainMenuTimerCount(0);
    mainMenuTimer->stop();

    QJsonObject jsonObj;
    jsonObj.insert("offset",0);

    QString site_url=Environment::base_url()+"/transaction/"+idaccount;
    qDebug()<<"idaccount="+idaccount;
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    getTransactionsManager = new QNetworkAccessManager(this);
    connect(getTransactionsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(showTransactionsSlot(QNetworkReply*)));
    reply = getTransactionsManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Mainmenu::showTransactionsSlot(QNetworkReply *reply)
{

    response_data=reply->readAll();
    qDebug()<<response_data;

    if (response_data=="Forbidden") {
        responseForbidden();
    }
    else if (response_data=="-11"){
        responseDbError();
    }
    else if ((response_data.length()<1)||response_data.contains("Unavailable")){
        responseServerError();
    }
    else {
    Transactions *objTransactions=new Transactions(this);
    objTransactions->showTable(response_data);
    objTransactions->setMyToken(myToken);
    objTransactions->setIdaccount(idaccount);
    objTransactions->open();

    reply->deleteLater();
    getTransactionsManager->deleteLater();
    }
}



void Mainmenu::balanceCheck()
{
    QString site_url=Environment::base_url()+"/account/"+idaccount;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    getBalanceManager = new QNetworkAccessManager(this);

    connect(getBalanceManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getBalanceSlot(QNetworkReply*)));

    reply = getBalanceManager->get(request);
}

void Mainmenu::getBalanceSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    if (response_data=="Forbidden") {
        responseForbidden();
    }
    else if (response_data=="-11"){
        responseDbError();
    }
    else if((response_data.length()<1)||response_data.contains("Unavailable")){
        responseServerError();
    }
    else {
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    //QJsonArray json_array = json_doc.array();
    Balance *objBalance= new Balance(this);
    objBalance->setIdaccount(idaccount);
    objBalance->setBalance(json_doc["balance"].toString());

    objBalance->setLimit(json_doc["credit_limit"].toString());

    objBalance->setMyToken(myToken);
    objBalance->setIdcard(idcard);
    objBalance->setIduser(iduser);
    //objBalance->userDataCheck();
    objBalance->open();

    reply->deleteLater();
    getBalanceManager->deleteLater();
    }
}


void Mainmenu::on_btnLogout_clicked()
{
    this->close();
    mainMenuTimer->stop();
}


void Mainmenu::on_btnWithdraw_clicked()
{
    withdrawal *objWithdrawal= new withdrawal(this);
    objWithdrawal->setMyToken(myToken);
    objWithdrawal->setIdaccount(idaccount);
    objWithdrawal->checkCreditLimit();
    objWithdrawal->open();
    setMainMenuTimerCount(0);
    mainMenuTimer->stop();
}


void Mainmenu::on_btnBalance_clicked()
{
    balanceCheck();
    setMainMenuTimerCount(0);
    mainMenuTimer->stop();

}

void Mainmenu::on_btnTransfer_clicked()
{
    Transfer *objTransfer = new Transfer(this);
    objTransfer->setMyToken(myToken);
    objTransfer->setUserAccountList(userAccountList);
    objTransfer->open();
    setMainMenuTimerCount(0);
    mainMenuTimer->stop();
}

void Mainmenu::on_btnPay_clicked()
{
    Payment *objPay = new Payment(this);
    objPay->setIdaccount(idaccount);
    objPay->setMyToken(myToken);
    objPay->open();

    setMainMenuTimerCount(0);
    mainMenuTimer->stop();
}


void Mainmenu::mainMenuTimerTick()
{
    this->setMainMenuTimerCount(mainMenuTimerCount+1);
    qDebug()<<mainMenuTimerCount;
    if(mainMenuTimerCount==10) {
        this->close();
        mainMenuTimer->stop();
    }
}


void Mainmenu::responseForbidden()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Istunto on vanhentunut"));
    messageBox->setText(tr("Istuntosi on vanhentunut. Kirjaudu sisään uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    messageBox->exec();
    this->close();
}

void Mainmenu::responseDbError()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Tietokanta ei vastaa"));
    messageBox->setText(tr("Tietokanta ei vastaa. Yritä hetken kuluttua uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    mainMenuTimer->stop();
    messageBox->exec();
    mainMenuTimer->start();
}

void Mainmenu::responseServerError()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Palvelin ei vastaa"));
    messageBox->setText(tr("Palvelin ei vastaa. Yritä hetken kuluttua uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    mainMenuTimer->stop();
    messageBox->exec();
    mainMenuTimer->start();
}
