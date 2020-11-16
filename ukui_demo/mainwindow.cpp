#include "mainwindow.h"
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusInterface>
#include <QDebug>

#define AUDIO_API_MODULE_NAME_LEN 32

struct module_register {
    char module_name[AUDIO_API_MODULE_NAME_LEN];
    char api[32];
    char dbus_path[128];
    int need_time;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    widget = new QWidget(this);
    setCentralWidget(widget);
    QString name, api, dbus;
    int need_time = 0;

    //session bus 会话总线
    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    if(sessionBus.registerService("org.ukui.module")){
        sessionBus.registerObject("/org/ukui/module",this,
                                  QDBusConnection::ExportAllContents);
    }
    qDebug() << "call audio_api dbus";

    QDBusInterface interface( "org.ukui.audio_api", "/org/ukui/audio_api","org.ukui.audio_api", QDBusConnection::sessionBus());
    QDBusReply<int> reply = interface.call( "module_register", "ukui-control-centor", "ukui_module_exe_cmd_api", \
                                                "org.ukui.module", "/org/ukui/module", "local.ukui_demo.MainWindow", 0);
    if ( reply.isValid() && reply.value() == 0) {
        qDebug( "%d", reply.value());          // prints 4
    } else {
        qDebug() << "fail";
    }

    reply = interface.call( "cmd_register", "ukui-control-centor", 5, "cmd5");
    if ( reply.isValid() && reply.value() == 0) {
        qDebug( "%d", reply.value());          // prints 4
    } else {
        qDebug() << "fail";
    }
    qDebug() << "end";

    reply = interface.call( "mod_register_finish", "ukui-control-centor");
    if ( reply.isValid() && reply.value() == 0) {
        qDebug( "%d", reply.value());          // prints 4
    } else {
        qDebug() << "fail";
    }

    qDebug() << "end";

}
int MainWindow::ukui_module_exe_cmd_api(int cmd)
{
    qDebug() << "ukui_module_exe_cmd_api in";
    QDBusInterface interface( "org.ukui.audio_api", "/org/ukui/audio_api","org.ukui.audio_api", QDBusConnection::sessionBus());
    QDBusReply<int> reply = interface.call( "cmd_execute_result", "ukui-control-centor", 0, "ok");
    if ( reply.isValid() && reply.value() == 0) {
        qDebug( "%d", reply.value());          // prints 4
    } else {
        qDebug() << "fail";
    }
    return 0;
}

MainWindow::~MainWindow()
{
}

