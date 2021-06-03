#include "dialog.h"
#include "ui_dialog.h"
#include <wiringPi.h>
#include <softPwm.h>

bool state = 0;

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

void Dialog::on_pushButton_clicked()
{
    state = !state;
    digitalWrite(28,state);
    QPixmap pix1(":/slike/Photo1.png");
    QPixmap pix2(":/slike/Photo2.png");
    if(state){
        ui->label->setPixmap(pix1);
    }
    else {
        ui->label->setPixmap(pix2);
    }
}

void Dialog::on_horizontalSlider_valueChanged(int value)
{
    softPwmWrite(27,value);
}
