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
    short gyro;
    void init();
    void read();
    void reset();
};

extern class YX65491 *xyz;

#endif
