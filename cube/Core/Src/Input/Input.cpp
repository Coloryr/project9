#include "Input.h"
#include "cmsis_os.h"

Input *io;

Input::Input()
{
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_0);
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1);
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);
}

void Input::scan()
{
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_0);
    osDelay(10);
    KEY temp = KEY_NULL;
    if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_4) == 0)
    {
        if (now == KEY_1)
        {
            temp = KEY_1;
        }
        else
        {
            now = KEY_1;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_5) == 0)
    {
        if (now == KEY_4)
        {
            temp = KEY_4;
        }
        else
        {
            now = KEY_4;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_6) == 0)
    {
        if (now == KEY_7)
        {
            temp = KEY_7;
        }
        else
        {
            now = KEY_7;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_7) == 0)
    {
        if (now == KEY_N)
        {
            temp = KEY_N;
        }
        else
        {
            now = KEY_N;
        }
    }
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_0);
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_1);
    osDelay(10);
    if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_4) == 0)
    {
        if (now == KEY_2)
        {
            temp = KEY_2;
        }
        else
        {
            now = KEY_2;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_5) == 0)
    {
        if (now == KEY_5)
        {
            temp = KEY_5;
        }
        else
        {
            now = KEY_5;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_6) == 0)
    {
        if (now == KEY_8)
        {
            temp = KEY_8;
        }
        else
        {
            now = KEY_8;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_7) == 0)
    {
        if (now == KEY_0)
        {
            temp = KEY_0;
        }
        else
        {
            now = KEY_0;
        }
    }
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1);
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_2);
    osDelay(10);
    if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_4) == 0)
    {
        if (now == KEY_3)
        {
            temp = KEY_3;
        }
        else
        {
            now = KEY_3;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_5) == 0)
    {
        if (now == KEY_6)
        {
            temp = KEY_6;
        }
        else
        {
            now = KEY_6;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_6) == 0)
    {
        if (now == KEY_9)
        {
            temp = KEY_9;
        }
        else
        {
            now = KEY_9;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_7) == 0)
    {
            temp = KEY_M;
            now = KEY_M;
    }
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_3);
    osDelay(10);
    if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_4) == 0)
    {
        if (now == KEY_A)
        {
            temp = KEY_A;
        }
        else
        {
            now = KEY_A;
        }
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_5) == 0)
    {
            temp = KEY_B;
            now = KEY_B;
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_6) == 0)
    {
            temp = KEY_C;
            now = KEY_C;
    }
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_7) == 0)
    {
            temp = KEY_D;
            now = KEY_D;
    }
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);

    if (temp == KEY_NULL)
    {
        if (now != KEY_NULL)
        {
            out = now;
            now = KEY_NULL;
        }
    }
}

KEY Input::get()
{
    KEY temp = out;
    out = KEY_NULL;
    return temp;
}
