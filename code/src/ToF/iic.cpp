#include <Arduino.h>
#include "iic.h"

iic::iic(I2C_TypeDef *iic)
{
    this->_iic = iic;
}

void iic::init(bool Remap = false)
{
    LL_RCC_ClocksTypeDef rcc_clocks;
    LL_GPIO_InitTypeDef GPIO_Initstruct;

    if (_iic == I2C1)
    {
        RCC->APB1RSTR |= (RCC_APB1RSTR_I2C1RST);
        RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C1RST);
        LL_AHB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

        GPIO_Initstruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_Initstruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
        GPIO_Initstruct.Pull = LL_GPIO_PULL_UP;
        GPIO_Initstruct.Speed = LL_GPIO_MODE_OUTPUT_10MHz;
        if (Remap)
        {
            GPIO_Initstruct.Pin = LL_GPIO_PIN_8 | LL_GPIO_PIN_9;
            LL_GPIO_AF_EnableRemap_I2C1();
        }
        else
        {
            GPIO_Initstruct.Pin = LL_GPIO_PIN_8 | LL_GPIO_PIN_9;
            LL_GPIO_AF_DisableRemap_I2C1();
        }
        LL_GPIO_Init(GPIOB, &GPIO_Initstruct);
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
    }
    else if (_iic == I2C1)
    {
        RCC->APB1RSTR |= (RCC_APB1RSTR_I2C1RST);
        RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C1RST);
        LL_AHB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

        GPIO_Initstruct.Mode = LL_GPIO_MODE_ALTERNATE;
        GPIO_Initstruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
        GPIO_Initstruct.Pull = LL_GPIO_PULL_UP;
        GPIO_Initstruct.Speed = LL_GPIO_MODE_OUTPUT_10MHz;
        if (Remap)
        {
            GPIO_Initstruct.Pin = LL_GPIO_PIN_8 | LL_GPIO_PIN_9;
            LL_GPIO_AF_EnableRemap_I2C1();
        }
        else
        {
            GPIO_Initstruct.Pin = LL_GPIO_PIN_8 | LL_GPIO_PIN_9;
            LL_GPIO_AF_DisableRemap_I2C1();
        }
        LL_GPIO_Init(GPIOB, &GPIO_Initstruct);
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
    }

    LL_I2C_Disable(_iic);
    LL_RCC_GetSystemClocksFreq(&rcc_clocks);
    LL_I2C_ConfigSpeed(_iic, rcc_clocks.PCLK1_Frequency, 1000000, LL_I2C_DUTYCYCLE_2);
    LL_I2C_Enable(_iic);
}