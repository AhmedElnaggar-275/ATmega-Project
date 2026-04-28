#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include "TIMER_Private.h"
#include "STD_TYPES.h"

// wave generation mode bits for Timer/Counter0
#define WGM00 0  // bit 0 in TCCR0A
#define WGM01 1  // bit 1 in TCCR0A
#define WGM02 3  // bit 3 in TCCR0B

#define OCF0A 1 // compare match flag bit for OCR0A (bit 1 in TFR0) 

typedef enum
{
    NO_CLK,          // timer stops
    PSC_1,          // prescaler = 1 (no prescaling)
    PSC_8,          // prescaler = 8 (clock frequency is divided by 8)
    PSC_64,         // prescaler = 64 (clock frequency is divided by 64)
    PSC_256,        // prescaler = 256 (clock frequency is divided by 256)
    PSC_1024,       // prescaler = 1024 (clock frequency is divided by 1024)
} Timer_PSC_t;

// functions prototypes
void setPrescaler(Timer_PSC_t prescaler);
void set_CTC_Mode(void); // to set the TOP value by setting OCR0A as we want 
void setTopValue(u8 topValue); // using OCR0A
void delay_us(u32 microseconds);
void delay_ms(u32 milliseconds);
void stopTimer(void);

#endif // TIMER_INTERFACE_H