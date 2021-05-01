#ifndef INPUT_h
#define INPUT_h

#include <Arduino.h>

enum KEY
{
    KEY_NULL,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_N,
    KEY_M
};

class Input
{
private:
    KEY now;
    KEY out;

public:
    Input();
    void scan();
    KEY get();
};

#endif
