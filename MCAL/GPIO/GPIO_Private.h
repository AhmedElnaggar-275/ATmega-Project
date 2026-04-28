#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#include "STD_TYPES.h"

//Define Port B
# define DDRB *((volatile u8*)0x24)
# define PORTB *((volatile u8*)0x25)
# define PINB *((volatile u8*)0x23)
//Define Port C
# define DDRC *((volatile u8*)0x27)
# define PORTC *((volatile u8*)0x28)
# define PINC *((volatile u8*)0x26)
//Define Port D
# define DDRD *((volatile u8*)0x2A)
# define PORTD *((volatile u8*)0x2B)
# define PIND *((volatile u8*)0x29)

#endif