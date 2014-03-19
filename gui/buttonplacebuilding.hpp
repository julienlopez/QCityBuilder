#ifndef BUTTONPLACEBUILDING_HPP
#define BUTTONPLACEBUILDING_HPP

#include <world/buildingtypehandler.hpp>

#include <QPushButton>

#include <memory>

class iState;

class ButtonPlaceBuilding : public QPushButton
{
    Q_OBJECT
public:
    explicit ButtonPlaceBuilding(World::BuildingTypeHandler::type_identifier id, QWidget* parent_ = 0);

signals:
    void activated(std::shared_ptr<iState>);

public slots:

};

#endif // BUTTONPLACEBUILDING_HPP
