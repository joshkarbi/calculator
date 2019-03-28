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


// each row corresponds to a switch and 4 keys
// ie. row 0 is SW0 and KEYS[3:0]
volatile char primaryButtons[KEYPAD_ROWS][KEYPAD_COLS] = {
                                                            {'1', '2', '3', 'C'},
                                                            {'4', '5', '6', 0x2F},
                                                            {'7', '8', '9', '.'},
                                                            {'=', '0', '(', ')'},
                                                            {'+', '-', '/', 'S'},
                                                            {'*', 's', 'c', 0},
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
    if (currentKeypad[0][3])
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
                inputSequence[inputSize] = primaryButtons[i][j];
                inputSize++;
                if (i == 0 && j == 3)
                {
                    // CLR pressed
                    clearInputBuffer();

                }
                if (i == 4 && j == 3)
                {
                    appState = STATE_DISPLAY_INFO;
                }
            }
        }
    }
}

void waitForButtonPress()
{
    // TODO 
    int i = 0;
    int j = 0;
    while (1)
    {
        scanKeypad();
        for (; i < KEYPAD_ROWS; i++)
            for (; j < KEYPAD_COLS; j++)
                if (currentKeypad[i][j] && !pastKeypad[i][j])
                    return;
    }
}

void slightDelay()
{
	/*volatile int t = 0;
	while (t < 10)
	{
		t++;
	}*/
}

/** Holds high-level application logic **/
int main()
{
	initKeypadGPIO();
    initBatteryGPIO();

    while (1)
    {
        scanKeypad();

        updateInputBuffer();

        if (appState == STATE_CALCULATING)
        {
            if (inputSize != 0 && inputSequence[inputSize-1] == '=')
            {
                inputSequence[inputSize-1] = '\0';
                double result = evaluateExpression(inputSequence, inputSize);
                displayResult(result);

                // TODO
                waitForButtonPress();
                clearInputBuffer();
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
            volatile unsigned int percentagePower20Intervals[] = {0, 0, 0, 0, 0}; // 0-20, 20-40, 40-60, 60-80, 80-100
            updateBatteryPercentage(percentagePower20Intervals);
            volatile unsigned int k = 0;
            volatile unsigned int percentageResult = 0;
            for (; k < 5; k++) 
            {
                if (!percentagePower20Intervals[k])
                {
                    // found first non-1 so this tells us percentage
                    double percentage = (double)((k+1)*20); 
                    displayResult(percentage);
                }
            }


        while (1) {
            scanKeypad();
            volatile unsigned int i = 0;
            volatile unsigned int j = 0;
            for(; i < 8; i++)
            {
                for(; j < 4; j++)
                {
                    if (currentKeypad[i][j])
                    {
                        // button was pressed so go back to calculating mode
                        appState = STATE_CALCULATING;
                        break;
                    }
                }
                j = 0;
            }
         }
        }

        slightDelay();
    }
    return 0;
}
