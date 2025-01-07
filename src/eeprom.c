#include "eeprom.h"

void eepromReset()
{
	uint16_t i;
	for (i = 0; i <= EEPROM_SIZE; i++)
	{
		eeprom_write_byte((uint8_t*)i, 0xFF);
	}
	saveStudentNumber(0);
	buzzerOn();
	_delay_ms(200);
	buzzerOff();
}

// Function to write a string to EEPROM
void eepromWriteString(uint16_t address, const char* data)
{
	while (*data)
	{
		eeprom_write_byte((uint8_t*)address++, *data++);
	}
	eeprom_write_byte((uint8_t*)address, '\0'); // Null-terminate the string
}

// Function to read a string from EEPROM
void eepromReadString(uint16_t address, char* buffer)
{
	uint16_t length = STUDENT_INFO_SIZE;
	while (length--)
	{
		*buffer = eeprom_read_byte((const uint8_t*)address++);
		if (*buffer == '\0')
			break;
		buffer++;
	}
	*buffer = '\0'; // Ensure the string is null-terminated
}

// save student nuber in eeprom
void saveStudentNumber(uint16_t number)
{
	char buffer[8];
	sprintf(buffer, "%u", number);
	eepromWriteString(STUDENT_NUMBER_ADDRESS, buffer);
}
// load student number from eeprom
uint16_t loadStudentNumber()
{
	char buffer[10];
	eepromReadString(STUDENT_NUMBER_ADDRESS, buffer);
	uint16_t studentNumber = atoi(buffer);

	if (studentNumber <= STUDENT_MAX_NUMBER)
	{
		return studentNumber;
	}
	else
	{
		return 0;
	}
}

//  save student from start address and append new ones
void saveStudent(char studentCode[STUDENT_CODE_SIZE])
{
	uint16_t address = STUDENT_START_ADDRESS + loadStudentNumber() * STUDENT_INFO_SIZE;
	char student[STUDENT_INFO_SIZE];
	uint8_t hour, minute, second, day, date, month, year;
	char buffer[DATE_SIZE];

	ds1307GetTime(&hour, &minute, &second);
	ds1307GetDate(&day, &date, &month, &year);

	// sprintf(buffer, "%02d/%02d/%02d %02d:%02d:%02d\0", date, month, year, hour, minute, second);
	sprintf(buffer, "%02d/%02d/%02d %02d:%02d\0", date, month, year, hour, minute);
	sprintf(student, "%s %s", studentCode, buffer);
	eepromWriteString(address, student);

	saveStudentNumber(loadStudentNumber() + 1);
}

// return address of student if exist else return -1
uint16_t searchStudent(char studentCode[STUDENT_CODE_SIZE])
{
	uint16_t address = STUDENT_START_ADDRESS;
	char buffer[STUDENT_INFO_SIZE];

	uint16_t i;
	for (i = 0; i < loadStudentNumber(); i++)
	{
		eepromReadString(address, buffer);
		if (strncmp(buffer, studentCode, STUDENT_CODE_SIZE - 1) == 0)
		{
			return address;
		}
		address += STUDENT_INFO_SIZE;
	}

	return (uint16_t)-1;
}

void removeStudentCode(char studentCode[STUDENT_CODE_SIZE])
{
	uint16_t address = searchStudent(studentCode);
	if (address != (uint16_t)-1)
	{
		uint16_t studentCount = loadStudentNumber();
		uint16_t i;
		for (i = address; i < (STUDENT_START_ADDRESS + (studentCount - 1) * STUDENT_INFO_SIZE); i += STUDENT_INFO_SIZE)
		{
			char buffer[STUDENT_INFO_SIZE];
			eepromReadString(i + STUDENT_INFO_SIZE, buffer);
			eepromWriteString(i, buffer);
		}
		uint16_t j;
		for (j = 0; j < STUDENT_INFO_SIZE; j++)
		{
			eeprom_write_byte((uint8_t*)(STUDENT_START_ADDRESS + (studentCount - 1) * STUDENT_INFO_SIZE + j), 0xFF);
		}
		saveStudentNumber(studentCount - 1);
	}
}