#include "Timer.h"
#include "ultrasonic.h"

volatile uint32_t elapsedTime = 0;

ISR(TIMER0_COMP_vect)
{
	elapsedTime++;
}

void timerInit()
{
	// init timer0
	TCCR0 |= (1 << WGM01); // CTC Mode
	TCCR0 |= (1 << CS01) | (1 << CS00); // Prescaler 32
	TIMSK |= (1 << OCIE0); // Enable Compare Match Interrupt

	OCR0 = 250; // Compare Match value for 1ms
	// Enable global interrupts
	sei();
}

uint32_t getElapsedTime()
{
	uint32_t time;
	cli(); // Disable interrupts
	time = elapsedTime;
	sei(); // Enable interrupts
	return time / 1000;
}