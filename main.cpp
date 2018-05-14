#include "differentialequationcalc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DifferentialEquationCalc w;
    w.show();

    return a.exec();
}
