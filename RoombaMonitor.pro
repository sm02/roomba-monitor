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
    capteur.cpp \
    configliaison.cpp \
    liaison.cpp \
    logger.cpp \
    mesurage.cpp \
    roomba.cpp \
    trame.cpp \
    test.cpp

HEADERS  += capteur.h \
    configliaison.h \
    liaison.h \
    logger.h \
    mesurage.h \
    roomba.h \
    trame.h \
    test.h

win32: LIBS += -L$$PWD/C:/Qt/Desktop/4.8.4/lib/ -lQtSerialPortd

#INCLUDEPATH += $$PWD/C:/Qt/Desktop/4.8.4/include
#DEPENDPATH += $$PWD/C:/Qt/Desktop/4.8.4/include

#win32:!win32-g++ PRE_TARGETDEPS += $$PWD/C:/Qt/Desktop/4.8.4/lib/QtSerialPortd.lib
#else:win32-g++: PRE_TARGETDEPS += $$PWD/C:/Qt/Desktop/4.8.4/lib/libQtSerialPortd.a
