#include "DRV8825.h"

DRV8825 *drv;

DRV8825::DRV8825()
{
    LL_GPIO_ResetOutputPin(GPIOB, DRV_Enable);

    LL_GPIO_SetOutputPin(GPIOB, DRV_Sleep);
    LL_GPIO_SetOutputPin(GPIOB, DRV_Res);

    LL_GPIO_SetOutputPin(GPIOB, DRV_M0);
    LL_GPIO_ResetOutputPin(GPIOB, DRV_M1);
    LL_GPIO_SetOutputPin(GPIOB, DRV_M2);
}

void DRV8825::set(bool dir)
{
    if (dir)
    {
        LL_GPIO_SetOutputPin(GPIOB, DRV_Dir);
    }
    else
    {
        LL_GPIO_ResetOutputPin(GPIOB, DRV_Dir);
    }
}

void DRV8825::run()
{
    LL_GPIO_SetOutputPin(GPIOB, DRV_Step);
    LL_GPIO_ResetOutputPin(GPIOB, DRV_Step);
}

void DRV8825::runFast()
{
    LL_GPIO_ResetOutputPin(GPIOB, DRV_M2);
    run();
    LL_GPIO_SetOutputPin(GPIOB, DRV_M2);
}
