#include "mainwindow.hpp"
#include "resourcespanel.hpp"
#include "screen.hpp"
#include "statedock.hpp"

#include <QStatusBar>

MainWindow::MainWindow(World::City* city, QWidget* p)
    : QMainWindow(p)
{
    auto* screen = new Screen(city, this);
    connect(screen, &Screen::displayStatusText, this, &MainWindow::onDisplayStatusText);
    setCentralWidget(screen);
    screen->setMinimumSize(800, 600);

    auto* resourcesDock = new ResourcesPanel(city, this);
    addDockWidget(Qt::TopDockWidgetArea, resourcesDock);

    auto* stateDock = new StateDock;
    addDockWidget(Qt::RightDockWidgetArea, stateDock);
    connect(stateDock, &StateDock::newStateActivated, screen, &Screen::onNewStateActivated);
    connect(screen, &Screen::currentStateCleared, stateDock, &StateDock::clearCurrentState);
}

void MainWindow::onDisplayStatusText(QString text)
{
    statusBar()->showMessage(text);
}
