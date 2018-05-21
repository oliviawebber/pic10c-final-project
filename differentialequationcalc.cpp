#include <Python.h>
#include "differentialequationcalc.h"
#include "ui_differentialequationcalc.h"
#include <iostream>

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

    Py_Initialize();
    //PyObject* module_name_string = PyUnicode_FromString("diff_eq_solver");

    QString path = QDir::currentPath();

    PyObject* module = PyImport_ImportModule("diff_eq_solver.py");
    PyErr_Print();
    /*
    PyObject* function = PyObject_GetAttrString(module, "solve");
    std::cout << "Step 3\n";

    PyObject* arglist = PyTuple_Pack(5, x_initial, y_initial, width, height, step_size);
    std::cout << "Step 4\n";

    PyObject* python_result = PyObject_CallObject(function, arglist);
    std::cout << "Step 5\n";

    long int size;
    const char* cpp_result = PyUnicode_AsUTF8AndSize(python_result, &size);
    std::cout << "Step 6\n";

    QString result = QString::fromUtf8(cpp_result);
    std::cout << "Step 7\n";
    Py_Finalize();


    // Send signal with results
    emit computation_result(result);*/
}
