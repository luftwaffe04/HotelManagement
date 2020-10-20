#ifndef ROOMSTATUS101_H
#define ROOMSTATUS101_H

#include <QDialog>
#include <QDebug>
#include <QTimer>

namespace Ui {
class RoomStatus101;
}

class RoomStatus101 : public QDialog
{
    Q_OBJECT

public:
    explicit RoomStatus101(QWidget *parent = nullptr);
    ~RoomStatus101();
public slots:
    void room_check_function(int temp, int humi, int fire, int gas);

    //void status_change();

private slots:
    //void on_pushButton_clicked();

private:
    Ui::RoomStatus101 *ui;

    QTimer * timer;
    int temp_;
    int humi_;
    int fire_;
    int gas_;
    int temp_s;
    int humi_s;
    int fire_s;
    int gas_s;
};

#endif // ROOMSTATUS101_H
