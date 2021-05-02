#ifndef YX65491_h
#define YX65491_h

#include <Arduino.h>

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

#endif
