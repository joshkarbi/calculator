// SmartCalculator

#include "utils/CalculatorMath.h"
#include "utils/Electrical.h"

#define INPUT_BUFFER_SIZE 200
#define STATE_CALCULATING 0
#define STATE_DISPLAY_INFO 1

volatile unsigned int appState = STATE_CALCULATING;

// holds input sequence (ie. "(2+1)x3" )
volatile char inputSequence[INPUT_BUFFER_SIZE] = {};
// current index - will need to be updated accordingly
volatile unsigned int inputSize = 0;


volatile char primaryButtons[KEYPAD_ROWS][KEYPAD_COLS] = {
                                                            {'1', '2', '3', 'C'},
                                                            {'4', '5', '6', 0x2F},
                                                            {'7', '8', '9', '.'},
                                                            {'=', '0', '(', ')'}
                                                         };

volatile char secondaryButtons[KEYPAD_ROWS][KEYPAD_COLS] = {
                                                            {'+', '-', '\\', 'S'},
                                                            {'x', 's', 'c', 0},
                                                            {'t', '^', '!', '.'},
                                                            {'=', 'l', '(', ')'}
                                                           };

// denoting state (1 for second function or 0 for primary function)
volatile int functionState = 0;

void clearInputBuffer()
{
    volatile unsigned int index = 0;
    for (; index < inputSize; index++)
        inputSequence[index] = 0;
    inputSize = 0;
}

// decode key presses and store in inputSequence
void updateInputBuffer()
{
    if (currentKeypad[1][3] && !pastKeypad[1][3])
    {
        // 2nd Function button pressed
        // toggle 2nd function state
        functionState = (functionState == 0) ? 1 : 0;
    }

    if (currentKeypad[0][3] && !functionState)
    {
        // CLR button pressed
        clearInputBuffer();
    }

    // TODO: Check for press on "Show Info"


    volatile unsigned int i = 0;
    volatile unsigned int j = 0;
    for ( ; i < KEYPAD_ROWS; i++)
    {
        for ( ; j < KEYPAD_COLS; j++)
        {
            if (currentKeypad[i][j] && !pastKeypad[i][j])
            {
                // button was just pressed
                if (inputSize == INPUT_BUFFER_SIZE)
                {
                    return;
                }

                if (functionState)
                {
                    functionState = 0;

                    // 2nd function
                    if (i == 0 && j == 3)
                    {
                        // display battery, light, temperature information
                        appState = STATE_DISPLAY_INFO;
                        clearInputBuffer();
                        return;
                    }

                    inputSequence[inputSize] = secondaryButtons[i][j];
                }
                else
                {
                    inputSequence[inputSize] = primaryButtons[i][j];
                }
                inputSize++;
            }
        }
    }
}


void slightDelay()
{
	volatile int t = 0;
	while (t < 10)
	{
		t++;
	}
}

/** Evaluate the expression in inputSequence and return result **/
double evaluate()
{

    // TEMPORARY
    return 0;
}

/** Holds high-level application logic **/
int main()
{
	initKeypadGPIO();

    while (1)
    {
        scanKeypad();

        updateInputBuffer();

        if (appState == STATE_CALCULATING)
        {
            if (inputSequence[inputSize-1] == '=')
            {
                double result = evaluate();
                displayResult(result);
            }
            else
            {
                displayCurrentInput(inputSequence, inputSize);
            }
        }
        else
        {
            // TODO: add logic for showing sensor info
            // loop iterating through sensor values
            // checking for any button press which forces appState back to calculating
        }

        slightDelay();
    }
    return 0;
}
