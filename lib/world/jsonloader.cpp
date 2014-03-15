#include "jsonloader.hpp"
#include "city.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <cassert>

BEGIN_NAMESPACE_WORLD

QJsonObject JsonLoader::stringToJsonObject(const std::string& json)
{
    auto doc = QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
    assert(doc.isObject());
    return doc.object();
}

City JsonLoader::parseCity(const QJsonObject& object)
{
    assert(!object.isEmpty());

    auto it = object.find("name");
    assert(it != object.end());
    assert(it.value().isString());
    std::string name = it.value().toString().toStdString();

    it = object.find("size");
    assert(it != object.end());
    assert(it.value().isObject());
    utils::SizeU size = parseSizeU(it.value().toObject());

    City city(name, size);

    it = object.find("buildings");
    assert(it != object.end());
    assert(it.value().isArray());
    auto array = it.value().toArray();
    for(const auto& value : array)
    {
        assert(value.isObject());
        city.add(parseBuilding(value.toObject()));
    }

    it = object.find("roads");
    assert(it != object.end());
    assert(it.value().isArray());
    array = it.value().toArray();
    for(const auto& value : array)
    {
        assert(value.isObject());
        city.addRoad({parsePointU(value.toObject())});
    }

    return city;
}

Building JsonLoader::parseBuilding(const QJsonObject& object)
{
    assert(!object.isEmpty());

    auto it = object.find("type");
    assert(it != object.end());
    assert(it.value().isString());
    std::string type = it.value().toString().toStdString();

    it = object.find("entrance");
    assert(it != object.end());
    assert(it.value().isObject());
    auto entrance = parsePointU(it.value().toObject());

    it = object.find("rectangle");
    assert(it != object.end());
    assert(it.value().isObject());
    auto rectangle = parseRectU(it.value().toObject());

    return Building(entrance, rectangle);
}

utils::SizeU JsonLoader::parseSizeU(const QJsonObject& object)
{
    assert(!object.isEmpty());

    auto it = object.find("width");
    assert(it != object.end());
    assert(it.value().isDouble());
    std::size_t width = it.value().toDouble();

    it = object.find("height");
    assert(it != object.end());
    assert(it.value().isDouble());
    std::size_t height = it.value().toDouble();

    return utils::SizeU(width, height);
}

utils::PointU JsonLoader::parsePointU(const QJsonObject& object)
{
    assert(!object.isEmpty());

    auto it = object.find("x");
    assert(it != object.end());
    assert(it.value().isDouble());
    std::size_t x = it.value().toDouble();

    it = object.find("y");
    assert(it != object.end());
    assert(it.value().isDouble());
    std::size_t y = it.value().toDouble();

    return utils::PointU(x, y);
}

utils::RectU JsonLoader::parseRectU(const QJsonObject& object)
{
    assert(!object.isEmpty());

    auto it = object.find("size");
    assert(it != object.end());
    assert(it.value().isObject());
    auto size = parseSizeU(it.value().toObject());

    it = object.find("topleft");
    assert(it != object.end());
    assert(it.value().isObject());
    auto topleft = parsePointU(it.value().toObject());

    return utils::RectU(topleft, size);
}


END_NAMESPACE_WORLD
