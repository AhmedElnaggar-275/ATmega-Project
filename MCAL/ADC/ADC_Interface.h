#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H
#include "ADC_Private.h"
#include "STD_BITMATH.h"

typedef enum
{
    A0=0,
    A1,
    A2,
    A3,
    A4,
    A5,
} enADC_Channels;// Enumeration for ADC channels, representing the available analog input pins on the microcontroller
typedef enum
{
    ADC_PRESCALER_0 = 0, // represents division factor of 2
    ADC_PRESCALER_2,    // also represents division factor of 2
    ADC_PRESCALER_4,
    ADC_PRESCALER_8,
    ADC_PRESCALER_16,
    ADC_PRESCALER_32,
    ADC_PRESCALER_64,
    ADC_PRESCALER_128
} enADC_Prescalers;// Enumeration for ADC prescaler options, representing the different clock division factors that can be applied to the ADC clock to control the conversion speed
typedef enum
{
    EXTERNAL,
    DEFAULT,
    INTERNAL
} enADC_Vref;// Enumeration for ADC voltage reference options, representing the different reference voltage sources that can be used for ADC conversions

void analogReferenceWithPrescaler(enADC_Vref vref, enADC_Prescalers prescaler);
void analogReference(enADC_Vref vref);
u16 analogRead(enADC_Channels channel);
void ADC_INIT(void);
#endif /* ADC_INTERFACE_H */