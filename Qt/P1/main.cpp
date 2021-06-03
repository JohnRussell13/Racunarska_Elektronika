#include "dialog.h"
#include <QApplication>
#include <wiringPi.h>
#include <softPwm.h>

int main(int argc, char *argv[])
{
    wiringPiSetup();
    pinMode(28, OUTPUT);
    softPwmCreate(27,0,100);

    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
