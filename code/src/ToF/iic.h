#ifndef IIC_h
#define IIC_h

#include <Arduino.h>
#include "LL/stm32yyxx_ll.h"

class iic
{
private:
    I2C_TypeDef *_iic;
    void I2C_HW_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);

public:
    iic(I2C_TypeDef *iic);
    void init(bool Remap);

};

#endif
