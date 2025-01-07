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
// #define BUFFER_SIZE 44
//
#define EEPROM_SIZE 0x7ff
#define STUDENT_NUMBER_ADDRESS 0x0000
#define STUDENT_START_ADDRESS 0x0008
#define STUDENT_CODE_SIZE 9
#define DATE_SIZE 14
#define STUDENT_INFO_SIZE 24
#define STUDENT_MAX_NUMBER 50

void eepromReset();
void eepromWriteString(uint16_t address, const char* data);
void eepromReadString(uint16_t address, char* buffer);
void saveStudentNumber(uint16_t number);
uint16_t loadStudentNumber();
void saveStudent(char stuedentCode[STUDENT_CODE_SIZE]);
uint16_t searchStudent(char studentCode[STUDENT_CODE_SIZE]);
void removeStudentCode(char studentCode[STUDENT_CODE_SIZE]);
#endif // EEPROM_H