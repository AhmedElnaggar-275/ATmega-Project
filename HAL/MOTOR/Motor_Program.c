#include "Motor_Declarations.h"
#include "Motor_Macros.h"

void motorInit(void)
{
    pinMode(MOTOR_1_IN1, OUTPUT);
    pinMode(MOTOR_1_IN2, OUTPUT);
    pinMode(MOTOR_2_IN3, OUTPUT);
    pinMode(MOTOR_2_IN4, OUTPUT);
    pinMode(MOTOR_1_ENA, OUTPUT);
    pinMode(MOTOR_2_ENB, OUTPUT);
    digitalWrite(MOTOR_1_ENA, HIGH); // Enable motor 1
    digitalWrite(MOTOR_2_ENB, HIGH); // Enable motor 2
    motorStopAll();
}
void motorDrive(enMotorID motorID, enMotorDirecrtion direction)
{
    
    if(motorID == motor1)
    {
        if(direction == motorForWard)
        {
            motor1Forward();
        }
        else if(direction == motorBackWard)
        {
            motor1Backward();
        }
        else if(direction == motorStop)
        {
            motor1Stop();
        }
    }
    else if(motorID == motor2)
    {
        if(direction == motorForWard)
        {
            motor2Forward();
        }
        else if(direction == motorBackWard)
        {
            motor2Backward();
        }
        else if(direction == motorStop)
        {
            motor2Stop();
        }
    }
}
    

void motorStopAll(void)
{
    motorDrive(motor1, motorStop);
    motorDrive(motor2, motorStop);
}
void motorForward(void)
{
    motorDrive(motor1, motorForWard);
    motorDrive(motor2, motorForWard);
}

void motorBackward(void)
{
    motorDrive(motor1, motorBackWard);
    motorDrive(motor2, motorBackWard);
}
void motorTurnRight(void)
{
    motorDrive(motor2, motorForWard);
    motorDrive(motor1, motorBackWard);
}
void motorTurnLeft(void)
{
    motorDrive(motor1, motorForWard);
    motorDrive(motor2, motorBackWard);
}