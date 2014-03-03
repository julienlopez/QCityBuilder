QT -= gui widgets

TARGET = QCityBuilder
TEMPLATE = lib

include (../QCityBuilder.pri)

OBJECTS_DIR = $$QCITYBUILDER_OBJ_LIB
MOC_DIR= $$QCITYBUILDER_MOC_LIB

SOURCES += \

HEADERS  += \
    utils/namespace_utils.hpp \
    utils/pimpl.hpp \
    utils/noncopiable.hpp \
    utils/noninstantiable.hpp \
    utils/make_unique.hpp \
    utils/point.hpp \
    utils/uniquecontainerwithname.hpp
