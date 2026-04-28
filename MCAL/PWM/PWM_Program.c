#include "PWM_Interface.h"
#include "PWM_Private.h"
#include "GPIO_Private.h"
#include "STD_TYPES.h"
#include "STD_BITMATH.h"

// Function implementations
void PWM_init(channel_t channel, waveGenMode_t waveGenMode, invertMode_t invertMode)
{
    switch (channel){

        case CHANNEL_A:
            // configure OC1A pin (Pin 9 on Arduino Uno) as output
            setBit(DDRB, 1); // OC1A is on PB1

            // disconnect OC1B pin (Pin 10 on Arduino Uno) from timer PWM operation
            clearBit(TCCR1A, COM1B0); // bit 4
            clearBit(TCCR1A, COM1B1); // bit 5

            switch(invertMode){

                case NON_INVERT:
                    /* non-inverting mode: reset OC1A on compare match during upcounting, 
                    set OC1A on compare match during downcounting */
                    clearBit(TCCR1A, COM1A0); // bit 6
                    setBit(TCCR1A, COM1A1);   // bit 7
                break;

                case INVERT:
                    // inverting mode: reverse operation of non-inverting mode
                    setBit(TCCR1A, COM1A0);   // bit 6
                    setBit(TCCR1A, COM1A1);   // bit 7
                break;
            }
        break;

        case CHANNEL_B:
            // configure OC1B pin (Pin 10 on Arduino Uno) as output
            setBit(DDRB, 2); // OC1B is on PB2

            // disconnect OC1A pin (Pin 9 on Arduino Uno) from timer PWM operation
            clearBit(TCCR1A, COM1A0); // bit 6
            clearBit(TCCR1A, COM1A1); // bit 7
            
            switch(invertMode){

                case NON_INVERT:
                    // non-inverting mode: reset OC1B on compare match during upcounting, set OC1B on compare match during downcounting
                    clearBit(TCCR1A, COM1B0); // bit 4
                    setBit(TCCR1A, COM1B1);   // bit 5
                break;

                case INVERT:
                    // inverting mode: reverse operation of non-inverting mode
                    setBit(TCCR1A, COM1B0);   // bit 4
                    setBit(TCCR1A, COM1B1);   // bit 5
                break;
            }
        break;
        
        case DUAL_CHANNEL:
            // configure both OC1A and OC1B pins as outputs
            setBit(DDRB, 1); // OC1A is on PB1
            setBit(DDRB, 2); // OC1B is on PB2

            switch(invertMode){

                case NON_INVERT:
                    // non-inverting mode: reset OC1x on compare match during upcounting, set OC1x on compare match during downcounting
                    clearBit(TCCR1A, COM1A0); // bit 6
                    setBit(TCCR1A, COM1A1);   // bit 7
                    clearBit(TCCR1A, COM1B0); // bit 4
                    setBit(TCCR1A, COM1B1);   // bit 5
                break;

                case INVERT:
                    // inverting mode: reverse operation of non-inverting mode
                    setBit(TCCR1A, COM1A0);   // bit 6
                    setBit(TCCR1A, COM1A1);   // bit 7
                    setBit(TCCR1A, COM1B0);   // bit 4
                    setBit(TCCR1A, COM1B1);   // bit 5
                break;
            }
        break;

        switch (waveGenMode){
                case FAST_PWM:  
                // Fast PWM mode with TOP defined by ICR1 , compare by OCR1x
                // WGM13:10 = 1110 for Fast PWM with TOP defined by ICR1
                    clearBit(TCCR1A, WGM10);
                    setBit(TCCR1A, WGM11);
                    setBit(TCCR1B, WGM12);
                    setBit(TCCR1B, WGM13);
                break;

                case PHASE_CORRECT_PWM:  
                // Phase Correct PWM mode with TOP defined by ICR1 , compare by OCR1x
                // WGM13:10 = 1010 for Phase Correct PWM with TOP defined by ICR1
                    clearBit(TCCR1A, WGM10);
                    setBit(TCCR1A, WGM11);
                    clearBit(TCCR1B, WGM12);
                    setBit(TCCR1B, WGM13);
                break;

                case PHASE_FREQ_CORRECT_PWM: 
                // Phase and Frequency Correct PWM mode with TOP defined by ICR1 , compare by OCR1x
                // WGM13:10 = 1000 for Phase and Frequency Correct PWM with TOP defined by ICR1
                    clearBit(TCCR1A, WGM10);
                    clearBit(TCCR1A, WGM11);
                    clearBit(TCCR1B, WGM12);
                    setBit(TCCR1B, WGM13);
                break;
            }
    }
}

