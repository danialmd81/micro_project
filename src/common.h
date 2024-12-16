#ifndef COMMON_H
#define COMMON_H

#define F_CPU 8000000UL
#define BAUD 9600
#define BAUD_PRESCALER (((F_CPU / 16 / (BAUD))) - 1)

#endif // COMMON_H