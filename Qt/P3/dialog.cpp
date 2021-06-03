#include "dialog.h"
#include "ui_dialog.h"
#include "wiringPi.h"
#include "lcd.h"

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
    const int RS = 3;
    const int EN = 14;
    const int D0 = 4;
    const int D1 = 12;
    const int D2 = 13;
    const int D3 = 6;

    QString text1 = "H1";
    QString text2 = "H2";
    text1 = ui->lineEdit->text();
    text2 = ui->lineEdit_2->text();
    if(text1.count() > 16) text1 = "H1";
    if(text2.count() > 16) text2 = "H2";
    ui->label->setText(text1);
    ui->label_2->setText(text2);

    int lcd_h;
    wiringPiSetup();
    lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
    lcdPosition(lcd_h, 0,0);
    lcdPrintf(lcd_h, text1.toLocal8Bit().constData());
    lcdPosition(lcd_h, 0,1);
    lcdPrintf(lcd_h, text2.toLocal8Bit().constData());
}
