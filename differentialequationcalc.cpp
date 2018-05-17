#include "differentialequationcalc.h"
#include "ui_differentialequationcalc.h"
#include <ginac/ginac.h>
using namespace GiNaC;

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

// *****************
// ***** Slots *****
// *****************
void DifferentialEquationCalc::set_order(int n) const {
    switch(n) {
    // Decided against trying to setup switch statements to reduce code in favor of being easily
    // readable
    case 1:
        // Turn off y'' and y', since y never gets turned off don't need to turn it on
        ui->doubleSpinBox->setEnabled(false);
        ui->doubleSpinBox->setValue(0);
        ui->doubleSpinBox_2->setEnabled(false);
        ui->doubleSpinBox_2->setValue(0);
        break;
    case 2:
        // Turn off y''
        ui->doubleSpinBox->setEnabled(false);
        ui->doubleSpinBox->setValue(0);
        ui->doubleSpinBox_2->setEnabled(true);
        break;
    case 3:
        // Don't turn off any
        ui->doubleSpinBox->setEnabled(true);
        ui->doubleSpinBox_2->setEnabled(true);
        break;
    default:
        break;
    }
}

void DifferentialEquationCalc::perform_computation() const {
    double y_coefficient = ui->doubleSpinBox_3->value();
    double dy_coefficient = ui->doubleSpinBox_2->value();
    double ddy_coefficient = ui->doubleSpinBox->value();

    symbol x("x");
    ex poly;

    poly += (ddy_coefficient*pow(x,2) + dy_coefficient*x + y_coefficient);

    // Pipe the Symbolic to a string stream
    std::stringstream s;
    s << poly;

    // Convert the string stream to a string, and convert the string to a QString
    std::string ss = s.str();
    QString result = QString::fromStdString(ss);

    // Send signal with results
    emit computation_result(result);
}
