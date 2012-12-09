#-------------------------------------------------
#
# Project created by QtCreator 2012-09-22T19:01:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DEG
TEMPLATE = app

INCLUDEPATH += /usr/include /usr/local/include /usr/include/qwt-qt4 /usr/include/qt4/QtExtSerialPort ../../Quadrocopter/control/qt ../../Quadrocopter/arduino/auto_controlled_engine_set_oop/

LIBS += -L/usr/local/lib -lqwt-qt4
LIBS += -L/usr/local/lib -lQtSvg

CONFIG += qwt


SOURCES += main.cpp\
        DEG.cpp \
    ../../Quadrocopter/control/qt/mytime.cpp \
    ../../Quadrocopter/arduino/auto_controlled_engine_set_oop/RVector3D.cpp

HEADERS  += DEG.h \
    ../../Quadrocopter/control/qt/mytime.h \
    ../../Quadrocopter/arduino/auto_controlled_engine_set_oop/RVector3D.h

FORMS    += DEG.ui
