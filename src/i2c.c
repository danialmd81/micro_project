#include "i2c.h"

void i2cInit()
{
    // Set SCL frequency to 100kHz with 8MHz clock
    TWSR = 0x00;
    TWBR = 0x48;
    // Enable TWI (I2C)
    TWCR = (1 << TWEN);
}

void i2cStart()
{
    // Send START condition
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // Wait for TWINT flag set
    while (!(TWCR & (1 << TWINT)));
}

void i2cStop()
{
    // Send STOP condition
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2cWrite(uint8_t data)
{
    // Load data into TWDR register
    TWDR = data;
    // Start transmission
    TWCR = (1 << TWINT) | (1 << TWEN);
    // Wait for TWINT flag set
    while (!(TWCR & (1 << TWINT)));
}

uint8_t i2cReadAck()
{
    // Enable ACK and start reception
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    // Wait for TWINT flag set
    while (!(TWCR & (1 << TWINT)));
    // Return received data
    return TWDR;
}

uint8_t i2cReadNack()
{
    // Enable reception without ACK
    TWCR = (1 << TWINT) | (1 << TWEN);
    // Wait for TWINT flag set
    while (!(TWCR & (1 << TWINT)));
    // Return received data
    return TWDR;
}