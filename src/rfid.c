#include "rfid.h"
#include "common.h"

unsigned char a;
unsigned char value[15];
unsigned int b;
unsigned int k = 0, i = 0, j, l;

unsigned char value1[] = { "140071D1A612" }; // Predefined ID
unsigned char value2[] = { "51005D6899FD" };

void usartinit()
{
	UBRRH = 00;
	UBRRL = 77;
	UCSRB |= (1 << RXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}

void softwareUartInit()
{
	// Set TX pin as output
	RFID_DDR |= (1 << RFID_TX_PIN);
	// Set RX pin as input
	RFID_DDR &= ~(1 << RFID_RX_PIN);
	// Enable pull-up resistor on RX pin
	RFID_PORT |= (1 << RFID_RX_PIN);
}

void softwareUartSend(unsigned char data)
{
	// Start bit
	RFID_PORT &= ~(1 << RFID_TX_PIN);
	_delay_us(BIT_DELAY);

	// Data bits
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		if (data & (1 << i))
			RFID_PORT |= (1 << RFID_TX_PIN);
		else
			RFID_PORT &= ~(1 << RFID_TX_PIN);
		_delay_us(BIT_DELAY);
	}

	// Stop bit
	RFID_PORT |= (1 << RFID_TX_PIN);
	_delay_us(BIT_DELAY);
}

unsigned char softwareUartReceive()
{
	unsigned char data = 0;

	// Wait for start bit
	while (RFID_PIN & (1 << RFID_RX_PIN))
		;

	_delay_us(BIT_DELAY / 2);

	// Data bits
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		_delay_us(BIT_DELAY);
		if (RFID_PIN & (1 << RFID_RX_PIN))
			data |= (1 << i);
	}

	// Wait for stop bit
	_delay_us(BIT_DELAY);

	return data;
}

void softwareUartSendString(const char* str)
{
	while (*str)
	{
		softwareUartSend(*str++);
	}
}