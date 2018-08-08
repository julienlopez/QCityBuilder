QT       += core gui widgets

TARGET = QCityBuilder
TEMPLATE = app

include (../QCityBuilder.pri)

LIBS += -L$$QCITYBUILDER_BIN -lQCityBuilder

INCLUDEPATH += $$QCITYBUILDER_LIB
DEPENDPATH += $$QCITYBUILDER_LIB

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
    resourcespanel.cpp

HEADERS  += mainwindow.hpp \
    screen.hpp \
    statedock.hpp \
    buttonplacebuilding.hpp \
    states/placebuildingstate.hpp \
    states/istate.hpp \
    states/placeroadstate.hpp \
    buttonplaceroad.hpp \
    resourcespanel.hpp
