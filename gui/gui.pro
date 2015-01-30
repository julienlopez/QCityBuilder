#-------------------------------------------------
#
# Project created by QtCreator 2014-02-20T09:20:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCityBuilder
TEMPLATE = app

include (../QCityBuilder.pri)

LIBS += -L$$QCITYBUILDER_BIN
LIBS += -lQCityBuilder

INCLUDEPATH += $$QCITYBUILDER_LIB

OBJECTS_DIR = $$QCITYBUILDER_OBJ_GUI
MOC_DIR= $$QCITYBUILDER_MOC_GUI

SOURCES += main.cpp\
        mainwindow.cpp \
    screen.cpp \
    statedock.cpp \
    buttonplacebuilding.cpp \
    states/placebuildingstate.cpp \
    states/istate.cpp \
    states/placeroadstate.cpp \
    buttonplaceroad.cpp \
    ressourcespanel.cpp

HEADERS  += mainwindow.hpp \
    screen.hpp \
    statedock.hpp \
    buttonplacebuilding.hpp \
    states/placebuildingstate.hpp \
    states/istate.hpp \
    states/placeroadstate.hpp \
    buttonplaceroad.hpp \
    ressourcespanel.hpp
