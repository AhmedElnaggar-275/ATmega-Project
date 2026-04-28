#include "GPIO_Interface.h"
#include "STD_BITMATH.h"

void getPinMap(enPins pin,u8**ddr,u8**port,u8**pin_reg,u8*bit)
{
    /* This function takes the address of the pointers that will hold
       the addresses of the DDRx, PORTx, and PINx registers for the specified pin */
    /* It also takes the address of the bit position to change bit value accordingly 
       with the specified pin */

    // PortD from D0 to D7
    if(pin <= D7)   // PD0 to PD7 (8 digital pins)
    {
        *ddr = &DDRD;
        *port = &PORTD;
        *pin_reg = &PIND;
        *bit = pin;
    }
    // PORTB from D8 to D13
    else if(pin>=D8 && pin<=D13) // PB0 to PB5 (6 digital pins)
    {
        *ddr = &DDRB;
        *port = &PORTB;
        *pin_reg = &PINB;
        *bit = pin - D8;
    }
    // PORTC from A0 to A5
    else if (pin>=A0 && pin<=A5) // PC0 to PC5 (6 analog pins that can also be used as digital pins)
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

    getPinMap(pin,&ddr,&port,&pin_reg,&bit); // Get the address of the target port registers 
                                             // and the bit position for the specified pin

    switch (mode)
    {
    case OUTPUT:
        setBit(*ddr,bit); // Configure pin as Output
        break;
    
    case INPUT:
        clearBit(*ddr,bit); // Configure pin as Input
        break;

    case INPUT_PULLUP:
        setBit(MCUCR, 0); // PULL_UP resistors disable is off (PULL_UP enabled)
        clearBit(*ddr,bit); // Configure pin as Input
        setBit(*port,bit); // Use PULL_UP resistor option for the pin
        break;
    }
}
enValue digitalRead (enPins pin)
{
    u8*ddr,*port,bit,*pin_reg;

    getPinMap(pin,&ddr,&port,&pin_reg,&bit); // Get the address of the target port registers 
                                             // and the bit position for the specified pin

    clearBit(*ddr,bit);// configure pin as Input

    return (enValue)(readBit(*pin_reg,bit));// return 0 means LOW , returns 1 means HIGH.
}
void digitalWrite (enPins pin , enValue value)
{
    u8*ddr,*port, *pin_reg,bit;

    getPinMap(pin,&ddr,&port,&pin_reg,&bit); // Get the address of the target port registers 
                                             // and the bit position for the specified pin

    setBit(*ddr,bit);// configure pin as Output 
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

    getPinMap(pin,&ddr,&port,&pin_reg,&bit); // Get the address of the target port registers 
                                             // and the bit position for the specified pin
    setBit(*ddr,bit);// configure pin as Output

    toggleBit(*port,bit);// Toggle pin value
}