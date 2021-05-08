#include "AD9833.h"
#include <math.h>

#define FCLK 25000000 //设置晶振频率
double RealFreDat = 268435456.0 / FCLK;
AD9833 *dds;

void FSYNC_SetHigh()
{
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);
}
void SCK_SetHigh()
{
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);
}
void DATA_SetHigh()
{
    LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_15);
}
void FSYNC_SetLOW()
{
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
}

AD9833::AD9833()
{
    LL_SPI_Enable(SPI2);
    SCK_SetHigh();
    DATA_SetHigh();
    FSYNC_SetHigh();
    FSYNC_SetLOW();
    AD9833_SPI_Write(AD9833_REG_CMD | AD9833_RESET);
    FSYNC_SetHigh();
}
void AD9833::AD9833_SPI_Write(uint16_t data)
{
    to.u16 = data;
    FSYNC_SetLOW();
    LL_SPI_TransmitData8(SPI2, to.u8[1]);
    while (!LL_SPI_IsActiveFlag_TXE(SPI2))
        ;
    LL_SPI_TransmitData8(SPI2, to.u8[0]);
    while (!LL_SPI_IsActiveFlag_TXE(SPI2))
        ;
    FSYNC_SetHigh();
}

void AD9833::AD9833_SetFrequency(uint16_t reg, float fout)
{
    uint16_t freqHi = reg;
    uint16_t freqLo = reg;
    unsigned long val = RealFreDat * fout; //F寄存器的值
    freqHi |= (val & 0xFFFC000) >> 14;
    freqLo |= (val & 0x3FFF);
    AD9833_SPI_Write(AD9833_B28);
    AD9833_SPI_Write(freqLo);
    AD9833_SPI_Write(freqHi);
}

void AD9833::AD9833_SetFrequencyQuick(float fout, uint16_t type)
{
    AD9833_SetFrequency(AD9833_REG_FREQ0, fout * 1000); // 400 kHz
    AD9833_Setup(AD9833_FSEL0, AD9833_PSEL0, type);
}

void AD9833::AD9833_Setup(uint16_t freq,
                          uint16_t phase,
                          uint16_t type)
{
    uint16_t val = 0;

    val = freq | phase | type;
    AD9833_SPI_Write(val);
}
