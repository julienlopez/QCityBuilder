#include "buttonplacebuilding.hpp"
#include "states/placebuildingstate.hpp"

ButtonPlaceBuilding::ButtonPlaceBuilding(World::BuildingTypeHandler::type_identifier id, QWidget* parent_)
    : QPushButton(parent_)
{
    setCheckable(true);
    setFixedSize(128, 128);
    const auto& bt = World::BuildingTypeHandler::instance().get(id);
    setText(QString::fromStdString(bt.name));
    connect(this, &QPushButton::clicked, [this, id]() { emit activated(std::make_shared<PlaceBuildingState>(id)); });
}
