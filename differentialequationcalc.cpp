#include "differentialequationcalc.h"
#include "ui_differentialequationcalc.h"


DifferentialEquationCalc::DifferentialEquationCalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DifferentialEquationCalc),
    pw("pic10c-final-project", "diff_eq_solver", "solve")
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
void DifferentialEquationCalc::perform_computation() const {
    double x_initial = ui->x_spinbox->value();
    double y_initial = ui->y_spinbox->value();

    QString qt_forcing_term = ui->forcing_term->toPlainText();
    QByteArray array_forcing_term = qt_forcing_term.toUtf8();
    char* forcing_term = array_forcing_term.data();

    int width = 10;
    int height = 10;
    double step_size = 0.1;

    QVector< QVector<double> > result = pw.call_function(x_initial, y_initial, width, height, step_size, forcing_term);


    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(result[0], result[1]);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, width);
    ui->customPlot->yAxis->setRange(-height, height);
    ui->customPlot->replot();

    // Send signal with results
    //emit computation_result(result);
}
