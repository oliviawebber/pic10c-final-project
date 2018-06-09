#!/usr/bin/env python
# -*- coding: utf-8 -*-


def solve(x_inital, y_initial, width, height, step_size, c_forcing_term):
    # Import statements need to be put inside function since C++ API will only execute
    # function call
    from sympy.parsing.sympy_parser import parse_expr
    from sympy import lambdify
    from sympy.abc import y, t
    import matplotlib.pyplot as plt


    # Create a sympy expression based on the input recieved
    forcing_term = parse_expr(c_forcing_term)

    # Convert that expression into a lambda function
    f = lambdify((y, t) , forcing_term)

    # Create x-coordinates
    x_coords = []
    x_value = x_inital
    while x_value <= width:
        x_coords.append(x_value)
        x_value += step_size

    # Create positive y-coordinates
    y_coords = []
    y_n = y_initial
    for i in range(len(x_coords)):
        try:
            y_n_p1 = y_n + (step_size * f(y_n, x_coords[i]))
        except OverflowError:
            break
        y_coords.append(y_n_p1)
        y_n = y_n_p1

    # Check that x-coordinates and y-coordinates are the same size
    while len(x_coords) > len(y_coords):
        x_coords.pop()
    while len(y_coords) > len(x_coords):
        y_coords.pop()

    return (x_coords + y_coords)

solve(0, 1, 10, 10, 0.01, "y")
