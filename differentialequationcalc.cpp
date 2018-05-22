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
    double x_initial = 0;
    double y_initial = 0;
    int width = 0;
    int height = 0;
    double step_size = 0;

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
    PyObject* arglist = Py_BuildValue("ddiid", x_initial, y_initial, width, height, step_size);

    // Call the function with the constructed argument list
    PyObject* python_result = PyObject_CallObject(function, arglist);

    // arglist and function are now both done so decrement
    Py_DecRef(function);
    Py_DecRef(arglist);

    // Process the return value into a form usable by Qt
    long int size;
    const char* cpp_result = PyUnicode_AsUTF8AndSize(python_result, &size);
    QString result = QString::fromUtf8(cpp_result);

    // Result is processed to decrement
    //Py_DecRef(python_result);

    // End the python interpreter
    Py_Finalize();

    // Send signal with results
    emit computation_result(result);
}
