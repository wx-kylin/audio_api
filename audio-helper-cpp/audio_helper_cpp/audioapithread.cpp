#include "audioapithread.h"
#include "lib_audio_api.h"
#include "audio_helper_common.h"
#include <QDebug>
//#include <QCoreApplication>
#include <QDir>
AudioApiThread::AudioApiThread()
{

}

void AudioApiThread::run()
{
    int ret;

    audio_helper_version();
    audio_api_get_verison_info();
//    QString fileName = QCoreApplication::applicationDirPath();

    QString cfgFile = QDir::homePath();
    cfgFile += "/.config/audio_api_cfg.txt";
    qDebug() << "cfg file path is " << cfgFile;
    ret = audio_api_init((char *)cfgFile.toStdString().data());
    qDebug() << "audio_api_init ret = " << ret;
    exec();
    return;
}
