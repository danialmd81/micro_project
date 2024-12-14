#include "eeprom.h"

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
	uint16_t length = 9;
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
	return (uint16_t)atoi(buffer);
}

void saveStudent(char stuedentCode[10])
{
	
}