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

/* public variables */
ringBuffer ADCData;

/* Private function prototypes */
void Enable_GPIOs(void);
void delay(uint32_t time);

int16_t average = 0;

int main(void)
{

	ringbuffer_init(&ADCData);

    RCC_Config();
    Enable_GPIOs();
    GPIO_ResetBits(GPIOA, GARAGE_BUTTON);
    //GPIO_SetBits(GPIOA, GARAGE_BUTTON);
    GPIO_SetBits(GPIOA, COMMAND_MODE);
    //GPIO_SetBits(GPIOA, GPIO_Pin_5);
    ADC1_CH1_Config();
    TIM2_Config();
    NVIC_Config();
    USART3_Config();

    int16_t data = 0;
    float32_t results = 0.0;
    int16_t count = 0;
    uint16_t USART_data = 0;
    uint32_t packed_data = 0;
    uint16_t open = 0;
    uint16_t on = 0;

	while(1) {
		/*
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

		if (count > 10000) {
		//	USART_Send(68);
			count = 0;
		}

		while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET) {
			USART_data = USART_Receive();
			packed_data = (packed_data << 8) | USART_data;
			if (packed_data == 0x4F50454E) {  // packed_data == "OPEN"
				packed_data = 0;
				open = 1;
			}
		}
		count++;

		if (open == 1) {
			open = 0;
			if (on == 0) {
				GPIO_SetBits(GPIOA, GARAGE_BUTTON);
				on = 1;
			} else {
			//delay(100000);
				GPIO_ResetBits(GPIOA, GARAGE_BUTTON);
				on = 0;
			}
		}

	}
}

void delay(uint32_t time) {
	uint32_t i;
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




