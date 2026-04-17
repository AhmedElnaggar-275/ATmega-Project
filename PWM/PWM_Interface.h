#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H

#include "PWM_Private.h"
#include "LIB/STD_TYPES.h"

// Define the PWM modes, channels, inverting modes, and prescaler options
typedef enum
{
    CHANNEL_A,
    CHANNEL_B,
    DUAL_CHANNEL
} channel_t;

typedef enum
{
    FAST_PWM,
    PHASE_CORRECT_PWM,
    PHASE_FREQ_CORRECT_PWM
} waveGenMode_t;

typedef enum
{
    WGM10 = 0,
    WGM11 = 1,
    WGM12 = 3,
    WGM13 = 4
}wgmBits_t;

typedef enum
{
    NON_INVERT,
    INVERT
} invertMode_t;

typedef enum
{
    NO_clk,
    PSC_1,
    PSC_8,
    PSC_64,
    PSC_256,
    PSC_1024,
} prescaler_t;

// Function prototypes
void PWM_init(channel_t channel , waveGenMode_t mode, invertMode_t invert_mode);
void PWM_setTopValue(u16 top_value);
void PWM_setDutyCycle(channel_t channel , u8 duty_cycle);
void PWM_start(prescaler_t prescaler);
void PWM_stop();
#endif // PWM_INTERFACE_H