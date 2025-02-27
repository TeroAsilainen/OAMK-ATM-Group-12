#include "transactions.h"
#include "ui_transactions.h"
#include "environment.h"

#include <QTableView>
#include <QDateTime>
#include <QMessageBox>


Transactions::Transactions(Mainmenu *parent)
    : QDialog(parent)
    , ui(new Ui::Transactions)
{
    setParentPointer(parent);

    ui->setupUi(this);

    this->setWindowState(Qt::WindowFullScreen);

    ui->btnContinue->hide();

    setTransactionsTimerCount(0);
    transactionsTimer = new QTimer(this);
    connect(transactionsTimer, SIGNAL(timeout()), this, SLOT(transactionsTimerTick()));
    transactionsTimer->start(2000);
}

Transactions::~Transactions()
{
    delete ui;
}

void Transactions::setIdaccount(const QString &newIdaccount)
{
    idaccount = newIdaccount;
}

void Transactions::setMyToken(const QByteArray &newMyToken)
{
    myToken = newMyToken;
    qDebug()<<"Transactions";
    qDebug()<<myToken;
}

void Transactions::showTable(QByteArray transactionData)
{
    qDebug()<<"transaction ikkuna";
    qDebug()<<transactionData;

    QJsonDocument json_doc = QJsonDocument::fromJson(transactionData);
    QJsonArray json_array = json_doc.array();

    //Datan näyttäminen tableViewssä:
    QStandardItemModel *transactions = new QStandardItemModel(json_array.size(), 4, this);

    transactions->setHeaderData(0, Qt::Horizontal, this->tr("Tilinumero"));
    transactions->setHeaderData(1, Qt::Horizontal, this->tr("Päivämäärä"));
    transactions->setHeaderData(2, Qt::Horizontal, this->tr("Tapahtuma"));
    transactions->setHeaderData(3, Qt::Horizontal, this->tr("Summa"));

    int row = 0;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();

        QStandardItem *account = new QStandardItem (json_obj["idaccount"].toString());
        transactions->setItem(row, 0, account);

        //Päivämäärän muotoilu
        QString originalDate = json_obj["date"].toString();
        QDateTime dateTime = QDateTime::fromString(originalDate, Qt::ISODate);
        if (dateTime.isValid()) {
            QString formattedDate = dateTime.toString("dd.MM.yyyy HH:mm:ss");
            QStandardItem * d = new QStandardItem(formattedDate);
            transactions->setItem(row, 1, d);
        }
        QString action = json_obj["action"].toString();
        if (action == "Nosto") {
            action = tr("Withdrawal");
        } else if (action == "Talletus") {
            action = tr("Deposit");
        }
        QStandardItem *ac = new QStandardItem (action);
        transactions->setItem(row, 2, ac);

        QStandardItem *am = new QStandardItem (json_obj["amount"].toString());
        transactions->setItem(row, 3, am);

        row++;
    }

    ui->tableTransactions->setModel(transactions);
    ui->tableTransactions->resizeColumnsToContents();
    ui->btnPreviousTransactions->setDisabled(true);

}

void Transactions::showNextPage()
{
    QJsonObject jsonObj;
    jsonObj.insert("offset",offset);

    QString site_url=Environment::base_url()+"/transaction/"+idaccount;
    qDebug()<<"idaccount="+idaccount;
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    nextPageManager = new QNetworkAccessManager(this);
    connect(nextPageManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(showNextPageSlot(QNetworkReply*)));
    reply = nextPageManager->post(request, QJsonDocument(jsonObj).toJson());
}


void Transactions::showNextPageSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
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
        transactionsTimer->stop();
        messageBox->exec();
        transactionsTimer->start();
    }
    else if ((response_data.length()<1)||response_data.contains("Unavailable")){
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle(tr("Palvelin ei vastaa"));
        messageBox->setText(tr("Palvelin ei vastaa. Yritä hetken kuluttua uudelleen."));
        QTimer::singleShot(10000, messageBox, SLOT(close()));
        transactionsTimer->stop();
        messageBox->exec();
        transactionsTimer->start();
    }
    else {
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    QStandardItemModel *transactions = new QStandardItemModel(json_array.size(), 4, this);
    transactions->setHeaderData(0, Qt::Horizontal, this->tr("Tilinumero"));
    transactions->setHeaderData(1, Qt::Horizontal, this->tr("Päivämäärä"));
    transactions->setHeaderData(2, Qt::Horizontal, this->tr("Tapahtuma"));
    transactions->setHeaderData(3, Qt::Horizontal, this->tr("Summa"));

    int row = 0;
    foreach(const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();

        QStandardItem *account = new QStandardItem (json_obj["idaccount"].toString());
        transactions->setItem(row, 0, account);

        //Päivämäärän muotoilu
        QString originalDate = json_obj["date"].toString();
        QDateTime dateTime = QDateTime::fromString(originalDate, Qt::ISODate);
        if (dateTime.isValid()) {
            QString formattedDate = dateTime.toString("dd.MM.yyyy HH:mm:ss");
            QStandardItem * d = new QStandardItem(formattedDate);
            transactions->setItem(row, 1, d);
        }
        QString action = json_obj["action"].toString();
        if (action == "Nosto") {
            action = tr("Withdrawal");
        } else if (action == "Talletus") {
            action = tr("Deposit");
        }
        QStandardItem *ac = new QStandardItem (action);
        transactions->setItem(row, 2, ac);

        QStandardItem *am = new QStandardItem (json_obj["amount"].toString());
        transactions->setItem(row, 3, am);

        row++;
    }
    ui->tableTransactions->setModel(transactions);

    if (offset == 0) {
        ui->btnPreviousTransactions->setDisabled(true);
    } else {
        ui->btnPreviousTransactions->setDisabled(false);
    }

    if(json_array.size() < 5) {
    ui->btnNextTransactions->setEnabled(false);
    } else {
        ui->btnNextTransactions->setEnabled(true);
    }

    reply->deleteLater();
    nextPageManager->deleteLater();
    }
}

void Transactions::transactionsTimerTick()
{
    this->setTransactionsTimerCount(transactionsTimerCount+1);
    qDebug()<<transactionsTimerCount;
    if(transactionsTimerCount==5){
        ui->labelTimer->setText(tr("Yhteyden aikakatkaisu pian"));
        ui->btnContinue->show();
    }
    else if(transactionsTimerCount<5 && ui->labelTimer->text()==tr("Yhteyden aikakatkaisu pian")){
        ui->labelTimer->setText("");
    }
    else if(transactionsTimerCount==7){
        this->close();
        transactionsTimer->stop();
        parentPointer->mainMenuTimer->start();
    }
}

void Transactions::setParentPointer(Mainmenu *newParentPointer)
{
    parentPointer = newParentPointer;
}

void Transactions::setTransactionsTimerCount(int newTransactionsTimerCount)
{
    transactionsTimerCount = newTransactionsTimerCount;
}


void Transactions::on_btnNextTransactions_clicked()
{
    qDebug()<< "Offset: " << offset;
    offset += 5;
    showNextPage();
    setTransactionsTimerCount(0);
}

void Transactions::on_btnPreviousTransactions_clicked()
{
    qDebug()<< "Offset: " << offset;
    offset -= 5;
    showNextPage();
    setTransactionsTimerCount(0);

}

void Transactions::on_btnCloseTransactions_clicked()
{
    transactionsTimer->stop();
    parentPointer->mainMenuTimer->start();
    this->close();
}


void Transactions::on_btnContinue_clicked()
{
    setTransactionsTimerCount(0);
}

