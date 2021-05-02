#include <Arduino.h>
#include "YX65491.h"
#include "LL/stm32yyxx_ll.h"
#include "main.h"
#include "Usart/usart.h"

YX65491::YX65491()
{
}

void YX65491::init()
{
    LL_USART_TransmitData8(USART2, 0XA5);
    LL_USART_TransmitData8(USART2, 0X55);
    LL_USART_TransmitData8(USART2, 0X12); //初始化GY25Z,输出陀螺和欧拉角
    LL_USART_TransmitData8(USART2, 0X0C);
    delay(100);

    LL_USART_TransmitData8(USART2, 0XA5);
    LL_USART_TransmitData8(USART2, 0X56); //初始化GY25Z,连续输出模式
    LL_USART_TransmitData8(USART2, 0X02); //初始化GY25Z,连续输出模式
    LL_USART_TransmitData8(USART2, 0XFD);
    delay(100);
}

void YX65491::read()
{
    mylcd->hlcd->LCDGotoXY(0, 5);
    for (uint8_t a = 0; a < 17; a++)
    {
        mylcd->hlcd->LCDChar(dma_buff[a]);
    }
    if (dma_buff[0] == 0x5A && dma_buff[1] == 0x5A) //检查帧头，帧尾
    {
        gyro[0] = (dma_buff[4] << 8 | dma_buff[5]); //合成数据，去掉小数点后2位
        gyro[1] = (dma_buff[6] << 8 | dma_buff[7]);
        gyro[2] = (dma_buff[8] << 8 | dma_buff[9]);

        YPR[0] = (dma_buff[10] << 8 | dma_buff[11]) / 100; //合成数据，去掉小数点后2位
        YPR[1] = (dma_buff[12] << 8 | dma_buff[13]) / 100;
        YPR[2] = (dma_buff[14] << 8 | dma_buff[15]) / 100;
    }
}
