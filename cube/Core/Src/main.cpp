#include "main.h"
#include "cmsis_os.h"
#include "Init/init.h"
#include "Input/Input.h"
#include "LCD/LCD.h"
#include "AD9833/AD9833.h"
#include "ADC/ADC.h"
#include "Relay/relay.h"

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

uint32_t now_set = 1000;
bool edit = false;
bool out = false;
uint8_t set_temp[10] = {0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F};
uint8_t set_pos = 0;
uint8_t setfail[] = "set fail                  ";
uint8_t setdone[] = "set done                  ";
uint8_t on[] = "on ";
uint8_t off[] = "off";

uint16_t AD1_DMA[2048];
uint16_t AD3_DMA[2048];

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

uint16_t find(uint16_t *data, uint16_t size)
{
  uint16_t max = 0;
  for (uint16_t a = 0; a < size; a++)
  {
    max = max < data[a] ? data[a] : max;
  }
  return max;
}

void changeOut(bool isOut)
{
  if (isOut)
  {
    dds->AD9833_SetFrequencyQuick(now_set, AD9833_OUT_SINUS);
    mylcd->hlcd->LCDGotoXY(168, 5);
    mylcd->hlcd->LCDString(on);
  }
  else
  {
    dds->AD9833_SetFrequencyQuick(0, AD9833_OUT_SINUS);
    mylcd->hlcd->LCDGotoXY(168, 5);
    mylcd->hlcd->LCDString(off);
  }
}

void ShowA(uint32_t data)
{
  uint8_t data_1[9];
  data_1[0] = data / 1 % 10;
  data_1[1] = data / 10 % 10;
  data_1[2] = data / 100 % 10;
  data_1[3] = data / 1000 % 10;
  data_1[4] = data / 10000 % 10;
  data_1[5] = data / 100000 % 10;
  data_1[6] = data / 1000000 % 10;
  data_1[7] = data / 10000000 % 10;
  data_1[8] = data / 100000000 % 10;
  data_1[9] = data / 1000000000;

  mylcd->hlcd->LCDChar(data_1[9] + 0x30);
  mylcd->hlcd->LCDChar(',');
  mylcd->hlcd->LCDChar(data_1[8] + 0x30);
  mylcd->hlcd->LCDChar(data_1[7] + 0x30);
  mylcd->hlcd->LCDChar(data_1[6] + 0x30);
  mylcd->hlcd->LCDChar(',');
  mylcd->hlcd->LCDChar(data_1[5] + 0x30);
  mylcd->hlcd->LCDChar(data_1[4] + 0x30);
  mylcd->hlcd->LCDChar(data_1[3] + 0x30);
  mylcd->hlcd->LCDChar(',');
  mylcd->hlcd->LCDChar(data_1[2] + 0x30);
  mylcd->hlcd->LCDChar(data_1[1] + 0x30);
  mylcd->hlcd->LCDChar(data_1[0] + 0x30);
}

void ShowB(uint16_t temp1, uint16_t temp3)
{
  uint8_t data_1[5];
  data_1[0] = temp1 / 1 % 10;
  data_1[1] = temp1 / 10 % 10;
  data_1[2] = temp1 / 100 % 10;
  data_1[3] = temp1 / 1000 % 10;
  data_1[4] = temp1 / 10000;

  mylcd->hlcd->LCDGotoXY(0, 7);
  mylcd->hlcd->LCDChar(data_1[4] + 0x30);
  mylcd->hlcd->LCDChar(data_1[3] + 0x30);
  mylcd->hlcd->LCDChar(data_1[2] + 0x30);
  mylcd->hlcd->LCDChar(data_1[1] + 0x30);
  mylcd->hlcd->LCDChar(data_1[0] + 0x30);

  mylcd->hlcd->LCDChar(' ');

  data_1[0] = temp3 / 1 % 10;
  data_1[1] = temp3 / 10 % 10;
  data_1[2] = temp3 / 100 % 10;
  data_1[3] = temp3 / 1000 % 10;
  data_1[4] = temp3 / 10000;

  mylcd->hlcd->LCDChar(data_1[4] + 0x30);
  mylcd->hlcd->LCDChar(data_1[3] + 0x30);
  mylcd->hlcd->LCDChar(data_1[2] + 0x30);
  mylcd->hlcd->LCDChar(data_1[1] + 0x30);
  mylcd->hlcd->LCDChar(data_1[0] + 0x30);
}

