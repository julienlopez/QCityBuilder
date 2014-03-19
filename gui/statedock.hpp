#ifndef STATEDOCK_HPP
#define STATEDOCK_HPP

#include <QDockWidget>

#include <memory>

class iState;

class QGroupBox;
class QButtonGroup;

class StateDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit StateDock(QWidget* parent_ = 0);

signals:
    void newStateActivated(std::shared_ptr<iState>);

public slots:

private:
    QButtonGroup* m_buildingButtons;

    QGroupBox* createBuildingGroupBox() const;

};

#endif // STATEDOCK_HPP
