#include "environment.h"
#include "payment.h"
#include "ui_payment.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QTimer>

Payment::Payment(Mainmenu *parent)
    : QDialog(parent)
    , ui(new Ui::Payment)
    , enteringSum(false)
{
    ui->setupUi(this);

    ui->btnCon->hide();

    setParentPointer(parent);

    this->setWindowState(Qt::WindowFullScreen);

    setPaymentTimerCount(0);
    PaymentTimer = new QTimer(this);
    connect(PaymentTimer, SIGNAL(timeout()), this, SLOT(PaymentTimerTick()));
    PaymentTimer->start(2000);
    ui->btnMaksa->setEnabled(false);
    ui->txtTili->setFocus();
    ui->txtTili->setStyleSheet("border: 2px solid blue;");
}

Payment::~Payment()
{
    delete ui;
}

void Payment::PaymentTimerTick()
{
    // qDebug()<<"tick";
    this->setPaymentTimerCount(PaymentTimerCount+1);
    qDebug()<<PaymentTimerCount;
    if(PaymentTimerCount==5){
        ui->labelAika->setText(tr("Yhteyden aikakatkaisu pian"));
        ui->btnCon->show();
    } else if(PaymentTimerCount<5 && ui->labelAika->text()==tr("Yhteyden aikakatkaisu pian")){
        ui->labelAika->setText("");
    } else if(PaymentTimerCount==7){
        this->close();
        PaymentTimer->stop();
        parentPointer->mainMenuTimer->start();
    }
}

void Payment::setPaymentTimerCount(int newPaymentTimerCount)
{
   PaymentTimerCount = newPaymentTimerCount;
}

void Payment::on_btnSwitch_clicked()
{
    setPaymentTimerCount(0);
    enteringSum = !enteringSum;

    if (enteringSum) {
        ui->txtSumma->setStyleSheet("border: 2px solid blue;");
        ui->txtTili->setStyleSheet("");
    } else {
        ui->txtTili->setStyleSheet("border: 2px solid blue;");
        ui->txtSumma->setStyleSheet("");
    }
}


void Payment::digitClicked(int digit)
{
    setPaymentTimerCount(0);

    if (enteringSum) {

        enteredSum += QString::number(digit);

        bool ok;
        double value = enteredSum.toDouble(&ok);

        if (ok) {
            double formattedValue = value / 100.0;
            ui->txtSumma->setText(QString::number(formattedValue, 'f', 2).replace(',', '.'));

            //estää 0 summan maksamisen
            if (formattedValue == 0.00) {
                ui->btnMaksa->setEnabled(false);
            } else {
                ui->btnMaksa->setEnabled(true);
            }
        }
    } else {

        enteredAccount += QString::number(digit);
        ui->txtTili->setText(enteredAccount);
    }
}



void Payment::on_btn1_clicked()
{
    digitClicked(1);
}


void Payment::on_btn2_clicked()
{
    digitClicked(2);
}


void Payment::on_btn3_clicked()
{
    digitClicked(3);
}


void Payment::on_btn4_clicked()
{
    digitClicked(4);
}


void Payment::on_btn5_clicked()
{
    digitClicked(5);
}


void Payment::on_btn6_clicked()
{
    digitClicked(6);
}


void Payment::on_btn7_clicked()
{
    digitClicked(7);
}


void Payment::on_btn8_clicked()
{
    digitClicked(8);
}


void Payment::on_btn9_clicked()
{
    digitClicked(9);
}


void Payment::on_btn0_clicked()
{
    digitClicked(0);
}


void Payment::on_btnErase_clicked()
{
    setPaymentTimerCount(0);

    if (enteringSum) {
        if (!enteredSum.isEmpty()) {
            enteredSum.chop(1);
            bool ok;
            double value = enteredSum.toDouble(&ok);

            if (ok) {
                double formattedValue = value / 100.0;
                ui->txtSumma->setText(QString::number(formattedValue, 'f', 2).replace(',', '.'));
                ui->btnMaksa->setEnabled(formattedValue > 0.00);
            }
                else {
                    ui->txtSumma->setText("0.00");
                    ui->btnMaksa->setEnabled(false);
            }
        }
    } else {
        if (!enteredAccount.isEmpty()) {
            enteredAccount.chop(1);
            ui->txtTili->setText(enteredAccount);
        }
    }
}


void Payment::on_btnClear_clicked()
{
    setPaymentTimerCount(0);

    if (enteringSum) {
        enteredSum.clear();
        ui->txtSumma->setText("0.00");
        ui->btnMaksa->setEnabled(false);
    } else {
        enteredAccount.clear();
        ui->txtTili->setText("");
    }

}

void Payment::on_btnPaluu_clicked()
{
    setPaymentTimerCount(0);
    PaymentTimer->stop();
    parentPointer->mainMenuTimer->start();
    this->close();
    //parentWidget()->show();
}

void Payment::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
}

