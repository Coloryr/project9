#include "main.h"
#include "cmsis_os.h"
#include "Init/init.h"
#include "Input/Input.h"
#include "LCD/LCD.h"
#include "AD9833/AD9833.h"
#include "ADC/ADC.h"

const osThreadAttr_t task_show = {
    .name = "show",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

const osThreadAttr_t task_input = {
    .name = "input",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

void TaskInput(void *argument);
void TaskShow(void *data);

uint32_t now_set = 0;
bool edit;
uint8_t set_temp[5] = {0x0F, 0x0F, 0x0F, 0x0F, 0x0F};
uint8_t set_pos = 0;
unsigned char setfail[] = "set fail";
unsigned char setdone[] = "set done";

uint16_t AD_DMA[2048];

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_SPI2_Init();
  MX_ADC3_Init();

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
    if (temp == KEY_A)
    {
    }
    else if (temp == KEY_B)
    {
    }
    else if (temp == KEY_C)
    {
    }
    else if (temp == KEY_N)
    {
      edit = true;
      set_pos = 0;
      set_temp[0] = set_temp[1] = set_temp[2] = set_temp[3] = set_temp[4] = 0xF;
      mylcd->hlcd->LCDGotoXY(200, 0);
      mylcd->hlcd->LCDChar('<');
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
      uint32_t set_ = set_temp[0] * 10000 + set_temp[1] * 1000 + set_temp[2] * 100 + set_temp[3] * 10 + set_temp[4] * 1;
      mylcd->hlcd->LCDGotoXY(0, 7);
      if (set_ > 5000)
      {
        mylcd->hlcd->LCDString(setfail);
      }
      else
      {
        now_set = set_;
        dds->AD9833_SetFrequencyQuick(now_set, AD9833_OUT_SINUS);
        mylcd->hlcd->LCDString(setdone);
      }
    }

    if (!edit)
    {
      data_1[0] = now_set / 1 % 10;
      data_1[1] = now_set / 10 % 10;
      data_1[2] = now_set / 100 % 10;
      data_1[3] = now_set / 1000 % 10;
      data_1[4] = now_set / 10000;

      mylcd->hlcd->LCDGotoXY(130, 0);

      mylcd->hlcd->LCDChar(data_1[4] + 0x30);
      mylcd->hlcd->LCDChar(data_1[3] + 0x30);
      mylcd->hlcd->LCDChar(data_1[2] + 0x30);
      mylcd->hlcd->LCDChar(data_1[1] + 0x30);
      mylcd->hlcd->LCDChar(data_1[0] + 0x30);
    }
    else
    {
      mylcd->hlcd->LCDGotoXY(40, 6);
      mylcd->hlcd->LCDChar(set_temp[0] + 0x30);
      mylcd->hlcd->LCDChar(set_temp[1] + 0x30);
    }

    osDelay(100);
  }
}

void TaskInput(void *argument)
{
  io = new Input();
  mylcd = new LCD();
  mylcd->initShow();
  dds = new AD9833();
  dds->AD9833_Init();
  dds->AD9833_SetFrequencyQuick(1, AD9833_OUT_SINUS);
  adc = new ADCs();
  
  osThreadNew(TaskShow, NULL, &task_input);
  for (;;)
  {
    io->scan();
    osDelay(10);
  }
}
