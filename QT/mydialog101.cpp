#include "mydialog101.h"
#include "ui_mydialog101.h"

MyDialog101::MyDialog101(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog101)
{
    ui->setupUi(this);
}

MyDialog101::~MyDialog101()
{
    delete ui;
}
