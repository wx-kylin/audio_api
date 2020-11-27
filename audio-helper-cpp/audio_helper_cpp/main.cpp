//#include <gio/gio.h>
#include "mainwindow.h"
//#include "lib_audio_api.h"
//#include "audio_helper_common.h"
#include <stdio.h>
#include <string.h>
#include <QApplication>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}

