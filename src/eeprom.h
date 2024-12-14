#ifndef EEPROM_H
#define EEPROM_H

#include "ddr.h"
#include <avr/eeprom.h>
#include <avr/io.h>

void saveStudentNumber(uint16_t number);
uint16_t loadStudentNumber();
void saveStudent(char stuedentCode[10]);

#endif // EEPROM_H