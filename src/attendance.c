#include "attendance.h"

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
	// Add your attendance initialization code here
}

void studentManagement()
{
}

void viewPresentStudents()
{
}

void temperatureMonitoring()
{
}

void retrieveStudentData()
{
}

void trafficMonitoring()
{
}