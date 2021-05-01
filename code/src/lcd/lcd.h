#ifndef LCD_h
#define LCD_h

#include <Arduino.h>
#include "ERM19264_UC1609_T.h"

#define CD PA1  // GPIO pin number pick any you want
#define RST PA0 // GPIO pin number pick any you want
#define CS PA4  // GPIO pin number pick any you want

class lcd
{
private:
public:
    ERM19264_UC1609_T *hlcd;
    lcd();
    void initShow();
};

#endif
