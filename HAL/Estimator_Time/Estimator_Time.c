/*
 * Module_Cfg.c
 *
 *  Created on: 29/12/2019
 *      Author: Sherif Adel
 */

/*
 * Estimater_ECU.c
 *
 *  Created on: 29/12/2019
 *      Author:Sherif Adel
 */

/************************************************************************/
/*				               Includes                                 */
/************************************************************************/
#include "../Estimator_Time/Estimator_Time.h"

#include "std_types.h"

#include "Timer.h"


#define Inital_Count  0
/************************************************************************/
/*		                Global and static Variables                     */
/************************************************************************/
static uint8 gu8_Overflows_Count=0;

/*********Global Static function***/
static void Timer_Count(void);



/************************************************************************/
/*		               FUNCTIONS' Definition		                    */
/************************************************************************/

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: initialize The Timer and PushButtons
 *
 */
ERROR_STATUS Estimator_Time_init(void)
{
	ERROR_STATUS State=E_OK;
	/**********initialize Timer 1******/

	Timer_cfg_s Timer1_Cfg;
	Timer1_Cfg.Timer_CH_NO=TIMER_CH1;
	Timer1_Cfg.Timer_Mode=TIMER_MODE;
	Timer1_Cfg.Timer_Polling_Or_Interrupt=TIMER_INTERRUPT_MODE;
	Timer1_Cfg.Timer_Prescaler=TIMER_PRESCALER_256;
	Timer1_Cfg.Timer_Cbk_ptr=Timer_Count;

	if(Timer_Init(&Timer1_Cfg)==E_NOK)
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
 * Description: Start the timer
 *
 */
ERROR_STATUS Estimator_Start_Timer(uint8 u8_initTime)
{
	ERROR_STATUS State=E_OK;
	if(Timer_Start(TIMER_CH1,Inital_Count)==E_NOK)
	{
		State=E_NOK;
	}
	gu8_Overflows_Count=u8_initTime;
	return State;
}

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Calculate Time from Timer1
 *
 */
ERROR_STATUS Calculate_Time(uint8 *u8_Time)
{
	ERROR_STATUS State=E_NOK;
	*u8_Time =gu8_Overflows_Count;
	return State;
}





static void Timer_Count(void)
{
	gu8_Overflows_Count++;
}


