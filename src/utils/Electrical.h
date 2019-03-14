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
														{0, 0, 0},
														{0, 0, 0},
														{0, 0, 0}
													   };
// global for past button presses on keypad
volatile int pastKeypad[KEYPAD_ROWS][KEYPAD_COLS] = {
													{0, 0, 0},
													{0, 0, 0},
													{0, 0, 0}
													};



volatile unsigned int* GPIO0_ADDR = (unsigned int*)(0xFF708000);
volatile unsigned int* GPIO1_ADDR = (unsigned int*)(0xFF709000);
volatile unsigned int* GPIO2_ADDR = (unsigned int*)(0xFF70A000);

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
void updateKeypad()
{
	// See:  gpio_swporta_dr   register for writing to output (rows)
	volatile unsigned int row = 0;
	volatile unsigned int col = 0;

	for (; row < KEYPAD_ROWS; row++)
	{
		// only affect bits 3:0 of GPIO0 (row select pins)
		*(GPIO0_ADDR) |= rowSelect[row];
		*(GPIO0_ADDR) &= (UINT_MAX & rowSelect[row]);

		// we've now isolated one row of the keypad -> scan for button presses
		// See:  gpio_ext_porta  register for reading external input signals
		col = 0;
		for (; col < KEYPAD_COLS; col++)
		{
			// save what the keypad state was the last time we checked
			pastKeypad[row][col] = currentKeypad[row][col];


			if ( (*GPIO0_ADDR + 0x50) & colSelect[col])
			{
				// button is pressed
				currentKeypad[row][col] = 1;
			}
			else
			{
				// button not pressed
				currentKeypad[row][col] = 0;
			}
		}
	}
}

// @param character: 0-9, ., [, ], s, t, c (sin, cos, tan), l, n, ^ 
void writeToDisplay(const char character, const unsigned int displayNum)
{

}
// display most recent 6 character from input sequence on hex displays as we input stuff
void displayCurrentInput(const char* input, const unsigned int size)
{

}

// display a result from calculation on seven segment displays (first 6 characters)
void displayResult(const double x)
{

}


#endif
