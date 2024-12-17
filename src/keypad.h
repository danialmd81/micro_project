#include <avr/io.h>
#include <avr/iom64.h>
#include <util/delay.h>

#ifndef KEYPAD_H
#define KEYPAD_H

// Array defined in another source file so used extern here
extern unsigned char keypad[4][4];

// Keypad Pins (C)
#define KEYPAD_DDR DDRC
#define KEYPAD_PORT PORTC
#define KEYPAD_PIN PINC

void keypadInit();
char keypadScan();
char keypadGetkey();

#endif // KEYPAD_H