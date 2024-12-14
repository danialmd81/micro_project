#include "virtualTerminal.h"

void uartInit()
{
	UBRRL = (unsigned char)BAUD_PRESCALER;
	UBRRH = (unsigned char)(BAUD_PRESCALER >> 8);
	UCSRB = (1 << RXEN) | (1 << TXEN);
	// Set UCSZ1 and UCSZ0 for 8-bit data
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0);
}

void uartSendChar(char data)
{
	while (!(UCSRA & (1 << UDRE)))
		;
	UDR = data;
}

void uartSendString(char* str)
{
	while (*str)
	{
		uartSendChar(*str++);
	}
}

char uartReceiveChar()
{
	while (!(UCSRA & (1 << RXC)))
		;
	return UDR;
}