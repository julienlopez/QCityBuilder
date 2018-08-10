#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace World
{
class City;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(World::City* city, QWidget* p = nullptr);

    virtual ~MainWindow() = default;

private slots:
    void onDisplayStatusText(QString text);
};

#endif // MAINWINDOW_HPP
