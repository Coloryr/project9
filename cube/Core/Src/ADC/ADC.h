#ifndef ADC_h
#define ADC_h

#include "main.h"

#define BUFF_SIZE 2048

class ADCs
{
private:
public:
    uint16_t adc1[BUFF_SIZE];
    uint16_t adc3[BUFF_SIZE];
    ADCs();
    void startADC1();
    void startADC3();
};

extern class ADCs *adc;

#endif