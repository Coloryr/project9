#include "main.h"
#include "Init/init.h"
#include "cmsis_os.h"
#include "DRV8825/DRV8825.h"
#include "LCD/LCD.h"
#include "Input/Input.h"
#include "YX65491/YX65491.h"
#include "ToF/tof.h"

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

bool balance = false;

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();
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
        uint16_t temp1 = tof_1->get();
        uint8_t a, b, c;
        a = temp1 / 100;
        b = temp1 / 10 % 10;
        c = temp1 % 10;
        mylcd->hlcd->LCDGotoXY(90, 0);
        mylcd->hlcd->LCDChar(a + 0x30);
        mylcd->hlcd->LCDChar(b + 0x30);
        mylcd->hlcd->LCDChar(c + 0x30);
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
        else if (temp == KEY_B)
        {
            xyz->reset();
        }
        else if (temp == KEY_D)
        {
            balance = true;
        }
        xyz->read();
        mylcd->hlcd->LCDGotoXY(40, 3);

        if (xyz->gyro > 180)
        {
            uint8_t temp = 180 - (xyz->gyro - 475);
            a = temp / 100;
            b = temp / 10 % 10;
            c = temp % 10;
            mylcd->hlcd->LCDChar('-');
            mylcd->hlcd->LCDChar(a + 0x30);
            mylcd->hlcd->LCDChar(b + 0x30);
            mylcd->hlcd->LCDChar(c + 0x30);
            if (balance)
            {
                drv->set(true);
                if (temp != 180)
                {
                    if (temp > 20)
                    {
                        drv->runFast();
                    }
                    else
                    {
                        drv->run();
                    }
                }
                else
                {
                    balance = false;
                }
            }
        }
        else
        {
            a = xyz->gyro / 100;
            b = xyz->gyro / 10 % 10;
            c = xyz->gyro % 10;
            mylcd->hlcd->LCDChar(' ');
            mylcd->hlcd->LCDChar(a + 0x30);
            mylcd->hlcd->LCDChar(b + 0x30);
            mylcd->hlcd->LCDChar(c + 0x30);
            if (balance)
            {
                drv->set(false);
                if (xyz->gyro != 179)
                {
                    if (temp > 20)
                    {
                        drv->runFast();
                    }
                    else
                    {
                        drv->run();
                    }
                }
                else
                {
                    balance = false;
                }
            }
        }
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
    tof_1 = new tof(I2C1);
    tof_2 = new tof(I2C2);

    osThreadNew(TaskShow, NULL, &task_input);
    for (;;)
    {
        io->scan();
        tof_1->read();
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