void ShowC(uint16_t temp1, uint16_t temp3)
{
  uint8_t data_1[5];
  data_1[0] = temp1 / 1 % 10;
  data_1[1] = temp1 / 10 % 10;
  data_1[2] = temp1 / 100 % 10;
  data_1[3] = temp1 / 1000 % 10;
  data_1[4] = temp1 / 10000;

  mylcd->hlcd->LCDGotoXY(100, 7);
  mylcd->hlcd->LCDChar(data_1[4] + 0x30);
  mylcd->hlcd->LCDChar(data_1[3] + 0x30);
  mylcd->hlcd->LCDChar(data_1[2] + 0x30);
  mylcd->hlcd->LCDChar(data_1[1] + 0x30);
  mylcd->hlcd->LCDChar(data_1[0] + 0x30);

  mylcd->hlcd->LCDChar(' ');

  data_1[0] = temp3 / 1 % 10;
  data_1[1] = temp3 / 10 % 10;
  data_1[2] = temp3 / 100 % 10;
  data_1[3] = temp3 / 1000 % 10;
  data_1[4] = temp3 / 10000;

  mylcd->hlcd->LCDChar(data_1[4] + 0x30);
  mylcd->hlcd->LCDChar(data_1[3] + 0x30);
  mylcd->hlcd->LCDChar(data_1[2] + 0x30);
  mylcd->hlcd->LCDChar(data_1[1] + 0x30);
  mylcd->hlcd->LCDChar(data_1[0] + 0x30);
}

#define VDDA_APPLI ((uint32_t)3300)

