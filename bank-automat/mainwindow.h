#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QLocale>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void changeLanguageToEnglish();
    void changeLanguageToFinnish();

    void on_btnStart_clicked();

    void on_btnStyle_toggled(bool checked);

    void on_btnEnglish_clicked();

    void on_btnFinnish_clicked();

private:
    Ui::MainWindow *ui;
    QTranslator translator;
    void retranslateUi();

};
#endif // MAINWINDOW_H
