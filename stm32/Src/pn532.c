/*
 * pn532.c
 *
 *  Created on: Apr 9, 2026
 *      Author: dontknow
 */


#include "pn532.h"

void PN532_Init(PN532_Handle *handle){
	//TODO: compatibiliteit voor software-gestuurde RSTPD_N

	switch(handle->protocol) {

	case PN532_SPI:
		//Chip wakker maken m.b.v. dummy-byte
		PN532_SPI_Wakeup(handle);
		//SAM configuratie
		switch(handle->mode){
		case PN532_MODE_NORMAL:
			uint8_t frame[] = {
					0x01, //Action Byte
					0x00, //Preamble
					0x00, //Start Code
					0xFF, //Start Code
					0x05, //5 bytes in data segment
					0xFB, //Lnegth Checksum: Length + LCS moet gelijk zijn aan 0x00 voor 8 bit (overflow) -> 0xFF - 0x05 + 0x01 = 0xFB
					0xD4, //TFI
					0x14, //Command = SAMConfiguration
					0x01, //Mode = Normal Mode
					0x14, //Timeout (aantal keren 50ms) -> 0x14 * 50ms = 1s
					0x01, //IRQ
					0x02, //Data Checksum: 0x100 - (TFI + CMD +  Mode + IRQ) = 0x02
					0x00, //PostAmble
			};
			HAL_GPIO_WritePin(handle->interface.spi.ss_port, handle->interface.spi.ss_pin, GPIO_PIN_RESET); //SS omlaag

			HAL_SPI_Transmit(handle->interface.spi.hspi, frame, sizeof(frame), 100);

			HAL_GPIO_WritePin(handle->interface.spi.ss_port, handle->interface.spi.ss_pin, GPIO_PIN_SET); //SS omlaag
			break;
		case PN532_MODE_VIRTUAL_CARD:

			break;
		default:
			break;
		}

		break;
	case PN532_I2C:
		//Voor latere implementatie
		break;
	case PN532_UART:
		//Voor latere implementatie
		break;
	default:
		break;
	}

	//
}

static void PN532_SPI_Wakeup(PN532_Handle *handle){
	HAL_GPIO_WritePin(handle->interface.spi.ss_port, handle->interface.spi.ss_pin, GPIO_PIN_RESET); //SS omlaag
	uint8_t dummy = 0x55;
	HAL_SPI_Transmit(handle->interface.spi.hspi, &dummy, 1, 1);
	HAL_GPIO_WritePin(handle->interface.spi.ss_port, handle->interface.spi.ss_pin, GPIO_PIN_SET); //SS omhoog
	HAL_Delay(5);
}

//Data frame: [Preamble, Start Code, LEN, LCS, TFI, Data Command, Data Val..., DCS, Postamble]

static void PN532_SendCommand(){

}

