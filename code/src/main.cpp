#include <Arduino.h>
#include "lcd/lcd.h"
#include "ToF/tof.h"
#include "IO/Input.h"
#include "DRV8825/DRV8825.h"
#include "YX65491/YX65491.h"
#include <STM32FreeRTOS.h>
#include "main.h"

lcd *mylcd;
tof *mytof;
Input *io;
DRV8825 *drv;
YX65491 *xyz;

void taskA(void *data)
{
    for (;;)
    {
        io->scan();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void taskB(void *data)
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
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void taskC(void *data)
{
    for (;;)
    {

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void setup()
{
    mylcd = new lcd();
    mylcd->initShow();
    io = new Input();
    drv = new DRV8825();
    xyz = new YX65491();
    xyz->init();
    // mytof = new tof(tof_scl, tof_sda);
    xTaskCreate(
        taskA, (const portCHAR *)"Key", 512,
        NULL, 2, NULL);

    xTaskCreate(
        taskB, (const portCHAR *)"Show", 512,
        NULL, 2, NULL);

    xTaskCreate(
        taskC, (const portCHAR *)"Serial", 512,
        NULL, 2, NULL);

    vTaskStartScheduler();
    while (1)
        ;
}

void loop()
{
}