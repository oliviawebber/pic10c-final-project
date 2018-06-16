# PIC10C Final Project
Layton Webber

## Summary
This project provides a graphical estimation of the solution to a differential equation using Euler's Method. It allows for setting the size of the graph, the step size used in Euler's method, and the forcing term of the differential equation.

## Concepts
#### Lambda Functions
A lambda function is used in the Python code, a function is used that converts the C string forcing term into a lambda function which is then used in Euler's method.

#### Generica Algorithms
A generic algorthim was not used due to the fact that in implementing Euler's method, the loop needs to know to know about previous y values, and saving previous values would place more restrictions on the iterators than might be guranteed.

#### Memory Management
The Python-C API uses references to PyObject's for its functionality. These references could lead to memory leaks if not handled properly. To combat this, the python object is wrapped in a self-coded Python wrapper class, so that object destruction also results in all references being properly destroyed. 

#### QT
QT is used to provide the interface for sending data to the Python calculator. Additionally, the graph functionality is provided by using a QT widget

#### Python-C API
QT and C++ are used in the front end, but the actual calculations are done by a Python program. This is done using the Python-C API which allows for passing C++ and Python objects back and forth, and using Python functions within C++.

### Future Additions
A future addition to this project might be using a lambda function and generic algorithm to clean the input, translating common errors like 5x into 5*x.

## Dependencies
1. QT
  2. [QT Plotting Widget](http://www.qcustomplot.com/)

2. Python Interpreter
  2. [SymPy](http://www.sympy.org/en/index.html)

### Link to Video
[![Video Image](http://img.youtube.com/vi/46qvxTmSG0Q/0.jpg)](http://www.youtube.com/watch?v=46qvxTmSG0Q)