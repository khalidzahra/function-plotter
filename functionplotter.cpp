#include "Expression.h"
#include "functionplotter.h"
#include "ui_functionplotter.h"
#include "QMessageBox"

FunctionPlotter::FunctionPlotter(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FunctionPlotter) {
    ui->setupUi(this);
    setupDisplay();
    connect(ui->plotBtn, SIGNAL(released()), this, SLOT(onPlotButtonClick()));
}

FunctionPlotter::~FunctionPlotter() {
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
    std::string equation = ui->eqtnInput->text().toStdString();
    if (!validateEquation(equation)) return;
    Expression expression(equation);
    QVector<double> x, y;
    double minY = 0, maxY = 0, factor = (maxX - minX) * 0.001;
    for (int i = 0; i < 1000; i++) {
        double xVal = minX + factor * i;
        double yVal = expression.evaluate(xVal); // finds y for this value of x
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

bool FunctionPlotter::isValidEquation(std::string &equation) {
    if (equation.length() == 0) return false;
    std::string prev = "";
    bool lastIsOperator = false, skippedSpace = false;
    for (int i = 0; i < equation.length(); i++) {
        if (equation[i] == ' ') {
            skippedSpace = true;
            continue;
        }
        if (!isDigitOrX(equation[i]) && !isOperator(equation[i])) return false;
        if (isDigitOrX(equation[i])) {
            if ((isCharacterX(equation[i]) && prev.length() != 0) || isCharacterX(prev[prev.length() - 1]) || (prev.length() != 0 && skippedSpace)) return false;
            prev += equation[i];
            lastIsOperator = false;
            skippedSpace = false;
        } else {
            if (prev.length() == 0) return false;
            prev = "";
            lastIsOperator = true;
            skippedSpace = false;
        }
    }
    return !lastIsOperator;
}

bool FunctionPlotter::validateEquation(std::string &equation) {
    if (!isValidEquation(equation)) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Equation Error");
        messageBox.setIcon(messageBox.Critical);
        messageBox.setText("Invalid equation.");
        messageBox.setInformativeText("Supported operators: +-*/^\nThe only supported variable name is 'x'");
        messageBox.setFixedWidth(300);
        messageBox.setFixedWidth(200);
        messageBox.exec();
        return false;
    }
    return true;
}

bool FunctionPlotter::isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

bool FunctionPlotter::isCharacterX(char ch) {
    return ch == 'x' || ch == 'X';
}

bool FunctionPlotter::isDigitOrX(char ch) {
    return isCharacterX(ch) || (((ch - '0') >= 0) && ((ch - '0') <= 9));
}
