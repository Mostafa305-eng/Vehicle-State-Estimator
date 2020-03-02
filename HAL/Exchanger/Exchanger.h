/*
 * Exchanger.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mohamed
 */

#ifndef HAL_EXCHANGER_EXCHANGER_H_
#define HAL_EXCHANGER_EXCHANGER_H_
#include "std_types.h"


typedef struct Exchanger_cfg_s
{
	uint8 *pu8_TimePointer;
	uint8 *pu8_SpeedPointer;
}Exchanger_cfg_s;





/************************************************************************/
/*		                   FUNCTIONS' PROTOTYPES          		        */
/************************************************************************/

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The AVR1 as Master
 *
 */
ERROR_STATUS Exhanger_Init(void);

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Send Time and Speed To measurment ECU
 *
 */
ERROR_STATUS Exhanger_SendData(uint8 u8_Time,uint8 u8_Speed);
/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The AVR2 as Slave
 *
 */
ERROR_STATUS SPI_Slave_init(void);


#endif /* HAL_EXCHANGER_EXCHANGER_H_ */
