QT -= gui widgets

TARGET = tests
TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

include (../QCityBuilder.pri)

LIBS += -L$$QCITYBUILDER_BIN -lQCityBuilder

DEPENDPATH += $$QCITYBUILDER_LIB
INCLUDEPATH += $$QCITYBUILDER_LIB
INCLUDEPATH += $$QCITYBUILDER_ROOT/3rd_party/catch

OBJECTS_DIR = $$QCITYBUILDER_OBJ_TESTS
MOC_DIR= $$QCITYBUILDER_MOC_TESTS

SOURCES += main.cpp \
    testcontainerwithidentifier.cpp \
    testinventory.cpp \
    testproducer.cpp \
    testmap.cpp \
    testcity.cpp \
    testbuildingtype.cpp \
    testrect.cpp \
    testguihelper.cpp \
    test_villager.cpp \
    test_building.cpp
