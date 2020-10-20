#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <stdio.h>
#include <QImage>
#include <QThread>
#include "secdialog101.h"
#include "roomstatus101.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QPixmap>

#include "mydialog101.h"


//소켓통신 관련 헤더
#include <QtCore>
#include <QtNetwork>
#include <QString>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/qserialport.h>


/*
 * Update Detail
 * Date : 20-10-05
 * Worker : Park Dong-sung
 * Detail : SQL Header
*/
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QtSql/QtSql>

#include "cameraworker.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int client_check;

    QSerialPort *port;
    QString name_;
    int phone_;
    int room_;
    int total_human_;
    int total_date_;

    int year01_;
    int year02_;
    int month01_;
    int month02_;
    int date01_;
    int date02_;


    int total_count_;
private:
    QTimer *timer;

private slots:
    int tupdate();

    //void on_pushButton_client101_clicked();
    void on_pushButton_status101_clicked();


    //CCTV slot
    void handleImage(QImage &image);
    void on_btnStart_clicked();
    void cameraFinished();

    void on_pushButton_checkout101_clicked();

    void on_pushButton_client102_clicked();

    void on_pushButton_client103_clicked();

    void on_pushButton_client104_clicked();

    void on_pushButton_client105_clicked();

    void on_pushButton_client201_clicked();

    void on_pushButton_client202_clicked();

    void on_pushButton_client203_clicked();

    void on_pushButton_client204_clicked();

    void on_pushButton_client205_clicked();

    void on_pushButton_checkout102_clicked();

    void on_pushButton_checkout103_clicked();

    void on_pushButton_checkout104_clicked();

    void on_pushButton_checkout105_clicked();

    void on_pushButton_checkout201_clicked();

    void on_pushButton_checkout202_clicked();

    void on_pushButton_checkout203_clicked();

    void on_pushButton_checkout204_clicked();

    void on_pushButton_checkout205_clicked();

    void on_pushButton_checkin101_clicked();

   // void on_pushButton_Scan_clicked();

   // void on_pushButton_Connect_clicked();

public slots:
    void client_ButtonClick();
    void reserve_check_function(int reserve_check, QString name, int phone, int room, int total_human, int total_date, int total_count);
    //void recData(int str);
    void text_Reading();

signals:
    void sendData_2(int client_check);
    void sendData_3(int temp, int humi, int fire, int gas); //메인에서 방상태창으로 데이터를 보내는함수

private:
    Ui::MainWindow *ui;
    SecDialog101 * secDialog101;    //예약상태 dialog창
    RoomStatus101 * roomStatus101;  //방상태 dialog창

    MyDialog101 * mydialog101;

    int check_point;
    bool cameraRunning;
    QThread *workerThread;
    CameraWorker *worker;

    QUdpSocket *socket;
    int temp;
    int humi;
    int fire;
    int gas;

    int temp_tmp;
    int humi_tmp;
    int fire_tmp;
    int gas_tmp;

    QString data;
    QList <QString> datalist;




};

#endif // MAINWINDOW_H
