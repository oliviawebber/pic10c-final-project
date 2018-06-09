#ifndef DIFFERENTIALEQUATIONCALC_H
#define DIFFERENTIALEQUATIONCALC_H
#include "pythonwrapper.h"
#include <QMainWindow>

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
    mutable PythonWrapper pw;

private slots:
    void perform_computation() const;
};

#endif // DIFFERENTIALEQUATIONCALC_H
