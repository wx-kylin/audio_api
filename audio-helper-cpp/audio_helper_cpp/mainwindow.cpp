#include "mainwindow.h"
#include "mythread.h"
#include "lib_audio_api.h"
#include <QDebug>
#include <QGridLayout>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("audio_helper"));
    mainWidget = new QWidget(this);
    mainWidget->resize(400, 300);
    getLog = new QPushButton();
    getLog->setText(tr("get_log"));
    filePath = new QLineEdit();
    filePath->setText(tr("/home/wangxia/git/audio-helper/audio_api_log.txt"));
    log = new QTextEdit();
    name = new QLabel();
    name->setText(tr("mod_name"));
    mod_name = new QLineEdit();
    mod_name->setText("ukui-control-centor");
    cmd = new QLabel();
    cmd->setText(tr("cmd_name"));
    cmd_name = new QLineEdit();
    cmd_name->setText("1");
    cmdBtn = new QPushButton();
    cmdBtn->setText(tr("cmd exe"));

    QGridLayout *layOut = new QGridLayout(mainWidget);

    layOut->addWidget(name, 0, 0);
    layOut->addWidget(mod_name, 0, 1);
    layOut->addWidget(cmd, 1, 0);
    layOut->addWidget(cmd_name, 1, 1);
    layOut->addWidget(cmdBtn, 2, 1);
    layOut->addWidget(getLog, 3, 0);
    layOut->addWidget(filePath, 3, 1);
    layOut->addWidget(log, 4, 0, 1, 2);
    connect(cmdBtn, SIGNAL(clicked()), this, SLOT(cmdExecute()));
    connect(getLog, SIGNAL(clicked()), this, SLOT(getLogInfo()));

}

void MainWindow::getLogInfo(void)
{
    int ret;
    QString displayString;
    QString path;

    path = filePath->text();
    ret = audio_api_read_module_info((char *)path.toStdString().data());
    QFile file("/home/wangxia/git/audio-helper/audio_api_log.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        qDebug()<< str;
        displayString.append(str);
    }
    log->clear();
    log->setPlainText(displayString);
}

void MainWindow::cmdExecute(void)
{
    qDebug() << mod_name->text();
    MyThread *myThread = new MyThread;
    myThread->name = mod_name->text();
    myThread->cmd = cmd_name->text();
    myThread->start();
//    audio_api_cmd_execute(mod_name->text().toUtf8().data(), cmd_name->text().toInt());
    qDebug() << cmd_name->text();
}

MainWindow::~MainWindow()
{
}

