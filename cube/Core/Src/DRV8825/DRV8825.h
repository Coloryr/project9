#ifndef DRV8825_h
#define DRV8825_h

#include "main.h"

#define DRV_Enable LL_GPIO_PIN_0
#define DRV_Step LL_GPIO_PIN_8
#define DRV_Dir LL_GPIO_PIN_9
#define DRV_Res LL_GPIO_PIN_4
#define DRV_Sleep LL_GPIO_PIN_5

#define DRV_M0 LL_GPIO_PIN_1
#define DRV_M1 LL_GPIO_PIN_2
#define DRV_M2 LL_GPIO_PIN_3

class DRV8825
{
private:
public:
    DRV8825();
    void run();
    void runFast();
    void set(bool dir);
};

extern class DRV8825 *drv;

#endif
