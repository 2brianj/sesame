/*
 * main.c

 *
 *  Created on: Nov 5, 2013
 *      Author: rick
 */

#include "main.h"

#define LED GPIO_Pin_9
#define GARAGE_BUTTON GPIO_Pin_8
#define COMMAND_MODE GPIO_Pin_4
#define CODE_WORD 0x12345678

/* public variables */
//ringBuffer ADCData;

/* Private function prototypes */
void Enable_GPIOs(void);
void delay(uint32_t time);

int16_t average = 0;

int main(void)
{

	//ringbuffer_init(&ADCData);

    RCC_Config();
    Enable_GPIOs();
    GPIO_ResetBits(GPIOA, GARAGE_BUTTON);
    GPIO_SetBits(GPIOA, COMMAND_MODE);
    //ADC1_CH1_Config();
    //TIM2_Config();
    NVIC_Config();
    USART3_Config();

    //int16_t data = 0;
    //float32_t results = 0.0;
    uint16_t USART_data = 0;
    uint32_t packed_data = 0;
    uint16_t toggle_open = 0;

	while(1) {
		/* Uses goertzel filter to check for 5000Hz signal.. unused currently
		while (!ringbuffer_empty(&ADCData)) {
			data = ringbuffer_get(&ADCData);
			results = tandem_RT_zero_goertzel_filter(data, 50);
		}

		if (results > 0.39) {
			GPIO_SetBits(GPIOA, GARAGE_BUTTON);
			GPIO_ResetBits(GPIOA, LED);
		}
		else {
			GPIO_ResetBits(GPIOA, GARAGE_BUTTON);
			GPIO_SetBits(GPIOA, LED);
		}
		*/


		/* Check for USART receive flag, if set process the data
		 * If data says CODE_WORD, set open to 1 to trigger door.
		 */
		while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET) {
			USART_data = USART_Receive();
			packed_data = (packed_data << 8) | USART_data;
			if (packed_data == CODE_WORD) {
				packed_data = 0;
				toggle_open = 1;
			}
		}

		/* Toggle garage open and close using toggle_open.
		 *
		 */
		if (toggle_open == 1) {
			toggle_open = 0;
			GPIO_SetBits(GPIOA, GARAGE_BUTTON);
			delay(50000);
			GPIO_ResetBits(GPIOA, GARAGE_BUTTON);
		}

	}
}

void delay(uint32_t time) {
	uint32_t i;
	time = time * 100;
	for (i = 0; i < time; i++);
}

void Enable_GPIOs(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = LED | GARAGE_BUTTON | COMMAND_MODE;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}




