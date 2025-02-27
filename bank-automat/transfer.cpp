#include "transfer.h"
#include "ui_transfer.h"
#include "mainmenu.h"
#include "environment.h"

#include <QMessageBox>

Transfer::Transfer(Mainmenu *parent)
    : QDialog(parent)
    , ui(new Ui::Transfer)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowFullScreen);

    ui->btnContinue->hide();

    setTransferTimerCount(0);
    transferTimer = new QTimer(this);
    connect(transferTimer, SIGNAL(timeout()), this, SLOT(transferTimerTick()));
    transferTimer->start(2000);

    setParentPointer(parent);
}

Transfer::~Transfer()
{
    delete ui;
    transferTimer->stop();
}

void Transfer::on_btnCancel_clicked()
{
    transferTimer->stop();
    parentPointer->mainMenuTimer->start();
    this->close();
}


void Transfer::setTransferTimerCount(int newTransferTimerCount)
{
    transferTimerCount = newTransferTimerCount;
}

void Transfer::setUserAccountList(const QStringList &newUserAccountList)
{
    userAccountList = newUserAccountList;
    ui->comboAccount1->addItem("");
    ui->comboAccount2->addItem("");
    foreach (const QString value, userAccountList) {
        ui->comboAccount1->addItem(value);
        ui->comboAccount2->addItem(value);
    }
}

void Transfer::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
}


void Transfer::digitClicked(int digit)
{
    setTransferTimerCount(0);
    setTransferAmountInput(transferAmountInput + QString::number(digit));
    if((this->ui->comboAccount2->currentText().isEmpty()==false)&&(this->ui->comboAccount1->currentText().isEmpty()==false)&&(this->ui->comboAccount2->currentText()!=this->ui->comboAccount1->currentText())&&(ui->textAmount->text().isEmpty()==false)&&(ui->textAmount->text().toDouble()!=0)){
        ui->btnTransfer->setEnabled(true);
    } else {
        ui->btnTransfer->setDisabled(true);
    }
}




void Transfer::on_btn1_clicked()
{
    digitClicked(1);
}


void Transfer::on_btn2_clicked()
{
    digitClicked(2);
}


void Transfer::on_btn3_clicked()
{
    digitClicked(3);
}


void Transfer::on_btn4_clicked()
{
    digitClicked(4);
}


void Transfer::on_btn5_clicked()
{
    digitClicked(5);
}


void Transfer::on_btn6_clicked()
{
    digitClicked(6);
}


void Transfer::on_btn7_clicked()
{
    digitClicked(7);
}


void Transfer::on_btn8_clicked()
{
    digitClicked(8);
}


void Transfer::on_btn9_clicked()
{
    digitClicked(9);
}


void Transfer::on_btn0_clicked()
{
    digitClicked(0);
}


void Transfer::on_btnErase_clicked()
{
    setTransferTimerCount(0);
    QString text = transferAmountInput;
    text.chop(1);
    if (text.isEmpty()) {
        text = "";
    }
    setTransferAmountInput(text);
    if((this->ui->comboAccount2->currentText().isEmpty()==false)&&(this->ui->comboAccount1->currentText().isEmpty()==false)&&(this->ui->comboAccount2->currentText()!=this->ui->comboAccount1->currentText())&&(ui->textAmount->text().isEmpty()==false)&&(ui->textAmount->text().toDouble()!=0)){
        ui->btnTransfer->setEnabled(true);
    } else {
        ui->btnTransfer->setDisabled(true);
    }
}


void Transfer::on_btnEmpty_clicked()
{
    setTransferTimerCount(0);
    setTransferAmountInput("");
    ui->btnTransfer->setDisabled(true);
}



void Transfer::transferTimerTick()
{
    this->setTransferTimerCount(transferTimerCount+1);
    qDebug()<<transferTimerCount;
    if(transferTimerCount==5){
        ui->textWarning->setText(tr("Yhteyden aikakatkaisu pian"));
        ui->btnContinue->show();
    }
    else if(transferTimerCount<5 && ui->textWarning->text()==tr("Yhteyden aikakatkaisu pian")){
        ui->textWarning->setText("");
    }
    else if(transferTimerCount==7){
        this->close();
        transferTimer->stop();
        parentPointer->mainMenuTimer->start();
    }
}


void Transfer::on_btnContinue_clicked()
{
    setTransferTimerCount(0);
}






void Transfer::on_comboAccount1_highlighted(int index)
{
    setTransferTimerCount(0);
}

void Transfer::on_comboAccount1_activated(int index)
{
    setTransferTimerCount(0);
}

void Transfer::on_comboAccount2_highlighted(int index)
{
    setTransferTimerCount(0);
}

void Transfer::on_comboAccount2_activated(int index)
{
    setTransferTimerCount(0);
}

void Transfer::setFormattedTransferAmount(double newFormattedTransferAmount)
{
    formattedTransferAmount = newFormattedTransferAmount;
    ui->textAmount->setText(QString::number(formattedTransferAmount, 'f', 2));
}

void Transfer::setTransferAmountInput(const QString &newTransferAmountInput)
{
    transferAmountInput = newTransferAmountInput;
    setFormattedTransferAmount((transferAmountInput.toDouble())/100);

}

void Transfer::setParentPointer(Mainmenu *newParentPointer)
{
    parentPointer = newParentPointer;
}

