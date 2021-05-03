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
    if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_4) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_5) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_6) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_7) == 0)
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
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_0);
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_1);
    osDelay(10);
    if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_4) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_5) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_6) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_7) == 0)
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
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_1);
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_2);
    osDelay(10);
    if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_4) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_5) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_6) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_7) == 0)
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
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_2);
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_3);
    osDelay(10);
    if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_4) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_5) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_6) == 0)
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
    else if (LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_7) == 0)
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
    LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_3);
}

KEY Input::get()
{
    KEY temp = out;
    out = KEY_NULL;
    return temp;
}
