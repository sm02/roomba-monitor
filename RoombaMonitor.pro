#-------------------------------------------------
#
# Project created by QtCreator 2014-10-24T20:40:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoombaMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    capteur.cpp \
    configliaison.cpp \
    cserie.cpp \
    dialogconfiguration.cpp \
    liaison.cpp \
    logger.cpp \
    mesurage.cpp \
    roomba.cpp \
    trame.cpp \
    wdgselectionmesure.cpp \
    controleurindicateurs.cpp \
    indicateurstatus.cpp

HEADERS  += mainwindow.h \
    capteur.h \
    configliaison.h \
    cserie.h \
    dialogconfiguration.h \
    liaison.h \
    logger.h \
    mesurage.h \
    roomba.h \
    trame.h \
    wdgselectionmesure.h \
    controleurindicateurs.h \
    indicateurstatus.h

FORMS    += mainwindow.ui \
    dialogconfiguration.ui \
    wdgselectionmesure.ui \
    indicateurstatus.ui



win32: LIBS += -L$$PWD/lib/ -lanalogwidgets

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/analogwidgets.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libanalogwidgets.a
