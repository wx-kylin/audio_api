#include "mythread.h"
#include "lib_audio_api.h"
#include <QDebug>

MyThread::MyThread()
{

}

void MyThread::run()
{
    int ret;
    qDebug() << "run start";
    qDebug() << name << cmd;
    ret = audio_api_cmd_execute(name.toUtf8().data(), cmd.toInt());
    qDebug() << "run end, ret = " << ret;

}
