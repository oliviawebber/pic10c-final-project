#!/usr/bin/env python
# -*- coding: utf-8 -*-

def solve(x_inital, y_initial, width, height, step_size, c_forcing_term):
    # Import statements need to be put inside function since C++ API will only execute
    # function call
    from sympy.parsing.sympy_parser import parse_expr
    from sympy import lambdify
    from sympy.abc import x

    # Create a sympy expression based on the input recieved
    forcing_term = parse_expr(c_forcing_term)

    # Convert that expression into a lambda function
    f = lambdify(x, forcing_term)

    print(f(2))

    return "It worked"
