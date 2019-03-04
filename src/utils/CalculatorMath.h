// CalculatorMath.h

/**
 *	Contains functions that perform
 *  basic arithmetic, trigonometric, and logarithmic evaluations.
 */

#ifndef INTELLICALC_CALCULATOR_MATH
#define INTELLICALC_CALCULATOR_MATH

// ARITHMETIC //

// this will make our other code look cleaner
double add(double x, double y);
double subtract(double x, double y);
double multiply(double x, double y);
double divide(double x, double y);

// TRIGONOMETRY //

// angle in degrees for now
double sin(double angle);
double cos(double angle);
double tan(double angle);

// LOGARITHMIC //

// log base 10
double log(double x);
// log base e
double ln(double x);

#endif