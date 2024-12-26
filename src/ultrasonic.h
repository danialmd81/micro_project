#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <avr/io.h>
#include <avr/iom64.h>
#include <util/delay.h>

// Ultrasonic Pins (D2-D3)
#define US_TRIG_DDR DDRF
#define US_ECHO_DDR DDRF
#define US_TRIG_PORT PORTF
#define US_ECHO_PORT PINF
#define US_TRIG_PIN PF3
#define US_ECHO_PIN PF2
#define CALIBRATION_FACTOR 58.0 // 58 us/cm
#define US_ERROR -1 // Error indicator
#define US_NO_OBSTACLE -2 // No obstacle indicator

void ultrasonicInit();
int getDistance();

#endif // ULTRASONIC_H