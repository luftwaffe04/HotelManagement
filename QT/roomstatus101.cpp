#include "roomstatus101.h"
#include "ui_roomstatus101.h"

RoomStatus101::RoomStatus101(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomStatus101)
{
    ui->setupUi(this);

   /* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(status_change()));
    timer -> start(1000);
    */
   /*  temp_=0;
     humi_=0;
     fire_=1000;
     gas_=500;*/
}

RoomStatus101::~RoomStatus101()
{
    delete ui;
}

void RoomStatus101::room_check_function(int temp, int humi, int fire, int gas)
{
    temp_=temp;
   // qDebug() <<"TEMP: "<<temp_<<endl;


    humi_=humi;

    //qDebug() <<"HUMI: "<<humi_<<endl;
    fire_=fire;

   // qDebug() <<"FIRE: "<<fire_<<endl;
    gas_ =gas;

    //qDebug() <<"gas: "<<gas_<<endl;

    ui->lcdNumber_Temp->display(temp_);

    //qDebug() <<"TEMPCHECK"<<endl;
    ui->lcdNumber_Humi->display(humi_);
//qDebug() <<"HUMICHECK"<<endl;
    if(fire_<2000)
        ui->progressBar_Fire->setValue(100);
    else {
        ui->progressBar_Fire->setValue(0);
    }
//qDebug() <<"FIRECHECK"<<endl;
    if(gas_>2500)
        ui->progressBar_Gas->setValue(100);
    else {
        ui->progressBar_Gas->setValue(0);
    }
//qDebug() <<"GASCHECK"<<endl;


}


