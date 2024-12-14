#include "attendance.h"

uint16_t eepromAddress = 0x00;

void submitStudentCode()
{
	lcdClear();
	lcdStringXY(1, 0, "Enter Student Code:");
	char studentCode[10]; // 40130023
	int index = 0;

	char key;

	while (1)
	{
		key = keypadGetkey();
		if (key == '=') // Assuming '#' is used to submit the code
		{
			studentCode[index] = '\0';
			break;
		}
		else if (key == ' ') // Assuming '*' is used to clear the input
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
		eepromWriteString(eepromAddress, studentCode);
		eepromAddress++;
		lcdStringXY(2, 0, "Code Accepted");
	}

	_delay_ms(700);
	attendanceInitialization(); // Return to attendance ready state
}

void attendanceInitialization()
{
	lcdClear();

	lcdStringXY(1, 0, "1 . Submit Student Code");
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

void searchStudent()
{
	lcdClear();
	lcdStringXY(1, 0, "Enter Student Code:");
	char studentCode[10];
	char storedCode[10];
	int index = 0;
	char key;

	while (1)
	{
		key = keypadGetkey();
		if (key == '=') // Assuming '=' is used to submit the code
		{
			studentCode[index] = '\0';
			break;
		}
		else if (key == ' ') // Assuming ' ' is used to clear the input
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
	int i;
	for (i = 0; i < eepromAddress; i++)
	{
		eepromReadString(i, storedCode);
		// Compare the entered code with the stored code
		if (strcmp(studentCode, storedCode) == 0)
		{
			lcdStringXY(2, 0, "Student Present");
			_delay_ms(700);
			return studentManagement(); // Return to student management menu
		}
	}
	lcdStringXY(2, 0, "Student Absent");
	_delay_ms(700);
	return studentManagement(); // Return to student management menu
}

void studentManagement()
{
	lcdClear();
	lcdStringXY(1, 0, "1. Search Students");
	lcdStringXY(2, 0, "2. Exit");

	char key;
	while (1)
	{
		key = keypadGetkey();
		switch (key)
		{
		case '1':
			searchStudent();
			break;
		case '2':
			return;
		}
	}
}

void viewPresentStudents()
{
}

void temperatureMonitoring()
{
	lcdClear();
	char buffer[16];
	while (1)
	{
		uint16_t temperature = getTemp();
		sprintf(buffer, "Temp: %d C", temperature);
		lcdStringXY(1, 0, buffer);
		_delay_ms(50);
	}
}

void retrieveStudentData()
{
}

void trafficMonitoring()
{
}