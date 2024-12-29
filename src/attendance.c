#include "attendance.h"
#include "ultrasonic.h"

void submitStudentCode()
{
	glcdClearAll();
	if(getElapsedTime() > TIME_LIMIT_SECOND)
	{
		glcdString(0, "The absence attendance time is over");
		buzzerOn();
		_delay_ms(700);
		buzzerOff();
	}
	else
	{
	// glcdString(0, "Enter Student Code(press c to clear|press * to exit):");
	glcdString(0, "Enter Student Code:");
	char studentCode[STUDENT_CODE_SIZE] = { 0 };
	int index = 0;
	char key;

	while (1)
	{
		key = keypadGetkey();
		if(getElapsedTime() > TIME_LIMIT_SECOND)
		{
			glcdClearAll();
			index = 0;
			memset(studentCode, 0, STUDENT_CODE_SIZE);
			glcdString(0, "The absence attendance time is over");
			buzzerOn();
			_delay_ms(700);
			buzzerOff();
			break;
		}
		else if (key == '=') // Assuming '#' is used to submit the code
		{
			studentCode[index] = '\0';
			if (index == 8)
			{
				if (searchStudent(studentCode) != -1)
				{
					glcdString(2, "Code Already Exists");
					buzzerOn();
					_delay_ms(500);
					buzzerOff();
					index = 0;
					memset(studentCode, 0, STUDENT_CODE_SIZE);
					glcdClearLine(1);
					glcdClearLine(2);
				}
				else
				{
					saveStudent(studentCode);
					glcdString(2, "Code Accepted");
					_delay_ms(700);
					index = 0;
					memset(studentCode, 0, STUDENT_CODE_SIZE);
					glcdClearLine(1);
					glcdClearLine(2);
				}
			}
			else
			{
				glcdString(2, "Invalid Code");
				buzzerOn();
				_delay_ms(500);
				buzzerOff();
				glcdClearLine(2);
			}
		}
		else if (key == '*') // Assuming '*' is used to exit the input
		{
			break;
		}
		else if (key == 'c') // Assuming 'c' is used to clear the input
		{
			index = 0;
			memset(studentCode, 0, STUDENT_CODE_SIZE);
			glcdClearLine(1);
		}
		else if (isnum(key))
		{
			if (index < STUDENT_CODE_SIZE-1)
			{
				studentCode[index++] = key;
				glcdString(1, studentCode);
			}
			else
			{
				glcdString(2, "Invalid Code");
				buzzerOn();
				_delay_ms(500);
				buzzerOff();
				glcdClearLine(2);
			}
		}
		else if (isnum(key))
		{
			glcdString(2, "Invalid Key");
			buzzerOn();
			_delay_ms(500);
			buzzerOff();
			glcdClearLine(2);
		}
	}
	}
}

void studentManagement()
{
	glcdClearAll();
	// glcdString(0, "Enter Student Code(press c to clear|press * to exit):");
	glcdString(0, "Enter Student Code:");
	char studentCode[STUDENT_CODE_SIZE]; // 40130023
	memset(studentCode, 0, STUDENT_CODE_SIZE);
	int index = 0;
	char key;

	while (1)
	{
		key = keypadGetkey();
		if (key == '=') // Assuming '=' is used to submit the code
		{
			studentCode[index] = '\0';
			if (index == 8)
			{
				if (searchStudent(studentCode) != -1)
				{
					glcdString(2, "Student Present");
					_delay_ms(500);
					index = 0;
					glcdClearLine(1);
					glcdClearLine(2);
				}
				else
				{
					glcdString(2, "Student Absent");
					buzzerOn();
					_delay_ms(500);
					buzzerOff();
					index = 0;
					glcdClearLine(1);
					glcdClearLine(2);
				}
			}
			else
			{
				glcdString(2, "Invalid Code");
				buzzerOn();
				_delay_ms(500);
				buzzerOff();
				index = 0;
				glcdClearLine(2);
			}
		}
		else if (key == '*') // Assuming '*' is used to exit the input
		{
			break;
		}
		else if (key == 'c') // Assuming 'c' is used to clear the input
		{
			index = 0;
			memset(studentCode, 0, STUDENT_CODE_SIZE);
			glcdClearLine(1);
		}
		else if (isnum(key))
		{
			if (index > STUDENT_CODE_SIZE-1)
			{
				glcdString(2, "Invalid Code");
				buzzerOn();
				_delay_ms(500);
				buzzerOff();
				glcdClearLine(2);
				continue;
			}
			studentCode[index] = key;
			glcdString(1, studentCode);
			index++;
		}
		else
		{
			glcdString(2, "Invalid Key");
			buzzerOn();
			_delay_ms(500);
			buzzerOff();
			glcdClearLine(2);
		}
	}
}

void viewPresentStudents()
{
	glcdClearAll();
	uint16_t address = STUDENT_START_ADDRESS;
	char buffer[12];
	int presentCount = loadStudentNumber();

	// Display the number of present students
	sprintf(buffer, "Present: %d", presentCount);
	glcdString(0, buffer);

	// Display the student codes
	uint16_t i;
	for (i = 0; i < presentCount; i++)
	{
		char student[STUDENT_INFO_SIZE];
		eepromReadString(address, student);
		glcdString(1, student);
		_delay_ms(1000);
		glcdClearLine(1);
		address += STUDENT_INFO_SIZE;
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
	uint16_t studentCount = loadStudentNumber();

	uint16_t i;
	for (i = 0; i < studentCount; i++)
	{
		char student[STUDENT_INFO_SIZE];
		eepromReadString(address, student);
		virTerminalSendString(student);
		virTerminalSendString("\r\n");
		address += STUDENT_INFO_SIZE;
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
    char traffic_buff[23];
    char key = 0;

    while (1)
    {
        sprintf(dist_buff, "Dist: %d cm", Distance);
        glcdString(0, dist_buff);
        sprintf(traffic_buff, "traffic: %d  ", Traffic);
        glcdString(1, traffic_buff);

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
        memset(traffic_buff, 32, 22);
        traffic_buff[23] = '\0';
        glcdString(1, traffic_buff);
    }
}

void removeStudent()
{
	glcdClearAll();
	// glcdString(0, "Enter Student Code(press c to clear|press * to exit):");
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
			if (index == 8)
			{
				if (searchStudent(studentCode) != -1)
				{
					glcdString(2, "Student Removed");
					removeStudentCode(studentCode);
					_delay_ms(700);
					index = 0;
					glcdClearLine(1);
					glcdClearLine(2);
				}
				else
				{
					glcdString(2, "Student Not Found");
					buzzerOn();
					_delay_ms(700);
					buzzerOff();
					index = 0;
					glcdClearLine(1);
					glcdClearLine(2);
				}
			}
			else
			{
				glcdString(2, "Invalid Code");
				buzzerOn();
				_delay_ms(500);
				buzzerOff();
				glcdClearLine(2);
				continue;
			}
		}
		else if (key == '*')
		{
			break;
		}
		else if (key == 'c') // Assuming '*' is used to clear the input
		{
			index = 0;
			memset(studentCode, ' ', STUDENT_CODE_SIZE);
			glcdClearLine(1);
		}
		else if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0')
		{
			if (index > 7)
			{
				glcdString(2, "Invalid Code");
				buzzerOn();
				_delay_ms(700);
				buzzerOff();
				glcdClearLine(2);
				continue;
			}
			studentCode[index] = key;
			glcdString(1, studentCode);
			index++;
		}
		else
		{
			glcdString(2, "Invalid Key");
			buzzerOn();
			_delay_ms(700);
			buzzerOff();
			glcdClearLine(2);
		}
	}
}