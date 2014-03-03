#include "cityscene.hpp"

#include <cassert>

#include <QGraphicsEllipseItem>

#include <QDebug>

using namespace std::placeholders;

CityScene::CityScene(QObject* p) : QGraphicsScene(p)
{

}

CityScene::~CityScene()
{}
