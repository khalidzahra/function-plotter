#ifndef FUNCTIONPLOTTER_H
#define FUNCTIONPLOTTER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class FunctionPlotter; }
QT_END_NAMESPACE

class FunctionPlotter : public QMainWindow
{
    Q_OBJECT

public:
    FunctionPlotter(QWidget *parent = nullptr);
    ~FunctionPlotter();

private:
    Ui::FunctionPlotter *ui;
};
#endif // FUNCTIONPLOTTER_H
