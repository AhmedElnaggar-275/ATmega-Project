#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H
#include "ADC_Private.h"

typedef enum
{
    AN0=0,
    AN1,
    AN2,
    AN3,
    AN4,
    AN5,
} ADC_Channel_t;
typedef enum
{
    ADC_PRESCALER_2,
    ADC_PRESCALER_4,
    ADC_PRESCALER_8,
    ADC_PRESCALER_16,
    ADC_PRESCALER_32,
    ADC_PRESCALER_64,
    ADC_PRESCALER_128
} ADC_Prescaler_t;
typedef enum
{
    EXTERNAL,
    DEFAULT,
    INTERNAL
} ADC_Vref_t;

void analogReferenceWithPrescaler(ADC_Vref_t vref, ADC_Prescaler_t prescaler);
void analogReference(ADC_Vref_t vref);
u16 analogRead(ADC_Channel_t channel);
void ADC_INIT(void);
#endif /* ADC_INTERFACE_H */