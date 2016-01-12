#-------------------------------------------------
#
# Project created by QtCreator 2016-01-06T16:37:33
#
#-------------------------------------------------

QT       += core gui sql opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KaraOk
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    people.cpp \
    mysqldatabase.cpp \
    query.cpp \
    nehewidget.cpp \
    logindlg.cpp

HEADERS  += mainwindow.h \
    people.h \
    mysqldatabase.h \
    query.h \
    nehewidget.h \
    logindlg.h

FORMS    += mainwindow.ui \
    logindlg.ui

CONFIG  +=  c++11

LIBS    +=  -lglut -lGLU -lGL

DISTFILES +=
