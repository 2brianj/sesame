/*
 * rcc.c
 *
 *  Created on: Nov 18, 2013
 *      Author: rick
 */


#include "rcc.h"

void RCC_Config(void) {

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_USART3 |
            RCC_APB1Periph_I2C1 | RCC_APB1Periph_SPI3 | RCC_APB1Periph_TIM3, ENABLE);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_DMA2 |
            RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);

    // I2S3ext
    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // Enable I2S
    RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S);
    RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY);
    RCC_PLLI2SCmd(ENABLE);

    //RCC_I2SCLKConfig(RCC_I2S2CLKSource_PLLI2S);
    //RCC_GetFlagStatus(RCC_FLAG_PLLI2SRDY);
    //RCC_PLLI2SCmd(ENABLE);
    // Enable clock for GPIOs

    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE);

    // Enable clock for SPI, I2C
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1 | RCC_APB1Periph_SPI3, ENABLE);



    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* Enable ADC1 and GPIO clocks *******************************************/
    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

}
