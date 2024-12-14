#ifndef LCD_H
#define LCD_H

#include "ddr.h"

void lcdCommand(unsigned char cmnd);
void lcdInit();
void lcdChar(unsigned char data);
void lcdString(char* str);
void lcdStringXY(unsigned char row, unsigned char pos, char* str);
void lcdClear();

#endif // LCD_H