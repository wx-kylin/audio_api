#ifndef AUDIOAPITHREAD_H
#define AUDIOAPITHREAD_H
#include <QThread>

class AudioApiThread : public QThread
{
public:
    AudioApiThread();
    void run();
};

#endif // AUDIOAPITHREAD_H
