#include "GPIO_Interface.h"
#include "STD_BITMATH.h"

void getPinMap(enPins pin,u8**ddr,u8**port,u8**pin_reg,u8*bit)
{
    // PortD from D0 to D7
    if(pin <= D7)
    {
        *ddr = &DDRD;
        *port = &PORTD;
        *pin_reg = &PIND;
        *bit = pin;
    }
    // PORTB from D8 to D13
    else if(pin>=D8 && pin<=D13)
    {
        *ddr = &DDRB;
        *port = &PORTB;
        *pin_reg = &PINB;
        *bit = pin - D8;
    }
    // PORTC from A0 to A5
    else if (pin>=A0 && pin<=A5)
    {
        *ddr = &DDRC;
        *port = &PORTC;
        *pin_reg = &PINC;
        *bit = pin - A0;

    }
}
void pinMode(enPins pin ,enMode mode)
{
    u8*ddr,*port, *pin_reg,bit;
    getPinMap(pin,&ddr,&port,&pin_reg,&bit);
    switch (mode)
    {
    case OUTPUT:
        setBit(*ddr,bit);//Make pin Output
        break;
    
    case INPUT:
        clearBit(*ddr,bit);// Make pin Input
        break;

    case INPUT_PULLUP:
        clearBit(*ddr,bit);// Make pin Input
        setBit(*port,bit);// Enable pull-up resistor
        break;
    }
}
enValue digitalRead (enPins pin)
{
    u8*ddr,*port,bit,*pin_reg;
    getPinMap(pin,&ddr,&port,&pin_reg,&bit);// Get the address of the right port
    clearBit(*ddr,bit);// Make pin Input
    return (enValue)(readBit(*pin_reg,bit));// return 0 means LOW , returns 1 means HIGH.
}
void digitalWrite (enPins pin , enValue value)
{
    u8*ddr,*port, *pin_reg,bit;
    getPinMap(pin,&ddr,&port,&pin_reg,&bit);// Get the address of the right port
    setBit(*ddr,bit);//make pin Output 
    switch (value)
    {
    case HIGH:
        setBit(*port,bit);// Write HIGH on the pin
        break;
    
    case LOW:
        clearBit(*port,bit);// Write LOW on the pin
        break;
    }
}
void digitalToggle (enPins pin)
{
    u8*ddr,*port,*pin_reg,bit;
    getPinMap(pin,&ddr,&port,&pin_reg,&bit);// Get the address of the right port
    setBit(*ddr,bit);// Make pin Output
    toggleBit(*port,bit);// Toggle the value of the pin
}
void delay(u16 ms)
{
    while(ms--)
    {
        for(u16 i=0;i<1000;i++);// Do nothing for 1 millisecond
    }
}