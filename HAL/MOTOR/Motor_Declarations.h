#ifndef MOTOR_DECLARATIONS_H
#define MOTOR_DECLARATIONS_H

typedef enum
{
    motorForWard = 0,
    motorBackWard,
    motorStop
} enMotorDirecrtion;

typedef enum
{
    motor1 = 0,
    motor2,
} enMotorID;

void motorInit(void);
void motorDrive(enMotorID motorID, enMotorDirecrtion direction);
void motorStopAll(void);
void motorForward(void);
void motorBackward(void);
void motorTurnRight(void);
void motorTurnLeft(void);

#endif /* MOTOR_DECLARATIONS_H */