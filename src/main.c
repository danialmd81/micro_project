#include "attendance.h"
#include "buzzer.h"
#include "ddr.h"
#include "eeprom.h"
#include "keypad.h"
#include "lcd.h"
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
		sprintf(buffer, "Temp: %3.2f C", temperature);
		lcdStringXY(1, 0, buffer);
		_delay_ms(50);
	}
}

void testVirtualTerminal()
{
	uartInit(BAUD_PRESCALER);

	while (1)
	{
		uartSendString("Hello from UART\r\n");
		_delay_ms(500);
	}
}

void displayMainMenu(int startOption)
{
	lcdClear();

	switch (startOption)
	{
	case 1:
		lcdStringXY(1, 0, "1. Attendance Initialization");
		lcdStringXY(2, 0, "2. Student Management");
		break;
	case 2:
		lcdStringXY(1, 0, "3. View Present Students");
		lcdStringXY(2, 0, "4. Temperature Monitoring");
		break;
	case 3:
		lcdStringXY(1, 0, "5. Retrieve Student Data");
		lcdStringXY(2, 0, "6. Traffic Monitoring");
		break;
	default:
		lcdStringXY(1, 0, "1. Attendance Initialization");
		lcdStringXY(2, 0, "2. Student Management");
		break;
	}
}

void init()
{
	lcdInit();
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
	int startOption = 1;

	while (1)
	{
		displayMainMenu(startOption);
		char key = keypadGetkey();
		switch (key)
		{
		case '0':
			startOption++;
			if (startOption > 3)
			{
				startOption = 1;
			}
			break;
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

	return 0;
}