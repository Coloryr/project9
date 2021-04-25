#include <Arduino.h>
#include "tof.h"
#include "stm32f1xx_hal_i2c.h"
#include "LL/stm32yyxx_ll.h"

I2C_HandleTypeDef hi2c1;

tof::tof(uint32_t scl, uint32_t sda)
{
    this->scl = scl;
    this->sda = sda;
}

void tof::init()
{
    LL_RCC_ClocksTypeDef rcc_clocks;
    LL_GPIO_InitTypeDef GPIO_Initstruct;
    /* 1.初始化对应IO. */
    LL_AHB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
    GPIO_Initstruct.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_9;
    GPIO_Initstruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_Initstruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_Initstruct.Pull = LL_GPIO_PULL_UP;
    GPIO_Initstruct.Speed = LL_GPIO_MODE_OUTPUT_10MHz;
    LL_GPIO_Init(GPIOB, &GPIO_Initstruct);
    RCC->APB1RSTR |= (RCC_APB1RSTR_I2C1RST);
    RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C1RST);
    /* 2.开启I2C时钟. */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
    /* 3.先禁止I2C外设,这样才能设置寄存器. */
    LL_I2C_Disable(I2C1);
    /* 4.设置I2C速度为100kHz. */
    LL_RCC_GetSystemClocksFreq(&rcc_clocks);
    LL_I2C_ConfigSpeed(I2C1, rcc_clocks.PCLK1_Frequency, 100000, LL_I2C_DUTYCYCLE_2);
    /* 5.使能I2C外设. */
    LL_I2C_Enable(I2C1);
}
