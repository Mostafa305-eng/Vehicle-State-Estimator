/*
 * Exchanger.c
 *
 *  Created on: 29/12/2019
 *      Author: Sherif Adel
 */

#include "std_types.h"
#include "Exchanger.h"
#include "spi.h"
#include "DIO.h"
#include "softwareDelay.h"





/************************************************************************/
/*		               FUNCTIONS' Definition		                    */
/************************************************************************/
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The AVR1 as Master
 *
 */
ERROR_STATUS Exhanger_Init(void)
{
	ERROR_STATUS State=E_OK;


	SPI_Cfg_s SPI_cfg=
	{
			MASTER ,
			MODE_0,
			MSB,
			INTERRUPT,
			SPI_PRESCALER_32,
			NULL
	};
	if(SPI_Init(&SPI_cfg)==E_NOK)
	{
		State=E_NOK;
	}
	return State;
}

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Send Time and Speed To measurment ECU
 *
 */
ERROR_STATUS Exhanger_SendData(uint8 u8_Time,uint8 u8_Speed)
{
	ERROR_STATUS State=E_OK;

	SPI_SendByte('t');
	SwDelay_ms(20);
	SPI_SendByte(u8_Time);
	SwDelay_ms(20);
	SPI_SendByte('s');
	SwDelay_ms(20);
	SPI_SendByte(u8_Speed);

	return State;
}
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The AVR2 as Slave
 *
 */
ERROR_STATUS SPI_Slave_init(void)
{
	ERROR_STATUS State=E_OK;
	SPI_Cfg_s SPI_cfg=
	{
			SLAVE ,
			MODE_0,
			MSB,
			POLLING,
			SPI_PRESCALER_16,
			NULL
	};
	if(SPI_Init(&SPI_cfg)==E_NOK)
	{
		State=E_NOK;
	}
	return State;
}

