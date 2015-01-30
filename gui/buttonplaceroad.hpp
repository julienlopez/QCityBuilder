#ifndef BUTTONPLACEROAD_HPP
#define BUTTONPLACEROAD_HPP

#include <QPushButton>

#include <memory>

class iState;

class ButtonPlaceRoad : public QPushButton
{
    Q_OBJECT
public:
    explicit ButtonPlaceRoad(QWidget* parent_ = 0);

signals:
    void activated(std::shared_ptr<iState>);
};

#endif // BUTTONPLACEROAD_HPP
