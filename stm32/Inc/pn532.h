/*
 * pn532.h
 *
 *  Created on: Apr 9, 2026
 *      Author: dontknow
 */

#ifndef PN532_H_
#define PN532_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f407xx.h"

typedef enum {
	PN532_SPI,
	PN532_I2C,
	PN532_UART,
} PN532_Protocol;

typedef enum {
	PN532_MODE_NORMAL = 0x01,
	PN532_MODE_VIRTUAL_CARD = 0x02,
	PN532_MODE_WIRED_CARD = 0x03
} PN532_SAM_Mode;


//Dit struct dient om de chip de configureren
typedef struct {
	PN532_Protocol protocol;
	PN532_SAM_Mode mode;

	union {
		struct {
			SPI_HandleTypeDef *hspi; //SPI module die men wilt gebruiken

			//Externe GPIO-Pin als Slave Select wegens instabiliteit van eigen NSS
			GPIO_TypeDef *ss_port;
			uint32_t ss_pin;
		} spi;

		struct {
			//Voor latere implementatie
		} i2c;

		struct {
			//Voor latere implementatie
		} uart;

	} interface;

} PN532_Handle ;

uint8_t PN532_Init(PN532_Handle *handle);


/*
PSEUDOCODE

pn532_read(){
	if ...
	pn532_spi_read();

	if ...
	pn532_i2c_read();

	...

}

static pn532_spi_read();

static pn532_i2c_read();

static pn532_uart_read();

static pn532_spi_read();

static pn532_i2c_read();

static pn532_uart_read();

*/





#endif /* PN532_H_ */
