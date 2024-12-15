#include "temperature.h"
#include <avr/io.h>
#include <util/delay.h>

uint16_t lastTempReading = 0; // Global variable to store ADC value
float ADC_Scale_Factor = 5.0 / 1024.0;

void tempInit(void)
{
    // Set PA0 (ADC0) and PA1 (ADC1) as input
    TEMP_DDR &= ~(1 << TEMP_PIN);
    TEMP_DDR &= ~(1 << (TEMP_PIN + 1));

    // Configure ADC
    ADMUX = (1 << REFS0); // AVCC as reference

    ADCSRA = (1 << ADEN) |  // Enable ADC
             (1 << ADPS2) | // Prescaler 128 for 16MHz
             (1 << ADPS1) | // (16MHz/128 = 125KHz)
             (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel)
{
    // Select ADC channel
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

    // Start ADC conversion
    ADCSRA |= (1 << ADSC);

    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));

    // Read ADC value
    return ADC;
}

int getTemp(void)
{
    // Read ADC values for Vout and Vgnd
    uint16_t ADC_Vout_Sample = ADC_Read(0);
    uint16_t ADC_Vgnd_Sample = ADC_Read(1);

    // Convert ADC values to voltages
    float ADC_Vout_Voltage = ADC_Vout_Sample * ADC_Scale_Factor;
    float ADC_Vgnd_Voltage = ADC_Vgnd_Sample * ADC_Scale_Factor;

    // Calculate temperature
    float Temp_Value = (ADC_Vout_Voltage - ADC_Vgnd_Voltage) / 0.01;
	int temp;
	if(Temp_Value < 0)
		temp = (int)(2.0*Temp_Value);
	else
		temp = (int)(Temp_Value);

    return temp;
}