#include "Input.h"
#include "cmsis_os.h"

Input::Input()
{
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_0, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_2, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_3, GPIO_PIN_SET);
}

void Input::scan()
{
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_0, GPIO_PIN_RESET);
    osDelay(10);
    if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_4) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_5) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_6) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_7) == GPIO_PIN_RESET)
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
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_0, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_1, GPIO_PIN_RESET);
    osDelay(10);
    if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_4) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_5) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_6) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_7) == GPIO_PIN_RESET)
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
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_2, GPIO_PIN_RESET);
    osDelay(10);
    if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_4) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_5) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_6) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_7) == GPIO_PIN_RESET)
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
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_2, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_3, GPIO_PIN_RESET);
    osDelay(10);
    if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_4) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_5) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_6) == GPIO_PIN_RESET)
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
    else if (HAL_GPIO_ReadPin(GPIOC, LL_GPIO_PIN_7) == GPIO_PIN_RESET)
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
    HAL_GPIO_WritePin(GPIOC, LL_GPIO_PIN_3, GPIO_PIN_SET);
}

KEY Input::get()
{
    KEY temp = out;
    out = KEY_NULL;
    return temp;
}
