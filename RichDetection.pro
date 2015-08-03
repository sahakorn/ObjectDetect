#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T20:39:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RichDetection
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/lib/x86_64-linux-gnu/ -lopencv_core  -lopencv_highgui -lopencv_imgproc
