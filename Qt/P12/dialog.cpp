#include "dialog.h"
#include "ui_dialog.h"
#include <QTimer>

QT_CHARTS_USE_NAMESPACE

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    wiringPiSetup ();
    fd = wiringPiI2CSetup(PCF8591);
/*
    QTimer *myTimer1 = new QTimer(this);
    connect(myTimer1, SIGNAL(timeout()), this, SLOT(funkcija()));
    myTimer1->start(1000);
    X = 0;
*/
    //kreiranje podataka za prikaz
    series = new QLineSeries();

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    //chart->createDefaultAxes();

    //postavljanje opsega
    QValueAxis *aX = new QValueAxis;
    aX->setRange(0,5);
    aX->setTickCount(6);
    chart->setAxisX(aX, series);

    QValueAxis *aY = new QValueAxis;
    aY->setRange(0,64);
    aY->setTickCount(5);
    chart->setAxisY(aY, series);

    chart->setTitle("Merenje napona");

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //postavljanje grafika u vertikal layout
    ui->verticalLayout->addWidget(chartView);

    start = 0;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::funkcija()
{
    if(X > 5){
        X = 0;
        series->clear();
        series->append(X,Y);
        X++;
    }
    Y = wiringPiI2CReadReg8(fd,PCF8591+6);
    series->append(X,Y);
    X++;
}

void Dialog::on_pushButton_clicked()
{
    X = 0;
    series->clear();
}

void Dialog::on_pushButton_2_clicked()
{
    if (!start){
        QTimer *myTimer1 = new QTimer(this);
        connect(myTimer1, SIGNAL(timeout()), this, SLOT(funkcija()));
        myTimer1->start(1000);
        X = 0;
        start = 1;
    }
}
