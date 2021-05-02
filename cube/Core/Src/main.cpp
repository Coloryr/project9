#include "main.h"
#include "Init/init.h"
#include "cmsis_os.h"
#include "DRV8825/DRV8825.h"
#include "LCD/LCD.h"
#include "Input/Input.h"

osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

void StartDefaultTask(void *argument);

DRV8825 *drv;
Input *io;
LCD *mylcd;

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();
    MX_I2C1_Init();
    MX_I2C2_Init();
    MX_SPI1_Init();

    osKernelInitialize();

    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

    osKernelStart();

    while (1)
    {
    }
}

void StartDefaultTask(void *argument)
{
    drv = new DRV8825();
    io = new Input();
    mylcd = new LCD();
    mylcd->initShow();
    for (;;)
    {
        osDelay(1);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
        HAL_IncTick();
    }
}

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
