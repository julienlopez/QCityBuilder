QCITYBUILDER_ROOT = $$PWD

QCITYBUILDER_BIN = $$QCITYBUILDER_ROOT/bin

QCITYBUILDER_LIB = $$QCITYBUILDER_ROOT/lib

QCITYBUILDER_OBJ_LIB = $$QCITYBUILDER_ROOT/obj_lib

QCITYBUILDER_MOC_LIB = $$QCITYBUILDER_ROOT/moc_lib

QCITYBUILDER_OBJ_GUI = $$QCITYBUILDER_ROOT/obj_gui

QCITYBUILDER_MOC_GUI = $$QCITYBUILDER_ROOT/moc_gui

QCITYBUILDER_OBJ_TESTS = $$QCITYBUILDER_ROOT/obj_tests

QCITYBUILDER_MOC_TESTS = $$QCITYBUILDER_ROOT/moc_tests

DESTDIR = $$QCITYBUILDER_BIN

CONFIG += c++17

win32 {
    QMAKE_CXXFLAGS += /std:c++17
} else {
    QMAKE_CXXFLAGS += -std=c++17 -O0 --coverage -fprofile-arcs -ftest-coverage -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations \
                      -Wredundant-decls -Wno-long-long -Wuninitialized
}

LIBS += -lgcov --coverage -fprofile-arcs -ftest-coverage
