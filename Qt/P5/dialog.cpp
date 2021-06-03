#include "dialog.h"
#include "ui_dialog.h"
#include <bcm2835.h>
#include "wiringPi.h"
#include "lcd.h"

char WriteBuf[2];
unsigned char ReadBuf;
unsigned char g8563_Store[6];
// sec,min,sat
unsigned char init8563_Store[6]={0x00,0x59,0x08,0,0,0};

extern void P8563_settime()
{
WriteBuf[0] = SEK;
WriteBuf[1] = g8563_Store[0];
bcm2835_i2c_write(WriteBuf,2);
WriteBuf[0] = MIN;
WriteBuf[1] = g8563_Store[1];
bcm2835_i2c_write(WriteBuf,2);

WriteBuf[0] = SAT;
WriteBuf[1] = g8563_Store[2];
bcm2835_i2c_write(WriteBuf,2);

WriteBuf[0] = DAN;
WriteBuf[1] = g8563_Store[3];
bcm2835_i2c_write(WriteBuf,2);
WriteBuf[0] = MES;
WriteBuf[1] = g8563_Store[4];
bcm2835_i2c_write(WriteBuf,2);
WriteBuf[0] = GOD;
WriteBuf[1] = g8563_Store[5];
bcm2835_i2c_write(WriteBuf,2);
}

extern void P8563_Readtime()
{
char time[7];
WriteBuf[0] = SEK;
bcm2835_i2c_write_read_rs(WriteBuf, 1, time, 7);

g8563_Store[0] = time[0] & 0x7f;
g8563_Store[1] = time[1] & 0x7f;
g8563_Store[2] = time[2] & 0x3f;
g8563_Store[3] = time[3] & 0x3f;
g8563_Store[4] = time[5] & 0x1f;
g8563_Store[5] = time[6] & 0xff;

g8563_Store[0] = changeHexToInt(g8563_Store[0]);
g8563_Store[1] = changeHexToInt(g8563_Store[1]);
g8563_Store[2] = changeHexToInt(g8563_Store[2]);
g8563_Store[3] = changeHexToInt(g8563_Store[3]);
g8563_Store[4] = changeHexToInt(g8563_Store[4]);
g8563_Store[5] = changeHexToInt(g8563_Store[5]);
}

extern void P8563_init()
{
unsigned char i;
for(i=0;i<=6;i++)
g8563_Store[i]=init8563_Store[i];

P8563_settime();

//inicijalizacija RTC-a
WriteBuf[0] = 0x0;
WriteBuf[1] = 0x00; //normalni rezim rada
bcm2835_i2c_write(WriteBuf,2);
}


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QString text(reinterpret_cast<unsigned char> (g8563_Store[2]));
    ui->label->setText(text);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    P8563_Readtime();
    QString text0;
    QString text1;
    QString text2;

    text0 = ui->lineEdit->text();
    text1 = ui->lineEdit_2->text();
    text2 = ui->lineEdit_3->text();

    unsigned char x0 = (unsigned char) atoi(text0.toStdString().c_str());
    unsigned char x1 = (unsigned char) atoi(text1.toStdString().c_str());
    unsigned char x2 = (unsigned char) atoi(text2.toStdString().c_str());

    g8563_Store[0] = x0;
    g8563_Store[1] = x1;
    g8563_Store[2] = x2;
    P8563_settime();

    QString text5;
    text0.setNum(x0);
    text1.setNum(x1);
    text2.setNum(x2);

    text5.append(text2);
    text5.append(':');
    text5.append(text1);
    text5.append(':');
    text5.append(text0);

    ui->label->setText(text5);


    const int RS = 3;
    const int EN = 14;
    const int D0 = 4;
    const int D1 = 12;
    const int D2 = 13;
    const int D3 = 6;

    int lcd_h;
    wiringPiSetup();
    lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
    lcdPosition(lcd_h, 0,0);
    lcdPrintf(lcd_h, text2.toLocal8Bit().constData());
    lcdPosition(lcd_h, 2,0);
    lcdPrintf(lcd_h, ":");
    lcdPrintf(lcd_h, text1.toLocal8Bit().constData());
    lcdPosition(lcd_h, 5,0);
    lcdPrintf(lcd_h, ":");
    lcdPrintf(lcd_h, text0.toLocal8Bit().constData());

    bcm2835_delay(5000);
}

void Dialog::on_pushButton_2_clicked()
{

    P8563_Readtime();
    QString text0(reinterpret_cast<unsigned char> (g8563_Store[0]));
    QString text1(reinterpret_cast<unsigned char> (g8563_Store[1]));
    QString text2(reinterpret_cast<unsigned char> (g8563_Store[2]));

    unsigned char x0 = g8563_Store[0];
    unsigned char x1 = g8563_Store[1];
    unsigned char x2 = g8563_Store[2];

    QString text5;

    text0.setNum(x0);
    text1.setNum(x1);
    text2.setNum(x2);

    text5.append(text2);
    text5.append(':');
    text5.append(text1);
    text5.append(':');
    text5.append(text0);

    ui->label->setText(text5);

    bcm2835_delay(5000);

}
