#include "withdrawal.h"
#include "ui_withdrawal.h"
#include "amount.h"
#include "environment.h"
#include <QMessageBox>
#include <QTimer>

withdrawal::withdrawal(Mainmenu *parent)
    : QDialog(parent)
    , ui(new Ui::withdrawal)
{
    ui->setupUi(this);

    ui->btnCont->hide();
    setParentPointer(parent);

    this->setWindowState(Qt::WindowFullScreen);

    setWithdrawalTimerCount(0);
    WithdrawalTimer = new QTimer(this);
    connect(WithdrawalTimer, SIGNAL(timeout()), this, SLOT(WithdrawalTimerTick()));
    WithdrawalTimer->start(2000);

}

withdrawal::~withdrawal()
{
    delete ui;
}

void withdrawal::WithdrawalTimerTick()
{
    // qDebug()<<"tick";
    this->setWithdrawalTimerCount(WithdrawalTimerCount+1);
    qDebug()<<WithdrawalTimerCount;
    if(WithdrawalTimerCount==5){
        ui->labelTime->setText(tr("Yhteyden aikakatkaisu pian"));
        ui->btnCont->show();
    } else if(WithdrawalTimerCount<5 && ui->labelTime->text()==tr("Yhteyden aikakatkaisu pian")){
        ui->labelTime->setText("");
    } else if(WithdrawalTimerCount==7){
        this->close();
        WithdrawalTimer->stop();
        parentPointer->mainMenuTimer->start();
    }
}

void withdrawal::setWithdrawalTimerCount(int newWithdrawalTimerCount)
{
    WithdrawalTimerCount = newWithdrawalTimerCount;
}

void withdrawal::on_btnpaluu_clicked()
{
    setWithdrawalTimerCount(0);
    this->close();
    WithdrawalTimer->stop();
    parentPointer->mainMenuTimer->start();
}


void withdrawal::on_btnmuu_clicked()
{
    setWithdrawalTimerCount(0);
    Amount *objAmount = new Amount(this);
    objAmount->setIdaccount(idaccount);
    objAmount->setMyToken(myToken);
    objAmount->setCreditLimit(creditLimit);
    objAmount->open();
    WithdrawalTimer->stop();
}


void withdrawal::on_btn200_clicked()
{
    setWithdrawalTimerCount(0);
    *amountPointer = 200;
    Withdrawal(amount);
    qDebug() << "Nosto " << amount;
}


void withdrawal::on_btn100_clicked()
{
    setWithdrawalTimerCount(0);
    *amountPointer = 100;
    Withdrawal(amount);
    qDebug() << "Nosto " << amount;
}


void withdrawal::on_btn80_clicked()
{
    setWithdrawalTimerCount(0);
    *amountPointer = 80;
    Withdrawal(amount);
    qDebug() << "Nosto " << amount;
}

void withdrawal::on_btn50_clicked()
{
    setWithdrawalTimerCount(0);
    *amountPointer = 50;
    Withdrawal(amount);
    qDebug() << "Nosto " << amount;
}


void withdrawal::on_btn20_clicked()
{
    setWithdrawalTimerCount(0);
    *amountPointer = 20;
    Withdrawal(amount);
    qDebug() << "Nosto " << amount;
}


void withdrawal::on_btn10_clicked()
{
    setWithdrawalTimerCount(0);
    *amountPointer = 10;
    Withdrawal(amount);
    qDebug() << "Nosto " << amount;
}

void withdrawal::setIdaccount(const QString &newIdaccount)
{
    idaccount = newIdaccount;
}

void withdrawal::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
}

void withdrawal::checkCreditLimit()
{
    //Luottorajan tarkistus

    setWithdrawalTimerCount(0);
    QString site_url=Environment::base_url()+"/account/" +idaccount;
    qDebug() << "Tilinumero: " << idaccount;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    creditLimitManager = new QNetworkAccessManager(this);
    connect(creditLimitManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(creditLimitSlot(QNetworkReply*)));
    reply = creditLimitManager->get(request);
}

