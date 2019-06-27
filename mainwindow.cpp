#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "QDebug"
#include "math.h"
#include <QWebEngineView>
#include <QtWebEngineWidgets>


class Heading
{
public:
    double X,Y,Z;
};

QString TEAM_ID = "2540";

int lol = 100;
int i=100;
int count =0;

int Acceleration=0;

int Minutes,Seconds;Heading CurrentHeading;
double PacketCount=0.0,Altitude=0.0,Pressure=0.0,Speed=0.0,Temperature,Voltage=0.0;

int Altitude_Min,Altitude_Max;
int Speed_Min,Speed_Max;
int Pressure_Min,Pressure_Max;

QString Latitude = "32.2206";
QString Longitude = "-98.2022";

QString SecondUnit = "";

QWebEngineView *Map;
QString gMapURL;

int lat = 32.2206;int lon = -98.2022;

QTimer* timer;

QVector<double> arr,arr2;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        arr2.push_back(100);


    QWebEngineView *Map = new QWebEngineView(ui->Map);
    QString gMapURL = "England"; // this is where you want to point
    gMapURL="http://maps.google.com/?ll="+Latitude+","+Longitude;

    Map->load(QUrl(gMapURL));

    Map->resize(1024, 750);
    Map->show();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(RefreshScreen()));
    timer->start(300);

    QPixmap logo("/Users/Abhishek/Downloads/logo.jpg");
    ui->Logo->setPixmap(logo);
    ui->Logo->setScaledContents( true );

    ui->Logo->setPixmap(logo.scaled(ui->Logo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap cansatLOGO("/Users/Abhishek/Downloads/cansatLOGO.jpg");
    ui->cansatLOGO->setPixmap(cansatLOGO);
    ui->cansatLOGO->setScaledContents(true);
    ui->cansatLOGO->setPixmap(cansatLOGO.scaled(ui->cansatLOGO->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RefreshScreen()
{
    lat++;
    lon++;




    //Design-Based
    QFont sansFont("Helvetica [Cronyx]", 8);

    Seconds++;
    if(Seconds<10)
        SecondUnit = "0";
    else
        SecondUnit = "";
    if(Seconds>=60)
    {
        Minutes++;
        Seconds=0;

    }

    //Plotted Values
    ui->AltitudeVal->setText(QString::number(arr2[count])+" metres");
    ui->SpeedVal->setText(QString::number(arr2[count])+" meters/sec");
    ui->PressureVal->setText(QString::number(arr2[count])+" pascal");

    ui->PacketCountVal->setText(QString::number(PacketCount));
    ui->LatitudeVal->setText(Latitude);
    ui->LongitudeVal->setText(Longitude);

    ui->MissionTimeVal->setText(QString::number(Minutes)+":"+SecondUnit+QString::number(Seconds));


    ui->AccelerationVal->setText(QString::number(Acceleration)+" metres/second^2");
    ui->TemperatureVal->setText(QString::number(rand()%50+32)+" degrees celsius");

    ui->TelemetryText->setText(TEAM_ID+","+QString::number(PacketCount)+",<ALT SENSOR>,"+QString::number(Pressure)+","+QString::number(Speed)+","+QString::number(Temperature)+","+QString::number(Voltage)+","+Latitude+","+Longitude+","+QString::number(Altitude)+",<GPS SAT NUM>,<GPS SPEED>,<COMMAND TIME>,<COMMAND COUNT>,[<BONUS>]");

    arr.push_back(count);
    lol = lol-(rand() % 2);
    arr2.push_back(lol);
    if(arr2[count]<0)
        timer->stop();


    if(arr2[count]>Altitude_Max)
    {
        Altitude_Max = arr2[count];
    }
    if(arr2[count]>Speed_Max)
    {
        Speed_Max = arr2[count];
    }
    if(arr2[count>Pressure_Max])
    {
        Pressure_Max = arr2[count];
    }

    //Altitude by Time
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(QColor(255, 100, 0)));
    ui->widget->xAxis->setLabelFont(sansFont);
    ui->widget->yAxis->setLabelFont(sansFont);
    ui->widget->xAxis->setTickLabelFont(sansFont);
    ui->widget->yAxis->setTickLabelFont(sansFont);
    ui->widget->graph(0)->setData(arr,arr2);
    ui->widget->xAxis->setRange(0,count);
    ui->widget->yAxis->setRange(0,Altitude_Max);
    ui->widget->xAxis->setLabel("Time");
    ui->widget->yAxis->setLabel("Altitude");
    ui->widget->replot();

    //Speed by Time
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setPen(QPen(QColor(255, 100, 0)));
    ui->widget_2->xAxis->setLabelFont(sansFont);
    ui->widget_2->yAxis->setLabelFont(sansFont);
    ui->widget_2->xAxis->setTickLabelFont(sansFont);
    ui->widget_2->yAxis->setTickLabelFont(sansFont);
    ui->widget_2->graph(0)->setData(arr,arr2);
    ui->widget_2->xAxis->setRange(0,count);
    ui->widget_2->yAxis->setRange(0,Speed_Max);
    ui->widget_2->xAxis->setLabel("Time");
    ui->widget_2->yAxis->setLabel("Speed");
    ui->widget_2->replot();

    //Pressure by Time
    ui->widget_3->addGraph();
    ui->widget_3->graph(0)->setPen(QPen(QColor(255, 100, 0)));
    ui->widget_3->xAxis->setLabelFont(sansFont);
    ui->widget_3->yAxis->setLabelFont(sansFont);
    ui->widget_3->xAxis->setTickLabelFont(sansFont);
    ui->widget_3->yAxis->setTickLabelFont(sansFont);
    ui->widget_3->graph(0)->setData(arr,arr2);
    ui->widget_3->xAxis->setRange(0,count);
    ui->widget_3->yAxis->setRange(0,Altitude_Max);
    ui->widget_3->xAxis->setLabel("Time");
    ui->widget_3->yAxis->setLabel("Pressure");
    ui->widget_3->replot();


    if(count>5)
    {
        Acceleration = arr[count]-arr[count-5]/(arr2[count]-arr2[count-5]);
    }

    i--;count++;

}
