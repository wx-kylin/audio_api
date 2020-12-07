#include "audioapithread.h"
#include "lib_audio_api.h"
#include "audio_helper_common.h"
#include <QDebug>

AudioApiThread::AudioApiThread()
{

}

void AudioApiThread::run()
{
    int ret;

    audio_helper_version();
    audio_api_get_verison_info();
    ret = audio_api_init();
    qDebug() << "audio_api_init ret = " << ret;
    exec();
    return;
}
