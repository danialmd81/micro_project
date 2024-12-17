#include "rfid.h"
#include "common.h"

unsigned char a;
unsigned char value[15];
unsigned int b;
unsigned int k = 0, i = 0, j, l;

unsigned char value1[] = { "140071D1A612" }; // Predefined ID
unsigned char value2[] = { "51005D6899FD" };

void rfidInit()
{
	UBRR1L = (unsigned char)BAUD_PRESCALER;
	UBRR1H = (unsigned char)(BAUD_PRESCALER >> 8);
	UCSR1B = (1 << RXEN) | (1 << TXEN);
	// Set UCSZ1 and UCSZ0 for 8-bit data
	UCSR1C = (1 << UCSZ1) | (1 << UCSZ0);
}

void rfidSendChar(char data)
{
	while (!(UCSR1A & (1 << UDRE1)))
		;
	UDR1 = data;
}

void rfidSendString(char* str)
{
	while (*str)
	{
		rfidSendChar(*str++);
	}
}

char rfidReceive()
{
	while (!(UCSR1A & (1 << RXC1)))
		;
	return UDR1;
}
