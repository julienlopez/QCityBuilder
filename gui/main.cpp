#include "mainwindow.hpp"

#include <world/currentcityholder.hpp>

#include <QApplication>

void loadTestCity()
{
    World::CurrentCityHolder::initialize("Test", {50, 50});
    auto& city = World::CurrentCityHolder::get();
    city.addRoad({{0,5}, {1,5}, {2,5}, {3,5}});
}

int main(int argc, char *argv[])
{
    loadTestCity();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
