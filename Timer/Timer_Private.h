#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H
#include "LIB/STD_TYPES.h"

// Timer/Counter0 control Registers
#define TCCR0A *((volatile u8*)0x44)
#define TCCR0B *((volatile u8*)0x45)

// Timer/Counter0 count value store Register
#define TCNT0 *((volatile u8*)0x46)

#endif // TIMER_PRIVATE_H