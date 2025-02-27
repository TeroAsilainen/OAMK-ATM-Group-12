#include "amount.h"
#include "environment.h"
#include "ui_amount.h"
#include <QMessageBox>
#include <QTimer>

Amount::Amount(withdrawal *parent)
    : QDialog(parent)
    , ui(new Ui::Amount)
{
    ui->setupUi(this);
    ui->btnJatka->hide();
    setParentPointer(parent);

    this->setWindowState(Qt::WindowFullScreen);

    setAmountTimerCount(0);
    AmountTimer = new QTimer(this);
    connect(AmountTimer, SIGNAL(timeout()), this, SLOT(AmountTimerTick()));
    AmountTimer->start(2000);
}

Amount::~Amount()
{
    delete ui;
}

void Amount::setIdaccount(const QString &newIdaccount)
{
    idaccount = newIdaccount;
}

void Amount::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
}

void Amount::AmountTimerTick()
{
    this->setAmountTimerCount(AmountTimerCount+1);
    qDebug()<<AmountTimerCount;
    if(AmountTimerCount==5){
        ui->labelTimer->setText(tr("Yhteyden aikakatkaisu pian"));
        ui->btnJatka->show();
    } else if(AmountTimerCount<5 && ui->labelTimer->text()==tr("Yhteyden aikakatkaisu pian")){
        ui->labelTimer->setText("");
    } else if(AmountTimerCount==7){
        this->close();
        AmountTimer->stop();
        parentPointer->WithdrawalTimer->start();
    }
}

void Amount::setAmountTimerCount(int newAmountTimerCount)
{
    AmountTimerCount = newAmountTimerCount;
}


void Amount::on_btnBack_clicked()
{
    setAmountTimerCount(0);
    this->close();
    AmountTimer->stop();
    parentPointer->WithdrawalTimer->start();
}

void Amount::digitClicked(int digit)
 {
    setAmountTimerCount(0);
    enteredAmount += QString::number(digit);
    ui->textEnteredAmount->setText(enteredAmount);
 }


