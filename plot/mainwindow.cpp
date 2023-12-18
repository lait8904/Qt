#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->customplot->addGraph();
    ui->customplot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customplot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->customplot->xAxis->setLabel("X");
    ui->customplot->yAxis->setLabel("Y");

    ui->customplot->rescaleAxes();

    QCustomPlot* customPlot = ui->customplot;

    QCPCurve *someFunc_1 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
    QCPCurve *someFunc_2 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

    const int pointCount = 200;

    QVector<QCPCurveData> dataFunc_1(pointCount);
    QVector<QCPCurveData> dataFunc_2(pointCount);

    for (int i=0; i<pointCount; ++i)
    {
      double phi = i/(double)(pointCount-1)*2*M_PI;
      dataFunc_1[i] = QCPCurveData(i, qSin(2 * phi) - \
                                       qCos(3 * phi), qSin(phi) * qSin(phi));
      dataFunc_2[i] = QCPCurveData(i, qSin(2 * phi) - \
                                    1 / 2. * qCos(3 * phi), qSin(phi) * qSin(phi));
    }

    someFunc_1->data()->set(dataFunc_1, true);
    someFunc_2->data()->set(dataFunc_2, true);
    someFunc_1->setPen(QPen(Qt::red));
    someFunc_2->setPen(QPen(Qt::blue));

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customPlot->axisRect()->setupFullAxesBox();

    customPlot->rescaleAxes();

    ui->customplot->replot();
    ui->customplot->update();

}

MainWindow::~MainWindow()
{
    delete ui;
}

