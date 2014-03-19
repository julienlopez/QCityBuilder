#include "screen.hpp"
#include <states/istate.hpp>

#include <world/currentcityholder.hpp>

#include <cassert>

#include <QWheelEvent>

#include <QPainter>

#include <QDebug>

Screen::Screen(QWidget* p): QWidget(p)
{
//    setDragMode(QGraphicsView::ScrollHandDrag);
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

void Screen::paintEvent(QPaintEvent* evt)
{
    Q_UNUSED(evt);

    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());

    assert(World::CurrentCityHolder::isInitialized());
    auto& city = World::CurrentCityHolder::get();
    double ratio = computeZoomToFit(city);

    painter.translate((width()-city.map().width()*ratio)/2, (height()-city.map().height()*ratio)/2);

    painter.scale(ratio, ratio);
    drawGround(city, painter);
}

double Screen::computeZoomToFit(const World::City& city) const
{
    double ratioX = (double)width()/city.map().width();
    double ratioY = (double)height()/city.map().height();
    return std::min(ratioX, ratioY);
}

void Screen::drawGround(const World::City& city, QPainter& painter) const
{
    for(std::size_t i = 0; i < city.map().width(); i++)
        for(std::size_t j = 0; j < city.map().height(); j++)
        {
            QPen p = painter.pen();
            p.setColor(Qt::black);
            p.setWidthF(.05);
            painter.setPen(p);
            QBrush b = painter.brush();
            b.setStyle(Qt::SolidPattern);
            b.setColor(type2color(city.map().squareType({i, j})));
            painter.setBrush(b);
            painter.drawRect(QRectF(QPointF(i, j), QSizeF(1, 1)));
        }
}

void Screen::wheelEvent(QWheelEvent* evt)
{
    do_zoom(evt->delta());
    evt->accept();
}

void Screen::do_zoom(int delta)
{
//    double zoom = 1.0 + (delta / 1000.0);
//    scale(zoom, zoom);
}

void Screen::onNewStateActivated(std::shared_ptr<iState> state)
{
    m_currentState = state;
    emit displayStatusText(QString::fromStdString(state->message()));
    update();
}
