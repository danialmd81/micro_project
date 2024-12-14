#include "ultrasonic.h"

void ultrasonicInit()
{
	// Set TRIG as output, ECHO as input
	US_TRIG_DDR |= (1 << US_TRIG_PIN);
	US_ECHO_DDR &= ~(1 << US_ECHO_PIN);
}

void ultrasonicTrigger()
{
	// Send a 10us pulse to trigger the sensor
	US_TRIG_PORT |= (1 << US_TRIG_PIN);
	_delay_us(20);
	US_TRIG_PORT &= ~(1 << US_TRIG_PIN);
}

uint32_t GetPulseWidth()
{
	uint32_t i, result;

	// Wait for rising edge on Echo pin
	for (i = 0; i < 600000; i++)
	{
		if (!(US_ECHO_PORT & (1 << US_ECHO_PIN)))
			continue;
		else
			break;
	}

	if (i == 600000)
		return US_ERROR; // Timeout error if no rising edge detected

	// Start timer with prescaler 8
	TCCR1A = 0x00;
	TCCR1B = (1 << CS11);
	TCNT1 = 0x00; // Reset timer

	// Wait for falling edge on Echo pin
	for (i = 0; i < 600000; i++)
	{
		if (!(US_ECHO_PORT & (1 << US_ECHO_PIN)))
			break; // Falling edge detected
		if (TCNT1 > 60000)
			return US_NO_OBSTACLE; // No obstacle in range
	}

	result = TCNT1; // Capture timer value
	TCCR1B = 0x00; // Stop timer

	if (result > 60000)
		return US_NO_OBSTACLE;
	else
		return (result >> 1); // Return the measured pulse width in microseconds
}

int getDistance()
{
	uint32_t pulseWidth; // Pulse width from echo
	int distance; // Calculated distance

	_delay_ms(100); // Delay for sensor stability

	ultrasonicTrigger(); // Send trigger pulse
	pulseWidth = GetPulseWidth(); // Measure echo pulse

	if (pulseWidth == US_ERROR)
	{
		return US_ERROR; // Return error if pulse width is invalid
	}
	else if (pulseWidth == US_NO_OBSTACLE)
	{
		return US_NO_OBSTACLE; // Return no obstacle if pulse width is too high
	}
	else
	{
		distance = (int)((pulseWidth / CALIBRATION_FACTOR) + 0.1);
		return distance;
	}
}