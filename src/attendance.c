#include "attendance.h"

int presentStudents = 0; // Store the number of present students at any po

void submitStudentCode()
{
	lcdClear();
	lcdStringXY(1, 0, "Enter Student Code:");
	char studentCode[STUDENT_CODE_SIZE]; // 40130023
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
		// char buffer[16];
		// sprintf(buffer, "student %d", searchStudent(studentCode));
		// lcdStringXY(2, 0, buffer);
		if(searchStudent(studentCode)!=-1){
			lcdStringXY(2, 0, "Code Already Exists");
			buzzerOn();
			_delay_ms(500);
			buzzerOff();			
		}
		else{
			saveStudent(studentCode);
			lcdStringXY(2, 0, "Code Accepted");
		}
	}

	_delay_ms(700);
	return attendanceInitialization(); // Return to attendance ready state
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
			lcdClear();
			lcdStringXY(1, 0, "Enter Student Code:");
			char studentCode[STUDENT_CODE_SIZE];
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
			if (searchStudent(studentCode)!=-1)
			{
				lcdStringXY(2, 0, "Student Present");
				_delay_ms(700);
			}
			else
			{
				lcdStringXY(2, 0, "Student Absent");
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
	lcdClear();
	uint16_t address = STUDENT_START_ADDRESS;
	char buffer[BUFFER_SIZE];
	char studentCode[STUDENT_CODE_SIZE];
	int presentCount = loadStudentNumber();

	// Display the number of present students
	sprintf(buffer, "Present: %d", presentCount);
	lcdStringXY(1, 0, buffer);

	// Display the student codes one by one
	uint16_t i;
	for (i = 0; i < presentCount; i++)
	{
		eepromReadString(address, studentCode);
		lcdStringXY(2, 0, studentCode);
		_delay_ms(1000);
		address += STUDENT_CODE_SIZE;
	}

	// Return to the main menu after displaying all student codes
	return;
}

void temperatureMonitoring()
{
    lcdClear();
    char temp_buff[32];
    char key = 0;

    while (1)
    {
        int temperature = getTemp();
        sprintf(temp_buff, "Temp: %d C", temperature);
        lcdStringXY(1, 0, temp_buff);

        char exit_key[] = "Press * to exit";
        lcdStringXY(2, 0, exit_key);
        
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

        _delay_ms(50); // Add a small delay to prevent continuous reading of the same key press
        lcdClear();
    }
}

void retrieveStudentData()
{
	lcdClear();
	lcdStringXY(1, 0, "Retrieving Data...");
	_delay_ms(700);

	uint16_t address = STUDENT_START_ADDRESS;
	char studentCode[STUDENT_CODE_SIZE];
	uint16_t studentCount = loadStudentNumber();

	uint16_t i;
	for (i = 0; i < studentCount; i++)
	{
		eepromReadString(address, studentCode);
		uartSendString(studentCode);
		uartSendString("\r\n");
		address += STUDENT_CODE_SIZE;
	}

	lcdClear();
	lcdStringXY(1, 0, "Data Retrieved");
	_delay_ms(700);
	lcdClear();
}

void trafficMonitoring()
{
	lcdClear();
	char dist_buff[16];
	char presents_buff[32];
	char key = 0;
	while (1)
	{
		int dist = getDistance();

		// sprintf(dist_buff, "Dist:         ");
		sprintf(dist_buff, "Dist: %d cm", dist);
		lcdStringXY(1, 0, dist_buff);
		if (dist < 6)
		{
			presentStudents++;
		}
		sprintf(presents_buff, "Presents: %d  Press * to exit", presentStudents);
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
				if (key == '*')
					return;
			}
		}
		_delay_ms(50); // Add a small delay to prevent continuous reading of the same key press
		lcdClear();
	}

}