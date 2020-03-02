/*
 * Estimater_ECU.c
 *
 *  Created on: 29/12/2019
 *      Author:Sherif Adel
 */

/************************************************************************/
/*				               Includes                                 */
/************************************************************************/
#include <stdlib.h>
#include "std_types.h"
#include "INT_interface.h"
#include "PcData.h"
#include "Exchanger.h"
#include "pushButton.h"
#include "DIO.h"
#include "Estimator_Time.h"
#include "Estimater_ECU.h"
#include "char_lcd .h"
/************************************************************************/
/*		                Global and static Variables                     */
/************************************************************************/
 uint8 gu8_Speed=0;
 uint8 gu8_Time=0;
 uint8 gu8_InitTime=0;

	char LCD_buffer[20];
	char LCD_buffer2[20];
/************************************************************************/
/*		               FUNCTIONS' Definition		                    */
/************************************************************************/

 static void Reciever_Fetch (void)
{


	Exhanger_SendData(gu8_Time,gu8_Speed);

}


/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Intialize  Estimator Application
 *
 */
ERROR_STATUS Estimator_init(void)
{
	ERROR_STATUS State=E_OK;



	if(Exhanger_Init()==E_NOK)
	{
		State=E_NOK;
	}
	if(Estimator_Time_init()==E_NOK)
	{
		State=E_NOK;
	}
	PushButton_Cfg_st mybtn1={BTN_1};
	pushButton_Init(&mybtn1);

	PushButton_Cfg_st mybtn0={BTN_0};
	pushButton_Init(&mybtn0);

	PcData_init();
	PcData_Update(&gu8_InitTime,&gu8_Speed);
	Estimator_Start_Timer(gu8_InitTime);

	INT_interface_init(Reciever_Fetch);


return State;

}

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Update Time and Speed
 *
 */
ERROR_STATUS Estimator_Update(void)
{
	ERROR_STATUS State=E_OK;

	uint8 u8_Button0_State=0;
	uint8 u8_Button1_State=0;
	Calculate_Time(&gu8_Time);

	pushButton_Update();

	pushButton_GetStatus(BTN_0,&u8_Button0_State);
	pushButton_GetStatus(BTN_1,&u8_Button1_State);

	if(u8_Button1_State==Prepressed)
	{
		gu8_Speed++;
		Exhanger_SendData(gu8_Time,gu8_Speed);
	}
	if(u8_Button0_State==Prepressed)
	{
		gu8_Speed--;

		Exhanger_SendData(gu8_Time,gu8_Speed);
	}
}



