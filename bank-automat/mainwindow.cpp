#include "login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowState(Qt::WindowMaximized);

    QFile file(":/styles/resources/lightmode.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet { QString(file.readAll()) };

    //setup stylesheet
    qApp->setStyleSheet(styleSheet);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnStart_clicked()
{
    login *objLogin=new login(this);
    objLogin->open();
    // this->close();
}

void MainWindow::on_btnStyle_toggled(bool checked)
{
    if (checked){
        QFile file(":/styles/resources/darkmode.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet { QString(file.readAll()) };

        //setup stylesheet
        qApp->setStyleSheet(styleSheet);
    }
    else{
        QFile file(":/styles/resources/lightmode.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet { QString(file.readAll()) };

        //setup stylesheet
        qApp->setStyleSheet(styleSheet);
    }
}


void MainWindow::on_btnEnglish_clicked()
{
    changeLanguageToEnglish();
}


void MainWindow::on_btnFinnish_clicked()
{
    changeLanguageToFinnish();
}

void MainWindow::changeLanguageToEnglish()
{
    if (!translator.load(":/translations/translations/bank-automat_en.qm")) {
        qDebug() << "Failed to load English translation!";
        return;
    }

    qApp->installTranslator(&translator);
    retranslateUi();

}

void MainWindow::changeLanguageToFinnish()
{
    if (!translator.load(":/translations/translations/bank-automat_fi.qm")) {
        qDebug() << "Failed to load Finnish translation!";
        return;
    }

    qApp->installTranslator(&translator);
    retranslateUi();
}

void MainWindow::retranslateUi()
{
    ui->retranslateUi(this);
}
