#-------------------------------------------------
#
# Project created by QtCreator 2018-11-29T09:30:54
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Verbundprojekt
QTPLUGIN += QSQLMYSQL
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

RC_ICONS = vpj.ico

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    robotino.cpp \
    fertigungsplanung.cpp \
    clickablelabel.cpp \
    platz.cpp \
    station.cpp \
    fertigungsstrasse.cpp \
    parkplatz.cpp \
    prozess.cpp \
    prozessschritt.cpp \
    auftrag.cpp \
    databasehandler.cpp \
    auftragsitem.cpp \
    prozessitem.cpp \
    timestamp.cpp \
    simulatedrobot.cpp \
    udphandler.cpp

HEADERS += \
        mainwindow.h \
    initdb.h \
    robotino.h \
    fertigungsplanung.h \
    clickablelabel.h \
    platz.h \
    station.h \
    fertigungsstrasse.h \
    parkplatz.h \
    prozess.h \
    prozessschritt.h \
    auftrag.h \
    databasehandler.h \
    auftragsitem.h \
    prozessitem.h \
    timestamp.h \
    simulatedrobot.h \
    udphandler.h

FORMS += \
        mainwindow.ui \
    auftragsitem.ui \
    auftragsitem.ui \
    prozessitem.ui

RESOURCES += \
    resources.qrc

DISTFILES +=

STATECHARTS +=

