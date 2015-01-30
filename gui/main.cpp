#include "mainwindow.hpp"

#include <world/currentcityholder.hpp>
#include <world/jsonloader.hpp>
#include <resourceshandler.hpp>

#include <QApplication>
#include <QDir>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>

void loadTestCity()
{
    World::CurrentCityHolder::initialize("Test", {50, 50});
    auto& city = World::CurrentCityHolder::get();
    city.addRoad({{0,5}, {1,5}, {2,5}, {3,5}});
}

void loadBuildingTypesFromFile(QString fileName)
{
    fileName = QDir(QApplication::applicationDirPath()).filePath(fileName);
    assert(QFile::exists(fileName));
    QFile f(fileName);
    bool ok = f.open(QIODevice::ReadOnly);
    assert(ok);
    QTextStream stream(&f);
    QString json = stream.readAll();
    auto array = World::JsonLoader::stringToJsonArray(json.toStdString());
    for(const auto& o : array)
    {
        World::BuildingTypeHandler::instance().add(World::JsonLoader::parseBuildingType(o.toObject()));
    }
}

void loadResourcesFromFile(QString fileName)
{
    fileName = QDir(QApplication::applicationDirPath()).filePath(fileName);
    assert(QFile::exists(fileName));
    QFile f(fileName);
    bool ok = f.open(QIODevice::ReadOnly);
    assert(ok);
    QTextStream stream(&f);
    QString json = stream.readAll();
    auto array = World::JsonLoader::stringToJsonArray(json.toStdString());
    std::vector<std::string> ressources(array.size());
    std::transform(array.begin(), array.end(), ressources.begin(), [&ressources](const QJsonValue& value){ return value.toString().toStdString(); });
    ResourcesHandler::loadResources(ressources);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loadBuildingTypesFromFile("buildings.json");
    loadResourcesFromFile("ressources.json");
    loadTestCity();

    MainWindow w;
    w.show();

    return a.exec();
}
