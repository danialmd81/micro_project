#include "keypad.h"

unsigned char col, row;

// Define keypad matrix layout
unsigned char keypad[4][4] = {
	{ '7', '8', '9', '/' },
	{ '4', '5', '6', '*' },
	{ '1', '2', '3', '-' },
	{ 'c', '0', '=', '+' }
};

void keypadInit(void)
{
	KEYPAD_DDR = 0xF0; // Set rows as output (high nibble), columns as input (low nibble)
	KEYPAD_PORT = 0xFF; // Enable pull-ups on inputs
}

char keypadScan(void)
{
	// Initialize scanning
	KEYPAD_PORT = 0xFF;

	// Scan each row
	for (row = 0; row < 4; row++)
	{
		KEYPAD_DDR = 0xF0; // Set rows as outputs, columns as inputs
		KEYPAD_PORT = ~(1 << (row + 4)); // Set current row low
		_delay_us(2); // Small delay for stability

		// Read columns
		col = (KEYPAD_PIN & 0x0F);

		if (col != 0x0F)
		{
			// Key pressed
			// Determine which column
			if (!(col & 0x01))
				return keypad[row][0]; // Column 0
			if (!(col & 0x02))
				return keypad[row][1]; // Column 1
			if (!(col & 0x04))
				return keypad[row][2]; // Column 2
			if (!(col & 0x08))
				return keypad[row][3]; // Column 3
		}
	}

	return 0; // No key pressed
}

char keypadGetkey(void)
{
	char key = 0;
	while (1)
	{
		key = keypadScan();
		if (key != 0)
		{
			_delay_ms(20); // Debounce delay
			if (keypadScan() == key)
			{
				// Verify key press
				while (keypadScan() == key)
					;
				// Wait for key release
				return key;
			}
		}
	}
}

int isdigit(char c)
{
	return (c=='0' || c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9');
}