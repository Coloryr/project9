#include "DRV8825.h"
#include <Arduino.h>

DRV8825::DRV8825()
{
    pinMode(Enable, OUTPUT);   // Enable
    pinMode(Step, OUTPUT);     // Step
    pinMode(Dir, OUTPUT);      // Dir
    digitalWrite(Enable, LOW); // Set Enable low
}

void DRV8825::run()
{
    digitalWrite(4, HIGH);        // Set Dir high  
    for (int x = 0; x < 200; x++) // Loop 200 times  
    {
        digitalWrite(5, HIGH);  // Output high  
        delayMicroseconds(800); // Wait 1/2 a ms  
        digitalWrite(5, LOW);   // Output low  
        delayMicroseconds(800); // Wait 1/2 a ms  
    }
    delay(1000);                  // pause one second   
    digitalWrite(4, LOW);         // Set Dir low  
    for (int x = 0; x < 200; x++) // Loop 2000 times  
    {
        digitalWrite(5, HIGH);  // Output high  
        delayMicroseconds(800); // Wait 1/2 a ms  
        digitalWrite(5, LOW);   // Output low  
        delayMicroseconds(800); // Wait 1/2 a ms  
    }
    delay(1000); // pause one second  
}