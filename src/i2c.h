#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <util/twi.h>

void i2cInit();
void i2cStart();
void i2cStop();
void i2cWrite(uint8_t data);
uint8_t i2cReadAck();
uint8_t i2cReadNack();

#endif // I2C_H