#include "environment.h"
#include "login.h"
#include "mainmenu.h"
#include "selectaccount.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QTimer>

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowFullScreen);

    this->lineEditPointer=this->ui->textKortti;

    setLoginTimerCount(0);
    loginTimer = new QTimer(this);
    connect(loginTimer, SIGNAL(timeout()), this, SLOT(loginTimerTick()));
    loginTimer->start(2000);
}

login::~login()
{
    delete ui;
}

void login::loginTimerTick()
{
    // qDebug()<<"tick";
    this->setLoginTimerCount(loginTimerCount+1);
    qDebug()<<loginTimerCount;
    if(loginTimerCount==5){
        ui->labelWarning->setText(tr("Yhteyden aikakatkaisu pian"));
    } else if(loginTimerCount<5 && ui->labelWarning->text()==tr("Yhteyden aikakatkaisu pian")){
        ui->labelWarning->setText("");
    } else if(loginTimerCount==7){
        this->close();
        loginTimer->stop();
    }
}

void login::setLoginTimerCount(int newLoginTimerCount)
{
    loginTimerCount = newLoginTimerCount;
}

void login::on_btnKirjaudu_clicked()
{
    setLoginTimerCount(0);
    wrongAttemptsCheck(ui->textKortti->text());
}


void login::wrongAttemptsCheck(QString idcard)
{
    QString site_url=Environment::base_url()+"/login/"+idcard;
    QNetworkRequest request(site_url);
    // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    wrongAttemptsManager = new QNetworkAccessManager(this);
    connect(wrongAttemptsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(wrongAttemptsSlot(QNetworkReply*)));
    reply = wrongAttemptsManager->get(request);
}

void login::wrongAttemptsSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    if((response_data.length()<1)||response_data.contains("Unavailable")){
        qDebug()<<"Palvelin ei vastaa";
        ui->labelWarning->setText(tr("Palvelin ei vastaa!"));
    }
    else {
        if(response_data=="-11"){
            ui->labelWarning->setText(tr("Tietokanta ei vastaa!"));
        }
        else{
            this->setWrongAttempts(response_data.toInt());
            if (wrongAttempts>=3){
                qDebug()<<"Kortti lukittu"<<response_data;
                ui->labelWarning->setText(tr("Kortti lukittu. Ota yhteys pankkiisi."));
            }
            else{
                ui->labelWarning->setText("");
                loginTry();
            }
        }
    }
    reply->deleteLater();
    wrongAttemptsManager->deleteLater();
}

void login::loginTry()
{
    QJsonObject jsonObj;
    jsonObj.insert("idcard", ui->textKortti->text());
    jsonObj.insert("pin",ui->textPin->text());

    QString site_url=Environment::base_url()+"/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));
    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}


void login::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    if((response_data.length()<2)||response_data.contains("Unavailable")){
        qDebug()<<"Palvelin ei vastaa";
        ui->labelWarning->setText(tr("Palvelin ei vastaa!"));
    }
    else {
        if(response_data=="-11"){
            ui->labelWarning->setText(tr("Tietokanta ei vastaa!"));
        }
        else{
            if(response_data!="false" && response_data.length()>20){
                qDebug()<<response_data;
                ui->labelWarning->setText("");

                int updatedAttempts=0;
                this->setWrongAttempts(updatedAttempts);
                wrongAttemptsUpdate(ui->textKortti->text());

                myToken="Bearer "+response_data;
                cardAccountCheck(ui->textKortti->text(), myToken);
                //Tässä pitäisi hakea korttia vastaava tilinumero (idaccount)

            }
            else {
            qDebug()<<response_data;
                ui->labelWarning->setText(tr("Väärä kortti/PIN!"));
            int updatedAttempts=wrongAttempts+1;
            this->setWrongAttempts(updatedAttempts);
            wrongAttemptsUpdate(ui->textKortti->text());
            if (updatedAttempts==3){
                qDebug()<<"Kortti lukittu"<<response_data;
                ui->labelWarning->setText(tr("Kortti lukittu. Ota yhteys pankkiisi."));
                QMessageBox *messageBox = new QMessageBox;
                messageBox->setWindowTitle(tr("Kortti lukittu"));
                messageBox->setText(tr("Kortti lukittu. Ota yhteys pankkiisi."));
                //messageBox->defaultButton()->setText("Sulje");
                QTimer::singleShot(10000, messageBox, SLOT(close()));
                messageBox->exec();

                this->close();

            }
            }
        }
    }
    qDebug()<<response_data;
    reply->deleteLater();
    loginManager->deleteLater();
}


void login::cardAccountCheck(QString idcard, QByteArray myToken)
{
    QString site_url=Environment::base_url()+"/card_account/"+idcard;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    cardAccountManager = new QNetworkAccessManager(this);

    connect(cardAccountManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cardAccountSlot(QNetworkReply*)));

    reply = cardAccountManager->get(request);
}


