#ifndef DDR_H
#define DDR_H

#define F_CPU 8000000UL
#define BAUD 9600
#define BAUD_PRESCALER (((F_CPU / 16 / (BAUD))) - 1)

//
#include <avr/interrupt.h>
// header to enable data flow control over pins
#include <avr/eeprom.h>
#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/sleep.h>
// header to enable delay function in program
#include <util/delay.h>

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif // DDR_H