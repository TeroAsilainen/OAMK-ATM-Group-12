#include "balance.h"
#include "ui_balance.h"
#include "mainmenu.h"

#include <QMessageBox>


Balance::Balance(Mainmenu *parent)
    : QDialog(parent)
    , ui(new Ui::Balance)
{
    setParentPointer(parent);

    ui->setupUi(this);

    this->setWindowState(Qt::WindowFullScreen);

    ui->TextFname->hide();
    ui->labelFname->hide();

    ui->TextLname->hide();
    ui->labelLname->hide();

    ui->TextPhoneNumber->hide();
    ui->labelPhoneNumber->hide();

    ui->TextAddress->hide();
    ui->labelAddress->hide();

    ui->btnContinue->hide();

    ui->label_9->hide();

    setBalanceTimerCount(0);
    balanceTimer = new QTimer(this);
    connect(balanceTimer, SIGNAL(timeout()), this, SLOT(balanceTimerTick()));
    balanceTimer->start(2000);

}

Balance::~Balance()
{
    delete ui;
}

void Balance::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
}

void Balance::setBalance(const QString &newBalance)
{
    balance = newBalance;
    ui->TextBalance->setText(balance);
}

void Balance::setLimit(const QString &newLimit)
{
    limit = newLimit;
    ui->TextCreditLimit->setText(limit);
}

void Balance::setIduser(const QString &newIduser)
{
    iduser = newIduser;
}

void Balance::setFname(const QString &newFname)
{
    fname = newFname;
    ui->TextFname->setText(fname);
}

void Balance::setLname(const QString &newLname)
{
    lname = newLname;
    ui->TextLname->setText(lname);
}

void Balance::setPhonenumber(const QString &newPhonenumber)
{
    phonenumber = newPhonenumber;
    ui->TextPhoneNumber->setText(phonenumber);
}

void Balance::setAddress(const QString &newAddress)
{
    address = newAddress;
    ui->TextAddress->setText(address);
}

void Balance::setIdcard(const QString &newIdcard)
{
    idcard = newIdcard;
}

void Balance::setIdaccount(const QString &newIdaccount)
{
    idaccount = newIdaccount;
    ui->TextAccountNumber->setText(idaccount);
}



void Balance::userDataCheck()
{
    QString site_url=Environment::base_url()+"/user/"+iduser;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    userDataManager = new QNetworkAccessManager(this);

    connect(userDataManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(userDataSlot(QNetworkReply*)));

    reply = userDataManager->get(request);
}

void Balance::userDataSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    if (response_data=="Forbidden") {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Istunto on vanhentunut"));
        messageBox->setText(tr("Istuntosi on vanhentunut. Kirjaudu sisään uudelleen."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        messageBox->exec();
        this->close();
        parentPointer->close();
    }
    else if (response_data=="-11"){
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Tietokanta ei vastaa"));
        messageBox->setText(tr("Tietokanta ei vastaa. Yritä hetken kuluttua uudelleen."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        balanceTimer->stop();
        messageBox->exec();
        balanceTimer->start();
    }
    else if ((response_data.length()<1)||response_data.contains("Unavailable")){
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Palvelin ei vastaa"));
        messageBox->setText(tr("Palvelin ei vastaa. Yritä hetken kuluttua uudelleen."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        balanceTimer->stop();
        messageBox->exec();
        balanceTimer->start();
    }
    else {
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    //QJsonObject json_obj = json_doc.object();

    this->setFname(json_doc["fname"].toString());
    this->setLname(json_doc["lname"].toString());
    this->setPhonenumber(json_doc["phonenumber"].toString());
    this->setAddress(json_doc["address"].toString());

    ui->TextFname->show();
    ui->labelFname->show();

    ui->TextLname->show();
    ui->labelLname->show();

    ui->TextPhoneNumber->show();
    ui->labelPhoneNumber->show();

    ui->TextAddress->show();
    ui->labelAddress->show();

    ui->label_9->show();
    ui->btnUserData->hide();

    reply->deleteLater();
    userDataManager->deleteLater();
    }
}



void Balance::on_btnUserData_clicked()
{
    setBalanceTimerCount(0);

    userDataCheck();
}


void Balance::on_btnBack_clicked()
{
    balanceTimer->stop();
    parentPointer->mainMenuTimer->start();
    this->close();
}

void Balance::balanceTimerTick()
{
    this->setBalanceTimerCount(balanceTimerCount+1);
    qDebug()<<balanceTimerCount;
    if(balanceTimerCount==5){
        ui->TextTimeOut->setText(tr("Yhteyden aikakatkaisu pian"));
        ui->btnContinue->show();
    }
    else if(balanceTimerCount<5 && ui->TextTimeOut->text()==tr("Yhteyden aikakatkaisu pian")){
        ui->TextTimeOut->setText("");
    }
    else if(balanceTimerCount==7){
        this->close();
        balanceTimer->stop();
        parentPointer->mainMenuTimer->start();
    }
}

void Balance::setBalanceTimerCount(int newBalanceTimerCount)
{
    balanceTimerCount = newBalanceTimerCount;
}


void Balance::on_btnContinue_clicked()
{
    setBalanceTimerCount(0);
}

void Balance::setParentPointer(Mainmenu *newParentPointer)
{
    parentPointer = newParentPointer;
}

