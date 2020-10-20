#include "mainwindow.h"
#include <QApplication>
#include "mythread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyThread * thread=new MyThread;
    QObject::connect(thread, &MyThread::finished, thread, &QObject::deleteLater);

    //쓰레드 시작
    thread->start();
/*
    QTimer::singleShot(3000, &a, [thread]()
    {

        //3초후에 쓰레드 중단을 요청
        thread->requestInterruption();

    });*/
    MainWindow w;
    w.show();

    return a.exec();
}
