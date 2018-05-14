#ifndef DIFFERENTIALEQUATIONCALC_H
#define DIFFERENTIALEQUATIONCALC_H

#include <QMainWindow>
#include "lib/headers/symbolicc++.h"

namespace Ui {
class DifferentialEquationCalc;
}

class DifferentialEquationCalc : public QMainWindow
{
    Q_OBJECT

public:
    explicit DifferentialEquationCalc(QWidget *parent = 0);
    ~DifferentialEquationCalc();

private:
    Ui::DifferentialEquationCalc *ui;

private slots:
    void set_order(int) const;
    void preform_computation() const;
};

#endif // DIFFERENTIALEQUATIONCALC_H
