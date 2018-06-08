#ifndef DIFFERENTIALEQUATIONCALC_H
#define DIFFERENTIALEQUATIONCALC_H

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

private slots:
    void perform_computation() const;

signals:
    void computation_result(QString) const;
};

#endif // DIFFERENTIALEQUATIONCALC_H
