#ifndef YX65491_h
#define YX65491_h

#include "main.h"

extern uint8_t Usart2_RxBuff[];
extern uint8_t Usart2_TxBuff[];

class YX65491
{
private:

public:
    YX65491();
    int YPR[3];
    int32_t gyro[3] = {0};
    void init();
    void read();
};

extern class YX65491 *xyz;

#endif
