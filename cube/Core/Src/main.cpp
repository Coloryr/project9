#include "main.h"
#include "Init/init.h"
#include "cmsis_os.h"
#include "DRV8825/DRV8825.h"
#include "LCD/LCD.h"
#include "Input/Input.h"
#include "YX65491/YX65491.h"
#include "ToF/tof.h"
#include <math.h>
#include "PID/pid.h"

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

char now_set = 0;
short need = 18000;
short now = 0;
short now_dis = 0;
bool edit;
uint8_t set_temp[2] = {0x0F, 0x0F};
bool set_nag = false;
uint8_t set_pos = 0;
unsigned char setfail[] = "set fail";
unsigned char setdone[] = "set done";

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

    uint8_t data_1[5];
    for (;;)
    {
        KEY temp = io->get();
        uint16_t temp1 = tof_1->get();
        now_dis = ((temp1 / 10) - 30);
        data_1[0] = temp1 / 100;
        data_1[1] = temp1 / 10 % 10;
        data_1[2] = temp1 % 10;
        mylcd->hlcd->LCDGotoXY(90, 0);
        mylcd->hlcd->LCDChar(data_1[0] + 0x30);
        mylcd->hlcd->LCDChar(data_1[1] + 0x30);
        mylcd->hlcd->LCDChar(data_1[2] + 0x30);
        mylcd->hlcd->LCDGotoXY(90, 2);

        bool nag = now_dis < 0;
        short data_2 = nag ? abs(now_dis) + 1 : now_dis;

        if (nag)
            mylcd->hlcd->LCDChar('-');
        else
            mylcd->hlcd->LCDChar(' ');
        mylcd->hlcd->LCDChar((data_2 / 10 % 10) + 0x30);
        mylcd->hlcd->LCDChar((data_2 % 10) + 0x30);

        if (temp == KEY_A)
        {
            drv->run();
        }
        else if (temp == KEY_B)
        {
            xyz->reset();
        }
        else if (temp == KEY_C)
        {
            xyz->reset();
        }
        else if (temp == KEY_N)
        {
            edit = true;
            set_pos = 0;
            set_nag = false;
            set_temp[0] = set_temp[1] = 0xF;
            mylcd->hlcd->LCDGotoXY(100, 6);
            mylcd->hlcd->LCDChar('<');
        }
        else if (temp == KEY_M)
        {
            if (edit)
                set_nag = !set_nag;
        }
        else if (edit)
        {
            if (temp == KEY_1)
            {
                set_temp[set_pos++] = 1;
            }
            else if (temp == KEY_2)
            {
                set_temp[set_pos++] = 2;
            }
            else if (temp == KEY_3)
            {
                set_temp[set_pos++] = 3;
            }
            else if (temp == KEY_4)
            {
                set_temp[set_pos++] = 4;
            }
            else if (temp == KEY_5)
            {
                set_temp[set_pos++] = 5;
            }
            else if (temp == KEY_6)
            {
                set_temp[set_pos++] = 6;
            }
            else if (temp == KEY_7)
            {
                set_temp[set_pos++] = 7;
            }
            else if (temp == KEY_8)
            {
                set_temp[set_pos++] = 8;
            }
            else if (temp == KEY_9)
            {
                set_temp[set_pos++] = 9;
            }
            else if (temp == KEY_0)
            {
                set_temp[set_pos++] = 0;
            }
        }

        if (set_pos == 2)
        {
            edit = false;
            mylcd->hlcd->LCDGotoXY(100, 6);
            mylcd->hlcd->LCDChar(' ');
            char set_ = set_temp[0] * 10 + set_temp[1];
            mylcd->hlcd->LCDGotoXY(0, 7);
            if (set_ > 25)
            {
                mylcd->hlcd->LCDString(setfail);
            }
            else
            {
                now_set = set_nag ? -set_ : set_;
                mylcd->hlcd->LCDString(setdone);
            }
        }

        xyz->read();
        now = xyz->gyro;

        nag = now < 0;
        data_2 = nag ? abs(now) + 1 : now;

        data_1[0] = data_2 / 1 % 10;
        data_1[1] = data_2 / 10 % 10;
        data_1[2] = data_2 / 100 % 10;
        data_1[3] = data_2 / 1000 % 10;
        data_1[4] = data_2 / 10000;

        mylcd->hlcd->LCDGotoXY(40, 3);
        if (nag)
            mylcd->hlcd->LCDChar('-');
        else
            mylcd->hlcd->LCDChar(' ');
        mylcd->hlcd->LCDChar(data_1[4] + 0x30);
        mylcd->hlcd->LCDChar(data_1[3] + 0x30);
        mylcd->hlcd->LCDChar(data_1[2] + 0x30);
        mylcd->hlcd->LCDChar('.');
        mylcd->hlcd->LCDChar(data_1[1] + 0x30);
        mylcd->hlcd->LCDChar(data_1[0] + 0x30);

        if (!edit)
        {
            need = balance(now_dis, now_set);

            nag = need < 0;
            data_2 = nag ? abs(need) + 1 : need;
            data_1[0] = data_2 / 1 % 10;
            data_1[1] = data_2 / 10 % 10;
            data_1[2] = data_2 / 100 % 10;
            data_1[3] = data_2 / 1000 % 10;
            data_1[4] = data_2 / 10000;

            mylcd->hlcd->LCDGotoXY(130, 3);

            if (nag)
                mylcd->hlcd->LCDChar('-');
            else
                mylcd->hlcd->LCDChar(' ');
            mylcd->hlcd->LCDChar(data_1[4] + 0x30);
            mylcd->hlcd->LCDChar(data_1[3] + 0x30);
            mylcd->hlcd->LCDChar(data_1[2] + 0x30);
            mylcd->hlcd->LCDChar('.');
            mylcd->hlcd->LCDChar(data_1[1] + 0x30);
            mylcd->hlcd->LCDChar(data_1[0] + 0x30);
            short temp_1 = abs(abs(need) - abs(now));
            if (temp_1 > 30)
            {
                if (need > 0)
                {
                    if (now > 0)
                    {
                        drv->set(now > need);
                    }
                    else
                    {
                        drv->set(true);
                    }
                }
                else
                {
                    if (now > 0)
                    {
                        drv->set(true);
                    }
                    else
                    {
                        drv->set(now < need);
                    }
                }
                if (now > 100)
                {
                    drv->runFast();
                }
                else
                {
                    drv->run();
                }
            }
            mylcd->hlcd->LCDGotoXY(40, 6);

            nag = now_set < 0;
            if (nag)
                mylcd->hlcd->LCDChar('-');
            else
                mylcd->hlcd->LCDChar(' ');
            data_1[1] = now_set % 10;
            data_1[0] = now_set / 10 % 10;

            mylcd->hlcd->LCDChar(data_1[0] + 0x30);
            mylcd->hlcd->LCDChar(data_1[1] + 0x30);
        }
        else
        {
            mylcd->hlcd->LCDGotoXY(40, 6);

            if (set_nag)
                mylcd->hlcd->LCDChar('-');
            else
                mylcd->hlcd->LCDChar(' ');
            mylcd->hlcd->LCDChar(set_temp[0] + 0x30);
            mylcd->hlcd->LCDChar(set_temp[1] + 0x30);
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
