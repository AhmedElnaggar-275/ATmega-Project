#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "STD_TYPES.h"
#include "STD_BITMATH.h"
void adc_Init(void)
{
    // Set prescaler (important for ADC clock)
    ADCSRA = (ADCSRA & ~0x07) | (1 << 2) | (1 << 1) | (1 << 0); // Set prescaler to 128 (for 16MHz clock, ADC clock will be 125KHz)
    setBit(ADCSRA, 7);   // Enable ADC
    // Select reference voltage (AVCC with external capacitor at AREF pin)
    setBit(ADMUX, 6); // set REFS0
    clearBit(ADMUX, 7); // Clear REFS1


    // Right adjust result (10-bit value format: ADCL + ADCH)
    clearBit(ADMUX, 5); // Clear ADLAR
    
}
void analogReferenceWithPrescaler(ADC_Vref_t vref, ADC_Prescaler_t prescaler)
{
    switch (prescaler)
    {
        // From table 24-5 in the datasheet, we need to set the ADPS2:0 bits in the ADCSRA register to select the desired prescaler value.
        case ADC_PRESCALER_2:
            setBit(ADCSRA, 0); // Set ADPS0
            clearBit(ADCSRA, 1); // Clear ADPS1
            clearBit(ADCSRA, 2); // Clear ADPS2
            break;
        case ADC_PRESCALER_4:
            clearBit(ADCSRA, 0); // Clear ADPS0
            setBit(ADCSRA, 1);   // Set ADPS1
            clearBit(ADCSRA, 2); // Clear ADPS2
            break;
        case ADC_PRESCALER_8:
            setBit(ADCSRA, 0); // Set ADPS0
            setBit(ADCSRA, 1); // Set ADPS1
            clearBit(ADCSRA, 2); // Clear ADPS2
            break;
        case ADC_PRESCALER_16:
            clearBit(ADCSRA, 0); // Clear ADPS0
            clearBit(ADCSRA, 1); // Clear ADPS1
            setBit(ADCSRA, 2);  // Set ADPS2
            break;
        case ADC_PRESCALER_32:
            setBit(ADCSRA, 0); // Set ADPS0
            clearBit(ADCSRA, 1); // Clear ADPS1
            setBit(ADCSRA, 2);  // Set ADPS2
            break;
        case ADC_PRESCALER_64:
            clearBit(ADCSRA, 0); // Clear ADPS0 
            setBit(ADCSRA, 1);  // Set ADPS1
            setBit(ADCSRA, 2);  // Set ADPS2
            break;
        case ADC_PRESCALER_128:
            setBit(ADCSRA, 0); // Set ADPS0
            setBit(ADCSRA, 1); // Set ADPS1
            setBit(ADCSRA, 2); // Set ADPS2
            break;
        default:
            setBit(ADCSRA, 0); // Set ADPS0
            setBit(ADCSRA, 1); // Set ADPS1
            setBit(ADCSRA, 2); // Set ADPS2
            break;
    }
    switch (vref)
    {
    case EXTERNAL:// External reference voltage at AREF pin
        clearBit(ADMUX, 6); // Clear REFS0
        clearBit(ADMUX, 7); // Clear REFS1
        break;
    case DEFAULT:// AVcc reference with external capacitor at AREF pin
        setBit(ADMUX, 6); // Set REFS0
        clearBit(ADMUX, 7); // Clear REFS1
        break;
    case INTERNAL:// Internal 1.1V Voltage Reference with external capacitor at AREF pin
        setBit(ADMUX, 6); // Set REFS0
        setBit(ADMUX, 7); // Set REFS1
        break;
        
    }
}
void analogReference(ADC_Vref_t vref)
{
    analogReferenceWithPrescaler(vref, ADC_PRESCALER_128); // Default prescaler value is 128 for maximum resolution
    /* default as Arduino UNO,the ADC clock frequency is 16MHz/128 = 125KHz, 
    which is within the recommended range of 50KHz to 200KHz for the ADC to operate correctly.*/
}
u16 analogRead(ADC_Channel_t channel)
{
    // Clear the MUX bits in the ADMUX register to select the desired ADC channel
    ADMUX &= 0xF0; // Clear the lower 4 bits (MUX3:0) to select the channel
    ADMUX |= channel; // Set the desired channel (0-5)
    setBit(ADCSRA, 6); // Start the conversion by setting the ADSC bit in the ADCSRA register
    while (ADCSRA & (1 << 6)); // Wait for the conversion to complete
    // complete by checking the ADSC bit. The bit will be cleared when the conversion is finished.
    u16 result = ADCL | (ADCH << 8);// Read the ADC result from the ADCL and ADCH registers. The result is a 10-bit value, so we combine the two registers to get the full result.
    return (result);
     
}