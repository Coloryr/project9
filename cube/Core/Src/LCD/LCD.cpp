#include "main.h"
#include "LCD.h"

LCD *mylcd;

uint8_t string1[] = "Output frequency:";
uint8_t string2[] = "Input resistance:";
uint8_t string3[] = "Output resistance";

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
    hlcd->LCDGotoXY(0, 1);
    hlcd->LCDString(string2);
    hlcd->LCDGotoXY(0, 2);
    hlcd->LCDString(string3);
}
