// CalculatorMath.h

/**
 *	Contains functions that perform
 *  basic arithmetic, trigonometric, and logarithmic evaluations.
 */

#ifndef INTELLICALC_CALCULATOR_MATH
#define INTELLICALC_CALCULATOR_MATH

// ARITHMETIC //

// this will make our other code look cleaner
double intelliAdd(double x, double y);
double intelliSubtract(double x, double y);
double intelliMultiply(double x, double y);
double intelliDivide(double x, double y);
double intelliSqrt(double x);

// TRIGONOMETRY //

// angle in degrees for now
double intelliSin(double angle);
double intelliCos(double angle);
double intelliTan(double angle);

// LOGARITHMIC //

// log base 10
double intelliLog(double x);
// log base e
double intelliLn(double x);

// weird way of linking
#include "CalculatorMath.c"

#endif