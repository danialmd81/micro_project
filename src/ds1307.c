#include "ds1307.h"

uint8_t bcdToDec(uint8_t bcd)
{
    return ((bcd / 16 * 10) + (bcd % 16));
}

uint8_t decToBcd(uint8_t dec)
{
    return ((dec / 10 * 16) + (dec % 10));
}

void ds1307Init()
{
    i2cInit();
}

void ds1307SetTime(uint8_t hour, uint8_t minute, uint8_t second)
{
    i2cStart();
    i2cWrite(DS1307_ADDRESS << 1);
    i2cWrite(0x00); // Set register pointer to 00h
    i2cWrite(decToBcd(second));
    i2cWrite(decToBcd(minute));
    i2cWrite(decToBcd(hour));
    i2cStop();
}

void ds1307SetDate(uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
    i2cStart();
    i2cWrite(DS1307_ADDRESS << 1);
    i2cWrite(0x03); // Set register pointer to 03h
    i2cWrite(decToBcd(day));
    i2cWrite(decToBcd(date));
    i2cWrite(decToBcd(month));
    i2cWrite(decToBcd(year));
    i2cStop();
}

void ds1307GetTime(uint8_t* hour, uint8_t* minute, uint8_t* second)
{
    i2cStart();
    i2cWrite(DS1307_ADDRESS << 1);
    i2cWrite(0x00); // Set register pointer to 00h
    i2cStart();
    i2cWrite((DS1307_ADDRESS << 1) | 1);
    *second = bcdToDec(i2cReadAck());
    *minute = bcdToDec(i2cReadAck());
    *hour = bcdToDec(i2cReadNack());
    i2cStop();
}

void ds1307GetDate(uint8_t* day, uint8_t* date, uint8_t* month, uint8_t* year)
{
    i2cStart();
    i2cWrite(DS1307_ADDRESS << 1);
    i2cWrite(0x03); // Set register pointer to 03h
    i2cStart();
    i2cWrite((DS1307_ADDRESS << 1) | 1);
    *day = bcdToDec(i2cReadAck());
    *date = bcdToDec(i2cReadAck());
    *month = bcdToDec(i2cReadAck());
    *year = bcdToDec(i2cReadNack());
    i2cStop();
}