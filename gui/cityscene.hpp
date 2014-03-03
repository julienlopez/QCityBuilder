#ifndef CITYSCENE_HPP
#define CITYSCENE_HPP

#include <QGraphicsScene>

class CityScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CityScene(QObject* p = 0);
    virtual ~CityScene();

signals:

public slots:

};

#endif // CITYSCENE_HPP
