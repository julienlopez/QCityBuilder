#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <QGraphicsView>

#include <memory>

class iState;

class Screen : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Screen(QGraphicsScene* s, QWidget* p = 0);

protected:
    virtual void drawBackground(QPainter* painter, const QRectF& rectangle) override;

    void wheelEvent(QWheelEvent* evt);

private:
    std::shared_ptr<iState> m_currentState;

    void do_zoom(int delta);

signals:
    void displayStatusText(QString);

public slots:
    void onNewStateActivated(std::shared_ptr<iState> state);
};

#endif // SCREEN_HPP
