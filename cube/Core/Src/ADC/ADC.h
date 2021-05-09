#ifndef ADC_h
#define ADC_h

#include "main.h"

extern uint16_t AD1_DMA[2048];
extern uint16_t AD3_DMA[2048];

#define BUFF_SIZE 2048

class ADCs
{
private:
public:
    ADCs();
    void startADC1();
    void startADC3();
};

extern class ADCs *adc;

#endif
