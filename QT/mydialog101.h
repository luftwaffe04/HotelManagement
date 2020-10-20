#ifndef MYDIALOG101_H
#define MYDIALOG101_H

#include <QDialog>

namespace Ui {
class MyDialog101;
}

class MyDialog101 : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog101(QWidget *parent = nullptr);
    ~MyDialog101();

private:
    Ui::MyDialog101 *ui;
};

#endif // MYDIALOG101_H
