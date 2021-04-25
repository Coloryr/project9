#include <Arduino.h>
#include "lcd.h"
#include "ERM19264_UC1609_T.h"

ERM19264_UC1609_T hlcd(CD, RST, CS);
#define VbiasPOT 0x49 //Constrast 00 to FE , 0x49 is default. user adjust

#define delay5 5000
#define delay50ms 50

void Tests()
{
    unsigned char test0_1[] = "No buffer mode 216 chars";
    unsigned char test0_2[] = "(192/7 * 64/8)= 216";

    unsigned char test1_1[] = "This is text only version";
    unsigned char test1_2[] = "123456789012345678901234567";
    unsigned char test1_3[] = "This is page 7";

    // Test 0 clear screen
    hlcd.LCDGotoXY(0, 0);
    hlcd.LCDString(test0_1); // Write a character string
    hlcd.LCDGotoXY(0, 1);
    hlcd.LCDString(test0_2); // Write a character string
    delay(delay5);
    hlcd.LCDFillScreen(0x00, 0); // Clear the screen
    delay(delay50ms);

    // Test 1 String function and goto function
    hlcd.LCDGotoXY(0, 0);    // (Col , page ) Col 0 to 191 , page 0 to 7
    hlcd.LCDString(test1_1); // Write a character string
    hlcd.LCDGotoXY(0, 4);
    hlcd.LCDString(test1_2);
    hlcd.LCDGotoXY(0, 7);
    hlcd.LCDString(test1_3);
    delay(delay5);

    // Test 2 clear page function
    hlcd.LCDGotoXY(0, 7);
    hlcd.LCDFillPage(0x00); // Clear page
    hlcd.LCDGotoXY(0, 6);
    hlcd.LCDFillPage(0x7E); // Write pattern (0111 1110) to a page
    delay(delay5);
    hlcd.LCDFillScreen(0x00, 0); // Clear the screen

    // Test 3 character function
    hlcd.LCDGotoXY(100, 2);
    hlcd.LCDChar('H'); // write single  character
    hlcd.LCDChar('2');
    delay(delay5);
    hlcd.LCDFillScreen(0x00, 0); // Clear the screen

    // Test 4 print ASCII font 0-127 with character function
    // For characters before space(0-0x20) in ASCII table user can comment in UC_FONT_MOD_One in font file (NOTE: this will increase program size)
    hlcd.LCDGotoXY(0, 0);
    uint8_t row = 1;
    unsigned char i = 1;
    for (i = UC1609_ASCII_OFFSET; i < 126; i++)
    {
        if (i % 27 == 0)
            hlcd.LCDGotoXY(0, row++);
        hlcd.LCDChar(i);
        delay(delay50ms);
    }
    delay(delay5);
    hlcd.LCDFillScreen(0x00, 0); // Clear the screen

    // TEST 5 print ASCII font 128-255 with character function
    // For characters after 'z{|}' in ASCII table user can comment in UC_FONT_MOD_TWO in font file
    // (NOTE: this will increase program size)
#ifdef UC_FONT_MOD_TWO
    hlcd.LCDGotoXY(0, 0);
    row = 1;
    unsigned char k = 1;
    for (k = 128; k < 255; k++)
    {
        if (k % 27 == 0)
            hlcd.LCDGotoXY(0, row++);
        hlcd.LCDChar(k);
        delay(delay50ms);
    }
    delay(delay5);
    hlcd.LCDFillScreen(0x00, 0); // Clear the screen
#endif
}

lcd::lcd()
{
    hlcd.LCDbegin(VbiasPOT);     // initialize the LCD
    hlcd.LCDFillScreen(0x00, 0); // clear screen

    Tests();
}
