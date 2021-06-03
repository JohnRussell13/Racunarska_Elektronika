#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <bcm2835.h>

#define changeHexToInt(hex) ((((hex)>>4) *10 ) + ((hex)%16) )

//adrese registara
#define SEK 0x02
#define MIN 0x03
#define SAT 0x04
#define DAN 0x05
#define MES 0x07
#define GOD 0x08

extern char WriteBuf[];
extern unsigned char ReadBuf;
extern unsigned char g8563_Store[];
// sec,min,sat
extern unsigned char init8563_Store[];

extern void P8563_settime();
extern void P8563_Readtime();
extern void P8563_init();

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
