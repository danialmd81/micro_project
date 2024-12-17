#include "attendance.h"

int presentStudents = 0; // Store the number of present students at any po

void submitStudentCode()
{
	glcdClearAll();
	glcdString(0, "Enter Student Code:");
	char studentCode[STUDENT_CODE_SIZE]; // 40130023
	memset(studentCode, 0, STUDENT_CODE_SIZE);
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
		else if (key == '*') // Assuming '*' is used to clear the input
		{
			index = 0;
			glcdString(1, "                "); // Clear the input line
		}
		else
		{
			studentCode[index++] = key;
			glcdString(1, studentCode);
		}
	}

	// Validate the student code
	if (index != 8) // Assuming student code length should be 8
	{
		glcdString(1, "Invalid Code");
		buzzerOn();
		_delay_ms(500);
		buzzerOff();
	}
	else
	{
		if (searchStudent(studentCode) != -1)
		{
			glcdString(1, "Code Already Exists");
			buzzerOn();
			_delay_ms(500);
			buzzerOff();
		}
		else
		{
			saveStudent(studentCode);
			glcdString(1, "Code Accepted");
		}
	}

	_delay_ms(700);
	return attendanceInitialization(); // Return to attendance ready state
}

void attendanceInitialization()
{
	glcdClearAll();

	glcdString(0, "1.Submit Student Code");
	glcdString(1, "2.Exit");
	char key;
	while (1)
	{
		key = keypadGetkey();
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
	glcdClearAll();
	glcdString(0, "1.Search Students");
	glcdString(1, "2.Exit");

	char key;
	while (1)
	{
		key = keypadGetkey();
		switch (key)
		{
		case '1':
			glcdClearAll();
			glcdString(0, "Enter Student Code:");
			char studentCode[STUDENT_CODE_SIZE];
			memset(studentCode, 0, STUDENT_CODE_SIZE);
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
				else if (key == '*') // Assuming '*' is used to clear the input
				{
					index = 0;
					glcdString(1, "                "); // Clear the input line
				}
				else
				{
					studentCode[index++] = key;
					glcdString(1, studentCode);
				}
			}
			if (searchStudent(studentCode) != -1)
			{
				glcdString(1, "Student Present");
				_delay_ms(700);
			}
			else
			{
				glcdString(1, "Student Absent");
				_delay_ms(700);
			}
			return studentManagement();
			break;
		case '2':
			return;
		}
	}
}

void viewPresentStudents()
{
	glcdClearAll();
	uint16_t address = STUDENT_START_ADDRESS;
	char buffer[BUFFER_SIZE];
	char studentCode[STUDENT_CODE_SIZE];
	int presentCount = loadStudentNumber();

	// Display the number of present students
	sprintf(buffer, "Present: %d", presentCount);
	glcdString(0, buffer);

	// Display the student codes
	uint16_t i;
	for (i = 0; i < presentCount; i++)
	{
		eepromReadString(address, studentCode);
		glcdString(i % 7 + 1, studentCode);
		_delay_ms(1000);
		address += STUDENT_CODE_SIZE;
	}

	// Return to the main menu after displaying all student codes
	return;
}

void temperatureMonitoring()
{
	glcdClearAll();
	char temp_buff[24];
	char key = 0;
	int temperature;
	glcdString(1, "Press * to exit");

	while (1)
	{
		temperature = getTemp();
		sprintf(temp_buff, "Temp: %d C", temperature);
		glcdString(0, temp_buff);
		_delay_ms(20);

		key = keypadScan();
		if (key != 0)
		{
			_delay_ms(20); // Debounce delay
			if (keypadScan() == key)
			{

				// Verify key press
				while (keypadScan() == key)
					;
				if (key == '*')
					return;
			}
		}

		_delay_ms(200); // Add a small delay to prevent continuous reading of the same key press
		memset(temp_buff, 32, 23);
		temp_buff[23] = '\0';
		glcdString(0, temp_buff);
	}
}

void retrieveStudentData()
{
	glcdClearAll();
	glcdString(0, "Retrieving Data...");
	_delay_ms(700);

	uint16_t address = STUDENT_START_ADDRESS;
	char studentCode[STUDENT_CODE_SIZE];
	uint16_t studentCount = loadStudentNumber();

	uint16_t i;
	for (i = 0; i < studentCount; i++)
	{
		eepromReadString(address, studentCode);
		virTerminalSendString(studentCode);
		virTerminalSendString("\r\n");
		address += STUDENT_CODE_SIZE;
	}

	glcdClearAll();
	glcdString(0, "Data Retrieved");
	_delay_ms(700);
	glcdClearAll();
}

void trafficMonitoring()
{
	glcdClearAll();
	glcdString(2, "Press * to exit");
	char dist_buff[16];
	char presents_buff[23];
	char key = 0;
	int dist;

	while (1)
	{
		dist = getDistance();

		sprintf(dist_buff, "Dist: %d cm", dist);
		glcdString(0, dist_buff);
		if (dist < 6)
		{
			presentStudents++;
		}
		sprintf(presents_buff, "Presents: %d  ", presentStudents);
		glcdString(1, presents_buff);

		key = keypadScan();
		if (key != 0)
		{
			_delay_ms(20); // Debounce delay
			if (keypadScan() == key)
			{

				// Verify key press
				while (keypadScan() == key)
					;
				if (key == '*')
					return;
			}
		}
		_delay_ms(200); // Add a small delay to prevent continuous reading of the same key press

		memset(dist_buff, 32, 15);
		dist_buff[15] = '\0';
		glcdString(0, dist_buff);
		memset(presents_buff, 32, 22);
		presents_buff[23] = '\0';
		glcdString(1, presents_buff);
	}
}

void removeStudent()
{
	glcdClearAll();
	glcdString(0, "Enter Student Code:");
	char studentCode[STUDENT_CODE_SIZE]; // 40130023
	memset(studentCode, 0, STUDENT_CODE_SIZE);
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
		else if (key == '*') // Assuming '*' is used to clear the input
		{
			index = 0;
			glcdString(1, "                "); // Clear the input line
		}
		else
		{
			studentCode[index++] = key;
			glcdString(1, studentCode);
		}
	}

	// Validate the student code
	if (index != 8) // Assuming student code length should be 8
	{
		glcdString(2, "Invalid Code");
		buzzerOn();
		_delay_ms(500);
		buzzerOff();
	}
	else
	{
		// Save the student code to EEPROM
		// char buffer[16];
		// sprintf(buffer, "student %d", searchStudent(studentCode));
		// glcdString(2, 0, buffer);
		if (searchStudent(studentCode) == -1)
		{
			glcdString(2, "Code Not Found");
			buzzerOn();
			_delay_ms(500);
			buzzerOff();
		}
		else
		{
			removeStudentCode(studentCode);
			glcdString(2, "Code Removed");
		}
	}

	_delay_ms(700);
	return; // Return to attendance ready state
}