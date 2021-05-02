#ifndef LCD_h
#define LCD_h

#include "ERM19264_UC1609_T.h"

class LCD
{
private:
public:
    ERM19264_UC1609_T *hlcd;
    LCD();
    void initShow();
};

extern class LCD *mylcd;

#endif
