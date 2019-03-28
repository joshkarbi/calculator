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
//#include "CalculatorMath.c"


// this will make our other code look cleaner
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
	if (exponent > 0) {// for loop if the exponent is positive 
		for (int i = 0;i < exponent;i++) {
			result = result*base;
		}
	}
	if (exponent < 0) {// for loop if the exponent is negative

		for (int i = exponent;i <0;i++) {
			result = result / base;
		}
	}
	if (exponent == 0) {// the answer is 1 if the exponent is zero
		result = 1;
	}
	return result;

}

double intelliFactorial(int number) {
	double result = number;
	if (number == 0) {
		result = 1;
	}
	//for all other numbers
	else {
		//Following loop is executed while n is greater than one
		for (int i = number - 1; i>0;i--) {
			//Determines the factorial by running the loop continuously
			result = result*i;
			//Reduces the value of n by each time while the loop is executed

		}
	}
	return result;
}



// TRIGONOMETRY //

// angle in  for now
double intelliSin(double angle){
	if (angle == 90 || angle == 270) return 1;
	
	angle=(angle*PI)/180;

	double result = 0, sum = 0;
	for (int i = 0;i < 1000;i++)
	{
		result = sum + result;
		sum = (intelliPower(-1, i)*intelliPower(angle, ((2 * i) + 1))) / intelliFactorial(2 * i + 1);

	}

	printf("SIN RESULT (%f): %f\n", angle, result);
	return result;

}
	

double intelliCos(double angle){
	
	angle=(angle*PI)/180;

	double result = 0, sum = 0;
	for (int i = 0;i < 1000;i++)
	{
		result = sum + result;
		sum = (intelliPower(-1, i)*intelliPower(angle, (2 * i))) / intelliFactorial(2 * i);

	}
	return result;
	
	
}
double intelliTan(double angle){
	angle=(angle*PI)/180;

	double result = 0;
	
	result=intelliSin(angle)/intelliCos(angle);
	
	return result;
}

// LOGARITHMIC //

// log base e
double intelliLn(double x)
{
	return 0;
}

// we should allow numerical digits, -ve sign, and decimal point
int isDigit(const volatile char letter)
{
	if (letter >= '0' && letter <= '9')
		return 1;

	if (letter == '-' || letter == '.')
		return 1;

	return 0;
}

// Parse input sequence as C string and return result //
// See Shunting-Yard Algorithm
double evaluateExpression(const volatile char* input, volatile unsigned int size)
{
	volatile unsigned int sizeOfNum1 = 0;
	volatile unsigned int sizeOfNum2 = 0;

	// find length of first number
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
	// for demo purposes input will have a number, +, -, *, or /, then another number followed by '='
	char * num1 = (char *)malloc(sizeof(char) * sizeOfNum1 + 1);
	char * num2 = (char *)malloc(sizeof(char) * sizeOfNum2 + 1);
	
	// fill buffers memcpy(dest, src, numBytes)
	memcpy((void *)num1, (void *)input, sizeOfNum1);
	memcpy((void *)num2, (void *)input, sizeOfNum2);
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