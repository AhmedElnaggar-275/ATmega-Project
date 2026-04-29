#include "headers.h"


void setup(void)
	{
		ADC_INIT();
		motorInit();
		batteryInit();
	}
	void loop(void)
	{
		enJoystickDirection direction = getDirectionFromJoystick();
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
		checkBatteryVoltage();
	}
	int main(void)
	{
		setup();
		while(1)
		{
			loop();
		}
		
		
	}

	