// CalculatorMath.h

/**
 *	Contains functions that perform
 *  basic arithmetic, trigonometric, and logarithmic evaluations.
 */

#include "tinyexpr.h"

#include <stdio.h>

#define PI 3.14159265359
#define NO_PARENS 123456

#ifndef INTELLICALC_CALCULATOR_MATH
#define INTELLICALC_CALCULATOR_MATH

// ARITHMETIC //

// for consistency across code base
double intelliAdd(double x, double y);
double intelliSubtract(double x, double y);
double intelliMultiply(double x, double y);
double intelliDivide(double x, double y);
double intelliSqrt(double x);

// TRIGONOMETRY //

// angle in degrees
double intelliSin(double angle);
double intelliCos(double angle);
double intelliTan(double angle);

// EXPONENTIAL / LOGARITHMIC //

// log base e
double intelliLn(double x);
// a^b
double intelliExponent(double a, double b);


// these functions are only for consistency across code-base
double intelliAdd(double x, double y){
	double val=0;
	val=x+y;
	return val;	
}


double intelliSubtract(double x, double y){
	double val=0;
	val=x-y;
	return val;
}

double intelliMultiply(double x, double y){
	double val=0;
	val=x*y;
	return val;

}
double intelliDivide(double x, double y){
	double val=0;
	val=x/y;
	return val;
}
double intelliPower(double base, int exponent)
{
	double result = 1;
	if (exponent == 0) { return 1.0; }
	else if (exponent < 0) {
		intelliPower(base, -1 * exponent));
	} else {
		int i = 0;
		for (; i < exponent; i++) {
			result *= base;
		}
	}
	return result;

}

double intelliFactorial(int number) {
	double result = 1;
	if (number <= 1) {
		result = 1.0;
	}
	else {
		for (; number >= 1; number--) {
			result *= number;
		}
	}
	return result;
}

// TRIGONOMETRY //

// angle in degrees for now
// these utilize the taylor series for sin, cos, tan
// number of interrations
#define TRIG_APPROXIMATE_ITERS 100
double intelliSin(double angle){
	double sign = 1;
	unsigned int i = 1;
	double result = 0;
	for (; i < TRIG_APPROXIMATE_ITERS; i+= 2) {
		result += (sign) * (intelliExponent(angle, i)/intelliFactorial(i));
		sign *= -1; // flip sign
	}
	return result;
}
	

double intelliCos(double angle){
	double sign = -1;
	unsigned int i = 2;
	double result = 1;
	for (; i < TRIG_APPROXIMATE_ITERS; i+= 2) {
		result += (sign) * (intelliExponent(angle, i)/intelliFactorial(i));
		sign *= -1; // flip sign
	}
	return result;
}

double intelliTan(double angle){
	return intelliSin(angle)/intelliCos(angle);
}

// LOGARITHMIC //

// log base e
// also uses taylor series for natural logarithm
#define LOGARITHMIC_APPROX_ITERS 100
double intelliLn(double x)
{
	double result = 0;
	double k = 1;
	for (; k < LOGARITHMIC_APPROX_ITERS; k++) {
			double term = intelliExponent(-1, k);
			term *= intelliExponent((-1 + x), k);
			term /= k;
			result += term;
	}
	if (!(x > 0 && x < 2))
	{
		result -= intelliLn(-1 + x);
	}

	result *= -1;
	return result;
}


// Parse input sequence as C string and return result //
double evaluateExpression(const volatile char* input, volatile unsigned int size)
{
	// uses tinyexpr library
	// this binds our custom functions to s, c, t, l in input sequence
	// ie. s(32) will call intelliSin
	te_variable vars[] = {
        {"s", intelliSin, TE_FUNCTION1},
        {"c", intelliCos, TE_FUNCTION1},
        {"t", intelliTan, TE_FUNCTION1},
        {"l", intelliLn, TE_FUNCTION1}
	};

	printf("evaluate\n");
	int err;
    te_expr *n = te_compile(input, vars, 1, &err);
    
    if (n) {
    	printf("Eval");
        double r = te_eval(n);
        te_free(n);
        return r;
    } 

    // return 0 if error occurred?
	return 0;
}


#endif