#ifndef JSONSAVER_HPP
#define JSONSAVER_HPP

#include <utils/noninstantiable.hpp>
#include <utils/rect.hpp>

#include "namespace_world.hpp"

#include <iosfwd>

class QJsonObject;

BEGIN_NAMESPACE_WORLD

class City;
//class Map;
class Building;
class BuildingType;

class JsonSaver : private utils::noninstantiable
{
public:
    static void writeToStream(const QJsonObject& object, std::ostream& o);

    static QJsonObject saveCity(const City& city);

    static QJsonObject saveBuilding(const Building& building);

    static QJsonObject saveBuildingType(const BuildingType& building);


//    static QJsonObject saveMap(const Map& map);

    static QJsonObject saveSizeU(const utils::SizeU& size);

    static QJsonObject savePointU(const utils::PointU& point);

    static QJsonObject saveRectU(const utils::RectU& rect);
};

END_NAMESPACE_WORLD

#endif // JSONSAVER_HPP
