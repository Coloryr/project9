#include "YX65491.h"
#include "cmsis_os.h"
#include "../LCD/LCD.h"

YX65491 *xyz;

#define BUFF_SIZE 512
uint8_t Usart2_RxBuff[BUFF_SIZE];
uint8_t Usart2_TxBuff[BUFF_SIZE];

void USART_DMA_CONFIG(void)
{
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_6, (uint32_t)(&USART2->DR));
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_6, (uint32_t)Usart2_RxBuff);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, BUFF_SIZE);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_6);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);
    LL_USART_EnableDMAReq_RX(USART2);
    LL_USART_EnableIT_IDLE(USART2);
}

YX65491::YX65491()
{
}

void YX65491::init()
{
    USART_DMA_CONFIG();
    LL_USART_TransmitData8(USART2, 0XA5);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0X55);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0XF0); //初始化GY25Z,输出陀螺和欧拉角
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0XEA);
    osDelay(100);
}

void YX65491::read()
{
    //A55601FC
    LL_USART_TransmitData8(USART2, 0XA5);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0X56);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0X01);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0XFC);
    osDelay(100);
    uint16_t cnt = LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_6);

    if (cnt != 0)
    {
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_6);
        LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, BUFF_SIZE);
        LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);
        LL_USART_ClearFlag_IDLE(USART2);
        if (Usart2_RxBuff[0] == 0x5A && Usart2_RxBuff[1] == 0x5A)
        {
            gyro = Usart2_RxBuff[4] << 8 | Usart2_RxBuff[5];
            // if (gyro > 180)
            // {
            //     gyro = -(180 - (xyz->gyro - 475));
            // }
        }
    }
}

void YX65491::reset()
{
    LL_USART_TransmitData8(USART2, 0XA5);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0X57);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0X01);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0XFD);
    osDelay(100);
    LL_USART_TransmitData8(USART2, 0XA5);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0X5A);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0X01);
    osDelay(1);
    LL_USART_TransmitData8(USART2, 0X00);
    osDelay(100);
}
