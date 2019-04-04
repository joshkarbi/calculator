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
// ie. row i is SW[i] and cols KEYS[3:0]
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
        return;
    }

    volatile unsigned int i = 0;
    volatile unsigned int j = 0;
    for ( ; i < KEYPAD_ROWS; i++)
    {
        for ( ; j < KEYPAD_COLS; j++)
        {
            // check is button was just pressed
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

// wait for SW9 to go high
void waitForButtonPress()
{
    volatile unsigned int SW9 = 0b100000000;
    while (1)
    {
        if (*switchAddr & SW9)
            break;
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

/** Holds high-level application logic **/
int main()
{
    initKeypadGPIO();
    initBatteryGPIO();
    // represent 20% intervals of battery power
    volatile unsigned int percentagePower20Intervals[] = {0, 0, 0, 0, 0};

    while (1)
    {
        // this updates global 2D arrays currentKeypad and pastKeypad in Electrical.h
        scanKeypad();

        // decode key press and store character in buffer
        // will also update appState to STATE_DISPLAY_INFO if needed
        updateInputBuffer();

        if (appState == STATE_CALCULATING)
        {
            if (inputSize != 0 && inputSequence[inputSize-1] == '=')
            {
                double result = evaluateExpression(inputSequence, inputSize);
                displayResult(result);
                slightDelay();
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
                    waitForButtonPress();
                    appState = STATE_CALCULATING;
                    clearInputBuffer();
                    break;
                }
            }
        }

    }
    return 0;
}
