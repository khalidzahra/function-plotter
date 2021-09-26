#include "functionplotter.h"
#include "ui_functionplotter.h"

FunctionPlotter::FunctionPlotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FunctionPlotter)
{
    ui->setupUi(this);
}

FunctionPlotter::~FunctionPlotter()
{
    delete ui;
}

