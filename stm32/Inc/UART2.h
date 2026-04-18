/*
 * UART2.h
 *
 *  Created on: Mar 15, 2026
 *      Author: dontknow
 */

#ifndef INC_UART2_H_
#define INC_UART2_H_

void UART_Init(void);
void UART_SendChar(char c);
void UART_SendString(char *s);

#endif /* INC_UART2_H_ */
