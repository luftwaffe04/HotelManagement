#ifndef SECDIALOG101_H
#define SECDIALOG101_H

#include <QDialog>
#include <QMainWindow>
#include <QTimer>
#include <QDebug>
//#include "mainwindow.h"

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

namespace Ui {
class SecDialog101;
//static int reserve_state;
//static int room_id;
}

class SecDialog101 : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog101(QWidget *parent = nullptr);
    ~SecDialog101();
    int reserve_check;

signals:
    void sendData(int reserve_check, QString name, int phone, int room, int total_human, int total_date, int total_count);
public slots:
    void dButtonClick();
    void client_check_function(int client_check);
private slots:
    //int state_cheked();
    void on_calendarWidget_clicked(const QDate &date);


    //void on_pushButton_reservation_apply_clicked();

    void on_pushButton_reservation_cancel_clicked();
    //void state_cheked();
    void on_pushButton_reservation_apply_clicked();

public:
    int client_check_;//mainWindow로 부터 데이터를 전송받는 변수

    int room_check;
    QString name;
    int phone;
    int room;
    int total_human;
    int total_date;

    int year01;
    int year02;
    int month01;
    int month02;
    int date01;
    int date02;

    int total_count;



private:
    QTimer * timer_sec;
    Ui::SecDialog101 *ui;


};

#endif // SECDIALOG101_H
