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
 *   - GPIO0 7:4 are inputs from column lines
 *	 - GPIO0 11:15 are inputs from battery power sensing circuit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INTELLICALC_ELECTRICAL
#define INTELLICALC_ELECTRICAL

#define KEYPAD_ROWS 8
#define KEYPAD_COLS 4
#define UINT_MAX 4294967295

// global for current button presses on keypad 
volatile int currentKeypad[KEYPAD_ROWS][KEYPAD_COLS] = {
														{0, 0, 0, 0},
														{0, 0, 0, 0},
														{0, 0, 0, 0},
														{0, 0, 0, 0},
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
													{0, 0, 0, 0},
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
//#include "Electrical.c"
// Electrical.c

void initKeypadGPIO()
{
	// take GPIO out of reset state
	// permodrst register has address 0xFFD05014
	// when bits are 1 - peripheral in reset
	volatile unsigned int* PERIPHERAL_RESET = (unsigned int*)(0xFFD05014);
	*(PERIPHERAL_RESET) &= (0b111 << 25); // bits 27, 26, 25 are GPIO 0, 1, 2


	/// https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/hb/cyclone-v/cv_54001.pdf
	// set gpio_debounce register bits so that buttons are debounced

	// configure 4 output pins [GPIO0 3:0] (ROWS)
	*(GPIO0_ADDR+0x4) = 0b1111;

	// configure 4 input pins (COLUMNS)
	// by above row GPIO [28:4] are inputs (0)

	// disable interrupts
	*(GPIO0_ADDR+0x30) = 0;
}

const unsigned int rowSelect[KEYPAD_ROWS] = {0b1000, 0b100, 0b10, 0b1};
const unsigned int colSelect[KEYPAD_COLS] = {0b10000000, 0b1000000, 0b100000, 0b10000};

// update global 2D arrays for keypad presses
// FOR DEMO - use switches and keys where each switch selects a row of the keypad
volatile unsigned int* switchAddr = (unsigned int*)0xFF200040;
volatile unsigned int* keyAddr = (unsigned int*)0xFF200050;
void scanKeypad()
{
	volatile unsigned int row = 0;
	volatile unsigned int col = 0;
	volatile unsigned int temp = 0;

	volatile unsigned int swPressed = 1;
	volatile unsigned int keyPressed = 1;

	const unsigned int MAX_SW_PRESSED = (0b1 << 7);
	const unsigned int MAX_KEY_PRESSED = (0b1 << 3);

	for (; swPressed <= MAX_SW_PRESSED; swPressed = (swPressed<<1))
	{
			// new row is selected -> always clear old row and set previous state
			row = swPressed/2;

			temp = 0;
			for (; temp <= KEYPAD_COLS; temp++)
			{
				pastKeypad[row][temp] = currentKeypad[row][temp];
				currentKeypad[row][temp] = 0;
			}

			if ( !(*switchAddr & swPressed))
			{
				// switch not up so no need to check buttons for this row
				continue;
			}

			keyPressed = 1;
			for (; keyPressed <= MAX_KEY_PRESSED; keyPressed = (keyPressed << 1))
			{
				switch(keyPressed)
				{
				case 1:
					col = 3;
					break;
				case 2:
					col = 2;
					break;
				case 4:
					col = 1;
					break;
				default:
					col = 0;
					break;
				}

				if (*keyAddr & keyPressed)
				{
					currentKeypad[row][col] = 1;
				}
			}

			/*if (*switchAddr & swPressed)
			{
				// can break after checking a valid row
				break;
			}*/
	}
}


/** Definitions for hex outputs **/
// for digits 0-9
unsigned char lookup[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 
							0x6D, 0x7D, 0x07, 0x7F, 0x67};

unsigned char decPointChar = 0b1000; // bottom LED
unsigned char expChar = 0b100011; // ^
unsigned char sinChar = 0b1101101; // S
unsigned char cosChar = 0b1011000; // C
unsigned char tanChar = 0b1111000; // t
unsigned char lnChar = 0b111000; // L

unsigned char plusChar = 0b1000110; // +
unsigned char multChar = 0b1110110; // x
unsigned char subChar = 0b1000000; // -
unsigned char divChar = 0b1100100; // \ 
unsigned char factChar = 0b1110001; // F

unsigned char leftBracketChar = 0b111001; // [
unsigned char rightBracketChar = 0b1111; // ]

/** Addresses for 7-segment displays **/
unsigned char * hexBaseAddr_Low = (unsigned char *)0xFF200020;
unsigned char * hexBaseAddr_High = (unsigned char *)0xFF200030;

// return corresponding hex code
unsigned char decodeChar(const char character)
{
	if (character >= '0' && character <= '9')
		return lookup[character-'0'];

	switch (character)
	{
	case '.':
		return decPointChar;
	case '^':
		return expChar;
	case 's':
		return sinChar;
	case 'c':
		return cosChar;
	case 't':
		return tanChar;
	case 'l':
		return lnChar;
	case '+':
		return plusChar;
	case '*':
		return multChar;
	case '-':
		return subChar;
	case '/':
		return divChar;
	case '!':
		return factChar;
	case '(':
		return leftBracketChar;
	case ')':
		return rightBracketChar;
	default:
		return 0;
	}
}

// give 7-segment registers time to update
void slightRAMDelay() {
	volatile unsigned int delayLen = 100;
	for (; delayLen != 0; delayLen--) {
		// nothing
	}
}

void clearCurrentKeypad() {
	volatile unsigned int row = 0;
	volatile unsigned int col = 0;
	for (; row < KEYPAD_ROWS; row++)
	{
		for (; col < KEYPAD_COLS; col++)
		{
			currentKeypad[row][col] = 0;
		}
	}
}
// @param character: 0-9, ., [, ], s, t, c (sin, cos, tan), l, n, ^ 
// @param displayNum - 0 to 5, 0 is right side, 5 is left
void writeToDisplay(const char character, const unsigned int displayNum)
{
	if (displayNum < 4)
	{
		*(hexBaseAddr_Low + displayNum) = decodeChar(character);
	}
	else
	{
		*(hexBaseAddr_High + (displayNum-4)) = decodeChar(character);
	}
	slightRAMDelay();
}

void turnDisplaysOff()
{
	int i = 0;
	while (i <= 5)
	{
		writeToDisplay(0, i++);
	}
	slightRAMDelay();
}

// display most recent 6 character from input sequence on hex displays as we input stuff
void displayCurrentInput(volatile char* input, unsigned int size)
{
	// always overwrite whats currently on display
	turnDisplaysOff();

	if (size == 0) {
		return;
	}

	int hexNum = 0;

	while (size != 0)
	{
		writeToDisplay(input[size-1], hexNum);
		size--;
		hexNum++;
	}
}

// display a result from calculation on seven segment displays (first 6 characters)
void displayResult(const double x)
{
	static char buffer[50];

	// confirmed this works
	sprintf(buffer, "%f", x);

	size_t bufferFilledLen = strlen(buffer);

	int i = 0;
	for (; i < 6 && i < bufferFilledLen; i++)
	{
		writeToDisplay(buffer[i], 6-i);
	}

}

// setup inputs on GPIO0 [11, 12, 13, 14, 15]
void initBatteryGPIO()
{
	// this function doesn't have to do anything since all input pins beside 3:0 are
	// already set as inputs by initKeypadGPIO()
	// GPIO is also already taken out of reset mode, interrupts disabled
}

void updateBatteryPercentage(volatile unsigned int percentagePower20Intervals[])
{
	volatile unsigned int checkBits[] = {0b1 << 11, 0b1 << 12, 0b1 << 13, 0b1 << 14, 0b1 << 15};
	volatile unsigned int i = 0;
	for (; i < 5; i++)
	{
		if ((*GPIO0_ADDR + 0x50) & checkBits[i])
		{
			// this interval is logic 1
			percentagePower20Intervals[i] = 1;
		}
		else
		{
			percentagePower20Intervals[i] = 0;
		}
	}
}

#endif
