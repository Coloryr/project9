#include "DRV8825.h"
#include <Arduino.h>

DRV8825::DRV8825()
{
    pinMode(DRV_M0, OUTPUT);
    pinMode(DRV_M1, OUTPUT);
    pinMode(DRV_M2, OUTPUT);
    pinMode(DRV_Enable, OUTPUT);
    pinMode(DRV_Step, OUTPUT);
    pinMode(DRV_Dir, OUTPUT);
    pinMode(DRV_Res, OUTPUT);
    pinMode(DRV_Sleep, OUTPUT);

    digitalWrite(DRV_Enable, LOW);

    digitalWrite(DRV_Sleep, HIGH);
    digitalWrite(DRV_Res, HIGH);

    digitalWrite(DRV_M0, HIGH);
    digitalWrite(DRV_M1, LOW);
    digitalWrite(DRV_M2, LOW);
}

void DRV8825::run()
{
    digitalWrite(DRV_Dir, HIGH);  // Set Dir high  
    for (int x = 0; x < 200; x++) // Loop 200 times  
    {
        digitalWrite(DRV_Step, HIGH); // Output high  
        delayMicroseconds(800);       // Wait 1/2 a ms  
        digitalWrite(DRV_Step, LOW);  // Output low  
        delayMicroseconds(800);       // Wait 1/2 a ms  
    }
    delay(1000);                  // pause one second   
    digitalWrite(DRV_Dir, LOW);   // Set Dir low  
    for (int x = 0; x < 200; x++) // Loop 2000 times  
    {
        digitalWrite(DRV_Step, HIGH); // Output high  
        delayMicroseconds(800);       // Wait 1/2 a ms  
        digitalWrite(DRV_Step, LOW);  // Output low  
        delayMicroseconds(800);       // Wait 1/2 a ms  
    }
    delay(1000); // pause one second  
}