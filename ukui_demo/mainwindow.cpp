#include "mainwindow.h"
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusInterface>
#include <QDebug>

#define AUDIO_API_MODULE_NAME_LEN 32
#define SETTINGS_AUDIO_API_SCHEMAS "org.ukui.audio_api"

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
    widget->setFixedSize(200,200);
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

    ukui_module_dbus_reg();

    mAudioApiInitSetting = new QGSettings(SETTINGS_AUDIO_API_SCHEMAS);
    connect(mAudioApiInitSetting,SIGNAL(changed(QString)),this,SLOT(ukui_module_register(QString)));
    qDebug() << "end";

}
void MainWindow::ukui_module_dbus_reg(void)
{
    QDBusInterface interface( "org.ukui.audio_api", "/org/ukui/audio_api","org.ukui.audio_api", QDBusConnection::sessionBus());
    QDBusReply<int> reply = interface.call( "module_register", "ukui_demo", "ukui_module_exe_cmd_api", \
                                                "org.ukui.module", "/org/ukui/module", "local.ukui_demo.MainWindow", 0);
    if ( reply.isValid() && reply.value() == 0) {
        qDebug( "%d", reply.value());          // prints 4
    } else {
        qDebug() << "fail";
        return;
    }

    reply = interface.call( "cmd_register", "ukui_demo", 5, "cmd5");
    if ( reply.isValid() && reply.value() == 0) {
        qDebug( "%d", reply.value());          // prints 4
    } else {
        qDebug() << "fail";
    }


    reply = interface.call( "mod_register_finish", "ukui_demo");
    if ( reply.isValid() && reply.value() == 0) {
        qDebug( "%d", reply.value());          // prints 4
    } else {
        qDebug() << "fail";
    }
}

void MainWindow::ukui_module_register(QString key)
{
    qDebug() << "call audio_api dbus in register";
    ukui_module_dbus_reg();
    qDebug() << "end";
}

int MainWindow::ukui_module_exe_cmd_api(int cmd)
{
    qDebug() << "ukui_module_exe_cmd_api in";
    QDBusInterface interface( "org.ukui.audio_api", "/org/ukui/audio_api","org.ukui.audio_api", QDBusConnection::sessionBus());
    QDBusReply<int> reply = interface.call( "cmd_execute_result", "ukui_demo", 0, "ok");
    if ( reply.isValid() && reply.value() == 0) {
        qDebug( "%d", reply.value());          // prints 4
    } else {
        qDebug() << "fail";
    }
    return 0;
}

MainWindow::~MainWindow()
{
    if (mAudioApiInitSetting) {
        delete mAudioApiInitSetting;
    }
}

