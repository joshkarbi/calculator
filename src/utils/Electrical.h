// Electrical.h

/**
 * Contains functions for:
 *
 *   - reading keypad, and GPIO (ie. battery test circuit, photoresistor, thermistor)
 *   - outputting to displays and warning LED light
 *
 *
 * GPIO Pinout:
 * 	 - GPIO0 3:0 are outputs to row select lines of keypad
 *   - GPIO0 8:5 are inputs from column lines
 */

#ifndef INTELLICALC_ELECTRICAL
#define INTELLICALC_ELECTRICAL

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4
#define UINT_MAX 4294967295

// global for current button presses on keypad 
volatile int currentKeypad[KEYPAD_ROWS][KEYPAD_COLS] = {
														{0, 0, 0, 0},
														{0, 0, 0, 0},
														{0, 0, 0, 0},
														{0, 0, 0, 0}
													   };
// global for past button presses on keypad
volatile int pastKeypad[KEYPAD_ROWS][KEYPAD_COLS] = {
													{0, 0, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0},
													{0, 0, 0, 0}
													};



volatile unsigned int* GPIO0_ADDR = (unsigned int*)(0xFF708000);
volatile unsigned int* GPIO1_ADDR = (unsigned int*)(0xFF709000);
volatile unsigned int* GPIO2_ADDR = (unsigned int*)(0xFF70A000);

void initKeypadGPIO();

// update global 2D arrays for keypad presses
void scanKeypad();

// @param character: 0-9, ., [, ], s, t, c (sin, cos, tan), l, n, ^ 
void writeToDisplay(const char character, const unsigned int displayNum);

// display most recent 6 character from input sequence on hex displays as we input stuff
void displayCurrentInput(volatile char* input, const unsigned int size);

// display a result from calculation on seven segment displays (first 6 characters)
void displayResult(const double x);

// linking
#include "Electrical.c"
#endif
