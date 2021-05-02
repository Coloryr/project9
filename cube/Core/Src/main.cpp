#include "main.h"
#include "Init/init.h"
#include "cmsis_os.h"
#include "DRV8825/DRV8825.h"
#include "LCD/LCD.h"
#include "Input/Input.h"
#include "YX65491/YX65491.h"

const osThreadAttr_t task_input = {
    .name = "input",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

const osThreadAttr_t task_show = {
    .name = "show",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

void TaskShow(void *data);
void TaskInput(void *data);

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

    osThreadNew(TaskInput, NULL, &task_input);

    osKernelStart();

    while (1)
    {
    }
}

void TaskShow(void *data)
{
    for (;;)
    {
        KEY temp = io->get();
        mylcd->hlcd->LCDGotoXY(0, 4);
        mylcd->hlcd->LCDChar(temp + 0x30);
        if (temp == KEY_1)
        {
            drv->run();
        }
        else if (temp == KEY_2)
        {
            drv->set(true);
        }
        else if (temp == KEY_3)
        {
            drv->set(false);
        }
        else if (temp == KEY_A)
        {
            drv->runFast();
        }
        mylcd->hlcd->LCDGotoXY(40, 3);
        mylcd->hlcd->LCDChar(xyz->gyro[0]);
        mylcd->hlcd->LCDGotoXY(72, 3);
        mylcd->hlcd->LCDChar(xyz->gyro[1]);
        mylcd->hlcd->LCDGotoXY(144, 3);
        mylcd->hlcd->LCDChar(xyz->gyro[2]);

        // Serial1.print("gyro:\t");
        // Serial1.print(gyro[0]);
        // Serial1.print("\t");
        // Serial1.print(gyro[1]);
        // Serial1.print("\t");
        // Serial1.print(gyro[2]);
        // Serial1.print("  ,YPR:\t");
        // Serial1.print(YPR[2], DEC);
        // Serial1.print("\t"); //显示航向
        // Serial1.print(YPR[1], DEC);
        // Serial1.print("\t");          //显示俯仰角
        // Serial1.println(YPR[0], DEC); //显示横滚角
        osDelay(100);
    }
}

void TaskInput(void *argument)
{
    drv = new DRV8825();
    io = new Input();
    mylcd = new LCD();
    mylcd->initShow();
    xyz = new YX65491();
    xyz->init();
    osThreadNew(TaskShow, NULL, &task_input);
    for (;;)
    {
        io->scan();
        osDelay(10);
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
