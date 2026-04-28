#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#include "STD_TYPES.h"

#define ADMUX *((volatile u8*)0x7C)
#define ADCSRA *((volatile u8*)0x7A)
#define ADCH *((volatile u8*)0x79)
#define ADCL *((volatile u8*)0x78)

#endif // ADC_PRIVATE_H