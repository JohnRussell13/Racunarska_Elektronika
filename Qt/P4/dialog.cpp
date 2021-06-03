#include "dialog.h"
#include "ui_dialog.h"
#include <bcm2835.h>

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )

//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04
#define DAN 0x05
#define MES 0x07
#define GOD 0x08

 char WriteBuf[2];
 unsigned char ReadBuf;
 unsigned char g8563_Store[6];
 // sec,min,sat
 unsigned char init8563_Store[6]={0x00,0x59,0x08,0,0,0};
void P8563_settime()
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
void P8563_init()
{
 unsigned char i;
 for(i=0;i<=6;i++)
 g8563_Store[i]=init8563_Store[i];

 P8563_settime();
 printf("Postavi početno tekuće vreme\n");

//inicijalizacija RTC-a
 WriteBuf[0] = 0x0;
 WriteBuf[1] = 0x00; //normalni rezim rada
 bcm2835_i2c_write(WriteBuf,2);
}
void P8563_Readtime()
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
    P8563_Readtime();
    /*printf("Sati:%d Minuti:%d Sekunde:%d Dalje: %d - %d - %d\n",
   g8563_Store[2], g8563_Store[1],
   g8563_Store[0], g8563_Store[5], g8563_Store[4], g8563_Store[3]);
    */

}
