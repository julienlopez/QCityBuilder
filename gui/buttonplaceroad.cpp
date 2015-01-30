#include "buttonplaceroad.hpp"
#include "states/placeroadstate.hpp"

ButtonPlaceRoad::ButtonPlaceRoad(QWidget* parent_) :
    QPushButton(parent_)
{
    setCheckable(true);
    setFixedSize(128, 64);
    setText(tr("Road"));
    connect(this, &QPushButton::clicked, [this](){ emit activated(std::make_shared<PlaceRoadState>()); });
}
