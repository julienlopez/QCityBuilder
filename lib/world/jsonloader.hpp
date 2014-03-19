#ifndef JSONLOADER_HPP
#define JSONLOADER_HPP

#include "namespace_world.hpp"

#include <utils/noninstantiable.hpp>
#include <utils/rect.hpp>

#include <string>

class QJsonObject;
class QJsonArray;

BEGIN_NAMESPACE_WORLD

class City;
class Building;
class BuildingType;

class JsonLoader : private utils::noninstantiable
{
public:
    static QJsonObject stringToJsonObject(const std::string& json);
    static QJsonArray stringToJsonArray(const std::string& json);

    static City parseCity(const QJsonObject& object);

    static Building parseBuilding(const QJsonObject& object);

    static BuildingType parseBuildingType(const QJsonObject& object);

    static utils::SizeU parseSizeU(const QJsonObject& object);
    static utils::PointU parsePointU(const QJsonObject& object);
    static utils::RectU parseRectU(const QJsonObject& object);

private:
    static std::string findString(const QJsonObject& object, const std::string& name);
    static double findDouble(const QJsonObject& object, const std::string& name);
    static QJsonObject findObject(const QJsonObject& object, const std::string& name);
    static QJsonArray findArray(const QJsonObject& object, const std::string& name);
};

END_NAMESPACE_WORLD

#endif // JSONLOADER_HPP
