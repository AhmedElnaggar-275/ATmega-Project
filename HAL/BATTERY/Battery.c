#include "Battery.h"


void batteryInit(void)
{
    pinMode(ALERT_PIN,OUTPUT);// Set the alert pin as an output
    digitalWrite(ALERT_PIN,LOW);// Initialize the alert pin to LOW
}

f32 readBatteryVoltage(void)
{
    f32 batteryVolt = analogRead(VOLTAGE_READ_CH) ; // Read the battery voltage from the defined ADC channel
    batteryVolt = (batteryVolt/1023.0)*5.0; // Convert the ADC value to voltage (assuming a 5V reference and 10-bit ADC resolution)
    return batteryVolt*5;  
    // Scale the voltage to the actual battery voltage (assuming a voltage divider with a ratio of 1:5)
}

void checkBatteryVoltage(void)
{
    if(readBatteryVoltage()<=BATTERY_LOW_VOLTAGE)// Check if the battery voltage is below or equal to the defined threshold
    {
        digitalWrite(ALERT_PIN,HIGH);// Trigger the alert if the battery voltage is below the threshold
    }
}