/*
 * tim.h
 *
 *  Created on: Nov 13, 2013
 *      Author: rick
 */

#ifndef TIM_H_
#define TIM_H_


#include "stm32f4xx_tim.h"
#include "adc.h"
#include "usart.h"
#include "goertzel.h"

#define SAMPLERATE 20000

void TIM2_Config(void);

#endif /* TIM_H_ */
