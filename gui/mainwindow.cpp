#include "mainwindow.hpp"
#include "screen.hpp"
#include "statedock.hpp"
#include "ressourcespanel.hpp"

#include <QStatusBar>

MainWindow::MainWindow(QWidget* p): QMainWindow(p)
{
    auto* screen = new Screen;
    connect(screen, &Screen::displayStatusText, this, &MainWindow::onDisplayStatusText);
    setCentralWidget(screen);
    screen->setMinimumSize(800, 600);

    auto* ressourcesDock = new RessourcesPanel;
    addDockWidget(Qt::TopDockWidgetArea, ressourcesDock);

    auto* stateDock = new StateDock;
    addDockWidget(Qt::RightDockWidgetArea, stateDock);
    connect(stateDock, &StateDock::newStateActivated, screen, &Screen::onNewStateActivated);
    connect(screen, &Screen::currentStateCleared, stateDock, &StateDock::clearCurrentState);
}

void MainWindow::onDisplayStatusText(QString text)
{
    statusBar()->showMessage(text);
}
