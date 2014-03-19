#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <utils/point.hpp>

#include <QWidget>

#include <memory>

class iState;

namespace World {
    class City;
}

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget* p = 0);

protected:
    virtual void paintEvent(QPaintEvent* evt) override;

    virtual void wheelEvent(QWheelEvent* evt) override;

private:
    utils::PointU m_mousePosition;
    std::shared_ptr<iState> m_currentState;

    double computeZoomToFit(const World::City& city) const;

    void drawGround(const World::City& city, QPainter& painter) const;

    void drawCurrentStateArea(const World::City& city, QPainter& painter) const;

    void do_zoom(int delta);

signals:
    void displayStatusText(QString);

public slots:
    void onNewStateActivated(std::shared_ptr<iState> state);
};

#endif // SCREEN_HPP
