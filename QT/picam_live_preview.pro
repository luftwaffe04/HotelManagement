#-------------------------------------------------
#
# Project created by QtCreator 2017-03-22T20:19:05
#
# Last Update : 2020-10-05
# Detail : + sql
#-------------------------------------------------

QT       += core gui sql
QT       += network
QT       += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = picam-live
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cameraworker.cpp \
    secdialog101.cpp \
    roomstatus101.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    cameraworker.h \
    secdialog101.h \
    roomstatus101.h \
    mythread.h

FORMS    += mainwindow.ui \
    secdialog101.ui \
    roomstatus101.ui \
    mythread.ui

# Requirements for raspicam
LIBS += -L/opt/vc/lib -lmmal -lmmal_core -lmmal_util
LIBS += -L/usr/local/lib -I/usr/local/include -lraspicam

DISTFILES += \
    .astylerc
