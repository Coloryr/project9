#include "ADC.h"
#include "cmsis_os2.h"

ADCs *adc;

ADCs::ADCs()
{
    LL_ADC_Enable(ADC1);
    LL_ADC_Enable(ADC3);
    LL_ADC_StartCalibration(ADC1);
    LL_ADC_StartCalibration(ADC3);
    while (LL_ADC_IsCalibrationOnGoing(ADC1) || LL_ADC_IsCalibrationOnGoing(ADC3))
        ;

    LL_mDelay(2); //延时2ms，避免DMA读取数据通道不对
    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
    LL_ADC_REG_SetDMATransfer(ADC3, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 2048);
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&ADC1->DR);
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&adc1);
    LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_5, 2048);
    LL_DMA_SetPeriphAddress(DMA2, LL_DMA_CHANNEL_5, (uint32_t)&ADC3->DR);
    LL_DMA_SetMemoryAddress(DMA2, LL_DMA_CHANNEL_5, (uint32_t)&adc3);
}

void ADCs::startADC1()
{
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 2048);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
    LL_ADC_REG_StartConversionSWStart(ADC1);
    osDelay(200);
    LL_ADC_REG_StopConversionExtTrig(ADC1);
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
}

void ADCs::startADC3()
{
    LL_DMA_SetDataLength(DMA2, LL_DMA_CHANNEL_5, 2048);
    LL_DMA_EnableChannel(DMA2, LL_DMA_CHANNEL_5);
    LL_ADC_REG_StartConversionSWStart(ADC3);
    osDelay(200);
    LL_ADC_REG_StopConversionExtTrig(ADC3);
    LL_DMA_DisableChannel(DMA2, LL_DMA_CHANNEL_5);
}