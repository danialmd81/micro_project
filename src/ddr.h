#ifndef DDR_H
#define DDR_H

#define F_CPU 8000000UL
#define BAUD 9600
#define BAUD_PRESCALER (((F_CPU / 16 / (BAUD))) - 1)

//
#include <avr/interrupt.h>
// header to enable data flow control over pins
#include <avr/io.h>
#include <avr/iom32.h>
#include <avr/sleep.h>
// header to enable delay function in program
#include <util/delay.h>

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

// Array defined in another source file so used extern here
extern unsigned char keypad[4][4];

// Temperature ADC (PA0)
#define TEMP_DDR DDRA
#define TEMP_PORT PORTA
#define TEMP_PIN PA0

// LCD Pins (B)
#define LCD_DDR DDRB
#define LCD_PORT PORTB
#define LCD_RS 0
#define LCD_EN 1

// Keypad Pins (C)
#define KEYPAD_DDR DDRC
#define KEYPAD_PORT PORTC
#define KEYPAD_PIN PINC

// UART Pins (D0-D1)
#define UART_DDR DDRD
#define UART_TX PD1
#define UART_RX PD0

// Ultrasonic Pins (D2-D3)
#define US_TRIG_DDR DDRD
#define US_ECHO_DDR DDRD
#define US_TRIG_PORT PORTD
#define US_ECHO_PORT PIND
#define US_TRIG_PIN PD2
#define US_ECHO_PIN PD3
#define CALIBRATION_FACTOR 58.0 // 58 us/cm
#define US_ERROR -1 // Error indicator
#define US_NO_OBSTACLE -2 // No obstacle indicator

// Buzzer Pins (D4)
#define BUZZER_PIN PD4
#define BUZZER_DDR DDRD
#define BUZZER_PORT PORTD

#endif // DDR_H