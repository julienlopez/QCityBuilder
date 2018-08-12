#include "jsonloader.hpp"

#include "buildingtype.hpp"
#include "city.hpp"
#include "resourceshandler.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <cassert>

#include <QDebug>

BEGIN_NAMESPACE_WORLD

namespace
{

std::string findString(const QJsonObject& object, const std::string& name)
{
    auto it = object.find(QString::fromStdString(name));
    assert(it != object.end());
    assert(it.value().isString());
    return it.value().toString().toStdString();
}

int findInt(const QJsonObject& object, const std::string& name)
{
    auto it = object.find(QString::fromStdString(name));
    assert(it != object.end());
    return it.value().toInt();
}

double findDouble(const QJsonObject& object, const std::string& name)
{
    auto it = object.find(QString::fromStdString(name));
    assert(it != object.end());
    assert(it.value().isDouble());
    return it.value().toDouble();
}

QJsonObject findObject(const QJsonObject& object, const std::string& name)
{
    auto it = object.find(QString::fromStdString(name));
    assert(it != object.end());
    assert(it.value().isObject());
    return it.value().toObject();
}

QJsonArray findArray(const QJsonObject& object, const std::string& name)
{
    auto it = object.find(QString::fromStdString(name));
    assert(it != object.end());
    assert(it.value().isArray());
    return it.value().toArray();
}

auto parseRequirements(const QJsonArray& array)
{
    BuildingType::requirements_map_t requirements;
    for(auto pair : array)
    {
        assert(pair.isObject());
        auto o = pair.toObject();

        std::string pairName = findString(o, "name");
        std::size_t pairAmount = findDouble(o, "amount");

        auto id = ResourcesHandler::const_instance().idOf(pairName);
        requirements.insert(std::make_pair(id, pairAmount));
    }
    return requirements;
}

auto parseRecipesIngredients(const QJsonArray& array)
{
    Recipe::container_pairs_identifier_amount ingredients;
    for(const auto value : array)
    {
        assert(value.isObject());
        const auto obj = value.toObject();
        const auto ressource = findString(obj, "ressource");
        const auto amount = findInt(obj, "amount");
        const auto res = ResourcesHandler::findByName(ressource);
        assert(res);
        ingredients.emplace_back(*res, amount);
    }
    return ingredients;
}

auto parseRecipes(const QJsonArray& array)
{
    BuildingType::recipes_container_t recipes;
    for(const auto value : array)
    {
        assert(value.isObject());
        const auto obj = value.toObject();
        const auto inputs = parseRecipesIngredients(findArray(obj, "inputs"));
        const auto outputs = parseRecipesIngredients(findArray(obj, "outputs"));
        const auto timeout = findInt(obj, "timeout");
        recipes.emplace_back(timeout, inputs, outputs);
    }
    return recipes;
}
}

QJsonObject JsonLoader::stringToJsonObject(const std::string& json)
{
    auto doc = QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
    assert(doc.isObject());
    return doc.object();
}

QJsonArray JsonLoader::stringToJsonArray(const std::string& json)
{
    auto doc = QJsonDocument::fromJson(QString::fromStdString(json).toUtf8());
    assert(doc.isArray());
    return doc.array();
}

City JsonLoader::parseCity(const QJsonObject& object)
{
    assert(!object.isEmpty());

    std::string name = findString(object, "name");
    utils::SizeU size = parseSizeU(findObject(object, "size"));
    City city(name, size);

    auto array = findArray(object, "buildings");
    for(const auto& value : array)
    {
        assert(value.isObject());
        city.add(parseBuilding(value.toObject()));
    }

    array = findArray(object, "roads");
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

    auto typeName = findString(object, "type");
    auto entrance = parsePointU(findObject(object, "entrance"));
    auto rectangle = parseRectU(findObject(object, "rectangle"));

    auto typeId = BuildingTypeHandler::instance().getByName(typeName);
    return Building(typeId, entrance, rectangle);
}

BuildingType JsonLoader::parseBuildingType(const QJsonObject& object)
{
    assert(!object.isEmpty());

    std::string name = findString(object, "name");
    auto size = parseSizeU(findObject(object, "size"));

    const auto requirements = parseRequirements(findArray(object, "requirements"));
    const auto recipes = parseRecipes(findArray(object, "recipes"));
    return BuildingType(name, size, requirements, recipes);
}

utils::SizeU JsonLoader::parseSizeU(const QJsonObject& object)
{
    assert(!object.isEmpty());

    std::size_t width = findDouble(object, "width");
    std::size_t height = findDouble(object, "height");

    return utils::SizeU(width, height);
}

utils::PointU JsonLoader::parsePointU(const QJsonObject& object)
{
    assert(!object.isEmpty());

    std::size_t x = findDouble(object, "x");
    std::size_t y = findDouble(object, "y");

    return utils::PointU(x, y);
}

utils::RectU JsonLoader::parseRectU(const QJsonObject& object)
{
    assert(!object.isEmpty());

    auto size = parseSizeU(findObject(object, "size"));
    auto topleft = parsePointU(findObject(object, "topleft"));

    return utils::RectU(topleft, size);
}

END_NAMESPACE_WORLD
