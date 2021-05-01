#include "Arduino.h"
#include "Input.h"
#include "LL/stm32yyxx_ll.h"

Input::Input()
{
    pinMode(PC0, OUTPUT);
    pinMode(PC1, OUTPUT);
    pinMode(PC2, OUTPUT);
    pinMode(PC3, OUTPUT);

    pinMode(PC4, INPUT);
    pinMode(PC5, INPUT);
    pinMode(PC6, INPUT);
    pinMode(PC7, INPUT);

    digitalWrite(PC0, HIGH);
    digitalWrite(PC1, HIGH);
    digitalWrite(PC2, HIGH);
    digitalWrite(PC3, HIGH);
}

void Input::scan()
{
    digitalWrite(PC0, LOW);
    delay(10);
    if (digitalRead(PC4) == LOW)
    {
        if (now == KEY_1)
        {
            out = KEY_1;
        }
        else
        {
            now = KEY_1;
        }
    }
    else if (digitalRead(PC5) == LOW)
    {
        if (now == KEY_4)
        {
            out = KEY_4;
        }
        else
        {
            now = KEY_4;
        }
    }
    else if (digitalRead(PC6) == LOW)
    {
        if (now == KEY_7)
        {
            out = KEY_7;
        }
        else
        {
            now = KEY_7;
        }
    }
    else if (digitalRead(PC7) == LOW)
    {
        if (now == KEY_N)
        {
            out = KEY_N;
        }
        else
        {
            now = KEY_N;
        }
    }
    digitalWrite(PC0, HIGH);
    digitalWrite(PC1, LOW);
    delay(10);
    if (digitalRead(PC4) == LOW)
    {
        if (now == KEY_2)
        {
            out = KEY_2;
        }
        else
        {
            now = KEY_2;
        }
    }
    else if (digitalRead(PC5) == LOW)
    {
        if (now == KEY_5)
        {
            out = KEY_5;
        }
        else
        {
            now = KEY_5;
        }
    }
    else if (digitalRead(PC6) == LOW)
    {
        if (now == KEY_8)
        {
            out = KEY_8;
        }
        else
        {
            now = KEY_8;
        }
    }
    else if (digitalRead(PC7) == LOW)
    {
        if (now == KEY_0)
        {
            out = KEY_0;
        }
        else
        {
            now = KEY_0;
        }
    }
    digitalWrite(PC1, HIGH);
    digitalWrite(PC2, LOW);
    delay(10);
    if (digitalRead(PC4) == LOW)
    {
        if (now == KEY_3)
        {
            out = KEY_3;
        }
        else
        {
            now = KEY_3;
        }
    }
    else if (digitalRead(PC5) == LOW)
    {
        if (now == KEY_6)
        {
            out = KEY_6;
        }
        else
        {
            now = KEY_6;
        }
    }
    else if (digitalRead(PC6) == LOW)
    {
        if (now == KEY_9)
        {
            out = KEY_9;
        }
        else
        {
            now = KEY_9;
        }
    }
    else if (digitalRead(PC7) == LOW)
    {
        if (now == KEY_M)
        {
            out = KEY_M;
        }
        else
        {
            now = KEY_M;
        }
    }
    digitalWrite(PC2, HIGH);
    digitalWrite(PC3, LOW);
    delay(10);
    if (digitalRead(PC4) == LOW)
    {
        if (now == KEY_A)
        {
            out = KEY_A;
        }
        else
        {
            now = KEY_A;
        }
    }
    else if (digitalRead(PC5) == LOW)
    {
        if (now == KEY_B)
        {
            out = KEY_B;
        }
        else
        {
            now = KEY_B;
        }
    }
    else if (digitalRead(PC6) == LOW)
    {
        if (now == KEY_C)
        {
            out = KEY_C;
        }
        else
        {
            now = KEY_C;
        }
    }
    else if (digitalRead(PC7) == LOW)
    {
        if (now == KEY_D)
        {
            out = KEY_D;
        }
        else
        {
            now = KEY_D;
        }
    }
    digitalWrite(PC3, HIGH);
}

KEY Input::get()
{
    KEY temp = out;
    out = KEY_NULL;
    return temp;
}
