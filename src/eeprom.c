#include "eeprom.h"

void eepromWriteString(uint16_t address, const char* data)
{
	while (*data)
	{
		eeprom_write_byte((uint8_t*)address++, *data++);
	}
	eeprom_write_byte((uint8_t*)address, '\0'); // Null-terminate the string
}

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