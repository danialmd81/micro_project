#include "eeprom.h"

void eepromReset()
{
	uint16_t i;
	for (i = 0; i <= EEPROM_SIZE; i++)
	{
		eeprom_write_byte((uint8_t*)i, 0xFF);
	}
	saveStudentNumber(0);
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
	uint16_t length = STUDENT_CODE_SIZE;
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
	char buffer[10];
	sprintf(buffer, "%u", number);
	eepromWriteString(STUDENT_NUMBER_ADDRESS, buffer);
}

// load student number from eeprom
uint16_t loadStudentNumber()
{
	char buffer[10];
	eepromReadString(STUDENT_NUMBER_ADDRESS, buffer);
	uint16_t studentNumber = atoi(buffer);

	if (studentNumber >= 0 && studentNumber <= STUDENT_MAX_NUMBER)
	{
		return studentNumber;
	}
	else
		return (uint16_t)0;
}

// for the first time i don't know to do what
//  save student from start address and append new ones
void saveStudent(char stuedentCode[10])
{
	uint16_t address = STUDENT_START_ADDRESS + loadStudentNumber() * STUDENT_CODE_SIZE;
	eepromWriteString(address, stuedentCode);
	saveStudentNumber(loadStudentNumber() + 1);
}

// return address of student if exist else return -1
uint16_t searchStudent(char* studentCode)
{
	uint16_t address = STUDENT_START_ADDRESS;
	char buffer[STUDENT_CODE_SIZE];

	uint16_t i;
	for (i = 0; i < loadStudentNumber(); i++)
	{
		eepromReadString(address, buffer);
		if (strcmp(buffer, studentCode) == 0)
		{
			return address;
		}
		address += STUDENT_CODE_SIZE;
	}

	return (uint16_t)-1;
}

void removeStudentCode(char* studentCode)
{
	uint16_t address = searchStudent(studentCode);
	if (address != (uint16_t)-1)
	{
		uint16_t studentCount = loadStudentNumber();
		uint16_t i;
		for (i = address; i < (STUDENT_START_ADDRESS + (studentCount - 1) * STUDENT_CODE_SIZE); i += STUDENT_CODE_SIZE)
		{
			char buffer[STUDENT_CODE_SIZE];
			eepromReadString(i + STUDENT_CODE_SIZE, buffer);
			eepromWriteString(i, buffer);
		}
		uint16_t j;
		for(j=0;j<STUDENT_CODE_SIZE;j++){
			eeprom_write_byte((uint8_t*)(STUDENT_START_ADDRESS + (studentCount - 1) * STUDENT_CODE_SIZE + j), 0xFF);	
			}
		saveStudentNumber(studentCount - 1);
	}
}