void Transfer::on_comboAccount1_currentTextChanged(const QString &arg1)
{
    if((arg1.isEmpty()==false)&&(this->ui->comboAccount2->currentText().isEmpty()==false)&&(arg1!=this->ui->comboAccount2->currentText())&&(ui->textAmount->text().isEmpty()==false)&&(ui->textAmount->text().toDouble()!=0)){
        ui->btnTransfer->setEnabled(true);
    } else {
        ui->btnTransfer->setDisabled(true);
    }
}


void Transfer::on_comboAccount2_currentTextChanged(const QString &arg1)
{
    if((arg1.isEmpty()==false)&&(this->ui->comboAccount1->currentText().isEmpty()==false)&&(arg1!=this->ui->comboAccount1->currentText())&&(ui->textAmount->text().isEmpty()==false)&&(ui->textAmount->text().toDouble()!=0)){
        ui->btnTransfer->setEnabled(true);
    } else {
        ui->btnTransfer->setDisabled(true);
    }
}

void Transfer::on_btnTransfer_clicked()
{
    setTransferTimerCount(0);
    QString site_url=Environment::base_url()+"/account/"+ui->comboAccount1->currentText();
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    isCreditManager = new QNetworkAccessManager(this);

    connect(isCreditManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(isCreditSlot(QNetworkReply*)));

    reply = isCreditManager->get(request);
}

void Transfer::isCreditSlot(QNetworkReply *reply)
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
        qDebug()<<"Luottoraja: "<< json_doc["credit_limit"].toString();
    if(json_doc["credit_limit"].toString()=="0.00"){
        isCredit=false;
    } else {
        isCredit=true;
    }
    qDebug()<<"On luotto: "<<isCredit;
    transfer(isCredit);


    reply->deleteLater();
    isCreditManager->deleteLater();
    }
}



void Transfer::transfer(bool isCredit)
{
    if (isCredit){
        QJsonObject jsonObj;
        jsonObj.insert("first_id", ui->comboAccount1->currentText());
        jsonObj.insert("second_id",ui->comboAccount2->currentText());
        jsonObj.insert("amount", ui->textAmount->text());

        QString site_url=Environment::base_url()+"/credit_procedures/";
        //qDebug()<<"idaccount="+idaccount;
        QNetworkRequest request(site_url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        transferManager = new QNetworkAccessManager(this);
        connect(transferManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transferSlot(QNetworkReply*)));
        reply = transferManager->post(request, QJsonDocument(jsonObj).toJson());
    }
    else {
        QJsonObject jsonObj;
        jsonObj.insert("first_id", ui->comboAccount1->currentText());
        jsonObj.insert("second_id",ui->comboAccount2->currentText());
        jsonObj.insert("amount", ui->textAmount->text());

        QString site_url=Environment::base_url()+"/debit_procedures/";
        //qDebug()<<"idaccount="+idaccount;
        QNetworkRequest request(site_url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //WEBTOKEN ALKU
        request.setRawHeader(QByteArray("Authorization"),(myToken));
        //WEBTOKEN LOPPU

        transferManager = new QNetworkAccessManager(this);
        connect(transferManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(transferSlot(QNetworkReply*)));
        reply = transferManager->post(request, QJsonDocument(jsonObj).toJson());
    }
}



void Transfer::transferSlot(QNetworkReply *reply)
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
    else if (response_data=="0"){
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Siirto epäonnistui"));
        messageBox->setText(tr("Siirto epäonnistui. Tilillä ei ole tarpeeksi katetta."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        transferTimer->stop();
        messageBox->exec();
        transferTimer->start();
        }
    else if (response_data=="1") {
        QMessageBox *messageBox = new QMessageBox;
            messageBox->setWindowTitle(tr("Siirto onnistui"));
        messageBox->setText(tr("Siirto onnistui."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        transferTimer->stop();
        messageBox->exec();
        transferTimer->start();
        this->close();
        }
    else {
        QMessageBox *messageBox = new QMessageBox;
            messageBox->setWindowTitle(tr("Siirto epäonnistui"));
        messageBox->setText(tr("Jotain meni vikaan. Yritä myöhemmin uudelleen."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        transferTimer->stop();
        messageBox->exec();
        transferTimer->start();
        this->close();
    }

    reply->deleteLater();
    transferManager->deleteLater();
}

void Transfer::responseForbidden()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Istunto on vanhentunut"));
    messageBox->setText(tr("Istuntosi on vanhentunut. Kirjaudu sisään uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    transferTimer->stop();
    messageBox->exec();
    this->close();
    parentPointer->close();
}

void Transfer::responseDbError()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Tietokanta ei vastaa"));
    messageBox->setText(tr("Tietokanta ei vastaa. Yritä hetken kuluttua uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    transferTimer->stop();
    messageBox->exec();
    transferTimer->start();
}

void Transfer::responseServerError()
{
    QMessageBox *messageBox = new QMessageBox;
    messageBox->setWindowTitle(tr("Palvelin ei vastaa"));
    messageBox->setText(tr("Palvelin ei vastaa. Yritä hetken kuluttua uudelleen."));
    QTimer::singleShot(10000, messageBox, SLOT(close()));
    transferTimer->stop();
    messageBox->exec();
    transferTimer->start();
}