void withdrawal::creditLimitSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"response_data: " << response_data;
    if(response_data == "Forbidden") {
        responseForbidden();
    }
    else if (response_data == "-11") {
        responseDbError();
    }
    else if ((response_data.length()<1)||response_data.contains("Unavailable")) {
        responseServerError();
    }
    else {
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        qDebug()<<"Luottoraja: "<< json_doc["credit_limit"].toString();
        if(json_doc["credit_limit"].toString() == "0.00"){
            creditLimit=false;
        } else {
            creditLimit=true;
        }
        qDebug()<<"On luotto: "<<creditLimit;

        reply->deleteLater();
        creditLimitManager->deleteLater();
    }
}


void withdrawal::Withdrawal(int amount)
{
    if(creditLimit) {
        QJsonObject jsonObj;
        jsonObj.insert("first_id", idaccount);
        jsonObj.insert("amount", amount);

        QString site_url=Environment::base_url()+"/credit_procedures/";
        QNetworkRequest request(site_url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        withdrawalManager = new QNetworkAccessManager(this);
        connect(withdrawalManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawalSlot(QNetworkReply*)));
        reply = withdrawalManager->put(request, QJsonDocument(jsonObj).toJson());
    }
    else {
        QJsonObject jsonObj;
        jsonObj.insert("first_id", idaccount);
        jsonObj.insert("amount", amount);

        QString site_url=Environment::base_url()+"/debit_procedures/";
        QNetworkRequest request(site_url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        withdrawalManager = new QNetworkAccessManager(this);
        connect(withdrawalManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(withdrawalSlot(QNetworkReply*)));
        reply = withdrawalManager->put(request, QJsonDocument(jsonObj).toJson());
    }
}

void withdrawal::withdrawalSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"response data: "<< response_data;

    if (response_data=="0"){
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Nosto epäonnistui"));
        messageBox->setText(tr("Nosto epäonnistui. Tilillä ei ole tarpeeksi katetta"));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        WithdrawalTimer->stop();
        messageBox->exec();
        WithdrawalTimer->start();
    }
    else if (response_data=="1") {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Nosto onnistui"));
        messageBox->setText(tr("Nosto onnistui. Nostit ") + QString::number(amount) + tr(" euroa."));

        qDebug() << tr("Nosto onnistui. Nostit ") + QString::number(amount) + tr(" euroa.");

        QTimer::singleShot(10000, messageBox, SLOT(close()));
        WithdrawalTimer->stop();
        messageBox->exec();
        this->close();
        parentPointer->mainMenuTimer->start();
    }
    else if(response_data == "Forbidden") {
        responseForbidden();
    }
    else if (response_data == "-11") {
        responseDbError();
    }
    else if ((response_data.length()<1)||response_data.contains("Unavailable")) {
        responseServerError();
    }
    else {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Nosto epäonnistui"));
        messageBox->setText(tr("Jotain meni vikaan. Yritä myöhemmin uudelleen."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        WithdrawalTimer->stop();
        messageBox->exec();
        this->close();
        parentPointer->mainMenuTimer->start();
    }

    reply->deleteLater();
    withdrawalManager->deleteLater();
}

void withdrawal::responseForbidden()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Istunto on vanhentunut"));
    messageBox->setText(tr("Istuntosi on vanhentunut. Kirjaudu sisään uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    WithdrawalTimer->stop();
    messageBox->exec();
    this->close();
    parentPointer->close();
}

void withdrawal::responseDbError()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Tietokanta ei vastaa"));
    messageBox->setText(tr("Tietokanta ei vastaa. Yritä hetken kuluttua uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    WithdrawalTimer->stop();
    messageBox->exec();
    WithdrawalTimer->start();
}

void withdrawal::responseServerError()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Palvelin ei vastaa"));
    messageBox->setText(tr("Palvelin ei vastaa. Yritä hetken kuluttua uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    WithdrawalTimer->stop();
    messageBox->exec();
    WithdrawalTimer->start();
}

void withdrawal::setParentPointer(Mainmenu *newParentPointer)
{
    parentPointer = newParentPointer;
}



void withdrawal::on_btnCont_clicked()
{
    setWithdrawalTimerCount(0);
}

