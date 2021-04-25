#ifndef ToF_h
#define ToF_h

#include <Arduino.h>

#define tof_scl PB6
#define tof_sda PB7

#define tof1 0x30
#define tof2 0x30

class tof
{
private:
    uint32_t scl;
    uint32_t sda;
    void I2C_HW_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
    
public:
    tof(uint32_t scl, uint32_t sda);
    void init();
    bool check();
};

#endif
