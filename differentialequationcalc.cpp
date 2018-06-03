#include <Python.h>
#include "differentialequationcalc.h"
#include "ui_differentialequationcalc.h"
#include <iostream>
#include <QDir>

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
void DifferentialEquationCalc::perform_computation() const {
    double x_initial = ui->x_spinbox->value();
    double y_initial = ui->y_spinbox->value();

    QString qt_forcing_term = ui->forcing_term->toPlainText();
    QByteArray array_forcing_term = qt_forcing_term.toUtf8();
    char* forcing_term = array_forcing_term.data();

    int width = 10;
    int height = 10;
    double step_size = 0.1;

    // Start the python interpreter
    Py_Initialize();

    // Append directory with the python file to system path
    // Qt builds to directory in following structure
    // /parent
    //   |--build/
    //     |--executable
    //   |--pic10c-final-project/
    //     |--diff_eq_solver
    // so to properly find final need to go up from build folder and then down into final project folder
    PyObject* sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyUnicode_FromString("./../pic10c-final-project"));
    PyObject* name = PyUnicode_DecodeFSDefault("diff_eq_solver");

    // Import the module
    PyObject* module = PyImport_Import(name);

    // name is now no longer needed so decrement it so it does not leak
    //Py_DecRef(name);

    // Get the function solve from the module
    PyObject* function = PyObject_GetAttrString(module, "solve");

    // module no longer needed so decrement
    Py_DecRef(module);

    // Build the agrument list which should be of the form (double, double, int, int, double)
    PyObject* arglist = Py_BuildValue("ddiids", x_initial, y_initial, width, height, step_size, forcing_term);

    // Call the function with the constructed argument list
    PyObject* list_result = PyObject_CallObject(function, arglist);

    // arglist and function are now both done so decrement
    Py_DecRef(function);
    Py_DecRef(arglist);

    QVector<double> x_coordinates;
    QVector<double> y_coordinates;
    Py_ssize_t midpoint = PyList_Size(list_result)/2;
    for(Py_ssize_t i = 0; i < PyList_Size(list_result); ++i) {
        PyObject* value = PyList_GetItem(list_result, i);
        if(i < midpoint)
            x_coordinates.push_back(PyFloat_AsDouble(value));
        else
            y_coordinates.push_back(PyFloat_AsDouble(value));
    }

    // End the python interpreter
    Py_Finalize();

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x_coordinates, y_coordinates);
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
