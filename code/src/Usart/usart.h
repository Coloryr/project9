#ifndef USART_h
#define USART_h

#include <Arduino.h>
#include "LL/stm32yyxx_ll.h"

#define MAX_BUFF_LEN 512
extern uint8_t dma_buff[MAX_BUFF_LEN];  //DMA数据缓冲

class usart
{
private:
    uint32_t recv_len = 0;                 //接收数据长度
public:
    usart();
};

#endif
