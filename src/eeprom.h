#include <avr/eeprom.h>
#include <avr/io.h>
#include <avr/iom64.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef EEPROM_H
#define EEPROM_H

#include "common.h"

//
#define BUFFER_SIZE 44

//
#define EEPROM_SIZE 0x3ff
#define STUDENT_NUMBER_ADDRESS 0x0000
#define STUDENT_START_ADDRESS 0x0010
#define STUDENT_CODE_SIZE 9
#define STUDENT_INFO_SIZE 48
#define STUDENT_MAX_NUMBER 150

void eepromReset();
void eepromWriteString(uint16_t address, const char* data);
void eepromReadString(uint16_t address, char* buffer);
void saveStudentNumber(uint16_t number);
uint16_t loadStudentNumber();
void saveStudent(char stuedentCode[10]);
uint16_t searchStudent(char* studentCode);
void removeStudentCode(char* studentCode);
#endif // EEPROM_H