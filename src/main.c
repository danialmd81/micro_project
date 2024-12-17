#include "attendance.h"
#include "buzzer.h"
#include "eeprom.h"
#include "glcd.h"
#include "keypad.h"
#include "rfid.h"
#include "ultrasonic.h"
#include "virtualTerminal.h"

/*
atmega64 setting
{CKSEL=0}
{CLOCK=8MHz}

buzzer setting
{VNOM=5V}
{LOAD=220}
{FREQ=2kHz}

UART
{BAUDRATE=9600}
{DATABITS=8}
{PARITY=NONE}
{STOPBITS=1}
*/

void testUltrasonic()
{
	ultrasonicInit();

	while (1)
	{
		int distance = getDistance();
		char buffer[16];
		sprintf(buffer, "Dist: %d cm", distance);
		glcdString(0, buffer);
		_delay_ms(1000);
		glcdClearAll();
	}
}

void testKeypad()
{
	keypadInit();

	while (1)
	{
		char key = keypadGetkey();
		char str[2];
		str[0] = key;
		str[1] = '\0';
		glcdString(0, str);
		_delay_ms(50);
		glcdClearAll();
	}
}

void testTemperature()
{
	glcdInit();
	tempInit();

	char buffer[16];
	while (1)
	{
		int temperature = getTemp();
		sprintf(buffer, "Temp: %d C", temperature);
		glcdString(0, buffer);
		_delay_ms(50);
	}
}

void testVirtualTerminal()
{
	virTerminalInit();

	while (1)
	{
		virTerminalSendString("Hello from UART\r\n");
		_delay_ms(500);
	}
}

void testGLCD()
{
	glcdClearAll(); /* Clear all GLCD display */
	glcdString(0, "Atmel");
}

void testRFID()
{
	unsigned char value[13];
	unsigned char value1[13] = "123456789012"; // Predefined ID for master
	unsigned char value2[13] = "987654321098"; // Predefined ID for student
	int i = 0, j = 0, k = 0;

	glcdClearAll(); // Clear all GLCD display

	while (1)
	{
		// Read input from virtual terminal
		value[i] = virTerminalReceive();
		virTerminalSendChar(value[i]);
		_delay_ms(1);

		if (value[i] == '*')
		{
			memset(value, 0, sizeof(value));
			i = -1;
		}
		i++;

		if (i == 12)
		{
			value[i] = '\0';
			for (j = 0; value1[j] != '\0'; j++)
			{
				if (value[j] == value1[j])
					k++;
			}
			if (k == 12) // Match with the predefined ID
			{
				glcdClearAll();
				glcdString(0, "Access Granted");
				glcdString(1, "Master");
				_delay_ms(1000);
				glcdClearAll();
			}
			else
			{
				k = 0;
				for (j = 0; value2[j] != '\0'; j++)
				{
					if (value[j] == value2[j])
						k++;
				}
				if (k == 12)
				{
					glcdClearAll();
					glcdString(0, "Access Granted");
					glcdString(1, "Student");
					_delay_ms(1000);
					glcdClearAll();
				}
				else
				{
					glcdClearAll();
					glcdString(0, "Access Denied");
					_delay_ms(1000);
					glcdClearAll();
				}
			}
			i = 0;
			k = 0;
		}
	}
}

void displayMainMenu()
{
	glcdClearAll();

	glcdString(0, "1.Attendance System");
	glcdString(1, "2.Student Management");
	glcdString(2, "3.Present Students");
	glcdString(3, "4.Temperature");
	glcdString(4, "5.Student Data");
	glcdString(5, "6.Traffic Monitoring");
	glcdString(6, "7.Remove Student");
}

void init()
{
	glcdInit();
	keypadInit();
	buzzerInit();
	tempInit();
	ultrasonicInit();
	virTerminalInit();
	rfidInit();
}

void menu()
{
	// eepromReset();

	while (1)
	{
		displayMainMenu();
		char key = keypadGetkey();
		switch (key)
		{
		case '1':
			attendanceInitialization();
			break;
		case '2':
			studentManagement();
			break;
		case '3':
			viewPresentStudents();
			break;
		case '4':
			temperatureMonitoring();
			break;
		case '5':
			retrieveStudentData();
			break;
		case '6':
			trafficMonitoring();
			break;
		case '7':
			removeStudent();
			break;
		default:
			buzzerOn();
			_delay_ms(200);
			buzzerOff();
			break;
		}
	}
}

int main()
{
	init();

	// Display the main menu and handle user input
	menu();

	// Uncomment one of the following lines to test a specific component
	// testUltrasonic();
	// testKeypad();
	// testTemperature();
	// testVirtualTerminal();
	// testGLCD();
	// testRFID();

	return 0;
}