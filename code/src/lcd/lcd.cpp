#include <Arduino.h>
#include "lcd.h"

unsigned char string1[] = "Distance  :";
unsigned char string2[] = "Now Pos:";
unsigned char string3[] = "gyro:      ,     ,     ";

lcd::lcd()
{
    hlcd = new ERM19264_UC1609_T(CD, RST, CS, PA5, PA7);
    hlcd = new ERM19264_UC1609_T(CD, RST, CS);
    hlcd->LCDbegin();             // initialize the LCD
    hlcd->LCDFillScreen(0x00, 1); // clear screen
    hlcd->LCDrotate(UC1609_ROTATION_NORMAL);
}

void lcd::initShow()
{
    hlcd->LCDGotoXY(0, 0);
    hlcd->LCDString(string1);
    hlcd->LCDGotoXY(64, 0);
    hlcd->LCDChar('1');
    hlcd->LCDGotoXY(0, 1);
    hlcd->LCDString(string1);
    hlcd->LCDGotoXY(64, 1);
    hlcd->LCDChar('2');
    hlcd->LCDGotoXY(0, 2);
    hlcd->LCDString(string2);
    hlcd->LCDGotoXY(0, 3);
    hlcd->LCDString(string3);
}