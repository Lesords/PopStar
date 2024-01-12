#-------------------------------------------------
#
# Project created by QtCreator 2022-02-11T15:41:57
#
#-------------------------------------------------

QT        += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = PopStar
TEMPLATE  = app

CONFIG    += c++11

SOURCES   += src/main.cpp \
    src/mainwindow.cpp \
    src/popstar.cpp \
    src/game_over.cpp

HEADERS   += src/mainwindow.h \
    src/popstar.h \
    src/game_over.h

FORMS     += ui/mainwindow.ui \
    ui/popstar.ui \
    ui/game_over.ui

RESOURCES += resources/image.qrc
