#include "temperature.h"

void tempInit(void)
{
	// Set PF0 (ADC0) and PF1 (ADC1) as input
	TEMP_DDR &= ~(1 << TEMP_PIN0);
	TEMP_DDR &= ~(1 << TEMP_PIN1);

	// Set reference voltage to AVcc (5V) and select TEMP_PIN0 (ADC0) and TEMP_PIN1
	ADMUX = (1 << REFS0) | (TEMP_PIN0 & 0x07) | (TEMP_PIN1 & 0x07);

	// Enable ADC, set prescaler to 128 (8MHz/128 = 62.5kHz)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel)
{
	// Select ADC channel
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

	// Start ADC conversion
	ADCSRA |= (1 << ADSC);

	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC))
		;

	// Read ADC value
	return ADCW;
}

int getTemp()
{
	// ADC_Scale_Factor is used to convert the raw ADC value to a voltage.
	float ADC_Scale_Factor = 5.0 / 1024.0;

	// Read ADC values for Vout and Vgnd
	uint16_t ADC_Vout_Sample = ADC_Read(TEMP_PIN0);
	uint16_t ADC_Vgnd_Sample = ADC_Read(TEMP_PIN1);

	// Convert ADC values to voltages
	float ADC_Vout_Voltage = ADC_Vout_Sample * ADC_Scale_Factor;
	float ADC_Vgnd_Voltage = ADC_Vgnd_Sample * ADC_Scale_Factor;

	// Calculate temperature
	float Temp_Value = (ADC_Vout_Voltage - ADC_Vgnd_Voltage) / 0.01;
	int temp;
	if (Temp_Value < 0)
	{
		Temp_Value *= 2.0;
		Temp_Value += 0.5; // telorance for casting to int
		temp = (int)(Temp_Value);
	}
	else
	{
		Temp_Value += 0.5; // telorance for casting to int
		temp = (int)(Temp_Value);
	}

	return temp;
}