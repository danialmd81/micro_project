#include "ultrasonic.h"

volatile int Traffic = 0;
volatile int Distance = 0;

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
    TCCR3A = 0x00;
    TCCR3B = (1 << CS31);
    TCNT3 = 0x00; // Reset timer

    // Wait for falling edge on Echo pin
    for (i = 0; i < 600000; i++)
    {
        if (!(US_ECHO_PORT & (1 << US_ECHO_PIN)))
            break; // Falling edge detected
        if (TCNT3 > 60000)
            return US_NO_OBSTACLE; // No obstacle in range
    }

    result = TCNT3; // Capture timer value
    TCCR3B = 0x00; // Stop timer

    if (result > 60000)
        return US_NO_OBSTACLE;
    else
        return result; // Return the measured pulse width in microseconds
}

ISR(INT5_vect)
{
    uint32_t pulseWidth; // Pulse width from echo

    ultrasonicTrigger(); // Send trigger pulse
    pulseWidth = GetPulseWidth(); // Measure echo pulse

    if (pulseWidth == US_ERROR)
    {
        Distance = US_ERROR; // Return error if pulse width is invalid
    }
    else if (pulseWidth == US_NO_OBSTACLE)
    {
        Distance = US_NO_OBSTACLE; // Return no obstacle if pulse width is too high
    }
    else
    {
        Distance = (int)((pulseWidth / CALIBRATION_FACTOR) + 0.1);
        if (Distance < 6)
        {
            // Person detection threshold
            Traffic++;
        }
    }
}

void ultrasonicInit()
{
    // Configure pins
    US_TRIG_DDR |= (1 << US_TRIG_PIN); // Trigger as output
    US_ECHO_DDR &= ~(1 << US_ECHO_PIN); // Echo as input

    // Configure Timer3 for measuring pulse width
    // TCCR3A = 0x00; // Normal mode

    // Configure INT5 for both edges
    EICRB |= (1 << ISC50); // Any logical change generates interrupt
    EIMSK |= (1 << INT5); // Enable INT5

    sei(); // Enable global interrupts
}

void ultrasonicTrigger()
{
    // Send trigger pulse
    US_TRIG_PORT |= (1 << US_TRIG_PIN);
    _delay_us(10);
    US_TRIG_PORT &= ~(1 << US_TRIG_PIN);
}