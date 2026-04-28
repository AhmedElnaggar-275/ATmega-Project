#include "Joystick_Definitions.h"
#include "Joystick_Declarations.h"

 void joystickRead(stJoystickReading * reading)
 {
// To modify the structure elements (Y and X), we have to call its address and not its value
// (call by reference)
    reading->Y = analogRead(JOYSTICK_Y_CH);
    reading->X = analogRead(JOYSTICK_X_CH);
 }
 enJoystickDirection joystickGetDirection(void)
 {
    stJoystickReading Reads;   // Create a structure of (X and Y) to hold the joystick readings

    joystickRead(&Reads); 
    //Read the joystick values and store them in the structure (call by reference)
    //(the function mentioned above)

    if(Reads.Y>JOYSTICK_UPPER) //only act when reading is above 512+100
    {
        return Forward;
    }
    else if(Reads.Y<JOYSTICK_LOWER) //only act when reading is below 512-100
    {
        return Backward;
    }
    else if(Reads.X>JOYSTICK_UPPER)
    {
        return Right;

    }
    else if(Reads.X<JOYSTICK_LOWER)
    {
        return Left;
    }
    else // if the readings are within the dead zone, then it's the center
    {
        return Stop;
    }

 }
