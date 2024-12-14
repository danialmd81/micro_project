#include "temperature.h"

static uint16_t lastTempReading = 0; // Global variable to store ADC value

void tempInit(void)
{
	// Set PA0 (ADC0) as input
	TEMP_DDR &= ~(1 << TEMP_PIN);

	// Configure ADC
	ADMUX = (1 << REFS0) | // AVCC as reference
		(0 << MUX0); // Select ADC0 channel

	ADCSRA = (1 << ADEN) | // Enable ADC
		(1 << ADPS2) | // Prescaler 128 for 16MHz
		(1 << ADPS1) | // (16MHz/128 = 125KHz)
		(1 << ADPS0);
}

uint16_t getTemp(void)
{
	// Start conversion
	ADCSRA |= (1 << ADSC);

	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC))
		;

	// Get ADC value and convert to temperature
	lastTempReading = ADC;
	// Convert to temperature in Celsius
	uint16_t temp = (lastTempReading * 500) / 1024;

	return temp;
}