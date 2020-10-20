#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secdialog101.h"
#include "roomstatus101.h"


#include "unistd.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cameraRunning(false)
{
    ui->setupUi(this);

    QPixmap pix("/home/pi/samba/screen2.jpg");
    int w = ui ->label_Screen2->width();
    int h = ui ->label_Screen2->height();
    ui->label_Screen2->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    ui->label_Screen3->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    ui->label_Screen4->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    QPixmap pix2("/home/pi/samba/haha.png");
    int w_2 = ui ->label_Haha->width();
    int h_2 = ui ->label_Haha->height();
    ui->label_Haha->setPixmap(pix2.scaled(w_2,h_2, Qt::KeepAspectRatio));
    //roomStatus101 = new RoomStatus101(this);

    //소켓관련
    //socket = new QUdpSocket(this);
    //socket->bind(QHostAddress("192.168.10.140"),1234);
    //connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    //serial관련
    port = new QSerialPort(this);
    //foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    //{
    //    port->setPortName(serialPortInfo.portName());
    //}
    port->setPortName("ttyACM0");
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);

    if(!port->open(QIODevice::ReadWrite))
        qDebug() << "\n Serial Port open Error !!\n";
    else
        qDebug() << "\n Serial Port open Success !!\n ";

    connect(port, SIGNAL(readyRead()), this, SLOT(text_Reading()));
    //on_pushButton_Scan_clicked();
    //소켓관련 임시변수초기화
    temp_tmp = 28;
    humi_tmp = 0;
    fire_tmp =0;
    gas_tmp =0;
    roomStatus101 = new RoomStatus101(this);

    //on_pushButton_client101_clicked
    connect(ui->pushButton_client101, SIGNAL(clicked()), this, SLOT(client_ButtonClick()));
    // SQL Preset
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("hotelmaster");
    db.setPassword("1234");
    db.setPort(3306);
    db.setDatabaseName("hahahotel");

    // DB Open
    if(db.open()) {
        qDebug() << "DB Connected";
    }
    else {
        qDebug() << "Error : DB Connect";
    }

    check_point = 0;

    //타이머 생성
    timer = new QTimer(this);
    //타이머가 타임아웃이 되면 tupdate()호출
    connect(timer, SIGNAL(timeout()), this, SLOT(tupdate()));
    //1000은 밀리세컨드 단위, 타임아웃을 몇ms로 할것인지 정함(1초에 한번)
    timer->start(100);
}
//고객정보 버튼을 누르면 이함수로 진입함
void MainWindow::client_ButtonClick()
{
    secDialog101 = new SecDialog101(this);
    client_check = 101; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}


int MainWindow::tupdate()
{
    QDateTime local(QDateTime::currentDateTime());
    //ui -> dateTimeEdit->setTime(local.toString());
    ui -> lineEdit_time->setText(local.toString());


    QSqlQuery query("select room_id, reserve_state from reserve"); // query에 select 구문 저장
    if(!query.isActive()) {
        qDebug() << "Query Error : " + query.lastError().text();
    }
    else while(query.next()) {
        // 쿼리 실행
        if(query.value(1).toInt()) {
            // reserve_state == 1이면
            switch (query.value(0).toInt()) {
                case 101: ui -> checkBox_101 ->setChecked(true); break;
                case 102: ui -> checkBox_102 ->setChecked(true); break;
                case 103: ui -> checkBox_103 ->setChecked(true); break;
                case 104: ui -> checkBox_104 ->setChecked(true); break;
                case 105: ui -> checkBox_105 ->setChecked(true); break;
                case 201: ui -> checkBox_6 ->setChecked(true); break;
                case 202: ui -> checkBox_7 ->setChecked(true); break;
                case 203: ui -> checkBox_8 ->setChecked(true); break;
                case 204: ui -> checkBox_9 ->setChecked(true); break;
                case 205: ui -> checkBox_10 ->setChecked(true); break;
            }
        }
        else {
            // reserve_state == 0이면
            switch (query.value(0).toInt()) {
                case 101: ui -> checkBox_101 ->setChecked(false); break;
                case 102: ui -> checkBox_102 ->setChecked(false); break;
                case 103: ui -> checkBox_103 ->setChecked(false); break;
                case 104: ui -> checkBox_104 ->setChecked(false); break;
                case 105: ui -> checkBox_105 ->setChecked(false); break;
                case 201: ui -> checkBox_6 ->setChecked(false); break;
                case 202: ui -> checkBox_7 ->setChecked(false); break;
                case 203: ui -> checkBox_8 ->setChecked(false); break;
                case 204: ui -> checkBox_9 ->setChecked(false); break;
                case 205: ui -> checkBox_10 ->setChecked(false); break;
            }
        }
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::reserve_check_function(    int reserve_check,
                                            QString name,
                                            int phone,
                                            int room,
                                            int total_human,
                                            int total_date,
                                            int total_count )
{

//    if(reserve_check == 1)
//        ui -> checkBox_101 ->setChecked(true);
//    else
//        ui -> checkBox_101 ->setChecked(false);
    name_ =name;
    qDebug()<<"Main - 이름:"<<name<<endl;
    phone_=phone;
    qDebug()<<"Main - 전화번호:"<<phone<<endl;
    room_ = room;
    qDebug()<<"Main - 방번호:"<<room<<endl;
    total_human_=total_human;
    qDebug()<<"Main - 총 인원:"<<total_human<<endl;
    total_date_ = total_date;
    qDebug()<<"Main - 총 일수:"<<total_date<<endl;
    total_count_ =total_count;
    qDebug()<<"Main - 총가격:"<<total_count<<endl;
}
/*
void MainWindow::on_pushButton_client101_clicked()
{
    secDialog101 = new SecDialog101(this);
    secDialog101->setModal(true);
    secDialog101->show();
}
*/
void MainWindow::on_pushButton_status101_clicked()
{
   /* mydialog101 = new MyDialog101(this);
    mydialog101 -> setModal(true);
    mydialog101 -> show();*/

    //roomStatus101 = new RoomStatus101(this);
    roomStatus101 ->setModal(true);
    roomStatus101->show();

}

void MainWindow::on_btnStart_clicked()
{
    workerThread = new QThread;
    worker = new CameraWorker;
    if(cameraRunning)
    {
        return;
    }
    // Setup the thread
    worker->moveToThread(workerThread);

    // Connect signals to slots
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), this, SLOT(cameraFinished()));
    connect(worker, SIGNAL(handleImage(QImage &)), this, SLOT(handleImage(QImage &)));
    connect(ui->btnStop, SIGNAL(clicked()), worker, SLOT(stopWork()));
    workerThread->start();

    // Update the running flag
    cameraRunning = true;

    // Disable the start button, enable the stop button
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}
void MainWindow::handleImage(QImage &image)
{
    // Update the image shown
    ui->imgLabel->setPixmap(QPixmap::fromImage(image));

    // Force an update of the UI so that the image is shown immediately.
    QApplication::processEvents();
    this->repaint();
}

