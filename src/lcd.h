#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <avr/iom32.h>
#include <util/delay.h>

// LCD Pins (B)
#define LCD_DDR DDRB
#define LCD_PORT PORTB
#define LCD_RS 0
#define LCD_EN 1

void lcdCommand(unsigned char cmnd);
void lcdInit();
void lcdChar(unsigned char data);
void lcdString(char* str);
void lcdStringXY(unsigned char row, unsigned char pos, char* str);
void lcdClear();

#endif // LCD_H