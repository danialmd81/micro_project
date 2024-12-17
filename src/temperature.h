#include <avr/io.h>
#include <avr/iom64.h>
#include <util/delay.h>

#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "common.h"

// Temperature ADC (PF0-PF1)
#define TEMP_DDR DDRF
#define TEMP_PORT PORTF
#define TEMP_PIN0 PF0
#define TEMP_PIN1 PF1

// extern uint16_t lastTempReading;
void tempInit();
int getTemp();

#endif // TEMPERATURE_H