#include "attendance.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void submitStudentCode()
{
	lcdClear();
	lcdStringXY(1, 0, "Enter Student Code:");
	char studentCode[10];
	int index = 0;
	char key;

	while (1)
	{
		key = keypadGetkey();
		if (key == '#') // Assuming '#' is used to submit the code
		{
			studentCode[index] = '\0';
			break;
		}
		else if (key == '*') // Assuming '*' is used to clear the input
		{
			index = 0;
			lcdStringXY(2, 0, "                "); // Clear the input line
		}
		else
		{
			studentCode[index++] = key;
			lcdChar(key);
		}
	}

	// Validate the student code
	if (index != 8) // Assuming student code length should be 8
	{
		lcdStringXY(2, 0, "Invalid Code");
		buzzerOn();
		_delay_ms(500);
		buzzerOff();
	}
	else
	{
		// Save the student code to EEPROM
		// eepromWriteString(studentCode);
		lcdStringXY(2, 0, "Code Accepted");
	}

	_delay_ms(1000);
	attendanceInitialization(); // Return to attendance ready state
}

void attendanceInitialization()
{
	lcdClear();
	lcdStringXY(1, 0, "Attendance Ready");
	_delay_ms(700);
	lcdStringXY(1, 0, "1 . Sub Stud Code");
	lcdStringXY(2, 0, "2 . Exit");
	while (1)
	{
		char key = keypadGetkey();
		switch (key)
		{
		case '1':
			submitStudentCode();
			break;
		case '2':
			return;
		}
	}
}

void studentManagement()
{
}

void viewPresentStudents()
{
}

void temperatureMonitoring() {
	lcdClear();
	char temp_buff[16];
	sprintf(temp_buff, "Temp: %d C", 0);
	lcdStringXY(1, 0, temp_buff);
	char exit_key[] = "Press * to exit";
	lcdStringXY(2, 0, exit_key);
	char key = 0;

	while (1) {
		uint16_t temperature = getTemp();
		sprintf(temp_buff, "Temp: %d C", temperature);
		lcdStringXY(1, 0, temp_buff);

		key = keypadScan();
		if (key != 0)
		{
			_delay_ms(20); // Debounce delay
			if (keypadScan() == key)
			{

				// Verify key press
				while (keypadScan() == key)
					;
				if(key == '*' )
					return ;
			}
		}
		
		_delay_ms(50); // Add a small delay to prevent continuous reading of the same key press
	}
}

void retrieveStudentData()
{
}

void trafficMonitoring()
{
}