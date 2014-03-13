#include "cityscene.hpp"

#include <world/currentcityholder.hpp>

#include <cassert>

#include <QGraphicsEllipseItem>

#include <QDebug>

const std::size_t CityScene::s_resolution = 10;

CityScene::CityScene(QObject* p) : QGraphicsScene(p)
{
    initScene();
}

namespace {
QColor type2color(World::Map::SquareType type)
{
    switch(type)
    {
        case World::Map::SquareType::Empty: return Qt::green;
        case World::Map::SquareType::Building: return Qt::blue;
        case World::Map::SquareType::Road: return Qt::lightGray;
    }
    return Qt::yellow;
}
}

void CityScene::initScene()
{
    assert(World::CurrentCityHolder::isInitialized());
    auto& city = World::CurrentCityHolder::get();
    setSceneRect(0, 0, s_resolution * city.map().width(), s_resolution * city.map().height());
    for(std::size_t x = 0; x < city.map().width(); x++)
        for(std::size_t y = 0; y < city.map().height(); y++)
        {
            auto* item = new QGraphicsRectItem(s_resolution * x, s_resolution * y, s_resolution, s_resolution);
            item->setPen(QPen(Qt::black));
            QBrush b = item->brush();
            b.setStyle(Qt::SolidPattern);
            b.setColor(type2color(city.map().squareType({x, y})));
            item->setBrush(b);
            addItem(item);
        }
}
