/*
 * tim.c
 *
 *  Created on: Nov 13, 2013
 *      Author: rick
 */

#include "tim.h"

#define  PWMDIV	24000000
#define MCLK GPIO_Pin_7

// Set timer2 to trigger at 50KHz
void TIM2_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* Time base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	//TIM_TimeBaseStructure.TIM_Period = 10 - 1;
	//TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)(84 - 1);
	TIM_TimeBaseStructure.TIM_Period = (84000000 / 40000) - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* TIM2 TRGO selection */
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update); // ADC_ExternalTrigConv_T2_TRGO

	// Enabled for clock check
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	// Allow TIM2 to trigger DMA
	//TIM_DMAcmd(TIM2, TIM_DMA_Update, ENABLE);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

uint8_t On = 1;
uint16_t bufferIndex = 0;
uint8_t halfFlag = 0; // buffer is half full
//int16_t ADCConvertedValues[BUFFERSIZE];
int32_t shiftedFilter = -10000;
uint16_t lastSample = 0;

//extern ringBuffer ADCData;

#define ALPHA 0.1
#define INV_ALPHA 1-ALPHA

void TIM2_IRQHandler(void) {

    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    	int32_t shiftedFCL;
    	uint16_t sample;
    	int16_t filtered_value = 0;

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        //if (On) {
        //	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
        //	On = 0;
        //}
        //else {
        //	GPIO_SetBits(GPIOA, GPIO_Pin_8);
        //	On = 1;
        //}

        ADC_SoftwareStartConv(ADC1);

        //while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
        sample = ADC_GetConversionValue(ADC1);
        //ringbuffer_put(&ADCData, sample);

        /* Filter out DC component */
        shiftedFCL = shiftedFilter + (int32_t)((sample - lastSample) << 5);
        shiftedFilter = shiftedFCL - (shiftedFCL >> 5);
        filtered_value = (shiftedFilter + 16) >> 5;
        //ringbuffer_put(&ADCData, filtered_value);
        lastSample = sample;

    }
}
