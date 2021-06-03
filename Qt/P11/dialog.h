#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void funkcija();

private:
    Ui::Dialog *ui;

    const char PCF8591 = 0x48; // adresa
    int fd, adcValPrev, num, X , Y, Z;
    char unsigned adcVal;
};

#endif // DIALOG_H
