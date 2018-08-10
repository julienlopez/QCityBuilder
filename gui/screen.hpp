#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <utils/point.hpp>

#include <QWidget>

#include <memory>

#include <optional>

class iState;

namespace World
{
class City;
}

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(World::City* city, QWidget* p = nullptr);

    virtual ~Screen() = default;

protected:
    virtual void keyPressEvent(QKeyEvent* evt) override;

    virtual void mouseMoveEvent(QMouseEvent* evt) override;

    virtual void mouseReleaseEvent(QMouseEvent* evt) override;

    virtual void wheelEvent(QWheelEvent* evt) override;

    virtual void paintEvent(QPaintEvent* evt) override;

private:
    World::City* m_city;
    std::optional<utils::PointU> m_mousePosition;
    std::shared_ptr<iState> m_currentState;

    double computeZoomToFit(const World::City& city) const;

    void drawGround(const World::City& city, QPainter& painter) const;

    void drawCurrentStateArea(const World::City& city, QPainter& painter) const;

    void do_zoom(int delta);

    struct ScreenInfos
    {
        double ratio;
        uint16_t xMargin;
        uint16_t yMargin;
    };

    ScreenInfos computeScreenInfos(const World::City& city) const;

signals:
    void currentStateCleared();
    void displayStatusText(QString);

public slots:
    void onNewStateActivated(std::shared_ptr<iState> state);
};

#endif // SCREEN_HPP
