#include "screen.hpp"
#include <states/istate.hpp>

#include <world/city.hpp>

#include <cassert>

#include <QWheelEvent>

#include <QPainter>

#include <QDebug>

Screen::Screen(World::City* city, QWidget* p)
    : QWidget(p)
    , m_city(city)
{
    //    setDragMode(QGraphicsView::ScrollHandDrag);
    setFocus();
}

void Screen::keyPressEvent(QKeyEvent* evt)
{
    if(evt->key() != Qt::Key_Escape)
    {
        QWidget::keyPressEvent(evt);
        return;
    }

    evt->accept();
    onNewStateActivated({});
}

void Screen::mouseMoveEvent(QMouseEvent* evt)
{
    if(!m_city) return;

    QPointF position(evt->pos());
    //    qDebug() << position;
    auto screenInfos = computeScreenInfos(*m_city);
    position -= QPoint(screenInfos.xMargin, screenInfos.yMargin);
    position /= screenInfos.ratio;
    //    qDebug() << position.toPoint();
    m_mousePosition = utils::PointU(position.toPoint().x(), position.toPoint().y());
    setFocus();
    update();
}

void Screen::mouseReleaseEvent(QMouseEvent* evt)
{
    if(evt->button() != Qt::LeftButton || !m_currentState || !m_city)
    {
        QWidget::mouseReleaseEvent(evt);
        return;
    }
    m_currentState->leftClick(*m_city, *m_mousePosition);
    update();
}

void Screen::wheelEvent(QWheelEvent* evt)
{
    do_zoom(evt->delta());
    evt->accept();
}

namespace
{
QColor type2color(World::Map::SquareType type)
{
    switch(type)
    {
    case World::Map::SquareType::Empty:
        return Qt::green;
    case World::Map::SquareType::Building:
        return Qt::blue;
    case World::Map::SquareType::Road:
        return Qt::lightGray;
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

    if(m_city)
    {
        auto screenInfos = computeScreenInfos(*m_city);
        double ratio = screenInfos.ratio;

        painter.translate(screenInfos.xMargin, screenInfos.yMargin);

        painter.scale(ratio, ratio);
        drawGround(*m_city, painter);
        drawCurrentStateArea(*m_city, painter);
    }
}

double Screen::computeZoomToFit(const World::City& city) const
{
    double ratioX = (double)width() / city.map().width();
    double ratioY = (double)height() / city.map().height();
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
    auto area = m_currentState->area(*m_mousePosition);
    if(m_city->isOutOfBound(area)) return;
    auto b = painter.brush();
    QColor c = city.isAreaFreeToBuild(area) ? Qt::yellow : c = Qt::red;
    c.setAlphaF(.6);
    b.setColor(c);
    painter.setBrush(b);
    painter.drawRect(
        QRectF(QPoint(area.topLeft().x(), area.topLeft().y()), QSize(area.size().width(), area.size().height())));
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
    res.xMargin = (width() - city.map().width() * res.ratio) / 2;
    res.yMargin = (height() - city.map().height() * res.ratio) / 2;
    return res;
}

void Screen::onNewStateActivated(std::shared_ptr<iState> state)
{
    m_currentState = state;
    emit displayStatusText(QString::fromStdString(state ? state->message() : ""));
    update();
    setMouseTracking((bool)m_currentState);

    if(!m_currentState)
    {
        m_mousePosition.reset();
        emit currentStateCleared();
    }
}
