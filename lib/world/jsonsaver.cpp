#include "jsonsaver.hpp"
#include "city.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

BEGIN_NAMESPACE_WORLD

void JsonSaver::writeToStream(const QJsonObject& object, std::ostream& o)
{
    QJsonDocument doc(object);
    QString str(doc.toJson(QJsonDocument::Compact));
    o << str.toStdString();
}

QJsonObject JsonSaver::saveCity(const City& city)
{
    QJsonObject res;
    res.insert("name", QString::fromStdString(city.name()));

    QJsonArray buildings;
    int i = 0;
    for(const auto& b : city.buildings())
        buildings.insert(i++, saveBuilding(b));
    res.insert("buildings", buildings);

    res.insert("size", saveSizeU(city.map().size()));

    QJsonArray roads;
    i = 0;
    for(std::size_t x = 0; x < city.map().width(); x++)
        for(std::size_t y = 0; y < city.map().height(); y++)
            if(city.map().squareType({x, y}) == Map::SquareType::Road)
            {
                roads.insert(i++, savePointU({x, y}));
            }

    res.insert("roads", roads);

    return res;
}

QJsonObject JsonSaver::saveBuilding(const Building& building)
{
    QJsonObject res;
    res.insert("type", QString("test_building"));
    res.insert("rectangle", saveRectU(building.rectangle()));
    res.insert("entrance", savePointU(building.entrance()));
    return res;
}

//QJsonObject JsonSaver::saveMap(const Map& map)
//{
//    QJsonObject res;
//    res.insert("size", saveSizeU(map.size()));
//    res.insert("squares", QJsonArray());
//    return res;
//}

QJsonObject JsonSaver::saveSizeU(const utils::SizeU& size)
{
    QJsonObject res;
    res.insert("height", (qint64)size.height());
    res.insert("width", (qint64)size.width());
    return res;
}

QJsonObject JsonSaver::savePointU(const utils::PointU& point)
{
    QJsonObject res;
    res.insert("x", (qint64)point.x());
    res.insert("y", (qint64)point.y());
    return res;
}

QJsonObject JsonSaver::saveRectU(const utils::RectU& rect)
{
    QJsonObject res;
    res.insert("size", saveSizeU(rect.size()));
    res.insert("topleft", savePointU(rect.topLeft()));
    return res;
}

END_NAMESPACE_WORLD
