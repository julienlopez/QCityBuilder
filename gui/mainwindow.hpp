#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* p = 0);
    virtual ~MainWindow() = default;

private slots:
    void onDisplayStatusText(QString text);
};

#endif // MAINWINDOW_HPP
