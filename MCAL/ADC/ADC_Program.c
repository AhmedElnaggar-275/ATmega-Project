#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "STD_TYPES.h"
#include "STD_BITMATH.h"

void ADC_INIT(void)
{
    // Select reference voltage (AVCC with external capacitor at AREF pin)
    // and adjust the prescaler to 128 (125KHz ADC clock with 16MHz system clock)
    // as recommended by the datasheet (50KHz to 200KHz ADC clock frequency for maximum resolution)
    analogReference(DEFAULT); // set the reference and the prescaler mentioned above

    setBit(ADCSRA, 7);   // Enable ADC

    // Right adjust result (10-bit value format: ADCL + ADCH)
    clearBit(ADMUX, 5); // Clear ADLAR
    
}
void analogReferenceWithPrescaler(enADC_Vref vref, enADC_Prescalers prescaler)
{
    /******** prescaler ********/

    ADCSRA &= ~(0x07); // reset the prescaler bits (ADPS2:0)

    ADCSRA |= prescaler;  //set prescaler bits

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
void analogReference(enADC_Vref vref)
{
    analogReferenceWithPrescaler(vref, ADC_PRESCALER_128); // Default prescaler value is 128 for maximum resolution
    /* default as Arduino UNO,the ADC clock frequency is 16MHz/128 = 125KHz, 
    which is within the recommended range of 50KHz to 200KHz for the ADC to operate correctly.*/
}
u16 analogRead(enADC_Channels channel)
{
    // Clear the MUX bits in the ADMUX register to select the desired ADC channel
    ADMUX &= 0xE0; // Clear the lower 4 bits (MUX3:0) to select the channel (also the reserved bit is cleared)
    ADMUX |= channel; // Set the desired channel (0-5)
    setBit(ADCSRA, 6); // Start the conversion by setting the ADSC bit in the ADCSRA register
    while (readBit(ADCSRA, 6)); // Wait for the conversion to complete
    // complete by checking the ADSC bit. The bit will be cleared when the conversion is finished.
    u16 result = ADCL | (ADCH << 8);// Read the ADC result from the ADCL and ADCH registers. The result is a 10-bit value, so we combine the two registers to get the full result.
    return (result);
    
}