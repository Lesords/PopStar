#-------------------------------------------------
#
# Project created by QtCreator 2022-02-11T15:41:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PopStar
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    popstar.cpp \
    game_over.cpp

HEADERS  += mainwindow.h \
    popstar.h \
    game_over.h

FORMS    += mainwindow.ui \
    popstar.ui \
    game_over.ui

RESOURCES += \
    image.qrc
