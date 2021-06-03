#include "dialog.h"
#include <QApplication>
#include <wiringPi.h>

int main(int argc, char *argv[])
{
    wiringPiSetup();
    pinMode(25,OUTPUT);
    pinMode(26,OUTPUT);
    pinMode(27,OUTPUT);
    pinMode(28,OUTPUT);
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
