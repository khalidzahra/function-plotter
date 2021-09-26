#include "functionplotter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FunctionPlotter w;
    w.show();
    return a.exec();
}
