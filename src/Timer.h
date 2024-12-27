#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

void timer1Init();
uint32_t getElapsedTime();

#endif // TIMER_H