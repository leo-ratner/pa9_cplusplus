#-------------------------------------------------
#
# Project created by QtCreator 2018-04-02T11:26:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Garden_Gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    commandeditor.cpp \
    garden.cpp \
    plant.cpp \
    tree.cpp \
    vegetable.cpp \
    flower.cpp \
    renderer.cpp \
    interpreter.cpp \
    plantmap.cpp \
    commandtextedit.cpp \
    linereader.cpp \
    colormap.cpp \
    fungus.cpp

HEADERS += \
        mainwindow.h \
    commandeditor.h \
    garden.h \
    plant.h \
    tree.h \
    planttypes.h \
    vegetable.h \
    flower.h \
    renderer.h \
    interpreter.h \
    plantmap.h \
    commandtextedit.h \
    linereader.h \
    colormap.h \
    fungus.h

FORMS += \
        mainwindow.ui \
    commandeditor.ui \
    renderer.ui
