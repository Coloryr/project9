#include "tof.h"
#include "iic.h"

tof *tof_1;
tof *tof_2;

uint8_t I2C_HW_Read(uint8_t Addr, uint8_t Reg)
{
    uint8_t Value = 0x00;
    /* 1.保证I2C外设不在使用中. */
    while (LL_I2C_IsActiveFlag_BUSY(I2C1))
    {
    }
    /* 2.发送START信号 */
    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
    LL_I2C_GenerateStartCondition(I2C1);
    while (!LL_I2C_IsActiveFlag_SB(I2C1))
    {
    }
    /* 2.写器件地址 */
    LL_I2C_TransmitData8(I2C1, Addr);
    while (!LL_I2C_IsActiveFlag_ADDR(I2C1))
    {
    }
    LL_I2C_ClearFlag_ADDR(I2C1);
    /* 3.地址位已经置位,通常TXE也会完成,为了谨慎,再查一下. */
    while (!LL_I2C_IsActiveFlag_TXE(I2C1))
    {
    }
    /* 4.发送器件寄存器地址. */
    LL_I2C_TransmitData8(I2C1, Reg);
    while (!LL_I2C_IsActiveFlag_TXE(I2C1))
    {
    }
    /* 5.提供RESTART信号. */
    LL_I2C_GenerateStopCondition(I2C1);
    LL_I2C_GenerateStartCondition(I2C1);
    while (!LL_I2C_IsActiveFlag_SB(I2C1))
    {
    }
    /* 6.重新发送地址,并附带读标记. */
    LL_I2C_TransmitData8(I2C1, Addr | 0x01);
    while (!LL_I2C_IsActiveFlag_ADDR(I2C1))
    {
    }
    /* 7.标记读完就STOP. */
    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
    LL_I2C_ClearFlag_ADDR(I2C1);

    LL_I2C_GenerateStopCondition(I2C1);
    while (!LL_I2C_IsActiveFlag_RXNE(I2C1))
    {
    }
    /* 8.数据已读取. */
    Value = LL_I2C_ReceiveData8(I2C1);
    return Value;
}

tof::tof(I2C_TypeDef *iic)
{
    _iic = iic;

    LL_I2C_InitTypeDef I2C_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    /**I2C1 GPIO Configuration
      PB6   ------> I2C1_SCL
      PB7   ------> I2C1_SDA
      */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    RCC->APB1RSTR |= (RCC_APB1RSTR_I2C1RST);
	RCC->APB1RSTR &= ~(RCC_APB1RSTR_I2C1RST);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
	LL_I2C_Disable(I2C1);
	LL_RCC_ClocksTypeDef rcc_clocks;
	LL_RCC_GetSystemClocksFreq(&rcc_clocks);
	LL_I2C_ConfigSpeed(I2C1, rcc_clocks.PCLK1_Frequency, 100000, LL_I2C_DUTYCYCLE_2);
	LL_I2C_Enable(I2C1);
	dis = 0;
}

void tof::read()
{
    uint8_t a = I2C_HW_Read(tof1, 0x04);
    uint8_t b = I2C_HW_Read(tof1, 0x05);
    dis = a << 8 | b;
}

uint16_t tof::get()
{
    return dis;
}
