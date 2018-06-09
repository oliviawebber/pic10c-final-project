#include "pythonwrapper.h"

PythonWrapper::PythonWrapper(const char* p_folder, const char* p_py_file, const char* p_func_name) {
    Py_Initialize();
    syspath = PySys_GetObject((char*)"path");

    char folder_path_front [50] = "./../";
    PyList_Append(syspath, PyUnicode_FromString(std::strcat(folder_path_front, p_folder)));

    func_name = PyUnicode_DecodeFSDefault(p_py_file);

    module = PyImport_Import(func_name);

    function = PyObject_GetAttrString(module, p_func_name);
}

QVector< QVector <double> > PythonWrapper::call_function(double x_initial, double y_initial, int width, int height, double step_size, char* forcing_term) {
    arglist = Py_BuildValue("ddiids", x_initial, y_initial, width, height, step_size, forcing_term);

    list_result = PyObject_CallObject(function, arglist);

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

    QVector<QVector<double>> xy_list;
    xy_list.push_back(x_coordinates);
    xy_list.push_back(y_coordinates);

    while (Py_REFCNT(arglist) != 0)
        Py_XDECREF(arglist);

    while (Py_REFCNT(list_result) != 0)
        Py_XDECREF(list_result);

    return xy_list;
}

PythonWrapper::~PythonWrapper() {
    while (Py_REFCNT(function) != 0)
        Py_XDECREF(function);

    while (Py_REFCNT(module) != 0)
        Py_XDECREF(module);

    while (Py_REFCNT(func_name) != 0)
        Py_XDECREF(func_name);

    while (Py_REFCNT(syspath) != 0)
        Py_XDECREF(syspath);

    Py_Finalize();
}