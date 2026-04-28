#include "TIMER_Private.h"
#include "TIMER_Interface.h"
#include "STD_TYPES.h"
#include "STD_BITMATH.h"

void setPrescaler(Timer_PSC_t prescaler)
{
    TCCR0B |= (prescaler); // Set the prescaler bits in TCCR0B to start the timer
}

void set_CTC_Mode(void)
{
    // Set CTC mode by setting WGM01 bit in TCCR0A and clearing WGM00 and WGM02 bits
    clearBit(TCCR0A, WGM00); // Clear WGM00 bit (bit 0)
    setBit(TCCR0A, WGM01);   // Set WGM01 bit (bit 1)
    clearBit(TCCR0B, WGM02); // Clear WGM02 bit (bit 3)
}

void setTopValue(u8 topValue)
{
    OCR0A = topValue; // Set the TOP value in OCR0A for CTC mode
}

void stopTimer(void)
{
    TCCR0B &= ~(0x07); // Clear the prescaler bits in TCCR0B to stop the timer
}

void delay_us(u32 microseconds)
{
    stopTimer(); // Stop the timer before configuring it for delay
    TCNT0 = 0; // Reset the timer count to 0
    set_CTC_Mode(); // Set CTC mode to use OCR0A as TOP value
    setTopValue(15); // Set the TOP value for 1 microsecond delay
    setPrescaler(PSC_1); // Set prescaler to 1 for 1 microsecond delay
 // Now: period = (prescaler * (1 + TOP)) / F_clk = (1 * (1 + 15)) / 16000000 = 1 microsecond

    u32 count = 0; // counter to keep track of elapsed microseconds
    while(count < microseconds)
    {
        while (!readBit(TIFR0, OCF0A)); // Wait for the compare match flag to be set
        setBit(TIFR0, OCF0A); // Clear the compare match flag by writing a 1 to it
        count++; // Increment the microsecond counter
        // each time the flag is set, it means 1 microsecond is elapsed
    }

    stopTimer(); // Stop the timer after the delay is complete
}

void delay_ms(u32 milliseconds)
{
    stopTimer(); // Stop the timer before configuring it for delay
    TCNT0 = 0; // Reset the timer count to 0
    set_CTC_Mode(); // Set CTC mode to use OCR0A as TOP value
    setTopValue(249); // Set the TOP value for 1 ms delay
    setPrescaler(PSC_64); // Set prescaler to 64 for 1 ms delay
 // Now: period = (prescaler * (1 + TOP)) / F_clk = (64 * (1 + 249)) / 16000000 = 1 ms
 
    u32 count = 0; // counter to keep track of elapsed milliseconds
    while(count < milliseconds)
    {
        while (!readBit(TIFR0, OCF0A)); // Wait for the compare match flag to be set
        setBit(TIFR0, OCF0A); // Clear the compare match flag by writing a 1 to it
        count++; // Increment the millisecond counter
        // each time the flag is set, it means 1 ms is elapsed
    }

    stopTimer(); // Stop the timer after the delay is complete
}