void MainWindow::cameraFinished()
{
    // Update running flag
    cameraRunning = false;

    // Disable the stop button, enable the start button
    ui->btnStop->setEnabled(false);
    ui->btnStart->setEnabled(true);

    // Reset the image label
    ui->imgLabel->setText("Camera Disabled");
}

void MainWindow::on_pushButton_checkout101_clicked()
{
    ui->progressBar_101->setValue(0);
    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='101'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_client102_clicked()
{
    secDialog101 = new SecDialog101(this);
    client_check = 102; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}

void MainWindow::on_pushButton_client103_clicked()
{
    secDialog101 = new SecDialog101(this);
    client_check = 103; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}

void MainWindow::on_pushButton_client104_clicked()
{
    secDialog101 = new SecDialog101(this);
    client_check = 104; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}

void MainWindow::on_pushButton_client105_clicked()
{
    secDialog101 = new SecDialog101(this);
    client_check = 105; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}

void MainWindow::on_pushButton_client201_clicked()
{
    secDialog101 = new SecDialog101(this);
    client_check = 201; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}

void MainWindow::on_pushButton_client202_clicked()
{
    secDialog101 = new SecDialog101(this);
    client_check = 202; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}

void MainWindow::on_pushButton_client203_clicked()
{
    secDialog101 = new SecDialog101(this);
    client_check = 203; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}

void MainWindow::on_pushButton_client204_clicked()
{
    secDialog101 = new SecDialog101(this);
    client_check = 204; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}

void MainWindow::on_pushButton_client205_clicked()
{
    secDialog101 = new SecDialog101(this);
    client_check = 205; // mainwindow.h에 public으로 선언된 전역변수
    //mainwindow의 sendData2와 secdialog101의 client_check_function연결
    connect(this, SIGNAL(sendData_2(int)), secDialog101, SLOT(client_check_function(int)));
    emit sendData_2(client_check);
    secDialog101->setModal(true);
    secDialog101->show();
}

void MainWindow::on_pushButton_checkout102_clicked()
{
    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='102'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_checkout103_clicked()
{
    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='103'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_checkout104_clicked()
{
    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='104'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_checkout105_clicked()
{
    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='105'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_checkout201_clicked()
{
    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='201'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_checkout202_clicked()
{
    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='202'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_checkout203_clicked()
{
    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='203'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_checkout204_clicked()
{
    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='204'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_checkout205_clicked()
{

    QString uq = "update reserve set reserve_state='0', name='NaN', password='NaN', chkin=NULL, chkout=NULL, crew='0', telephone=NULL where room_id='205'";

    QSqlQuery query(uq);
    query.exec();
}

void MainWindow::on_pushButton_checkin101_clicked()
{
    ui->progressBar_101->setValue(100);
}

void MainWindow::text_Reading()
{

    QList <QByteArray> bufferList;
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;
    char Data_check[50], TMP[4], WET[4], FIR[4], GAS[4];

    while (port->canReadLine())
    {
        bufferList.append(port->readLine());
    }
    for(QByteArray buffer2:bufferList)
    {
        //ui->textEdit->append(buffer2);     //차곡차곡 Data를 쌓는다. append:덧붙이다.
        //ui->textEdit->show();

        //textedit 스크롤이 저절로 내려가도록 설정
        //QTextCursor cursor = ui->textEdit->textCursor();
        //cursor.movePosition(QTextCursor::End);
        //ui->textEdit->setTextCursor(cursor);


        //qDebug() <<buffer2;
        data = QString(buffer2);
        //qDebug() <<data;
    }

    datalist = data.split(":");

    datalist[0].remove(0,5);
    datalist[1].remove(0,5);
    datalist[2].remove(0,5);
    datalist[3].remove(0,4);

    temp = datalist[0].toInt();
    humi = datalist[1].toInt();
    fire = datalist[2].toInt();
    gas  = datalist[3].toInt();
    if((20<=temp) && (temp <=35))
    {
       temp_tmp = temp;
    }
    else {
        temp = temp_tmp;
    }

    if(gas>2500)
        ui->label_first->setText("101호에서 가스가 감지되었습니다.!!");
    else {
        ui->label_first->setText("Have a nice Day~!!");
    }

//#if 1
    /*
    QList <QByteArray> receivedList;    //QByteArray 자료들을 담는 리스트
    char DHT[20], Tmp_ch[4], Wet_ch[4];

    while(port->canReadLine())    //new line(Enter키, 줄바꿈)를 만날때까지
    {
        receivedList.append(port->readLine());
    }
    for(QByteArray received : receivedList)
    {
        sprintf(DHT, "%s", received.data());




        ui->textEdit->append(received);     //차곡차곡 Data를 쌓는다. append:덧붙이다.
        ui->textEdit->show();

        //textedit 스크롤이 저절로 내려가도록 설정
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->textEdit->setTextCursor(cursor);

        qDebug() << received;
    }*/
    //temp =1 , humi =1, fire =1, gas = 1;
    connect(this,SIGNAL(sendData_3(int,int,int,int)), roomStatus101,SLOT(room_check_function(int,int,int,int)));
    emit sendData_3(temp,humi,fire,gas);
}
/*
void MainWindow::text_Reading()
{
    QList <QByteArray> bufferList;
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;
    char Data_check[50], TMP[4], WET[4], FIR[4], GAS[4];

    //buffer.resize(port->pendingDatagramSize());


   // socket->readDatagram(buffer.data(), buffer.size(),
                        // &sender, &senderPort);

    while (port->canReadLine())
    {
        bufferList.append(port->readLine());
    }
    for(QByteArray buffer2:bufferList)
    {
        qDebug() <<buffer2;
        data = QString(buffer2);
    }
    datalist = data.split(":");

    datalist[0].remove(0,5);
    datalist[1].remove(0,5);
    datalist[2].remove(0,5);
    datalist[3].remove(0,4);

    temp = datalist[0].toInt();
    humi = datalist[1].toInt();
    fire = datalist[2].toInt();
    gas  = datalist[3].toInt();

    if(gas>2500)
        ui->label_first->setText("101호에서 가스가 감지되었습니다.!!");
    else {
        ui->label_first->setText("Have a nice Day~!!");
    }


    sprintf(Data_check, "%s", buffer.data());
    if(!strncmp(Data_check, "TEMP_", strlen("TEMP_")))
    {

        strcpy(TMP, Data_check+5);
        temp = atoi(TMP);
        temp_tmp=temp;
        //ui->lineEdit_Temp->setText(QString::number(temp));
        qDebug() <<"CheckTEMP:"<< temp<<endl;
    }
    else {
        temp=temp_tmp;
    }
    if(!strncmp(Data_check, "HUMI_", strlen("HUMI_")))
    {
        //qDebug() <<"Checkhumi"<<endl;
        strcpy(WET, Data_check+5);
        humi = atoi(WET);
        humi_tmp = humi;
        //ui->lineEdit_Humi->setText(QString::number(humi));
    }
    else {
        humi=humi_tmp;
    }
    if(!strncmp(Data_check, "FIRE_", strlen("FIRE_")))
    {
        //qDebug() <<"CheckFIRE"<<endl;
        strcpy(FIR, Data_check+5);
        fire = atoi(FIR);
        fire_tmp =fire;
       // ui->lineEdit_Fire->setText(QString::number(fire));
    }
    else {
        fire=fire_tmp;
    }
    if(!strncmp(Data_check, "GAS_", strlen("GAS_")))
    {
       // qDebug() <<"CheckGAS"<<endl;
        strcpy(GAS, Data_check+4);
        gas = atoi(GAS);
        gas_tmp = gas;
        //ui->lineEdit_Gas->setText(QString::number(gas));
    }
    else {
        gas=gas_tmp;;
    }
   // qDebug() <<"Message from: "<<sender.toString();
   // qDebug() <<"Message port: "<<senderPort;
   // qDebug() <<"Message: " <<buffer;
    //ui->lineEdit->setText(buffer);
    //ui->textEdit->append(buffer);     //차곡차곡 Data를 쌓는다. append:덧붙이다.
    //ui->textEdit->show();

    connect(this,SIGNAL(sendData_3(int,int,int,int)), roomStatus101,SLOT(room_check_function(int,int,int,int)));
    emit sendData_3(temp,humi,fire,gas);
}
*/

