	#include "headers.h"

	void setup(void)
	{
		ADC_INIT();
		motorInit();
	}
	void loop(void)
	{
		checkBatteryVoltage();

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

	
