#include "mainwindow.hpp"
#include "screen.hpp"
#include "cityscene.hpp"

MainWindow::MainWindow(QWidget* p): QMainWindow(p)
{
    auto* screen = new Screen(new CityScene);
    setCentralWidget(screen);
    setMinimumSize(800, 600);
}

MainWindow::~MainWindow()
{

}
