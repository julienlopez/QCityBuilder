#include "resourcespanel.hpp"

#include <inventorysummary.hpp>

#include <world/city.hpp>

#include <QApplication>
#include <QGridLayout>
#include <QLabel>

ResourcesPanel::ResourcesPanel(World::City* city, QWidget* parent_)
    : QDockWidget(parent_)
    , m_city(city)
{
    auto* w = new QWidget;
    auto* lay = new QGridLayout;

    if(m_city)
    {
        auto inv = m_city->totalInventory();

        const auto& instance = ResourcesHandler::const_instance();
        std::size_t cpt = 0;
        for(auto it = instance.cbegin(); it != instance.cend(); ++it, cpt += 2)
        {
            auto* label = new QLabel(QString::number(inv.amount(it->first)));
            label->setToolTip(QString::fromStdString(it->second));
            m_mapLabels[it->first] = label;
            auto* labelImage = new QLabel;
            const auto path
                = QApplication::applicationDirPath() + QString::fromStdString("/img/" + it->second + ".png").toLower();
            labelImage->setPixmap(path);
            labelImage->setToolTip(QString::fromStdString(it->second));
            lay->addWidget(labelImage, cpt / nbElementsByLine, cpt % nbElementsByLine);
            lay->addWidget(label, (cpt + 1) / nbElementsByLine, (cpt + 1) % nbElementsByLine);
        }
    }

    w->setLayout(lay);
    setWidget(w);
}
