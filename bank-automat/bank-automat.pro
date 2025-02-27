QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TRANSLATIONS += translations/bank-automat_fi.ts \
    translations/bank-automat_en.ts

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    amount.cpp \
    balance.cpp \
    environment.cpp \
    login.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    payment.cpp \
    selectaccount.cpp \
    transactions.cpp \
    transfer.cpp \
    withdrawal.cpp

HEADERS += \
    amount.h \
    balance.h \
    environment.h \
    login.h \
    mainmenu.h \
    mainwindow.h \
    payment.h \
    selectaccount.h \
    transactions.h \
    transfer.h \
    withdrawal.h

FORMS += \
    amount.ui \
    balance.ui \
    login.ui \
    mainmenu.ui \
    mainwindow.ui \
    payment.ui \
    selectaccount.ui \
    transactions.ui \
    transfer.ui \
    withdrawal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
