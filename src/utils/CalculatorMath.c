// CalculatorMath.c

#include "CalculatorMath.h"
#include "tinyexpr.h"

#include <stdio.h>

#define PI 3.14159265359
#define NO_PARENS 123456

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

// log base 10
double log(double x);

// log base e
double intelliLn(double x)
{
	return 0;
}


// left and right should hold indices of innermost parentheses in input
void updateInnermostParens(volatile char* input, unsigned int* left, unsigned int* right, volatile unsigned int size)
{
	unsigned int i = 0;
	for (; i < size; i++)
	{
		if (input[i] == '(')
		{
			*left = i;
		}
		if (input[i] == ')')
		{
			*right = i;
			return;
		}
	}

	// if we make it here there are no brackets left to set left and right to UINT_MAX
	*left = *right = NO_PARENS;
}

// Parse input sequence as C string and return result //
// See Shunting-Yard Algorithm


double evaluateExpression(const volatile char* input, volatile unsigned int size)
{
	te_variable vars[] = {
        {"s", intelliSin, TE_FUNCTION1},
        {"c", intelliCos, TE_FUNCTION1},
        {"t", intelliTan, TE_FUNCTION1},
        {"l", intelliLn, TE_FUNCTION1}
	};

	/**unsigned int left = 0;
	unsigned int right = 0;
	double result = 0;

	while (left != NO_PARENS && right != NO_PARENS)
	{
		updateInnermostParens(input, &left, &right, size);

	}
	**/
	printf("evaluate\n");
	int err;
    te_expr *n = te_compile(input, vars, 1, &err);

    /* SWITCH 'x' with '*' */
    
    if (n) {
    	printf("Eval");
        double r = te_eval(n);
        te_free(n);
        return r;
    } else {
        
        /** ERROR **/

    }

	return 0;
}

// scan through input sequence and replace "s###", "c####", "t####" with just numbers
void processTrig(volatile char* input, volatile unsigned int size)
{

}

// scan through input sequence and replace "### + ### - ### x ### / ###", with just numbers
void processArithmetic(volatile char* input, volatile unsigned int size)
{

}

// scan through input sequence and replace "l###" and "### ^ ###" with numbers
void processLogarithmic(volatile char* input, volatile unsigned int size)
{

}

