#ifndef Relay_h
#define Relay_h

#include "main.h"

void TR_H()
{
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
}

void TR_L()
{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
}

void RIN_MCU_H()
{
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
}

void RIN_MCU_L()
{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
}

void TR_AC_MCU_H()
{
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_3);
}

void TR_AC_MCU_L()
{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_3);
}
void KEEP_H()
{
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_0);
}

void KEEP_L()
{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);
}

void AD_DC_MCU_H()
{
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
}

void AD_DC_MCU_L()
{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1);
}

void OUT_C_H()
{
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_2);
}

void OUT_C_L()
{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_2);
}

void ALL_L()
{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0 | LL_GPIO_PIN_1 | LL_GPIO_PIN_2 | LL_GPIO_PIN_3 | LL_GPIO_PIN_4 | LL_GPIO_PIN_5);
}

#endif
