#include "YX65491.h"
#include "cmsis_os.h"
#include "../LCD/LCD.h"

YX65491 *xyz;

#define BUFF_SIZE 512
uint8_t Usart2_RxBuff[BUFF_SIZE];
uint8_t Usart2_TxBuff[BUFF_SIZE];

void USART_DMA_CONFIG(void)
{
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_6, (uint32_t)(&USART1->DR)); // LL_USART_DMA_GetRegAddr(USART1->DR));
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_6, (uint32_t)BUFF_SIZE);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, BUFF_SIZE);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_6);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);
    LL_USART_EnableDMAReq_RX(USART2);
    LL_USART_EnableIT_IDLE(USART2);
}

void USART_RxIdleCallback(void)
{
    uint8_t cnt;
    if (LL_USART_IsActiveFlag_IDLE(USART2))
    {
        LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_6);
        cnt = LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_6);
        LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, BUFF_SIZE);
        LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);
        LL_USART_ClearFlag_IDLE(USART2);
    }
}

YX65491::YX65491()
{
}

void YX65491::init()
{
    LL_USART_TransmitData8(USART2, 0XA5);
    LL_USART_TransmitData8(USART2, 0X55);
    LL_USART_TransmitData8(USART2, 0X12); //初始化GY25Z,输出陀螺和欧拉角
    LL_USART_TransmitData8(USART2, 0X0C);
    osDelay(100);

    LL_USART_TransmitData8(USART2, 0XA5);
    LL_USART_TransmitData8(USART2, 0X56); //初始化GY25Z,连续输出模式
    LL_USART_TransmitData8(USART2, 0X02); //初始化GY25Z,连续输出模式
    LL_USART_TransmitData8(USART2, 0XFD);
    osDelay(100);
}

void YX65491::read()
{
    mylcd->hlcd->LCDGotoXY(0, 5);
    for (uint8_t a = 0; a < 17; a++)
    {
        mylcd->hlcd->LCDChar(Usart2_RxBuff[a]);
    }
    if (Usart2_RxBuff[0] == 0x5A && Usart2_RxBuff[1] == 0x5A) //检查帧头，帧尾
    {
        gyro[0] = (Usart2_RxBuff[4] << 8 | Usart2_RxBuff[5]); //合成数据，去掉小数点后2位
        gyro[1] = (Usart2_RxBuff[6] << 8 | Usart2_RxBuff[7]);
        gyro[2] = (Usart2_RxBuff[8] << 8 | Usart2_RxBuff[9]);

        YPR[0] = (Usart2_RxBuff[10] << 8 | Usart2_RxBuff[11]) / 100; //合成数据，去掉小数点后2位
        YPR[1] = (Usart2_RxBuff[12] << 8 | Usart2_RxBuff[13]) / 100;
        YPR[2] = (Usart2_RxBuff[14] << 8 | Usart2_RxBuff[15]) / 100;
    }
}
