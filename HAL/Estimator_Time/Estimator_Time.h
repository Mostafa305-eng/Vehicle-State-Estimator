/*
 * Module_Cfg.h
 *
 *  Created on: 29/12/2019
 *      Author: Sherif Adel
 */

#ifndef HAL_ESTIMATOR_TIME_ESTIMATOR_TIME_H_
#define HAL_ESTIMATOR_TIME_ESTIMATOR_TIME_H_

#include "std_types.h"
/************************************************************************/
/*		                   FUNCTIONS' PROTOTYPES          		        */
/************************************************************************/


/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The Timer
 *
 */
ERROR_STATUS Estimator_Time_init(void);



/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Start the timer
 *
 */
ERROR_STATUS Estimator_Start_Timer(uint8 u8_initTime);

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Calculate Time from Timer1
 *
 */
ERROR_STATUS Calculate_Time(uint8 *u8_Time);



#endif /* HAL_ESTIMATOR_TIME_ESTIMATOR_TIME_H_ */
