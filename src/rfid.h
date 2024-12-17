#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom64.h>
#include <util/delay.h>

#ifndef RFID_H
#define RFID_H

#define RFID_RX_PIN PD3
#define RFID_TX_PIN PD2
#define RFID_PORT PORTD
#define RFID_DDR DDRD
#define RFID_PIN PIND

void rfidInit();
void rfidSendChar(char data);
void rfidSendString(char* str);
char rfidReceive();

#endif // RFID_H