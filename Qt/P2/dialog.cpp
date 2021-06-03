#include "dialog.h"
#include "ui_dialog.h"
#include <wiringPi.h>

bool s0 = 0;
bool s1 = 0;
bool s2 = 0;
bool s3 = 0;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked(bool checked)
{
    s0 = !s0;
    digitalWrite(25,s0);
}

void Dialog::on_pushButton_2_clicked(bool checked)
{
    s1 = !s1;
    digitalWrite(26,s1);
}

void Dialog::on_pushButton_3_clicked(bool checked)
{
    s2 = !s2;
    digitalWrite(27,s2);
}

void Dialog::on_pushButton_4_clicked(bool checked)
{
    s3 = !s3;
    digitalWrite(28,s3);
}
