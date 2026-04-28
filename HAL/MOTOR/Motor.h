#ifndef MOTOR_H
#define MOTOR_H

#include "GPIO_Interface.h"

// direction control pins for motor 1
#define MOTOR_1_IN1    D6
#define MOTOR_1_IN2    D7

// direction control pins for motor 2
#define MOTOR_2_IN3    D8
#define MOTOR_2_IN4    D9

// enable pins for motor 1 and motor 2
#define MOTOR_1_ENA    D5
#define MOTOR_2_ENB    D10



#define motor1Forward()     { digitalWrite(MOTOR_1_IN1, HIGH); digitalWrite(MOTOR_1_IN2, LOW);  }

#define motor1Backward()   { digitalWrite(MOTOR_1_IN1, LOW);  digitalWrite(MOTOR_1_IN2, HIGH); }

#define motor1Stop()       { digitalWrite(MOTOR_1_IN1, LOW); digitalWrite(MOTOR_1_IN2, LOW);  }
                                     

#define motor2Forward()     { digitalWrite(MOTOR_2_IN3, HIGH); digitalWrite(MOTOR_2_IN4, LOW);  }

#define motor2Backward()   { digitalWrite(MOTOR_2_IN3, LOW);  digitalWrite(MOTOR_2_IN4, HIGH); }

#define motor2Stop()       { digitalWrite(MOTOR_2_IN3, LOW); digitalWrite(MOTOR_2_IN4, LOW);  }


typedef enum
{
    motorForWard = 0,
    motorBackWard,
    motorStop
} enMotorDirection;

typedef enum
{
    motor1 = 0,
    motor2,
} enMotorID;

void motorInit(void);
void motorDrive(enMotorID motorID, enMotorDirection direction);
void motorStopAll(void);
void motorForward(void);
void motorBackward(void);
void motorTurnRight(void);
void motorTurnLeft(void);


#endif /* MOTOR_H */