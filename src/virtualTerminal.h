#ifndef VIRTUALTERMINAL_H
#define VIRTUALTERMINAL_H

#include "ddr.h"

void uartInit();
void uartSendChar(char data);
void uartSendString(char* str);
char uartReceiveChar();

#endif // VIRTUALTERMINAL_H