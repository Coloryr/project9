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

void DRV8825::set(bool dir)
{
    digitalWrite(DRV_Dir, dir ? HIGH : LOW);
}

void DRV8825::run()
{
    digitalWrite(DRV_Step, HIGH);
    digitalWrite(DRV_Step, LOW);
}

void DRV8825::runFast()
{
    digitalWrite(DRV_M0, LOW);
    digitalWrite(DRV_Step, HIGH);
    digitalWrite(DRV_Step, LOW);
    digitalWrite(DRV_M0, HIGH);
}