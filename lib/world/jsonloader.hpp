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
struct BuildingType;

namespace JsonLoader
{

QJsonObject stringToJsonObject(const std::string& json);

QJsonArray stringToJsonArray(const std::string& json);

City parseCity(const QJsonObject& object);

Building parseBuilding(const QJsonObject& object);

BuildingType parseBuildingType(const QJsonObject& object);

utils::SizeU parseSizeU(const QJsonObject& object);
utils::PointU parsePointU(const QJsonObject& object);
utils::RectU parseRectU(const QJsonObject& object);
};

END_NAMESPACE_WORLD

#endif // JSONLOADER_HPP
