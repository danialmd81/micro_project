#include "virtualTerminal.h"

void virTerminalInit()
{
	UBRR0L = (unsigned char)BAUD_PRESCALER;
	UBRR0H = (unsigned char)(BAUD_PRESCALER >> 8);
	UCSR0B = (1 << RXEN) | (1 << TXEN);
	// Set UCSZ1 and UCSZ0 for 8-bit data
	UCSR0C = (1 << UCSZ1) | (1 << UCSZ0);
}

void virTerminalSendChar(char data)
{
	while (!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = data;
}

void virTerminalSendString(char* str)
{
	while (*str)
	{
		virTerminalSendChar(*str++);
	}
}

char virTerminalReceive()
{
	while (!(UCSR0A & (1 << RXC0)))
		;
	return UDR0;
}