#ifndef EEPROM_H
#define EEPROM_H

#include <avr/eeprom.h>
#include <avr/io.h>

// Function to write a string to EEPROM
void eepromWriteString(uint16_t address, const char* data);

// Function to read a string from EEPROM
void eepromReadString(uint16_t address, char* buffer);

#endif // EEPROM_H