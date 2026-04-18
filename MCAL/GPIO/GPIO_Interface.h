#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H
#include "GPIO_Private.h"
typedef enum 
{
    INPUT,OUTPUT,INPUT_PULLUP
} enMode;
typedef enum 
{
    LOW, HIGH
} enValue;
typedef enum{
    D0,D1,D2,D3,D4,D5,D6,D7,D8,D9,
    D10,D11,D12,D13,A0,A1,A2,A3,A4,A5
} enPins;


//define macros os function 
#define setBit(reg,bit) (reg |= (1<<bit)) 
#define clearBit(reg,bit) (reg &= ~(1<<bit))
#define toggleBit(reg,bit) (reg ^=(1<<bit))
#define readBit(reg,bit) ((reg & (1<<bit)))
void pinMode(enPins pin ,enMode mode);//determine the mode of the pin.
enValue digitalRead (enPins pin);// to read the value of the pin.
void digitalWrite (enPins pin , enValue value);// to write value on the pin .
void digitalToggle (enPins pin);// to toggle the value of the pin .
void delay(u16 ms);//delay by millisecond. ms -> milliSeconds
void getPinMap(enPins pin,u8**ddr,u8**port,u8**pin_reg,u8*bit);//return the addresse of the Right port.
#endif