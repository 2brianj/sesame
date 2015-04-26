/*
 * main.c

 *
 *  Created on: Nov 5, 2013
 *      Author: rick
 */

#include "main.h"

/* ----------------------------------------------------------------------
* Declare Global variables
* ------------------------------------------------------------------- */

/* public variables */
ringBuffer ADCData;

/* Private function prototypes */
void Enable_LED(void);

int16_t average = 0;

int main(void)
{

	ringbuffer_init(&ADCData);

    RCC_Config();
    Enable_LED();
    GPIO_ResetBits(GPIOA, GPIO_Pin_9);
    GPIO_SetBits(GPIOA, GPIO_Pin_9);
    ADC1_CH1_Config();
    TIM2_Config();
    NVIC_Config();

    int16_t data = 0;
    float32_t results = 0.0;

	while(1) {
		while (!ringbuffer_empty(&ADCData)) {
			data = ringbuffer_get(&ADCData);
			results = tandem_RT_zero_goertzel_filter(data, 50);
		}

		if (results > 0.39) {
			GPIO_SetBits(GPIOA, GPIO_Pin_9);
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		}
		else {
			GPIO_ResetBits(GPIOA, GPIO_Pin_9);
			GPIO_SetBits(GPIOA, GPIO_Pin_8);
		}

	}
}

void Enable_LED(void) {
	GPIO_InitTypeDef GPIO_InitStruct;

		/* This enables the peripheral clock to the GPIOD IO module
		 * Every peripheral's clock has to be enabled
		 *
		 * The STM32F4 Discovery's User Manual and the STM32F407VGT6's
		 * datasheet contain the information which peripheral clock has to be used.
		 *
		 * It is also mentioned at the beginning of the peripheral library's
		 * source file, e.g. stm32f4xx_gpio.c
		 */
		//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		/* In this block of instructions all the properties
		 * of the peripheral, the GPIO port in this case,
		 * are filled with actual information and then
		 * given to the Init function which takes care of
		 * the low level stuff (setting the correct bits in the
		 * peripheral's control register)
		 *
		 *
		 * The LEDs on the STM324F Discovery are connected to the
		 * pins PD12 thru PD15
		 */
	    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 		// we want the pins to be an output
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	// this sets the GPIO modules clock speed
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 	// this sets the pin type to push / pull (as opposed to open drain)
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 	// this sets the pullup / pulldown resistors to be inactive
		GPIO_Init(GPIOA, &GPIO_InitStruct); 			// this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.

}




