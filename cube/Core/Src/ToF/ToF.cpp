#include "tof.h"
#include "iic.h"

tof *tof_1;
tof *tof_2;

tof::tof(I2C_TypeDef *iic)
{
    _iic = iic;
    LL_I2C_Enable(iic);
}

void tof::read()
{
	I2C_READ_BYTES(tof1, 0x04, buff, 2);
    dis = buff[0] << 8 | buff[1];
}

uint16_t tof::get()
{
    return dis;
}
