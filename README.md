# Function Plotter
## Overview
This is a simple Qt application for plotting functions in x inputted by the user. The project uses an implementation of the **Shunting-Yard algorithm** in order to create a binary tree that contains all the numbers and operators which can then later be parsed for millions of values of x more efficiently than if the string were to be parsed every single time.

The supported operators are:

- \+ (Addition)
- \- (Subtraction)
- \* (Multiplication)
- / (Division)
- ^ (Exponentiation)
## Dependencies
This project only has Qt as a dependency
## Libraries
This project uses the QCustomPlot library for plotting graphs using the calculated data
## Documentation
All methods are documented in their respective header files
## Screenshots
### General Layout
![Gui Layout](img/gui-layout.png)
### Correct Inputs
![Parabola Plot](img/parabola.png)
![Modified Parabola Plot](img/modified-parabola.png)
![Cubic Parabola Plot](img/cubic-parabola.png)
![Rational Function Plot](img/rational-function.png)
### Incorrect Inputs
![Wrong Input Example 1](img/wrong-input-1.png)
![Wrong Input Example 2](img/wrong-input-2.png)
![Wrong Input Example 3](img/wrong-input-3.png)
![Wrong Input Example 4](img/wrong-input-4.png)
![Wrong Input Example 5](img/wrong-input-5.png)