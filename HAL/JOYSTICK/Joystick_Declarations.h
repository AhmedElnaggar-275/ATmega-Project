#ifndef JOYSTICK_DECLARATIONS_H
#define JOYSTICK_DECLARATIONS_H
#include "STD_TYPES.h"

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


#endif /* JOYSTICK_DECLARATIONS_H */