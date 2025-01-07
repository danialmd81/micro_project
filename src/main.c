#include "attendance.h"
#include "buzzer.h"
#include "ds1307.h"
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

void displayTimeAndDate()
{
	uint8_t hour, minute, second;
	uint8_t day, date, month, year;
	char buffer[20];

	ds1307GetTime(&hour, &minute, &second);
	ds1307GetDate(&day, &date, &month, &year);

	sprintf(buffer, "Time: %02d:%02d:%02d", hour, minute, second);
	virTerminalSendString(buffer);
	sprintf(buffer, "Date: %02d/%02d/20%02d", date, month, year);
	virTerminalSendString(buffer);
}

void testUltrasonic()
{
	ultrasonicInit();

	while (1)
	{
		// ultrasonicTrigger();
		int dist = Distance;
		int t = getElapsedTime();
		if (dist != US_ERROR && dist != US_NO_OBSTACLE)
		{
			char buffer[25];
			sprintf(buffer, "Dist: %d cm     %d s", dist, t);
			glcdString(0, buffer);
			_delay_ms(100);
			glcdClearAll();
		}
		_delay_ms(60); // Wait between measurements
	}

	return 0;
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
#define RFID_LENGTH 8
#define RFID_BUFFER_SIZE 9 // Including null terminator

	unsigned char value[RFID_BUFFER_SIZE];
	unsigned char value1[RFID_BUFFER_SIZE] = "12345678"; // Predefined ID for master
	unsigned char value2[RFID_BUFFER_SIZE] = "87654321"; // Predefined ID for student
	int i = 0, j = 0, matches = 0;

	glcdClearAll(); // Clear all GLCD display

	while (1)
	{
		// Protect against buffer overflow
		if (i >= RFID_LENGTH)
		{
			i = 0;
			memset(value, 0, sizeof(value));
			glcdClearAll();
			glcdString(0, "Buffer Overflow");
			_delay_ms(1000);
			glcdClearAll();
			continue;
		}

		// Read input from virtual terminal
		value[i] = virTerminalReceive();
		virTerminalSendChar(value[i]);
		_delay_ms(1);

		// Handle backspace
		if (value[i] == 8)
		{
			if (i > 0) // Only backspace if there are characters
			{
				i--;
				virTerminalSendString(" \b");
			}
			continue;
		}
		// Handle star
		else if (value[i] == '*')
		{
			// Reset for next attempt
			i = 0;
			memset(value, 0, sizeof(value));
			continue;
		}
		i++;

		// Process complete RFID input
		if (i == RFID_LENGTH)
		{
			value[i] = '\0';
			matches = 0;

			if (strcmp(value, value1) == 0)
			{
				glcdClearAll();
				glcdString(0, "Access Granted");
				glcdString(1, "Master");
				_delay_ms(1000);
				glcdClearAll();
				return;
			}

			else if (strcmp(value, value2) == 0)
			{
				glcdClearAll();
				glcdString(0, "Access Granted");
				glcdString(1, "Student");
				_delay_ms(1000);
				glcdClearAll();
				return;
			}

			// Invalid ID
			glcdClearAll();
			glcdString(0, "Access Denied");
			glcdString(1, "Invalid ID");
			_delay_ms(1000);
			glcdClearAll();

			// Reset for next attempt
			i = 0;
			memset(value, 0, sizeof(value));
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
	glcdString(7, "8.RFID");
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
	ds1307Init();
	timerInit();
}

void menu()
{
	while (1)
	{
		displayMainMenu();
		char key = keypadGetkey();
		switch (key)
		{
		case '1':
			submitStudentCode();
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
		case '8':
			testRFID();
			break;
		case '9':
			eepromReset();
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

	// testUltrasonic();
	// testKeypad();
	// testTemperature();
	// testVirtualTerminal();
	// testGLCD();
	// testRFID();

	return 0;
}