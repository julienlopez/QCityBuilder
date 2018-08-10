#include "mainwindow.hpp"

#include <resourceshandler.hpp>

#include <world/city.hpp>
#include <world/jsonloader.hpp>

#include <QApplication>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>

std::unique_ptr<World::City> loadTestCity()
{
    auto city = std::make_unique<World::City>("Test", utils::SizeU{50, 50});
    city->addRoad({{0, 5}, {1, 5}, {2, 5}, {3, 5}});
    return city;
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
    std::transform(array.begin(), array.end(), ressources.begin(),
                   [&ressources](const QJsonValue& value) { return value.toString().toStdString(); });
    ResourcesHandler::loadResources(ressources);
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    loadBuildingTypesFromFile("buildings.json");
    loadResourcesFromFile("ressources.json");
    auto city = loadTestCity();

    MainWindow w(city.get());
    w.show();

    return a.exec();
}
