#include "DRV8825.h"

DRV8825::DRV8825()
{
    HAL_GPIO_WritePin(GPIOB, DRV_Enable, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOB, DRV_Sleep, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, DRV_Res, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, DRV_M0, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, DRV_M1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, DRV_M2, GPIO_PIN_RESET);
}

void DRV8825::set(bool dir)
{
    HAL_GPIO_WritePin(GPIOB, DRV_Dir, dir ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void DRV8825::run()
{
    HAL_GPIO_WritePin(GPIOB, DRV_Step, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, DRV_Step, GPIO_PIN_RESET);
}

void DRV8825::runFast()
{
    HAL_GPIO_WritePin(GPIOB, DRV_M0, GPIO_PIN_RESET);
    run();
    HAL_GPIO_WritePin(GPIOB, DRV_M0, GPIO_PIN_SET);
}