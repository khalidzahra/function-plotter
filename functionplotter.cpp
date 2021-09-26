#include "Expression.h"
#include "functionplotter.h"
#include "ui_functionplotter.h"

FunctionPlotter::FunctionPlotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FunctionPlotter)
{
    ui->setupUi(this);
    setupDisplay();
    connect(ui->plotBtn, SIGNAL(released()), this, SLOT(onPlotButtonClick()));
}

FunctionPlotter::~FunctionPlotter()
{
    delete ui;
}

void FunctionPlotter::setupDisplay() {
    ui->minXInput->setMinimum(std::numeric_limits<double>::lowest());
    ui->minXInput->setMaximum(std::numeric_limits<double>::max());
    ui->maxXInput->setMinimum(std::numeric_limits<double>::lowest());
    ui->maxXInput->setMaximum(std::numeric_limits<double>::max());
    ui->display->addGraph();
    ui->display->setInteraction(QCP::iRangeDrag, true);
    ui->display->setInteraction(QCP::iRangeZoom, true);
    ui->display->replot();
}

void FunctionPlotter::onPlotButtonClick() {
    double minX = ui->minXInput->value(), maxX = ui->maxXInput->value();
    Expression expression(ui->eqtnInput->text().toStdString());
    QVector<double> x, y;
    double minY = 0, maxY = 0, factor = (maxX - minX) * 0.001;
    for (int i = 0; i < 1000; i++) {
        double xVal = minX + factor * i;
        double yVal = expression.evaluate(xVal);
        x.push_back(xVal);
        if (yVal < minY) minY = yVal;
        if (yVal > maxY) maxY = yVal;
        y.push_back(yVal);
    }
    ui->display->graph(0)->setData(x, y);
    ui->display->xAxis->setRange(minX, maxX);
    ui->display->yAxis->setRange(minY, maxY);
    ui->display->replot();
}
