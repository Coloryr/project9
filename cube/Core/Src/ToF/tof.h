#ifndef ToF_h
#define ToF_h

#include "main.h"

#define tof1 120
#define tof2 160

#define tof_reg 0x04

class tof
{
private:
    I2C_TypeDef *_iic;
    uint16_t dis;
    uint8_t buff[2];

public:
    tof(I2C_TypeDef *iic);
    void read();
    uint16_t get();
};

extern class tof *tof_1;
extern class tof *tof_2;

#endif
