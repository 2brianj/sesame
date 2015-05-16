/*
 * usart.c

 *
 *  Created on: Nov 8, 2013
 *      Author: rick
 */

#include "usart.h"


/*
 * @brief USART3 configuration PB10 - RX, PB11 - TX, PB13 - RTS, PB14 - CTS
 * @param None
 * @retval None
 */
void USART3_Config(void) {
	GPIO_InitTypeDef 	GPIO_InitStructure;
	USART_InitTypeDef 	USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;

	/* Enable USART3 and GPIO clocks *****************************************/

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); // RX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); // TX
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_USART3); // RTS
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_USART3); // CTS

	/* Configure GPIOB: TX pin 10 *********************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART3 ******************************************************/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

	/* USART3 Clock Initialization */
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;

	USART_ClockInit(USART3, &USART_ClockInitStructure);

	/* Enable USART3 */
	USART_Cmd(USART3, ENABLE);

}

/*
 * @brief Send data over USART, wait until USART is ready
 * @param data -- what to send
 * @retval None
 */
void USART_Send(uint16_t data) {
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	USART_SendData(USART3, data);
}

