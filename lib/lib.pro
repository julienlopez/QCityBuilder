QT -= gui widgets

TARGET = QCityBuilder
TEMPLATE = lib
CONFIG += staticlib

include (../QCityBuilder.pri)

OBJECTS_DIR = $$QCITYBUILDER_OBJ_LIB
MOC_DIR= $$QCITYBUILDER_MOC_LIB

SOURCES += \
    inventory.cpp \
    producer.cpp \
    production.cpp \
    world/map.cpp \
    world/building.cpp \
    world/city.cpp \
    world/jsonloader.cpp \
    world/jsonsaver.cpp \
    world/currentcityholder.cpp \
    world/buildingtype.cpp \
    world/buildingtypehandler.cpp \
    guihelper.cpp \
    inventorysummary.cpp \
    resourceshandler.cpp

HEADERS  += \
    utils/namespace_utils.hpp \
    utils/pimpl.hpp \
    utils/noncopiable.hpp \
    utils/noninstantiable.hpp \
    utils/make_unique.hpp \
    utils/point.hpp \
    utils/singleton.hpp \
    utils/uniquecontainerwithname.hpp \
    utils/containerwithidentifier.hpp \
    inventory.hpp \
    producer.hpp \
    production.hpp \
    world/map.hpp \
    world/namespace_world.hpp \
    utils/rect.hpp \
    world/building.hpp \
    utils/size.hpp \
    world/city.hpp \
    utils/array2d.hpp \
    world/jsonloader.hpp \
    world/jsonsaver.hpp \
    world/currentcityholder.hpp \
    world/buildingtype.hpp \
    world/buildingtypehandler.hpp \
    guihelper.hpp \
    inventorysummary.hpp \
    resourceshandler.hpp
