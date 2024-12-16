#ifndef BUZZER_H
#define BUZZER_H

#include "ddr.h"
// Buzzer Pins (D4)
#define BUZZER_PIN PD4
#define BUZZER_DDR DDRD
#define BUZZER_PORT PORTD

void buzzerInit();
void buzzerOn();
void buzzerOff();

#endif // BUZZER_H