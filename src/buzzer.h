#include <avr/io.h>
#include <avr/iom64.h>

#ifndef BUZZER_H
#define BUZZER_H

// Buzzer Pins (D4)
#define BUZZER_PIN PD4
#define BUZZER_DDR DDRD
#define BUZZER_PORT PORTD

void buzzerInit();
void buzzerOn();
void buzzerOff();

#endif // BUZZER_H