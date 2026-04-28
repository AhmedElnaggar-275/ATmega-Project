	#include "STD_TYPES.h"
	#include "STD_BITMATH.h"
	#include "GPIO_Interface.h"
	#include "ADC_interface.h"
	#include "Motor_Interface.h"
	#include "Motor_private.h"
	#include "Joystick_Interface.h"

	void setup(void)
	{
		ADC_INIT();
		motorInit();
	}
	void loop(void)
	{
		enJoystickDirection direction = joystickGetDirection();
		switch(direction)
		{
			case Forward:
				motorForward();
				break;
			case Backward:
				motorBackward();
				break;
			case Right:
				motorTurnRight();
				break;
			case Left:
				motorTurnLeft();
				break;
			case Stop:
				default:
					motorStopAll();
					break;
		}
	}
	int main(void)
	{
		setup();
		while(1)
		{
			loop();
		}
		
		
	}

	
