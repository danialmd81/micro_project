#ifndef TIMER_H
#define TIMER_H

#include <avr/interrupt.h>
#include <avr/io.h>

void timerInit();
uint32_t getElapsedTime();

#endif // TIMER_H