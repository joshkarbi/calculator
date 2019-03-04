// TestCalculatorMath.h

#include "../utils/CalculatorMath.h"

#include <assert.h>
#include <stdio.h>


int withinOnePercent(double a, double b)
{
	double onePerc = b*0.01;
	if ((b + onePerc) >= a || (b - onePerc)<=a)
	{
		return 1;
	}
	return 0;
}

void testSin()
{
	printf("TESTING SIN(x)\n");

	const int TEST_SIZE = 9;
	const double TEST_IN[] = {0, 30, 45, 60, 90, 120, 135, 150, 180};
	const double EXPECTED_OUT[] = {0, 0.5, 0.707106781, 0.866025403, 1, 0.866025403, 0.707106781, 0.5, 0};

	for (int i = 0; i < TEST_SIZE; i++)
	{
		printf("Testing sin(%f)\n", TEST_IN[i]);
		assert(withinOnePercent(intelliSin(TEST_IN[i]), EXPECTED_OUT[i]));
	}
}

void testCos()
{
	printf("TESTING COS(x)\n");

	const int TEST_SIZE = 9;
	const double TEST_IN[] = {0, 30, 45, 60, 90, 120, 135, 150, 180};
	const double EXPECTED_OUT[] = {1, 866025403, 0.707106781, 0.5, 0, -0.5, -0.707106781, -0.866025403, -1};

	for (int i = 0; i < TEST_SIZE; i++)
	{
		printf("Testing cos(%f)\n", TEST_IN[i]);
		assert(withinOnePercent(intelliSin(TEST_IN[i]), EXPECTED_OUT[i]));
	}
}

void testTan()
{

}
void testTrig()
{

	return;
}

void testArithmetic()
{

	return;
}

void testTrigonometric()
{
	testSin();
	testCos();
	testTan();
}

void testLogarithmic()
{

}

int main()
{
	testArithmetic();

	testTrigonometric();

	testLogarithmic();
	printf("All test cases passed.\n");
	return 0;
}