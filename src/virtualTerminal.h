#ifndef VIRTUALTERMINAL_H
#define VIRTUALTERMINAL_H

#include "ddr.h"

// UART Pins (D0-D1)
#define UART_DDR DDRD
#define UART_TX PD1
#define UART_RX PD0

void uartInit();
void uartSendChar(char data);
void uartSendString(char* str);
char uartReceiveChar();

#endif // VIRTUALTERMINAL_H