#include "dialog.h"
#include "ui_dialog.h"
#include <QTimer>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    wiringPiSetup ();
    fd = wiringPiI2CSetup(PCF8591);

    QTimer *myTimer1 = new QTimer(this);
    connect(myTimer1, SIGNAL(timeout()), this, SLOT(funkcija()));
    myTimer1->start(500);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::funkcija()
{
    X =  wiringPiI2CReadReg8(fd,PCF8591+1);
    Y =  wiringPiI2CReadReg8(fd,PCF8591+3);
    Z = wiringPiI2CReadReg8(fd,PCF8591+4);

    ui->verticalSlider->setValue(X);
    ui->dial->setValue(Y);
    ui->lcdNumber->display(Z);

    QString text5;
    text5.setNum(X);
    ui->label->setText(text5);
/*
    if(num <9 && adcVal <220){
        wiringPiI2CWriteReg8 (fd, PCF8591 + num, adcVal) ;
        num++;
        adcVal+=27;
        wiringPiI2CReadReg8(fd,PCF8591+2);
        if(adcVal<221){

        }
     delay(50);
     }
     else{
        adcVal=0;
        num=0;
     }
     */
}
