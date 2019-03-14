// SmartCalculator

#include "utils/CalculatorMath.h"
#include "utils/Electrical.h"

#define INPUT_BUFFER_SIZE 200

// holds input sequence (ie. "(2+1)x3" )
volatile char inputSequence[INPUT_BUFFER_SIZE] = {};
// current index - will need to be updated accordingly
volatile unsigned int inputSize = 0;


// decode key presses and store in inputSequence
void updateInputBuffer()
{

}


void slightDelay()
{
	volatile int t = 0;
	while (t < 10)
	{
		t++;
	}
}

/** Holds main logic **/
int main()
{
	initKeypadGPIO();

    while(1)
    {
        updateKeypad();

        updateInputBuffer();

        slightDelay();
    }
    return 0;
}