void Payment::setIdaccount(const QString &newIdaccount)
{
    idaccount = newIdaccount;
}

void Payment::setParentPointer(Mainmenu *newParentPointer)
{
    parentPointer = newParentPointer;
}

void Payment::on_btnMaksa_clicked()
{
    if ("FI" + enteredAccount == idaccount) {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Virhe!"));
        messageBox->setText(tr("Virhe. Et voi suorittaa maksua omalle tilillesi."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        PaymentTimer->stop();
        messageBox->exec();
        PaymentTimer->start();
        return;
    }

    if (enteredSum.isEmpty()) {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Virhe!"));
        messageBox->setText(tr("Virhe. Syötä maksettava summa."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        PaymentTimer->stop();
        messageBox->exec();
        PaymentTimer->start();
        return;
    }

    if (enteredAccount.isEmpty()) {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Virhe!"));
        messageBox->setText(tr("Virhe. Syötä tilinumero."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        PaymentTimer->stop();
        messageBox->exec();
        PaymentTimer->start();
        return;
    }

    //Luottorajan tarkistus

    setPaymentTimerCount(0);
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

void Payment::creditLimitSlot(QNetworkReply *reply)
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
    payment(creditLimit);

    reply->deleteLater();
    creditLimitManager->deleteLater();
    }
}


void Payment::payment(bool creditLimit)
{
    if(creditLimit) {
        QJsonObject jsonObj;
        jsonObj.insert("first_id",idaccount);
        jsonObj.insert("second_id", "FI" + ui->txtTili->text());
        jsonObj.insert("amount", ui->txtSumma->text());

        QString site_url=Environment::base_url()+"/credit_procedures/";
        QNetworkRequest request(site_url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        paymentManager = new QNetworkAccessManager(this);
        connect(paymentManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(paymentSlot(QNetworkReply*)));
        reply = paymentManager->post(request, QJsonDocument(jsonObj).toJson());
    }
    else {
        QJsonObject jsonObj;
        jsonObj.insert("first_id", idaccount);
        jsonObj.insert("second_id", "FI" + ui->txtTili->text());
        jsonObj.insert("amount", ui->txtSumma->text());

        QString site_url=Environment::base_url()+"/debit_procedures/";
        //qDebug()<<"idaccount="+idaccount;
        QNetworkRequest request(site_url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        paymentManager = new QNetworkAccessManager(this);
        connect(paymentManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(paymentSlot(QNetworkReply*)));
        reply = paymentManager->post(request, QJsonDocument(jsonObj).toJson());
    }
}


void Payment::paymentSlot(QNetworkReply *reply)
{
    bool ok;
    int value = enteredSum.toInt(&ok);
    QString formattedSum = "0.00";

    if (ok) {
      formattedSum = QString::number(value / 100.0, 'f', 2).replace(',', '.');
    }

    response_data=reply->readAll();
    qDebug()<<"response data: "<< response_data;

    if (response_data=="0"){
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Maksu epäonnistui"));
        messageBox->setText(tr("Maksu epäonnistui. Tarkista summa ja maksun saajan tilinumero."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        PaymentTimer->stop();
        messageBox->exec();
        PaymentTimer->start();
    }
    else if (response_data=="1") {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Maksu onnistui"));
        messageBox->setText(tr("Maksu onnistui. Maksettu ") + formattedSum + tr(" euroa.\nTilille: FI") + enteredAccount);
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        PaymentTimer->stop();
        messageBox->exec();

        parentPointer->mainMenuTimer->start();
        this->close();
    }
    else if (response_data=="Forbidden") {
        responseForbidden();
    }
    else if (response_data=="-11"){
        responseDbError();
    }
    else if((response_data.length()<1)||response_data.contains("Unavailable")){
        responseServerError();
    }
    else {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Maksu epäonnistui"));
        messageBox->setText(tr("Jotain meni vikaan. Yritä myöhemmin uudelleen."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        messageBox->exec();
        this->close();
        PaymentTimer->stop();
        parentPointer->mainMenuTimer->start();
    }

    reply->deleteLater();
    paymentManager->deleteLater();
}


void Payment::responseForbidden()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Istunto on vanhentunut"));
    messageBox->setText(tr("Istuntosi on vanhentunut. Kirjaudu sisään uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    PaymentTimer->stop();
    messageBox->exec();
    this->close();
    parentPointer->close();
}

void Payment::responseDbError()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Tietokanta ei vastaa"));
    messageBox->setText(tr("Tietokanta ei vastaa. Yritä hetken kuluttua uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    PaymentTimer->stop();
    messageBox->exec();
    PaymentTimer->start();
}

void Payment::responseServerError()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Palvelin ei vastaa"));
    messageBox->setText(tr("Palvelin ei vastaa. Yritä hetken kuluttua uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    PaymentTimer->stop();
    messageBox->exec();
    PaymentTimer->start();
}





void Payment::on_btnCon_clicked()
{
    setPaymentTimerCount(0);
}

