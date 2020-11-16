#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDBusInterface>
#include <QDBusConnection>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOTS:
    int ukui_module_exe_cmd_api(int cmd);
private:
    QWidget *widget;
};
#endif // MAINWINDOW_H
