/*
 * usart.h
 *
 *  Created on: Nov 8, 2013
 *      Author: rick
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"

#define USART USART3

void USART3_Config(void);
void USART_Send(uint16_t data);
uint16_t USART_Receive();

#endif /* USART_H_ */
