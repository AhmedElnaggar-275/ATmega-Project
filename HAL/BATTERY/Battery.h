#ifndef BATTERY_INTERFACE_H
#define BATTERY_INTERFACE_H

#include "ADC_Interface.h"
#include "GPIO_Interface.h"
#include "STD_TYPES.h"


#define VOLTAGE_READ_CH   A2 // Define the ADC channel for battery voltage reading
#define ALERT_PIN         D2 // Define the pin for battery voltage reading and alert signal
#define BATTERY_LOW_VOLTAGE  6 // Define the voltage threshold for low battery alert



void batteryInit(void); // Initialize the battery monitoring system
u16 readBatteryVoltage(void); // Read the current battery voltage and return it as a 16-bit 
void checkBatteryVoltage(void);// Check the battery voltage and trigger an alert if it is below the defined threshold

#endif