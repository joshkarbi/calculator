// CalculatorMath.c

#include "CalculatorMath.h"
#include <stdio.h>

double const pi=3.14159265359;

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
	
	angle=(angle*pi)/180;

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
	
	angle=(angle*pi)/180;

	double result = 0, sum = 0;
	for (int i = 0;i < 1000;i++)
	{
		result = sum + result;
		sum = (intelliPower(-1, i)*intelliPower(angle, (2 * i))) / intelliFactorial(2 * i);

	}
	return result;
	
	
}
double intelliTan(double angle){
	angle=(angle*pi)/180;

	double result = 0;
	
	result=intelliSin(angle)/intelliCos(angle);
	
	return result;
}

// LOGARITHMIC //

// log base 10
double log(double x);
// log base e
double ln(double x);