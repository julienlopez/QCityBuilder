#include "screen.hpp"

#include <cassert>

#include <QWheelEvent>

#include <QDebug>

Screen::Screen(QGraphicsScene* s, QWidget* p): QGraphicsView(s, p)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void Screen::drawBackground(QPainter* painter, const QRectF& rectangle)
{
    painter->save();

    painter->setBrush(Qt::black);
    painter->drawRect(rectangle);

    painter->restore();
}

void Screen::wheelEvent(QWheelEvent* evt)
{
    do_zoom(evt->delta());
    evt->accept();
}

void Screen::do_zoom(int delta)
{
    double zoom = 1.0 + (delta / 1000.0);
    scale(zoom, zoom);
}