void login::cardAccountSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    if(json_array.size()==2){
        this->setIdaccount(json_doc[0]["idaccount"].toString());
        this->setIdaccount2(json_doc[1]["idaccount"].toString());
        accountLimitCheck(idaccount, myToken);


    } else{
        Mainmenu *objMainmenu=new Mainmenu(this);
        objMainmenu->setIdcard(ui->textKortti->text());
        objMainmenu->setMyToken(myToken);
        objMainmenu->setIdaccount((json_array.at(0)["idaccount"].toString()));
        objMainmenu->iduserCheck();
        objMainmenu->open();

        loginTimer->stop();
        this->close();
    }

    reply->deleteLater();
    cardAccountManager->deleteLater();
}



void login::accountLimitCheck(QString idaccount, QByteArray myToken)
{
    QString site_url=Environment::base_url()+"/account/"+idaccount;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU
    accountLimitManager = new QNetworkAccessManager(this);

    connect(accountLimitManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(accountLimitSlot(QNetworkReply*)));

    reply = accountLimitManager->get(request);

}



void login::accountLimitSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    SelectAccount *objSelectAccount = new SelectAccount(this);
    if(json_doc["credit_limit"].toInt()==0){

        objSelectAccount->setIdDebitAccount(idaccount);
        objSelectAccount->setIdCreditAccount(idaccount2);
    } else{
        objSelectAccount->setIdDebitAccount(idaccount2);
        objSelectAccount->setIdCreditAccount(idaccount);
    }
    objSelectAccount->setIdcard(ui->textKortti->text());
    objSelectAccount->setMyToken(myToken);
    objSelectAccount->open();

    loginTimer->stop();
    this->close();

    reply->deleteLater();
    accountLimitManager->deleteLater();
}



void login::wrongAttemptsUpdate(QString idcard)
{
    QJsonObject jsonObj;

    jsonObj.insert("wrong_attempts", wrongAttempts);

    QString site_url=Environment::base_url()+"/login/"+idcard;
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    wrongAttemptsUpdateManager = new QNetworkAccessManager(this);
    connect(wrongAttemptsUpdateManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(wrongAttemptsUpdateSlot(QNetworkReply*)));
    reply = wrongAttemptsUpdateManager->put(request, QJsonDocument(jsonObj).toJson());
}

void login::wrongAttemptsUpdateSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    //QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    qDebug()<<"Wrong Attempts update "<<wrongAttempts;

    reply->deleteLater();
    wrongAttemptsUpdateManager->deleteLater();
}



void login::digitClicked(int digit)
{
    setLoginTimerCount(0);
    this->lineEditPointer->setText(this->lineEditPointer->text() + QString::number(digit));
}




void login::on_btnNext_clicked()
{
    setLoginTimerCount(0);

    ui->textKortti->setDisabled(true);
    ui->textPin->setEnabled(true);
    lineEditPointer=ui->textPin;
    ui->btnNext->setDisabled(true);
    ui->btnPrevious->setEnabled(true);
}


void login::on_btnPrevious_clicked()
{
    setLoginTimerCount(0);

    ui->textPin->setDisabled(true);
    ui->textKortti->setEnabled(true);
    lineEditPointer=ui->textKortti;
    ui->btnNext->setEnabled(true);
    ui->btnPrevious->setDisabled(true);
}


void login::on_btnNum1_clicked()
{
    digitClicked(1);
}


void login::on_btnNum2_clicked()
{
    digitClicked(2);
}


void login::on_btnNum3_clicked()
{
    digitClicked(3);
}


void login::on_btnNum4_clicked()
{
    digitClicked(4);
}


void login::on_btnNum5_clicked()
{
    digitClicked(5);
}


void login::on_btnNum6_clicked()
{
    digitClicked(6);
}


void login::on_btnNum7_clicked()
{
    digitClicked(7);
}


void login::on_btnNum8_clicked()
{
    digitClicked(8);
}


void login::on_btnNum9_clicked()
{
    digitClicked(9);
}


void login::on_btnNum0_clicked()
{
    digitClicked(0);
}


void login::on_btnBackspace_clicked()
{
    setLoginTimerCount(0);

    QString text = this->lineEditPointer->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "";
    }
    this->lineEditPointer->setText(text);
}


void login::on_btnClear_clicked()
{
    setLoginTimerCount(0);
    this->lineEditPointer->setText("");
}

void login::setWrongAttempts(int newWrongAttempts)
{
    wrongAttempts = newWrongAttempts;
}

void login::setIdaccount2(const QString &newIdaccount2)
{
    idaccount2 = newIdaccount2;
}

void login::setIdaccount(const QString &newIdaccount)
{
    idaccount = newIdaccount;
}

void login::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
}


void login::on_btnClose_clicked()
{
    loginTimer->stop();
    this->close();
}

