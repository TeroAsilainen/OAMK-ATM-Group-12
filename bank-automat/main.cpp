#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QDebug>


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;

    QTranslator translatorFi;

    QString translationFile =  ":/translations/translations/bank-automat_fi.qm";

    qDebug() << "Trying to load translation file:" << translationFile;

    if (translatorFi.load(translationFile)) {
        qApp->installTranslator(&translatorFi);
        qDebug() << "Finnish translation loaded!";
    } else {
        qDebug() << "Failed to load Finnish translation!";
    }

    w.show();
    return a.exec();
}

