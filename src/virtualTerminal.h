#include "common.h"
#include <avr/io.h>
#include <avr/iom64.h>
#include <util/delay.h>

#ifndef VIRTUALTERMINAL_H
#define VIRTUALTERMINAL_H

// virTerminal Pins (D0-D1)
#define virTerminal_DDR DDRE
#define virTerminal_TX PE0
#define virTerminal_RX PE1

void virTerminalInit();
void virTerminalSendChar(char data);
void virTerminalSendString(char* str);
char virTerminalReceive();

#endif // VIRTUALTERMINAL_H