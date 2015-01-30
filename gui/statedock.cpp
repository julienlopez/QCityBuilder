#include "statedock.hpp"
#include "buttonplacebuilding.hpp"
#include "buttonplaceroad.hpp"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include <QButtonGroup>

StateDock::StateDock(QWidget* parent_) :
    QDockWidget(parent_)
{
    m_buildingButtons = new QButtonGroup(this);
    m_buildingButtons->setExclusive(true);

    setMinimumWidth(200);
    auto* vl = new QVBoxLayout;

    vl->addWidget(createBuildingGroupBox());
    vl->addWidget(createUtilsGroupBox());

    vl->addStretch();

    auto* w = new QWidget;
    w->setLayout(vl);
    setWidget(w);
}

void StateDock::clearCurrentState()
{
    auto* b = m_buildingButtons->checkedButton();
    m_buildingButtons->setExclusive(false);
    b->setChecked(false);
    m_buildingButtons->setExclusive(true);
}

QGroupBox* StateDock::createBuildingGroupBox() const
{
    auto* gb = new QGroupBox(tr("Buildings"));
    auto* gl = new QGridLayout;

    int i = 0;
    for(const auto& pair : World::BuildingTypeHandler::instance())
    {
        auto* b = new ButtonPlaceBuilding(pair.first);
        connect(b, &ButtonPlaceBuilding::activated, this, &StateDock::newStateActivated);
        m_buildingButtons->addButton(b);
        gl->addWidget(b, i/3, i%3);
        ++i;
    }

    gb->setLayout(gl);
    return gb;
}

QGroupBox* StateDock::createUtilsGroupBox() const
{
    auto* gb = new QGroupBox(tr("Utilities"));
    auto* gl = new QGridLayout;

    int i = 0;
    auto* b = new ButtonPlaceRoad;
    connect(b, &ButtonPlaceRoad::activated, this, &StateDock::newStateActivated);
    m_buildingButtons->addButton(b);
    gl->addWidget(b, i/3, i%3);

    gb->setLayout(gl);
    return gb;
}
