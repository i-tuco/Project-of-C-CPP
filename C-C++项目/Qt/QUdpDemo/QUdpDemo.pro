#-------------------------------------------------
#
# Project created by QtCreator 2019-06-12T20:39:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QUdpDemo
TEMPLATE = app


SOURCES += main.cpp\
        udp1.cpp \
    udp2.cpp

HEADERS  += udp1.h \
    udp2.h

FORMS    += udp1.ui \
    udp2.ui
