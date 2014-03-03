QT -= gui widgets

TARGET = tests
TEMPLATE = app

include (../QCityBuilder.pri)
include (../gtest.pri)

LIBS += -L$$QCITYBUILDER_BIN
LIBS += -lQCityBuilder

INCLUDEPATH += $$QCITYBUILDER_LIB

OBJECTS_DIR = $$QCITYBUILDER_OBJ_TESTS
MOC_DIR= $$QCITYBUILDER_MOC_TESTS

SOURCES += main.cpp \
