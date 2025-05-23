#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom64.h>
#include <util/delay.h>

// Ultrasonic Pins (D2-D3)
#define US_TRIG_DDR DDRE
#define US_ECHO_DDR DDRE
#define US_TRIG_PORT PORTE
#define US_ECHO_PORT PINE
#define US_TRIG_PIN PE4
#define US_ECHO_PIN PE5
#define CALIBRATION_FACTOR 58.0 // 58 us/cm
#define US_ERROR -1 // Error indicator
#define US_NO_OBSTACLE -2 // No obstacle indicator

extern volatile unsigned int Traffic; // Store the number of present students at any point
extern volatile unsigned int Distance; // Store the distance measured by the ultrasonic sensor

void ultrasonicInit();
uint32_t GetPulseWidth();
void ultrasonicTrigger();

#endif // ULTRASONIC_H