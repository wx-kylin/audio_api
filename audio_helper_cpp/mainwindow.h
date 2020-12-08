#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QWidget>
#include <QLabel>

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void getLogInfo();
    void cmdExecute();

private:
    QWidget *mainWidget;
    QPushButton *getLog;
    QLineEdit *filePath;
    QTextEdit *log;
    QLabel *name;
    QLineEdit *mod_name;
    QLabel *cmd;
    QLineEdit *cmd_name;
    QPushButton *cmdBtn;

};
#endif // MAINWINDOW_H
