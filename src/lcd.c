#include "lcd.h"

void lcdCommand(unsigned char cmnd)
{
	PORTB = (PORTB & 0x0f) | (cmnd & 0xf0); /* SEND COMMAND TO DATA PORT */
	PORTB &= ~(1 << LCD_RS); /* RS = 0 FOR COMMAND */
	PORTB |= (1 << LCD_EN); /* EN = 1 FOR H TO L PULSE */
	_delay_us(1); /* WAIT FOR MAKE ENABLE WIDE */
	PORTB &= ~(1 << LCD_EN); /* EN = 0 FOR H TO L PULSE */
	_delay_us(100); /* WAIT FOR MAKE ENABLE WIDE */

	PORTB = (PORTB & 0x0f) | (cmnd << 4); /* SEND COMMAND TO DATA PORT */
	PORTB |= (1 << LCD_EN); /* EN = 1 FOR H TO L PULSE */
	_delay_us(1); /* WAIT FOR MAKE ENABLE WIDE */
	PORTB &= ~(1 << LCD_EN); /* EN = 0 FOR H TO L PULSE */
	_delay_us(2000); /* WAIT FOR MAKE ENABLE WIDE */
}

void lcdInit()
{
	LCD_DDR = 0xFF;
	_delay_ms(20); /* WAIT FOR SOME TIME */
	lcdCommand(0x02); /* SEND $32 FOR INIT OT 0X02 */
	lcdCommand(0x28); /* INIT. LCD 2 LINE, 5 X 7 MATRIX */
	lcdCommand(0x0C); /* DISPLAY ON CURSOR ON */
	lcdCommand(0x01); /* LCD CLEAR */
	lcdCommand(0x82); /* SHIFT CURSOR TO WRITE */
}

void lcdChar(unsigned char data)
{
	PORTB = (PORTB & 0x0f) | (data & 0xf0); /* SEND DATA TO DATA PORT */
	PORTB |= (1 << LCD_RS); /* MAKE RS = 1 FOR DATA */
	PORTB |= (1 << LCD_EN); /* EN=0 FOR H TO L PULSE */
	_delay_us(1); /* WAIT FOR MAKE ENABLE WIDE */
	PORTB &= ~(1 << LCD_EN); /* EN = 0 FOR H TO L PULSE */
	_delay_us(100); /* WAIT FOR MAKE ENABLE WIDE */

	PORTB = (PORTB & 0x0f) | (data << 4); /*  */
	PORTB |= (1 << LCD_EN); /* EN=0 FOR H TO L PULSE*/
	_delay_us(1); /* WAIT FOR MAKE ENABLE WIDE*/
	PORTB &= ~(1 << LCD_EN); /* EN = 0 FOR H TO L PULSE*/
	_delay_us(2000); /* WAIT FOR MAKE ENABLE WIDE*/
}

void lcdString(char* str)
{
	int i;
	for (i = 0; str[i] != 0; i++) /* Send each char of string till the NULL */
	{
		lcdChar(str[i]); /* Call LCD data write */
	}
}

void lcdStringXY(unsigned char row, unsigned char pos, char* str)
{
	if (row == 1)
		lcdCommand((pos & 0x0F) | 0x80); /* Command of first row and required position<16 */
	else if (row == 2)
		lcdCommand((pos & 0x0F) | 0xC0); /* Command of Second row and required position<16 */

	lcdString(str); /* Call LCD string function */
}

void lcdClear()
{
	lcdCommand(0x01);
	_delay_ms(3);
	lcdCommand(0x80);
}