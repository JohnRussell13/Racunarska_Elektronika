#include "dialog.h"
#include <QApplication>
#include <bcm2835.h>
#include "wiringPi.h"
#include "lcd.h"

int main(int argc, char *argv[])
{
    bcm2835_init();

    bcm2835_i2c_begin();
   // adresa PCF8563 na I2C magistrali
    bcm2835_i2c_setSlaveAddress(0x51);
    bcm2835_i2c_set_baudrate(10000);
    P8563_init() ;

    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
