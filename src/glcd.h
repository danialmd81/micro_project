#include <avr/io.h>
#include <avr/iom64.h>
#include <inttypes.h>
#include <util/delay.h> /* Include defined delay header file */

#ifndef GLCD_H
#define GLCD_H

#define Data_Port PORTB /* Define data port for GLCD */
#define Command_Port PORTA /* Define command port for GLCD */
#define Data_Port_Dir DDRB /* Define data port for GLCD */
#define Command_Port_Dir DDRA /* Define command port for GLCD */

#define GLCD_RS PA0 /* Define control pins */
#define GLCD_RW PA1
#define GLCD_EN PA2
#define GLCD_CS1 PA3
#define GLCD_CS2 PA4
#define GLCD_RST PA5

#define LINE_SIZE 26
#define TotalPage 8

void glcdCommand(char Command); /* GLCD command function */
void glcdData(char Data); /* GLCD data function */
void glcdInit(); /* GLCD initialize function */
void glcdClearAll(); /* GLCD all display clear function */
void glcdClearLine(int page);
void glcdString(char page_no, char* str); /* GLCD string write function */

#endif
