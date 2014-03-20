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

void Screen::mouseMoveEvent(QMouseEvent* evt)
{
    if(!World::CurrentCityHolder::isInitialized()) return;

    auto& city = World::CurrentCityHolder::get();
    QPointF position(evt->pos());
//    qDebug() << position;
    auto screenInfos = computeScreenInfos(city);
    position -= QPoint(screenInfos.xMargin, screenInfos.yMargin);
    position /= screenInfos.ratio;
//    qDebug() << position.toPoint();
    m_mousePosition = utils::PointU(position.toPoint().x(), position.toPoint().y());
    update();
}

void Screen::wheelEvent(QWheelEvent* evt)
{
    do_zoom(evt->delta());
    evt->accept();
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
    auto screenInfos = computeScreenInfos(city);
    double ratio = screenInfos.ratio;

    painter.translate(screenInfos.xMargin, screenInfos.yMargin);

    painter.scale(ratio, ratio);
    drawGround(city, painter);
    drawCurrentStateArea(city, painter);
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

void Screen::drawCurrentStateArea(const World::City& city, QPainter& painter) const
{
    if(!m_currentState) return;
    if(!m_mousePosition) return;
//    qDebug() << m_mousePosition->x() << ", " << m_mousePosition->y();
    auto rect = m_currentState->area(*m_mousePosition);
//    qDebug() << "{" << rect.topLeft().x() << ", " << rect.topLeft().y() << "}, {" << rect.bottomRight().x() << ", " << rect.bottomRight().y() << "}";
    auto b = painter.brush();
    QColor c = Qt::yellow;
    c.setAlphaF(.6);
    b.setColor(c);
    painter.setBrush(b);
    painter.drawRect(QRectF(QPoint(rect.topLeft().x(), rect.topLeft().y()), QSize(rect.size().width(), rect.size().height())));
}

void Screen::do_zoom(int delta)
{
//    double zoom = 1.0 + (delta / 1000.0);
//    scale(zoom, zoom);
}

auto Screen::computeScreenInfos(const World::City& city) const -> ScreenInfos
{
    ScreenInfos res;
    res.ratio = computeZoomToFit(city);
    res.xMargin = (width()-city.map().width()*res.ratio)/2;
    res.yMargin = (height()-city.map().height()*res.ratio)/2;
    return res;
}

void Screen::onNewStateActivated(std::shared_ptr<iState> state)
{
    m_currentState = state;
    emit displayStatusText(QString::fromStdString(state?state->message():""));
    update();
    setMouseTracking((bool)m_currentState);
}
