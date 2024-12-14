#include "attendance.h"

int presentStudents = 0; // Store the number of present students at any po

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
	lcdClear();
	char dist_buff[16];
	sprintf(dist_buff, "Dist: %d cm", 0);
	lcdStringXY(1, 0, dist_buff);
	char presents_buff[16];
	sprintf(presents_buff, "Presents: %d", 0);
	lcdStringXY(2, 0, presents_buff);
	char exit_key[] = "Press * to exit";
	lcdStringXY(2, 14, exit_key);
	char key = 0;

	while(1){
		int dist = getDistance();
		sprintf(dist_buff, "Dist: %d cm", dist);
		lcdStringXY(1, 0, dist_buff);
		if(dist < 6){
			presentStudents++;
		}
		char presents_buff[16];
		sprintf(presents_buff, "Presents: %d", presentStudents);
		lcdStringXY(2, 0, presents_buff);
		
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