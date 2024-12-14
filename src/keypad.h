#ifndef KEYPAD_H
#define KEYPAD_H

#include "ddr.h"

void keypadInit();
char keypadScan();
char keypadGetkey();

#endif // KEYPAD_H