#ifndef DS1307_H
#define DS1307_H

#include <avr/io.h>
#include "i2c.h"

#define DS1307_ADDRESS 0x68

void ds1307Init();
void ds1307SetTime(uint8_t hour, uint8_t minute, uint8_t second);
void ds1307SetDate(uint8_t day, uint8_t date, uint8_t month, uint8_t year);
void ds1307GetTime(uint8_t* hour, uint8_t* minute, uint8_t* second);
void ds1307GetDate(uint8_t* day, uint8_t* date, uint8_t* month, uint8_t* year);

#endif // DS1307_H