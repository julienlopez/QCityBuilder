#ifndef JSONLOADER_HPP
#define JSONLOADER_HPP

#include "namespace_world.hpp"

#include <utils/noninstantiable.hpp>
#include <utils/rect.hpp>

#include <string>

class QJsonObject;

BEGIN_NAMESPACE_WORLD

class City;
class Building;

class JsonLoader : private utils::noninstantiable
{
public:
    static QJsonObject stringToJsonObject(const std::string& json);

    static City parseCity(const QJsonObject& object);

    static Building parseBuilding(const QJsonObject& object);

    static utils::SizeU parseSizeU(const QJsonObject& object);
    static utils::PointU parsePointU(const QJsonObject& object);
    static utils::RectU parseRectU(const QJsonObject& object);
};

END_NAMESPACE_WORLD

#endif // JSONLOADER_HPP
