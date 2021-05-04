#include "main.h"
#include "LCD.h"

LCD *mylcd;

unsigned char string1[] = "Distance  :";
unsigned char string2[] = "Now Pos:";
unsigned char string3[] = "gyro:";
unsigned char string4[] = "set:";

LCD::LCD()
{
	LL_SPI_Enable(SPI1);
    hlcd = new ERM19264_UC1609_T();
    hlcd->LCDbegin();             // initialize the LCD
    hlcd->LCDFillScreen(0x00, 1); // clear screen
    hlcd->LCDrotate(UC1609_ROTATION_NORMAL);
}

void LCD::initShow()
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
    hlcd->LCDGotoXY(0, 6);
    hlcd->LCDString(string4);
}
