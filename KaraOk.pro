#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T16:37:33
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KaraOk
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    people.cpp

HEADERS  += mainwindow.h \
    people.h

FORMS    += mainwindow.ui

CONFIG  +=  c++11
