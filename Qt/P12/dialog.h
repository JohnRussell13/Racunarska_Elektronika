#ifndef DIALOG_H
#define DIALOG_H
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QDialog>

#include <QDialog>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;

private slots:
    void funkcija();


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;

    const char PCF8591 = 0x48; // adresa
    int fd, adcValPrev, num, X , Y, Z;
    char unsigned adcVal;
    bool clear;
    bool start;
};

#endif // DIALOG_H