void TaskShow(void *data)
{
  uint8_t data_1[10];
  for (;;)
  {
    KEY temp = io->get();
    if (temp == KEY_A)
    {
      ALL_L();
      changeOut(true);
      osDelay(1000);

      adc->startADC1();
      uint16_t temp1 = find(AD1_DMA, 2048);
      uint16_t temp2 = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, temp1, LL_ADC_RESOLUTION_12B) + 400;
      float Uo0 = (float)temp2 / 1000;

      RIN_MCU_H();

      ShowB(temp1, temp2);

      osDelay(1000);

      adc->startADC1();
      temp1 = find(AD1_DMA, 2048);
      temp2 = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, temp1, LL_ADC_RESOLUTION_12B) + 400;
      float Uo1 = (float)temp2 / 1000;

      changeOut(out);
      ALL_L();

      ShowC(temp1, temp2);

      float Rin = Uo1 * 5.1 / (Uo0 - Uo1);

      temp2 = Rin * 1000;
      data_1[0] = temp2 / 1 % 10;
      data_1[1] = temp2 / 10 % 10;
      data_1[2] = temp2 / 100 % 10;
      data_1[3] = temp2 / 1000 % 10;
      data_1[4] = temp2 / 10000;

      mylcd->hlcd->LCDGotoXY(100, 1);
      mylcd->hlcd->LCDChar(data_1[4] + 0x30);
      mylcd->hlcd->LCDChar(data_1[3] + 0x30);
      mylcd->hlcd->LCDChar('.');
      mylcd->hlcd->LCDChar(data_1[2] + 0x30);
      mylcd->hlcd->LCDChar(data_1[1] + 0x30);
      mylcd->hlcd->LCDChar(data_1[0] + 0x30);
    }
    else if (temp == KEY_B)
    {
      ALL_L();
      changeOut(true);
      osDelay(1000);

      adc->startADC1();
      uint16_t temp1 = find(AD1_DMA, 2048);
      uint16_t temp2 = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, temp1, LL_ADC_RESOLUTION_12B) + 400;
      float Uo0 = ((float)temp2 / 1000);

      OUT_C_H();

      ShowB(temp1, temp2);

      osDelay(1000);

      adc->startADC1();
      temp1 = find(AD1_DMA, 2048);
      temp2 = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, temp1, LL_ADC_RESOLUTION_12B) + 400;
      float Uo2 = ((float)temp2 / 1000);

      ShowC(temp1, temp2);

      ALL_L();

      float Rout = 2 * (Uo0 / Uo2 - 1);

      temp2 = Rout * 1000;
      data_1[0] = temp2 / 1 % 10;
      data_1[1] = temp2 / 10 % 10;
      data_1[2] = temp2 / 100 % 10;
      data_1[3] = temp2 / 1000 % 10;
      data_1[4] = temp2 / 10000;

      mylcd->hlcd->LCDGotoXY(100, 2);
      mylcd->hlcd->LCDChar(data_1[4] + 0x30);
      mylcd->hlcd->LCDChar(data_1[3] + 0x30);
      mylcd->hlcd->LCDChar('.');
      mylcd->hlcd->LCDChar(data_1[2] + 0x30);
      mylcd->hlcd->LCDChar(data_1[1] + 0x30);
      mylcd->hlcd->LCDChar(data_1[0] + 0x30);

      changeOut(out);
    }
    else if (temp == KEY_C)
    {
      ALL_L();
      changeOut(true);
      osDelay(1000);

      adc->startADC1();
      uint16_t temp1 = find(AD1_DMA, 2048);
      uint16_t temp2 = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, temp1, LL_ADC_RESOLUTION_12B) + 400;
      float Uo0 = ((float)temp2 / 1000);

      ShowB(temp1, temp2);
      ShowC(0, 0);

      float Au = Uo0 / 0.02;

      temp2 = Au;
      data_1[0] = temp2 / 1 % 10;
      data_1[1] = temp2 / 10 % 10;
      data_1[2] = temp2 / 100 % 10;
      data_1[3] = temp2 / 1000 % 10;
      data_1[4] = temp2 / 10000;

      mylcd->hlcd->LCDGotoXY(40, 5);
      mylcd->hlcd->LCDChar(data_1[4] + 0x30);
      mylcd->hlcd->LCDChar(data_1[3] + 0x30);
      mylcd->hlcd->LCDChar(data_1[2] + 0x30);
      mylcd->hlcd->LCDChar(data_1[1] + 0x30);
      mylcd->hlcd->LCDChar(data_1[0] + 0x30);

      changeOut(out);
    }
    else if (temp == KEY_D)
    {
      changeOut(true);
      ALL_L();
      uint32_t start = 10;
      float max = 0;
      uint32_t f_H;
      uint32_t f_L;
      uint8_t step = 0;
      for (;;)
      {
        dds->AD9833_SetFrequencyQuick(start, AD9833_OUT_SINUS);
        mylcd->hlcd->LCDGotoXY(80, 0);
        ShowA(start);
        osDelay(200);
        temp = io->get();
        if (temp == KEY_D)
        {
          dds->AD9833_SetFrequencyQuick(now_set, AD9833_OUT_SINUS);
          changeOut(out);
          break;
        }
        adc->startADC1();
        uint16_t temp1 = find(AD1_DMA, 2048);
        uint16_t temp2 = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, temp1, LL_ADC_RESOLUTION_12B) + 400;
        float Uo0 = (float)temp2 / 1000;
        if (step == 0)
        {
          if (Uo0 > max)
          {
            max = Uo0;
          }
          if (start < 300)
          {
            start += 10;
          }
          else if (start >= 300 && start < 1000)
          {
            start += 100;
          }
          else if (start > 200000)
          {
            start += 100000;
          }
          else
          {
            start += 1000;
          }
          if (max != Uo0)
          {
            if (Uo0 < max * 0.707)
            {
              f_H = start;
              step = 1;
              start = 10;
            }
          }
        }
        else if (step == 1)
        {
          if (Uo0 > max * 0.707)
          {
            f_L = start;
            step = 2;
            break;
          }
          if (start < 300)
          {
            start += 10;
          }
          else
          {
            start += 100;
          }
        }
        ShowB(temp1, temp2);
      }
      if (step == 2)
      {
        mylcd->hlcd->LCDGotoXY(40, 3);
        ShowA(f_L);
        mylcd->hlcd->LCDGotoXY(40, 4);
        ShowA(f_H);
      }
      else
      {
        mylcd->hlcd->LCDGotoXY(40, 3);
        ShowA(0);
        mylcd->hlcd->LCDGotoXY(40, 4);
        ShowA(0);
      }
    }
    else if (temp == KEY_N)
    {
      edit = true;
      set_pos = 0;
      set_temp[0] =
          set_temp[1] =
              set_temp[2] =
                  set_temp[3] =
                      set_temp[4] =
                          set_temp[5] =
                              set_temp[6] =
                                  set_temp[7] =
                                      set_temp[8] =
                                          set_temp[9] = 0xF;
      mylcd->hlcd->LCDGotoXY(70, 0);
      mylcd->hlcd->LCDChar('>');
    }
    else if (temp == KEY_M)
    {
      out = !out;
      changeOut(out);
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
    else if (!edit)
    {
      if (temp == KEY_0)
      {
        adc->startADC1();
        uint16_t temp1 = find(AD1_DMA, 2048);
        uint16_t temp2 = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, temp1, LL_ADC_RESOLUTION_12B) + 300;

        ShowB(temp1, temp2);
      }
    }

    if (set_pos == 10)
    {
      set_pos = 0;
      edit = false;
      mylcd->hlcd->LCDGotoXY(70, 0);
      mylcd->hlcd->LCDChar(' ');
      uint32_t set_ =
          set_temp[0] * 1000000000 +
          set_temp[1] * 100000000 +
          set_temp[2] * 10000000 +
          set_temp[3] * 1000000 +
          set_temp[4] * 100000 +
          set_temp[5] * 10000 +
          set_temp[6] * 1000 +
          set_temp[7] * 100 +
          set_temp[8] * 10 +
          set_temp[9] * 1;
      mylcd->hlcd->LCDGotoXY(0, 7);
      if (set_ > 10000000000)
      {
        mylcd->hlcd->LCDString(setfail);
      }
      else
      {
        now_set = set_;
        mylcd->hlcd->LCDString(setdone);
        if (out)
        {
          dds->AD9833_SetFrequencyQuick(now_set, AD9833_OUT_SINUS);
        }
      }
    }

    if (!edit)
    {
      mylcd->hlcd->LCDGotoXY(80, 0);
      ShowA(now_set);
    }
    else
    {
      mylcd->hlcd->LCDGotoXY(80, 0);

      mylcd->hlcd->LCDChar(set_temp[0] + 0x30);
      mylcd->hlcd->LCDChar(',');
      mylcd->hlcd->LCDChar(set_temp[1] + 0x30);
      mylcd->hlcd->LCDChar(set_temp[2] + 0x30);
      mylcd->hlcd->LCDChar(set_temp[3] + 0x30);
      mylcd->hlcd->LCDChar(',');
      mylcd->hlcd->LCDChar(set_temp[4] + 0x30);
      mylcd->hlcd->LCDChar(set_temp[5] + 0x30);
      mylcd->hlcd->LCDChar(set_temp[6] + 0x30);
      mylcd->hlcd->LCDChar(',');
      mylcd->hlcd->LCDChar(set_temp[7] + 0x30);
      mylcd->hlcd->LCDChar(set_temp[8] + 0x30);
      mylcd->hlcd->LCDChar(set_temp[9] + 0x30);
    }

    osDelay(100);
  }
}

void TaskInput(void *argument)
{
  io = new Input();
  mylcd = new LCD();
  mylcd->initShow();
  adc = new ADCs();
  dds = new AD9833();
  dds->AD9833_Init();

  ALL_L();

  //   uint8_t data = 1;
  //   for (;;)
  //   {
  //     dds->AD9833_SetFrequencyQuick((1000 * data++), AD9833_OUT_SINUS);
  //     LL_mDelay(500);
  //   }

  osThreadNew(TaskShow, NULL, &task_input);
  for (;;)
  {
    io->scan();
    osDelay(10);
  }
}