void Amount::on_btn1_clicked()
 {
     digitClicked(1);
 }


 void Amount::on_btn2_clicked()
 {
    digitClicked(2);
 }


 void Amount::on_btn3_clicked()
 {
     digitClicked(3);
 }


 void Amount::on_btn4_clicked()
 {
     digitClicked(4);
 }


 void Amount::on_btn5_clicked()
 {
     digitClicked(5);
 }


 void Amount::on_btn6_clicked()
 {
     digitClicked(6);
 }


 void Amount::on_btn7_clicked()
 {
     digitClicked(7);
 }


 void Amount::on_btn8_clicked()
 {
     digitClicked(8);
 }


 void Amount::on_btn9_clicked()
 {
     digitClicked(9);
 }


 void Amount::on_btn0_clicked()
 {
     digitClicked(0);
 }


 void Amount::on_btnErase_clicked()
 {
     setAmountTimerCount(0);
     if (!enteredAmount.isEmpty()) {
         enteredAmount.chop(1);
         ui->textEnteredAmount->setText(enteredAmount);
     }
 }


 void Amount::on_btnEmpty_clicked()
 {
     setAmountTimerCount(0);
     enteredAmount.clear();
     ui->textEnteredAmount->setText(enteredAmount);
 }


 void Amount::on_btnOk_clicked()
 {
     qDebug() << "Muu summa, luotto: " << creditLimit;
     setAmountTimerCount(0);
     if (enteredAmount.isEmpty()) {
         QMessageBox *messageBox = new QMessageBox;
         messageBox->setWindowTitle(tr("Virhe"));
         messageBox->setText(tr("Syötä nostettava summa!"));
         QTimer::singleShot(10000, messageBox, SLOT(close()));
         AmountTimer->stop();
         messageBox->exec();
         AmountTimer->start();

         return;
     }

     bool ok;
     int amount = enteredAmount.toInt(&ok);

     if (!ok || amount < 10) {
         QMessageBox *messageBox = new QMessageBox;
         messageBox->setWindowTitle(tr("Virhe"));
         messageBox->setText(tr("Nostettavan summan täytyy olla vähintään 10 €."));
         QTimer::singleShot(10000, messageBox, SLOT(close()));
         AmountTimer->stop();
         messageBox->exec();
         AmountTimer->start();

         return;
     }
     if (amount % 10 != 0) {
         QMessageBox *messageBox = new QMessageBox;
         messageBox->setWindowTitle(tr("Virhe"));
         messageBox->setText(tr("Nostettava summa ei ole maksettavissa 10 €, 20 € tai 50 € seteleillä."));
         QTimer::singleShot(10000, messageBox, SLOT(close()));
         AmountTimer->stop();
         messageBox->exec();
         AmountTimer->start();

         return;
     }

     //Nosto
     if(creditLimit) {
         QJsonObject jsonObj;
         jsonObj.insert("first_id", idaccount);
         jsonObj.insert("amount", ui->textEnteredAmount->text());

         QString site_url=Environment::base_url()+"/credit_procedures/";
         QNetworkRequest request(site_url);
         request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

         //WEBTOKEN ALKU
         request.setRawHeader(QByteArray("Authorization"),(myToken));
         //WEBTOKEN LOPPU

         enteredAmountManager = new QNetworkAccessManager(this);
         connect(enteredAmountManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(enteredAmountSlot(QNetworkReply*)));
         reply = enteredAmountManager->put(request, QJsonDocument(jsonObj).toJson());
     }
     else {
         QJsonObject jsonObj;
         jsonObj.insert("first_id", idaccount);
         jsonObj.insert("amount", ui->textEnteredAmount->text());

         QString site_url=Environment::base_url()+"/debit_procedures/";
         QNetworkRequest request(site_url);
         request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

         //WEBTOKEN ALKU
         request.setRawHeader(QByteArray("Authorization"),(myToken));
         //WEBTOKEN LOPPU

         enteredAmountManager = new QNetworkAccessManager(this);
         connect(enteredAmountManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(enteredAmountSlot(QNetworkReply*)));
         reply = enteredAmountManager->put(request, QJsonDocument(jsonObj).toJson());
     }
 }

 void Amount::enteredAmountSlot(QNetworkReply *reply)
 {
     response_data=reply->readAll();
     qDebug()<<"response data: "<< response_data;

     if (response_data=="0"){
         QMessageBox *messageBox = new QMessageBox;
         messageBox->setWindowTitle(tr("Nosto epäonnistui"));
         messageBox->setText(tr("Nosto epäonnistui. Tilillä ei ole tarpeeksi katetta"));
         QTimer::singleShot(10000, messageBox, SLOT(close()));
         AmountTimer->stop();
         messageBox->exec();
         AmountTimer->start();
     }
     else if (response_data=="1") {
         QMessageBox *messageBox = new QMessageBox;
         messageBox->setWindowTitle(tr("Nosto onnistui"));
         messageBox->setText(tr("Nosto onnistui. Nostit ") + enteredAmount + tr(" euroa."));
         qDebug() << "Nosto onnistui. Nostit " + enteredAmount + " euroa.";
         QTimer::singleShot(10000, messageBox, SLOT(close()));
         AmountTimer->stop();
         messageBox->exec();
         this->close();
         parentPointer->close();
         parentPointer->parentPointer->mainMenuTimer->start();
     }
    else if (response_data=="Forbidden") {
         QMessageBox *messageBox = new QMessageBox;
         messageBox->setWindowTitle(tr("Istunto on vanhentunut"));
         messageBox->setText(tr("Istuntosi on vanhentunut. Kirjaudu sisään uudelleen."));
         QTimer::singleShot(10000, messageBox, SLOT(close()));
         AmountTimer->stop();
         messageBox->exec();
         this->close();
         parentPointer->close();
         parentPointer->parentPointer->close();
     }
     else if (response_data=="-11"){
         QMessageBox *messageBox = new QMessageBox;
         messageBox->setWindowTitle(tr("Tietokanta ei vastaa"));
         messageBox->setText(tr("Tietokanta ei vastaa. Yritä hetken kuluttua uudelleen."));
         QTimer::singleShot(10000, messageBox, SLOT(close()));
         AmountTimer->stop();
         messageBox->exec();
         AmountTimer->start();
     }
     else if ((response_data.length()<1)||response_data.contains("Unavailable")){
         QMessageBox *messageBox = new QMessageBox;
         messageBox->setWindowTitle(tr("Palvelin ei vastaa"));
         messageBox->setText(tr("Palvelin ei vastaa. Yritä hetken kuluttua uudelleen."));
         QTimer::singleShot(10000, messageBox, SLOT(close()));
         AmountTimer->stop();
         messageBox->exec();
         AmountTimer->start();
     }
     else {
         QMessageBox *messageBox = new QMessageBox;
         messageBox->setWindowTitle(tr("Nosto epäonnistui"));
         messageBox->setText(tr("Jotain meni vikaan. Yritä myöhemmin uudelleen."));
         QTimer::singleShot(10000, messageBox, SLOT(close()));
         AmountTimer->stop();
         messageBox->exec();
         AmountTimer->start();
     }

     reply->deleteLater();
     enteredAmountManager->deleteLater();
 }

 void Amount::setParentPointer(withdrawal *newParentPointer)
 {
     parentPointer = newParentPointer;
 }

 void Amount::setCreditLimit(bool newCreditLimit)
 {
     creditLimit = newCreditLimit;
 }

 void Amount::on_btnJatka_clicked()
 {
     setAmountTimerCount(0);
 }

