#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGSettings>
#include <QMainWindow>
#include <QDBusInterface>
#include <QDBusConnection>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ukui_module_dbus_reg(void);

public Q_SLOTS:
    int ukui_module_exe_cmd_api(int cmd);
    void ukui_module_register(QString key);

private:
    QWidget *widget;
    QGSettings *mAudioApiInitSetting;
};
#endif // MAINWINDOW_H
