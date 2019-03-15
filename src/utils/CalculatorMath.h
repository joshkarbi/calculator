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

// EXPONENTIAL / LOGARITHMIC //

// log base 10
double intelliLog(double x);
// log base e
double intelliLn(double x);
// a^b
double intelliExponent(double a, double b);


// Contains algorithms for parsing input sequence and returning results //
double evaluateExpression(const volatile char* input, volatile unsigned int size);
void updateInnermostParens(volatile char* input, unsigned int* left, unsigned int* right, volatile unsigned int size);

// scan through input sequence and replace "s###", "c####", "t####" with just numbers
void processTrig(volatile char* input, volatile unsigned int size);

// scan through input sequence and replace "### + ### - ### x ### / ###", with just numbers
void processArithmetic(volatile char* input, volatile unsigned int size);

// scan through input sequence and replace "l###" and "### ^ ###" with numbers
void processLogarithmic(volatile char* input, volatile unsigned int size);

// weird way of linking
#include "CalculatorMath.c"

#endif