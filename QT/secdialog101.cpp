#include "secdialog101.h"
#include "ui_secdialog101.h"
//#include "ui_mainwindow.h"
//#include "mainwindow.h"

SecDialog101::SecDialog101(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog101)
{
    ui->setupUi(this);

    //OK버튼 클릭시 dButtonClick함수를 호출
    connect(ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(dButtonClick()));

    //reserve_check = 0;
    //  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(state_checked()));
    //timer_sec = new QTimer(this);
    //타이머가 타임아웃이 되면 tupdate()호출
    // connect(timer_sec, SIGNAL(timeout()), this, SLOT(state_checked()));
    //1000은 밀리세컨드 단위, 타임아웃을 몇ms로 할것인지 정함(1초에 한번)
    // timer_sec->start(100);

    //main_window = new QMainWindow(this);
    //MainWindow-> reserve_check;

}

SecDialog101::~SecDialog101()
{
    delete ui;
}

//각
void SecDialog101::dButtonClick()
{
    if(reserve_check) {
        // DB 연동된 상황
        this->close();
    }
    else {
        // DB 연동이 안됨
        QString uq = "update reserve set reserve_state='1', name='"+ui->lineEdit_client->text()+
                "', chkin='"+ui->lineEdit_year01->text()+"-"+ui->lineEdit_month01->text()+"-"+ui->lineEdit_date01->text()+
                "', chkout='"+ui->lineEdit_year02->text()+"-"+ui->lineEdit_month02->text()+"-"+ui->lineEdit_date02->text()+
                "', crew='"+ui->lineEdit_total_human->text()+"', telephone='"+ui->lineEdit_phonenumber->text()+
                "' where room_id="+ui->lineEdit_roomnumber->text();

        QSqlQuery query(uq);
        query.exec();

        this->close();
    }
#if 0
    name         = ui->lineEdit_client     ->text();
    phone        = ui->lineEdit_phonenumber->text().toInt();
    room         = ui->lineEdit_roomnumber ->text().toInt();
    total_human  = ui->lineEdit_total_human->text().toInt();
    total_date   = ui->lineEdit_total_date ->text().toInt();
    total_count  = ui->lineEdit_total_count->text().toInt();


    reserve_check =1;
    connect(this, SIGNAL(sendData(int,QString,int,int,int,int,int)), parent(), SLOT(reserve_check_function(int,QString,int,int,int,int,int)));
    emit sendData(reserve_check,name,room,phone,total_human,total_date,total_count);
    qDebug() << "reservation value :" << reserve_check << endl;
    this->close();
#endif
}


void SecDialog101::on_calendarWidget_clicked(const QDate &date)
{

}


//취소 버튼
void SecDialog101::on_pushButton_reservation_cancel_clicked()
{
    this->close();
}

//Apply버튼 숙박기간을 입력하여 총일수와 가격을 계산한다.
void SecDialog101::on_pushButton_reservation_apply_clicked()
{
    if(!reserve_check) {
        // reserve_check == 0
        year01 =  ui->lineEdit_year01  ->text().toInt();
        year02 =  ui->lineEdit_year02  ->text().toInt();
        month01 = ui->lineEdit_month01 ->text().toInt();
        month02 = ui->lineEdit_month02 ->text().toInt();
        date01 =  ui->lineEdit_date01  ->text().toInt();
        date02 =  ui->lineEdit_date02  ->text().toInt();

        total_date = date02 - date01;
        ui -> lineEdit_total_date  -> setText(QString::number(total_date));
        ui -> lineEdit_total_count -> setText(QString::number(total_date*10000));
    }

}
void SecDialog101::client_check_function(int client_check)
{
    client_check_=client_check;//Mainwindow로 부터 데이터를 전달받는다.
    //ui->lineEdit_client->setText(QString::number(3333));
//    qDebug()<<client_check_<<endl;

    QString q = "select * from reserve where room_id="+QString::number(client_check_);
    QSqlQuery query(q); // query에 select 구문 저장

    if(!query.isActive())
        qDebug() << "Query Error" + query.lastError().text();
    else while(query.next()) {
        // 쿼리 실행
        if(query.value(1).toInt()) { // reserve_status == 1
            reserve_check = 1;
            room = query.value(0).toInt();
            //qDebug() << query.value(0).toString();

            ui->lineEdit_roomnumber->setText(query.value(0).toString());
            ui->lineEdit_client->setText(query.value(2).toString());
            ui->lineEdit_total_human->setText(query.value(6).toString());
            ui->lineEdit_phonenumber->setText(query.value(7).toString());

            QStringList chkin = query.value(4).toString().split('-');
            ui->lineEdit_year01->setText(chkin[0]);
            ui->lineEdit_month01->setText(chkin[1]);
            ui->lineEdit_date01->setText(chkin[2]);
            QStringList chkout = query.value(5).toString().split('-');
            ui->lineEdit_year02->setText(chkout[0]);
            ui->lineEdit_month02->setText(chkout[1]);
            ui->lineEdit_date02->setText(chkout[2]);

            qint64 dt = query.value(4).toDate().daysTo(query.value(5).toDate());
            ui->lineEdit_total_date->setText(QString::number(dt));
            ui->lineEdit_total_count->setText(QString::number(dt*10000));
        }
        else { // reserve_status == 0
            reserve_check = 0;
            ui->lineEdit_roomnumber->setText(query.value(0).toString());
        }
    }
}
