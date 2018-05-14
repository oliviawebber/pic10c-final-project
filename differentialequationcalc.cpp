#include "differentialequationcalc.h"
#include "ui_differentialequationcalc.h"

DifferentialEquationCalc::DifferentialEquationCalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DifferentialEquationCalc)
{
    ui->setupUi(this);
}

DifferentialEquationCalc::~DifferentialEquationCalc()
{
    delete ui;
}
