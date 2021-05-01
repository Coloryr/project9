#ifndef DRV8825_h
#define DRV8825_h

#include <Arduino.h>

#define DRV_Enable PB0
#define DRV_Step PB8
#define DRV_Dir PB9
#define DRV_Res PB4
#define DRV_Sleep PB5

#define DRV_M0 PB1
#define DRV_M1 PB2
#define DRV_M2 PB3

class DRV8825
{
private:
public:
    DRV8825();
    void run();
};

#endif
