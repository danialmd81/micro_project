#ifndef EEPROM_H
#define EEPROM_H

#include "attendance.h"
#include "buzzer.h"
#include "ddr.h"
#include "eeprom.h"
#include "keypad.h"
#include "lcd.h"
#include "ultrasonic.h"
#include "virtualTerminal.h"



void eepromReset();
void eepromWriteString(uint16_t address, const char* data);
void eepromReadString(uint16_t address, char* buffer);
void saveStudentNumber(uint16_t number);
uint16_t loadStudentNumber();
void saveStudent(char stuedentCode[10]);
uint16_t searchStudent(char* studentCode);
void removeStudentCode(char* studentCode);
#endif // EEPROM_H