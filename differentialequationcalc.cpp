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
    // Get initial conditions
    double x_initial = ui->x_spinbox->value();
    double y_initial = ui->y_spinbox->value();

    // forcing_term needs to be in char*, so go through conversion steps from QString
    QString qt_forcing_term = ui->forcing_term->toPlainText();
    QByteArray array_forcing_term = qt_forcing_term.toUtf8();
    char* forcing_term = array_forcing_term.data();

    // Get graph size and step size information
    int width = ui->spinBox->value();
    int height = ui->spinBox_2->value();
    double step_size = ui->doubleSpinBox->value();

    // Call to solve function return is a QVector of 2 QVector<double>, the first QVector is the x-coordinates
    // and the seccond QVector is the y-coordinates
    QVector< QVector<double> > result = pw.call_function(x_initial, y_initial, width, height, step_size, forcing_term);

    // Create graph and assign data to it
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(result[0], result[1]);

    // Assign labels to graph
    ui->customPlot->xAxis->setLabel("t");
    ui->customPlot->yAxis->setLabel("y");

    // Set axes ranges
    ui->customPlot->xAxis->setRange(0, width);
    ui->customPlot->yAxis->setRange(-height, height);
    ui->customPlot->replot();

}
