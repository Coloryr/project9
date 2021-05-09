#include "main.h"

#define FSYNC LL_GPIO_PIN_12

#define FSYNC_SetHigh LL_GPIO_SetOutputPin(GPIOB, FSYNC);
#define FSYNC_SetLOW LL_GPIO_ResetOutputPin(GPIOB, FSYNC);

#define AD9833_REG_CMD		(0 << 14)
#define AD9833_REG_FREQ0	(1 << 14)
#define AD9833_REG_FREQ1	(2 << 14)
#define AD9833_REG_PHASE0	(6 << 13)
#define AD9833_REG_PHASE1	(7 << 13)

/* Command Control Bits */

#define AD9833_B28			(1 << 13)
#define AD9833_HLB			(1 << 12)
#define AD9833_FSEL0		(0 << 11)
#define AD9833_FSEL1		(1 << 11)
#define AD9833_PSEL0		(0 << 10)
#define AD9833_PSEL1		(1 << 10)
#define AD9833_PIN_SW		(1 << 9)
#define AD9833_RESET		(1 << 8)
#define AD9833_SLEEP1		(1 << 7)
#define AD9833_SLEEP12		(1 << 6)
#define AD9833_OPBITEN		(1 << 5)
#define AD9833_SIGN_PIB		(1 << 4)
#define AD9833_DIV2			(1 << 3)
#define AD9833_MODE			(1 << 1)

#define AD9833_OUT_SINUS	((0 << 5) | (0 << 1) | (0 << 3))
#define AD9833_OUT_TRIANGLE	((0 << 5) | (1 << 1) | (0 << 3))
#define AD9833_OUT_MSB		((1 << 5) | (0 << 1) | (1 << 3))
#define AD9833_OUT_MSB2		((1 << 5) | (0 << 1) | (0 << 3))

class AD9833
{
private:
    void AD9833_SetRegisterValue(uint16_t regValue);

public:
    AD9833();
    void AD9833_SetFrequency(uint16_t reg, uint32_t fout);
    void AD9833_SetFrequencyQuick(uint32_t fout, uint16_t type);
    void AD9833_Init();
    void AD9833_Setup(uint16_t freq, uint16_t phase, uint16_t type);
};

extern class AD9833 *dds;
