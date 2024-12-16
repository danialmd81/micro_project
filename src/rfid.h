#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom32.h>
#include <util/delay.h>

#ifndef RFID_H
#define RFID_H

#define RFID_RX_PIN PD6
#define RFID_TX_PIN PD7
#define RFID_PORT PORTD
#define RFID_DDR DDRD
#define RFID_PIN PIND

void softwareUartInit();
unsigned char softwareUartReceive();
void softwareUartSend(unsigned char data);
void softwareUartSendString(const char* str);

void usartinit();

#endif // RFID_H