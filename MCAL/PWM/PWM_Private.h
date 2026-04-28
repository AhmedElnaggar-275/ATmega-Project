#ifndef PWM_PRIVATE_H
#define PWM_PRIVATE_H

#include "STD_TYPES.h"

// Timer/Counter1 control Registers
#define TCCR1A *((volatile u8*)0x80)
#define TCCR1B *((volatile u8*)0x81)

// Timer/Counter1 TOP and compare read/write Registers
#define ICR1L *((volatile u8*)0x86)
#define ICR1H *((volatile u8*)0x87)
#define OCR1AL *((volatile u8*)0x88)
#define OCR1AH *((volatile u8*)0x89)
#define OCR1BL *((volatile u8*)0x8A)
#define OCR1BH *((volatile u8*)0x8B)

#endif // PWM_PRIVATE_H