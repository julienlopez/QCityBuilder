#ifndef RESSOURCESPANEL_HPP
#define RESSOURCESPANEL_HPP

#include <ressourceshandler.hpp>

#include <QDockWidget>

#include <QMap>

class QLabel;

class RessourcesPanel : public QDockWidget
{
    Q_OBJECT
public:
    explicit RessourcesPanel(QWidget* parent_ = 0);
    virtual ~RessourcesPanel() = default;

private:
    QMap<RessourcesHandler::type_identifier, QLabel*> m_mapLabels;

    static constexpr std::size_t nbElementsByLine = 4;
};

#endif // RESSOURCESPANEL_HPP
