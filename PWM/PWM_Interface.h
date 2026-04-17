#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H

#include "PWM_Private.h"
#include "LIB/STD_TYPES.h"

// Define the PWM modes, channels, inverting modes, and prescaler options
typedef enum
{
    CHANNEL_A,    // OC1A pin (Pin 9 on Arduino Uno)
    CHANNEL_B,    // OC1B pin (Pin 10 on Arduino Uno)
    DUAL_CHANNEL  // Both OC1A and OC1B pins (Pins 9 and 10 on Arduino Uno)
} channel_t;    // PWM channels on Timer/Counter1

typedef enum
{
    FAST_PWM,     // Fast PWM mode with TOP defined by ICR1 , compare by OCR1x
    PHASE_CORRECT_PWM,   // Phase Correct PWM mode with TOP defined by ICR1 , compare by OCR1x
    PHASE_FREQ_CORRECT_PWM  // Phase and Frequency Correct PWM mode with TOP defined by ICR1 , compare by OCR1x
} waveGenMode_t;   // wave generation mode for PWM

typedef enum
{
    NON_INVERT,   // (non-inverting mode): reset OC1x on compare match during upcounting, set OC1x on compare match during downcounting
    INVERT        // (inverting mode): reverse operation of NON_INVERT
} invertMode_t;   

typedef enum
{
    NO_clk,          // timer stops
    PSC_1,          // prescaler = 1 (no prescaling)
    PSC_8,          // prescaler = 8 (clock frequency is divided by 8)
    PSC_64,         // prescaler = 64 (clock frequency is divided by 64)
    PSC_256,        // prescaler = 256 (clock frequency is divided by 256)
    PSC_1024,       // prescaler = 1024 (clock frequency is divided by 1024)
} prescaler_t;
// note that PWM freq in timer1 is determined by the formula :
// F_pwm = F_clk / (prescaler * (1 + TOP))
// where TOP is the value in ICR1 when using modes with TOP defined by ICR1 (our case)

// Wave generation mode bits for Timer/Counter1
#define WGM10 0
#define WGM11 1
#define WGM12 3
#define WGM13 4

// Function prototypes
void PWM_init(channel_t channel, waveGenMode_t waveGenMode, invertMode_t invertMode);
void PWM_setTopValue(u16 topValue);
void PWM_setDutyCycle_A(u8 dutyCycle);
void PWM_setDutyCycle_B(u8 dutyCycle);
void PWM_start(prescaler_t prescaler);
void PWM_stop();
#endif // PWM_INTERFACE_H