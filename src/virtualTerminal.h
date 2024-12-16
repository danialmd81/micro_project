#include "common.h"
#include <avr/io.h>
#include <avr/iom32.h>
#include <util/delay.h>

#ifndef VIRTUALTERMINAL_H
#define VIRTUALTERMINAL_H

// UART Pins (D0-D1)
#define UART_DDR DDRD
#define UART_TX PD1
#define UART_RX PD0

void uartInit();
void uartSendChar(char data);
void uartSendString(char* str);
char uartReceive();

#endif // VIRTUALTERMINAL_H