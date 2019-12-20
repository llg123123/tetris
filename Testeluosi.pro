#-------------------------------------------------
#
# Project created by QtCreator 2018-07-11T23:32:40
#
#-------------------------------------------------

QT       += core gui

QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Testeluosi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    brick.cpp \
    menu.cpp \
    help.cpp

HEADERS  += mainwindow.h \
    board.h \
    brick.h \
    menu.h \
    help.h

FORMS    += \
    menu.ui \
    help.ui

RESOURCES += \
    photo/box.qrc
    RC_ICONS = Super.ico

DISTFILES +=