void PWM_setTopValue(u16 topValue)
{
    
// bits in ICR1L will be set to the lower 8 bits of topValue , other bits of topValue will be cleared
    ICR1L = (u8)(topValue & 0xFF); 
// bits in ICR1H will be set to the upper 8 bits of topValue , other bits will be cleared
    ICR1H = (u8)((topValue >> 8) & 0xFF);
    /*example
    if topValue = 1110011111011011
    then,
    ICR1L = (u8)(topValue & 0xFF) 
          = (u8)(1110011111011011 & 0000000011111111) 
          = (u8)(0000000011011011) 
          = 11011011 (ICR1L will be set to the lower 8 bits of topValue)
    ICR1H = (u8)((topValue >> 8) & 0xFF) 
          = (u8)((1110011111011011 >> 8) & 0000000011111111) 
          = (u8)(11100111 & 0000000011111111)
          = (u8)(0000000011100111)
          = 11100111 (ICR1H will be set to the upper 8 bits of topValue)
    */
}

void PWM_setFrequeny(u32 frequency)  // not less than 1kHz to avoid overflow in TOP value calculation
{
    // Calculate TOP value for the desired frequency
    u16 topValue = (F_CLK / (2 * frequency)) - 1;

    PWM_setTopValue(topValue);    // Set the TOP value in ICR1

}

void PWM_setDutyCycle_A(u8 dutyCycle) // dutyCycle for channel A (OC1A)
{
    if (dutyCycle > 100)
    {
        dutyCycle = 100; // because duty cycle is a percentage and cannot exceed 100%
    }

    u16 topValue = ICR1L | ((u16)ICR1H << 8); // Get the current TOP value from ICR1
    /*example
    ICR1 = 1110011111011011
    then,
    ICR1H = 11100111
    ICR1L = 11011011
    topValue = ICR1L | (ICR1H << 8) 
             = 11011011 | (11100111 << 8) 
             = 11011011 | 1110011100000000 
             = 1110011111011011  (Now topValue = ICR1 value)
    */
    u16 compareValue = ((f32)dutyCycle * topValue) / 100; // Calculate compare value
    OCR1AL = (u8)(compareValue & 0xFF); // Set compare value for OCR1A low byte
    OCR1AH = (u8)((compareValue >> 8) & 0xFF); // Set compare value for OCR1A high byte
}


void PWM_setDutyCycle_B(u8 dutyCycle) // dutyCycle for channel B (OC1B)
{
   if (dutyCycle > 100)
    {
        dutyCycle = 100; // Cap duty cycle at 100%
    }

    u16 topValue = ICR1L | (ICR1H << 8); // Get the current TOP value from ICR1
    u16 compareValue = ((f32)dutyCycle * topValue) / 100; // Calculate compare value
    OCR1BL = (u8)(compareValue & 0xFF); // Set compare value for OCR1B low byte
    OCR1BH = (u8)((compareValue >> 8) & 0xFF); // Set compare value for OCR1B high byte

}

void PWM_start(PWM_PSC_t prescaler) 
{   /* It is recommended to pass PSC_1but if it is required to divide 
       your chosen frequency by a factor then chose
       between PSC_1 , PSC_8 , PSC_64 , PSC_256 , PSC_1024 , where the number
       is the divisor (division factor) */

    clearBit(TCCR1B, 5); // clear the reserved bit as recommended in datasheet
    TCCR1B |= (prescaler); // Set the prescaler bits in TCCR1B to start the timer
}

void PWM_stop()
{
    TCCR1B &= ~(7); // Clear the prescaler bits in TCCR1B to stop the timer
}

