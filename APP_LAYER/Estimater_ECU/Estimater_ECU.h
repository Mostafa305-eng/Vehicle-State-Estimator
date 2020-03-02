/*
 * Estimater_ICU.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: mohamed
 */

#ifndef APP_LAYER_ESTIMATER_ECU_ESTIMATER_ECU_H_
#define APP_LAYER_ESTIMATER_ECU_ESTIMATER_ECU_H_

#include "std_types.h"
/************************************************************************/
/*		                   FUNCTIONS' PROTOTYPES          		        */
/************************************************************************/



/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Intialize  Estimator Application
 *
 */
ERROR_STATUS Estimator_init(void);

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Update Time and Speed
 *
 */
ERROR_STATUS Estimator_Update(void);



void EXT_INT_init(void);

#endif /* APP_LAYER_ESTIMATER_ECU_ESTIMATER_ECU_H_ */
