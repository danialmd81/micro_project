#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "common.h"

// Temperature ADC (PA6)
#define TEMP_DDR DDRA
#define TEMP_PORT PORTA
#define TEMP_PIN PA6
// #define TEMP_PIN PA7

// extern uint16_t lastTempReading;
void tempInit();
int getTemp();

#endif // TEMPERATURE_H