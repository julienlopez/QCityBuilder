#ifndef CITYSCENE_HPP
#define CITYSCENE_HPP

#include <QGraphicsScene>

class CityScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CityScene(QObject* p = 0);
    virtual ~CityScene() = default;

    void initScene();

    static const std::size_t s_resolution;

signals:

public slots:

};

#endif // CITYSCENE_HPP
