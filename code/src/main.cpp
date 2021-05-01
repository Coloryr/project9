#include <Arduino.h>
#include "lcd/lcd.h"
#include "ToF/tof.h"
#include "IO/Input.h"
#include "DRV8825/DRV8825.h"
#include "SPI.h"
#include <STM32FreeRTOS.h>

lcd *mylcd;
tof *mytof;
Input *io;
DRV8825 *drv;

void taskA(void *data)
{
    for (;;)
    {
        io->scan();
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void taskB(void *data)
{
    for (;;)
    {
        KEY temp = io->get();
        mylcd->hlcd->LCDGotoXY(0, 3);
        mylcd->hlcd->LCDChar(temp + 0x30);
        if (temp == KEY_1)
        {
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void setup()
{
    mylcd = new lcd();
    mylcd->initShow();
    io = new Input();
    drv = new DRV8825();
    // mytof = new tof(tof_scl, tof_sda);
    for (;;)
        drv->run();
    xTaskCreate(
        taskA, (const portCHAR *)"Key", 512,
        NULL, 2, NULL);

    xTaskCreate(
        taskB, (const portCHAR *)"Show", 512,
        NULL, 2, NULL);

    vTaskStartScheduler();
    while (1)
        ;
}

void loop()
{
    while (1)
    {
        // noInterrupts();
        // interrupts();
    }
}