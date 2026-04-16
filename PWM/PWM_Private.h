#ifndef PWM_PRIVATE_H
#define PWM_PRIVATE_H
#include "LIB/STD_TYPES.h"

#define TCCR0A *((volatile u8*)0x44)
#define TCCR0B *((volatile u8*)0x45)
#define TCNT0 *((volatile u8*)0x46)
#define OCR0A *((volatile u8*)0x47)
#define OCR0B *((volatile u8*)0x48)
#define TCCR1A *((volatile u8*)0x80)
#define TCCR1B *((volatile u8*)0x81)
#define TCNT1L *((volatile u8*)0x84)
#define TCCNT1H *((volatile u8*)0x85)
s

#endif // PWM_PRIVATE_H