#include "buzzer.h"

void buzzerInit()
{
	BUZZER_DDR |= (1 << BUZZER_PIN); // Set PD4 as output
}

void buzzerOn()
{
	BUZZER_PORT |= (1 << BUZZER_PIN); // Set PD4 high to turn on the buzzer
}

void buzzerOff()
{
	BUZZER_PORT &= ~(1 << BUZZER_PIN); // Set PD4 low to turn off the buzzer
}