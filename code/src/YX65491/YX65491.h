#ifndef YX65491_h
#define YX65491_h

#include <Arduino.h>

class YX6549
{
private:
    int YPR[3];
    int32_t gyro[3] = {0};
    unsigned char Re_buf[30];

public:
    YX6549();
    void init();
    void read();
};

#endif
