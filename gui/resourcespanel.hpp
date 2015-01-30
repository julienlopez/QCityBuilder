#ifndef RESOURCESPANEL_HPP
#define RESOURCESPANEL_HPP

#include <resourceshandler.hpp>

#include <QDockWidget>

#include <QMap>

class QLabel;

class ResourcesPanel : public QDockWidget
{
    Q_OBJECT
public:
    explicit ResourcesPanel(QWidget* parent_ = 0);
    virtual ~ResourcesPanel() = default;

private:
    QMap<ResourcesHandler::type_identifier, QLabel*> m_mapLabels;

    static constexpr std::size_t nbElementsByLine = 4;
};

#endif // RESOURCESPANEL_HPP
