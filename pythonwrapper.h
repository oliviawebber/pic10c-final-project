#ifndef PYTHONWRAPPER_H
#define PYTHONWRAPPER_H
#include <Python.h>
#include <cstring>
#include <QVector>

class PythonWrapper
{
private:
    PyObject* syspath;
    PyObject* file_name;
    PyObject* module;
    PyObject* function;
    PyObject* arglist;
    PyObject* list_result;

public:
    PythonWrapper(const char*, const char*, const char*);
    QVector< QVector <double> > call_function(double, double, int, int, double, char*);
    ~PythonWrapper();
};

#endif // PYTHONWRAPPER_H
