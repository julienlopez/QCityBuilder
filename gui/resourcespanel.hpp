#ifndef RESOURCESPANEL_HPP
#define RESOURCESPANEL_HPP

#include <resourceshandler.hpp>

#include <QDockWidget>

#include <QMap>

namespace World
{
class City;
}

class QLabel;

class ResourcesPanel : public QDockWidget
{
    Q_OBJECT
public:
    explicit ResourcesPanel(World::City* city, QWidget* parent_ = nullptr);
    virtual ~ResourcesPanel() = default;

private:
    World::City* m_city;
    QMap<ResourcesHandler::type_identifier, QLabel*> m_mapLabels;

    static constexpr std::size_t nbElementsByLine = 4;
};

#endif // RESOURCESPANEL_HPP
