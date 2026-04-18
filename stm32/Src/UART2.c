/*
 * UART2.c
 *
 *  Created on: Mar 15, 2026
 *      Author: dontknow
 */

#include "stm32f407xx.h"

void UART_Init(void){
	RCC->AHB1ENR |= 1; //enable clock on GPIOA
	//enable usart2 clock
	RCC->APB1ENR |= (1 << 17);

	//delay
	volatile uint32_t dummy;
	dummy = RCC->AHB1ENR;

	//gpio pin configuration
	GPIOA->MODER &= ~(0b1111 << 4); //clear PA2 and PA3 moder
	GPIOA->MODER |= (0b1010 << 4); //PA2 and PA3 on alternate function mode
	GPIOA->AFR[0] &= ~((0b1111 << 8) | (0b1111 << 12));
	GPIOA->AFR[0] |= (7 << 8); //AF7 USART1_TX on PA2
	GPIOA->AFR[0] |= (7 << 12); //AF7 USART1_RX on PA3
	//NOTE: AFR[0]=AFRL, AFR[1] = AFRH

	//usart configuration
	//APB1 clock: 16MHz  9600baud = 16MHz/1666.6667
	//BRR [11:4] -> mantissa/16, BRR[3:0] -> fraction = remainder*16
	//1666/16=104 0.1667*16=+-3
	USART2->BRR = 0x683;
	USART2->CR1 |= (1 << 13) | (1 << 3) | (1 << 2); //usart control -> enable usart, transmitter, receiver
}

void UART_SendChar(char c){
	//USART1_SR[7] "This bit is set by hardware when the content of the TDR register has been transferred into the shift register"
	while((USART2->SR & (1 << 7)) == 0){
		//wait until transmit data register is empty
	}
	USART2->DR = c;
}


void UART_SendString(char *s){;
	while(*s != '\0'){
		UART_SendChar(*s);
		s++;
	}
}
