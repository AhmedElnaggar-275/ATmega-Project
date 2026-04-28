#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "STD_TYPES.h"
#include "GPIO_Interface.h"
#include "ADC_Interface.h"

#define JOYSTICK_X_CH   AN1 // ADC channel for X-axis
#define JOYSTICK_Y_CH   AN0 // ADC channel for Y-axis


#define JOYSTICK_CENTER  512
// for 10-bit ADC, the center value is around 512
// the joystick is stopped at the center position
// Joystick spans from 0-5V and its center is around 2.5V
/* Due to manufacturing tolerances and noise, a zone should be set
   instead of a single position '512' to avoid false readings and unstable behavior */
// This zone is called the "dead zone" 

#define JOYSTICK_DEADZONE 200  // for error handling , approx +-10% of the ADC range (1023)
// here the dead zone is 512 +-100 (412 - 612)

#define JOYSTICK_UPPER      ( JOYSTICK_CENTER + JOYSTICK_DEADZONE/2)
// for forward and right directions

#define JOYSTICK_LOWER      ( JOYSTICK_CENTER - JOYSTICK_DEADZONE/2)
// for backward and left directions

typedef enum 
{
    Stop = 0,
    Forward,
    Backward,
    Right,
    Left
} enJoystickDirection;  // Enum to represent joystick directions
 typedef struct {
    u16 Y;
    u16 X;
 } stJoystickReading;  // Struct to hold joystick readings for X and Y axes

 void joystickRead(stJoystickReading * reading);
 // Function to read the joystick's X and Y values and store them in the structure

 enJoystickDirection joystickGetDirection(void); // Joystick action

#endif /* JOYSTICK_H */