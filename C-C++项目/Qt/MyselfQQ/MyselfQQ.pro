#-------------------------------------------------
#
# Project created by QtCreator 2019-06-11T21:09:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyselfQQ
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dialoglist.cpp

HEADERS  += widget.h \
    dialoglist.h

FORMS    += widget.ui \
    dialoglist.ui

RESOURCES += \
    res.qrc
