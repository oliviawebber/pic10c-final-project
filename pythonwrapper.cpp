#include "pythonwrapper.h"

PythonWrapper::PythonWrapper(const char* p_folder, const char* p_py_file, const char* p_func_name) :
    syspath(nullptr),
    file_name(nullptr),
    module(nullptr),
    function(nullptr),
    arglist(nullptr),
    list_result(nullptr)
{
    // Start Python interpreter
    Py_Initialize();

    // Get the system path, so that the location of the local py file can be added
    syspath = PySys_GetObject((char*)"path");

    // Syntax to for beginning of folder, extra array space is used to ensure strcat does not overflow
    char folder_path_front [50] = "./../";
    PyList_Append(syspath, PyUnicode_FromString(std::strcat(folder_path_front, p_folder)));

    // Get the name of the file to be imported from and import
    file_name = PyUnicode_DecodeFSDefault(p_py_file);
    module = PyImport_Import(file_name);

    // From the file, get the proper function
    function = PyObject_GetAttrString(module, p_func_name);
}

QVector< QVector <double> > PythonWrapper::call_function(double x_initial, double y_initial, int width, int height, double step_size, char* forcing_term) {
    // Build the agrument list for the function call, and call the function. The result is stored in a list
    arglist = Py_BuildValue("ddiids", x_initial, y_initial, width, height, step_size, forcing_term);
    list_result = PyObject_CallObject(function, arglist);

    QVector<double> x_coordinates;
    QVector<double> y_coordinates;

    // x and y coordinates are listed one after another in long list
    // Due to how the Python function creates this list, we can safely assume that the list is
    // an even number of entries long. Additionally, the first half will all be x-coordinates
    // and the second half will all be y-coordinates
    Py_ssize_t midpoint = PyList_Size(list_result)/2;
    for(Py_ssize_t i = 0; i < PyList_Size(list_result); ++i) {
        // Get the item, if we are in the first half it is an x-coordinate otherwise it is a
        // y-coordinate. Append it to the proper vector
        PyObject* value = PyList_GetItem(list_result, i);
        if(i < midpoint)
            x_coordinates.push_back(PyFloat_AsDouble(value));
        else
            y_coordinates.push_back(PyFloat_AsDouble(value));
    }

    // We can't pass two vectors back from a function so stick each vector inside another
    // vector and return the larger vector
    QVector< QVector<double> > xy_list;
    xy_list.push_back(x_coordinates);
    xy_list.push_back(y_coordinates);

    // Since these variables are altered locally, need to make sure that they are destructed before
    // the end of the function call
    while (Py_REFCNT(arglist) != 0)
        Py_XDECREF(arglist);

    while (Py_REFCNT(list_result) != 0)
        Py_XDECREF(list_result);

    return xy_list;
}

PythonWrapper::~PythonWrapper() {
    // The Python wrapper is going out of scope, so make sure that all remaining references
    // are brought to zero and destructed
    while (Py_REFCNT(function) != 0)
        Py_XDECREF(function);

    while (Py_REFCNT(module) != 0)
        Py_XDECREF(module);

    while (Py_REFCNT(file_name) != 0)
        Py_XDECREF(file_name);

    while (Py_REFCNT(syspath) != 0)
        Py_XDECREF(syspath);

    // End the Python interpreter
    Py_Finalize();
}
