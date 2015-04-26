/*
 * adc.h
 *
 *  Created on: Nov 8, 2013
 *      Author: rick
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx_adc.h"
//#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dma.h"

#define ADC1_DR_ADDRESS    ((uint32_t)0x4001204C)



void ADC1_CH1_Config(void);
void ADC1_CH1_DMA2_Config(void);

#endif /* ADC_H_ */
