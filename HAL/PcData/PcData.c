/*
 * PcData.c
 *
 *  Created on: 29/12/2019
 *      Author: Sherif Adel
 */
#include "std_types.h"
#include "DIO.h"
#include "UART.h"
#include"PcData.h"
/************************************************************************/
/*		               FUNCTIONS' Definition		                    */
/************************************************************************/

/******************* convert only one character to int  ********************/
static uint32 ConvCharToInt(uint8 CHAR){
	return (CHAR - '0');
}
/*************************convert string to int ************************************/

static uint32 ConvStringToInt(uint8 * ptr,uint32 exponent){
	uint32 i,total_number=0,number,digit=1;
	    for(i=0;i<(exponent-1);i++)
	    digit *=10;
	for(i=0;i<exponent;i++){
		number = ConvCharToInt(*(ptr+i));
		total_number += number * digit ;
		digit *=.100000;
	}
	return total_number;
}
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize the PC module
 *
 */
ERROR_STATUS PcData_init(void)
{
	UART_cfg_s myUart={UART_POLLING,TRANSCEIVER,UART_NO_DOUBLE_SPEED,UART_ONE_STOP_BIT\
			,UART_NO_PARITY,UART_8_BIT,9600,NULL,NULL,NULL};

	UART_Init(&myUart);
}

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Takes Inital values of both speed and time
 *
 *
 */
ERROR_STATUS PcData_Update(uint8 *u8_InitTime,uint8 *u8_InitSpeed)
{
	uint8 u8_UserTimeMessage[]="please write init time : ";
	uint8 u8_UserSpeedMessage[]="please write init speed : ";

	uint8 u8_InitTimeString[4];
	uint8 u8_InitSpeedString[4];

	uint8 u8_TempRead;
	uint8 u8_loopCounter=0;


	for (u8_loopCounter=0;u8_loopCounter<26;u8_loopCounter++)
	{
		UART_SendByte(u8_UserTimeMessage[u8_loopCounter]);
	}

	for(u8_loopCounter=0;u8_loopCounter<4;u8_loopCounter++)
	{
		UART_ReceiveByte(&u8_TempRead);
		if (u8_TempRead == '\r')
		{
			break;
		}
		u8_InitTimeString[u8_loopCounter]=u8_TempRead;
	}
	*u8_InitTime=ConvStringToInt(u8_InitTimeString,(u8_loopCounter));


	for (u8_loopCounter=0;u8_loopCounter<27;u8_loopCounter++)
	{
		UART_SendByte(u8_UserSpeedMessage[u8_loopCounter]);
	}



	for(u8_loopCounter=0;u8_loopCounter<4;u8_loopCounter++)
	{
		UART_ReceiveByte(&u8_TempRead);
		if (u8_TempRead == '\r')
		{
			break;
		}
		u8_InitSpeedString[u8_loopCounter]=u8_TempRead;
	}

	*u8_InitSpeed=ConvStringToInt(u8_InitSpeedString,(u8_loopCounter));




}


