#include "ultrasonic.h"

volatile int Traffic = 0; // Store the number of present students at any point
volatile int Distance = 0; // Store the distance measured by the ultrasonic sensor
volatile uint32_t pulseStart = 0; // Start time of the pulse

ISR(INT5_vect)
{
    if (US_ECHO_PORT & (1 << US_ECHO_PIN))
    {
        // Rising edge detected
        pulseStart = TCNT1;
    }
    else
    {
        // Falling edge detected
        uint32_t pulseWidth = TCNT1 - pulseStart;
        if (pulseWidth > 60000)
        {
            Distance = US_NO_OBSTACLE;
        }
        else
        {
            Distance = (int)((pulseWidth / CALIBRATION_FACTOR) + 0.1);
            if (Distance < 6)
            {
                Traffic++;
            }
        }
    }
}

void ultrasonicInit()
{
    // Set TRIG as output, ECHO as input
    US_TRIG_DDR |= (1 << US_TRIG_PIN);
    US_ECHO_DDR &= ~(1 << US_ECHO_PIN);

    // Configure external interrupt on INT0 (PD2)
    EICRA |= (1 << ISC00); // Trigger on any logical change
    EIMSK |= (1 << INT0);  // Enable INT0

    // Configure Timer1
    TCCR1A = 0x00;
    TCCR1B = (1 << CS11); // Prescaler 8
    TCNT1 = 0x00; // Reset timer

    // Enable global interrupts
    sei();
}

void ultrasonicTrigger()
{
    // Send a 20us pulse to trigger the sensor
    US_TRIG_PORT |= (1 << US_TRIG_PIN);
    _delay_us(20);
    US_TRIG_PORT &= ~(1 << US_TRIG_PIN);
}