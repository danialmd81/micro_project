#include "Timer.h"

volatile uint32_t elapsedTime = 0;

ISR(TIMER1_COMPA_vect)
{
    elapsedTime++;
}

void timer1Init()
{
    // Set Timer1 to CTC mode
    TCCR1B |= (1 << WGM12);
    // Set prescaler to 64
    TCCR1B |= (1 << CS11) | (1 << CS10);
    // Enable Timer1 compare interrupt
    TIMSK |= (1 << OCIE1A);
    // Set compare value for 1ms interrupt
    OCR1A = (F_CPU / 64 / 1000) - 1;
    // Enable global interrupts
    sei();
}

uint32_t getElapsedTime()
{
    uint32_t time;
    cli(); // Disable interrupts
    time = elapsedTime;
    sei(); // Enable interrupts
    return time/1000;
}