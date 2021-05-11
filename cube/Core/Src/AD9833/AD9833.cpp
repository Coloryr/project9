#include "AD9833.h"

#define FCLK 25000000 //设置晶振频率
//#define RealFreDat    268435456.0/FCLK//总的公式为 Fout=（Fclk/2的28次方）*28位寄存器的值
double RealFreDat = 268435456.0 / FCLK;
AD9833 *dds;

AD9833::AD9833()
{
    LL_SPI_Enable(SPI2);
    FSYNC_SetHigh
}

void AD9833::AD9833_SetRegisterValue(uint16_t regValue)
{
    uint8_t data[2];

    data[0] = (uint8_t)((regValue & 0xFF00) >> 8);
    data[1] = (uint8_t)((regValue & 0x00FF) >> 0);
    FSYNC_SetLOW

    LL_SPI_TransmitData8(SPI2, data[0]);
    LL_mDelay(1);
    LL_SPI_TransmitData8(SPI2, data[1]);
    LL_mDelay(1);
    FSYNC_SetHigh
}

void AD9833::AD9833_SetFrequency(uint16_t reg, uint32_t fout)
{
    uint16_t freqHi = reg;
    uint16_t freqLo = reg;
    uint32_t val = RealFreDat * fout; //F寄存器的值
    freqHi |= (val & 0xFFFC000) >> 14;
    freqLo |= (val & 0x3FFF);
    AD9833_SetRegisterValue(AD9833_B28);
    AD9833_SetRegisterValue(freqLo);
    AD9833_SetRegisterValue(freqHi);
}

void AD9833::AD9833_SetFrequencyQuick(uint32_t fout, uint16_t type)
{
    AD9833_SetFrequency(AD9833_REG_FREQ0, fout);
    AD9833_Setup(AD9833_FSEL0, AD9833_PSEL0, type);
}
void AD9833::AD9833_Init()
{
    AD9833_SetRegisterValue(AD9833_REG_CMD | AD9833_RESET);
}

void AD9833::AD9833_Setup(uint16_t freq, uint16_t phase, uint16_t type)
{
    uint16_t val = 0;

    val = freq | phase | type;
    AD9833_SetRegisterValue(val);
}
