// CalculatorMath.h

/**
 *	Contains functions that perform
 *  basic arithmetic, trigonometric, and logarithmic evaluations.
 */


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

// we should allow numerical digits, -ve sign, and decimal point
int isDigitFirstChar(const volatile char letter)
{
    if (letter >= '0' && letter <= '9')
    return 1;
    
    if (letter == '-' || letter == '.')
    return 1;
    
    return 0;
}
// when not first char, no negative sign
int isDigit(const volatile char letter)
{
    if (letter >= '0' && letter <= '9')
    return 1;
    
    if ( letter == '.')
    return 1;
    
    return 0;
}
double evaluateExpression(const volatile char* input, volatile unsigned int size)
{
    volatile unsigned int sizeOfNum1 = 0;
    volatile unsigned int sizeOfNum2 = 0;
    
    // find length of first number
    if (isDigitFirstChar(input[sizeOfNum1])) {
        sizeOfNum1++;
    }
    while (isDigit(input[sizeOfNum1++]));
    sizeOfNum1--;
    
    // sizeOfNum2 should point to one place past operand
    sizeOfNum2 = sizeOfNum1+1;
    char operand = '+';
    if (input[sizeOfNum2-1] == '+') { operand = '+'; }
    else if (input[sizeOfNum2-1] == '-') { operand = '-'; }
    else if (input[sizeOfNum2-1] == '*') { operand = '*'; }
    else { operand = '/'; }
    
    while (isDigit(input[sizeOfNum2++]));
    sizeOfNum2 -= sizeOfNum1+1;
    sizeOfNum2--; // NEW
    // for demo purposes input will have a number, +, -, *, or /, then another number followed by '='
    char * num1 = (char *)malloc(sizeof(char) * sizeOfNum1 + 1);
    char * num2 = (char *)malloc(sizeof(char) * sizeOfNum2 + 1);
    
    // fill buffers memcpy(dest, src, numBytes)
    memcpy((void *)num1, (void *)input, sizeOfNum1);
    memcpy((void *)num2, (void *)(input+sizeOfNum1+1), sizeOfNum2); // NEW
    num1[sizeOfNum1] = num2[sizeOfNum2] = '\0';
    
    double x = atof(num1);
    double y = atof(num2);
    
    free((void*)(num1));
    free((void*)(num2));
    
    switch(operand)
    {
        case '+':
        return x+y;
        case '-':
        return x-y;
        case '*':
        return x*y;
        case '/':
        return x/y;
        default:
        return 0;
    }
}

#endif