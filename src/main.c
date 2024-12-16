#include "attendance.h"
#include "buzzer.h"
#include "eeprom.h"
#include "glcd.h"
#include "keypad.h"
#include "lcd.h"
#include "rfid.h"
#include "ultrasonic.h"
#include "virtualTerminal.h"

/*
atmega32 setting
{CKSEL=0}
{CLOCK=16MHz}

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
		lcdStringXY(1, 0, buffer);
		_delay_ms(1000);
		lcdClear();
	}
}

void testKeypad()
{
	keypadInit();

	while (1)
	{
		char key = keypadGetkey();
		lcdChar(key);
		_delay_ms(50);
		lcdClear();
	}
}

void testTemperature()
{
	tempInit();

	char buffer[16];
	while (1)
	{
		float temperature = getTemp();
		sprintf(buffer, "Temp: %3.2f C", (double)temperature);
		lcdStringXY(1, 0, buffer);
		_delay_ms(50);
	}
}

void testVirtualTerminal()
{
	uartInit();

	while (1)
	{
		uartSendString("Hello from UART\r\n");
		_delay_ms(500);
	}
}

void testGLCD()
{
	glcdInit(); /* Initialize GLCD */
	glcdClearAll(); /* Clear all GLCD display */
	glcdString(0, "Atmel");
}

void testRFID()
{
	unsigned char value[13];
	unsigned char value1[13] = "123456789012"; // Predefined ID for master
	unsigned char value2[13] = "987654321098"; // Predefined ID for student
	int i = 0, j = 0, k = 0;

	uartInit(); // Initialize UART with baud rate 9600
	glcdInit(); // Initialize GLCD
	glcdClearAll(); // Clear all GLCD display

	while (1)
	{
		// Read input from virtual terminal
		value[i] = uartReceive();
		uartSendChar(value[i]);
		_delay_ms(1);

		if (value[i] == '\n')
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
	uartInit();
}

int main()
{
	// eepromReset();

	init();

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

	// Uncomment one of the following lines to test a specific component
	// testUltrasonic();
	// testKeypad();
	// testTemperature();
	// testVirtualTerminal();
	// testGLCD();
	// testRFID();

	return 0;
}