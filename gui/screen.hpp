#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <QGraphicsView>

class Screen : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Screen(QGraphicsScene* s, QWidget* p = 0);

protected:
    virtual void drawBackground(QPainter* painter, const QRectF& rectangle) override;

    void wheelEvent(QWheelEvent* evt);

private:
    void do_zoom(int delta);

signals:

public slots:

};

#endif // SCREEN_HPP
