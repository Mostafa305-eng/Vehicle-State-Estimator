/*
 * EXT_INT.c

 *
 *  Created on: 23/12/2019
 *      Author: Sherif Adel
 */
#include "std_types.h"
#include "registers.h"
#include "interrupt.h"
#include "ExternalInterrupt.h"


/**************Static Global Pointer to Function*********/
static  void (*EXT_INT_GptrCBK[3])(void)={NULL,NULL,NULL};



/************************************************************************/
/*				 		Functions Definition                            */
/************************************************************************/

/*
 * Function: ExternInt_Init
 * Inputs:	ExternIntCfg -> pointer of type ExternInt_Cfg_s which points to structure that contain the initialized data.
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Initiate the required external interrupt configuration as it specify
 *	event of interrupt.
 *	Enable the required external interrupt from GICR but to allow the interrupt global interrupt must be set
 */
ERROR_STATUS ExternInt_Init(ExternInt_Cfg_s *ExternIntCfg)
{
	ERROR_STATUS State=E_OK;


	switch(ExternIntCfg->ExternInt_No)
	{
	case EXTRN_INT_0:

		EXT_INT_GptrCBK[0]=ExternIntCfg->ExternInt_CBF_Ptr; /****CALL BACK FUNC.***/

		switch(ExternIntCfg->ExternInt_Event)
		{
		case LOW_LEVEL:
			MCUCR &=~3;
			break;

		case LOGICAL_CHANGE:
			MCUCR &=~3;
			MCUCR |=LOGICAL_CHANGE;
			break;

		case FALLING_EDGE:
			MCUCR &=~3;
			MCUCR |=FALLING_EDGE;
			break;

		case RISING_EDGE:
			MCUCR &=~3;
			MCUCR |=RISING_EDGE;
			break;

		default:
			State=E_NOK;
			break;

		}
		break;

		case EXTRN_INT_1:

			EXT_INT_GptrCBK[1]=ExternIntCfg->ExternInt_CBF_Ptr; /****CALL BACK FUNC.***/

			switch(ExternIntCfg->ExternInt_Event)
			{
			case LOW_LEVEL:
				MCUCR &=~0x0c;
				break;

			case LOGICAL_CHANGE:
				MCUCR &=~0x0c;
				MCUCR |=(LOGICAL_CHANGE<<2);
				break;

			case FALLING_EDGE:
				MCUCR &=~0x0c;
				MCUCR |=(FALLING_EDGE<<2);
				break;

			case RISING_EDGE:
				MCUCR &=~0x0c;
				MCUCR |=(RISING_EDGE<<2);
				break;

			default:
				State=E_NOK;
				break;

			}
			break;

			case EXTRN_INT_2:

				EXT_INT_GptrCBK[2]=ExternIntCfg->ExternInt_CBF_Ptr; /****CALL BACK FUNC.***/

				switch(ExternIntCfg->ExternInt_Event)
				{

				case FALLING_EDGE:
					MCUCSR &=~(1<<6);
					break;

				case RISING_EDGE:
					MCUCSR |=(1<<6);
					break;

				default:
					State=E_NOK;
				}
				break;

	}

	return State;

}

/*
 * Function: ExternInt_Enable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Enable the required external interrupt from GICR but to allow the interrupt global interrupt must be set.
 */
ERROR_STATUS ExternInt_Enable(uint8 ExternInt_No)
{
	ERROR_STATUS State=E_OK;

	switch(ExternInt_No)
	{
	case EXTRN_INT_0:
		GICR |=(1<<6);     /******Enable EXT INT0*****/
		break;

	case EXTRN_INT_1:
		GICR |=(1<<7);    /******Enable EXT INT1*****/
		break;

	case EXTRN_INT_2:
		GICR |=(1<<5);    /******Enable EXT INT2*****/
		break;

	default:
		State=E_NOK;
		break;
	}

return State;


}


/*
 * Function: ExternInt_SetEvent
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * 	       InterruptEvent -> indicate required event for INT0 and INT1 there are 4 events to check (RISING_EDGE,FALLING_EDGE,LOW_LEVEL,LOGICAL_CHANGE).
							  But for Interrupt 2 there are only Two cases (Rising,Falling)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: function is used to set event of required external interrupt.
 * 				note: usually used to poll on the flag.
 */
ERROR_STATUS ExternInt_SetEvent(uint8 ExternInt_No,uint8 InterruptEvent)
{
	ERROR_STATUS State=E_OK;
	switch(ExternInt_No)
	{
	case EXTRN_INT_0:

		switch(InterruptEvent)
		{
		case LOW_LEVEL:
			MCUCR &=~3;
			break;

		case LOGICAL_CHANGE:
			MCUCR &=~3;
			MCUCR |=LOGICAL_CHANGE;
			break;

		case FALLING_EDGE:
			MCUCR &=~3;
			MCUCR |=FALLING_EDGE;
			break;

		case RISING_EDGE:
			MCUCR &=~3;
			MCUCR |=RISING_EDGE;
			break;

		default:
			State=E_NOK;
			break;

		}
		break;

		case EXTRN_INT_1:

			switch(InterruptEvent)
			{
			case LOW_LEVEL:
				MCUCR &=~0x0c;
				break;

			case LOGICAL_CHANGE:
				MCUCR &=~0x0c;
				MCUCR |=(LOGICAL_CHANGE<<2);
				break;

			case FALLING_EDGE:
				MCUCR &=~0x0c;
				MCUCR |=(FALLING_EDGE<<2);
				break;

			case RISING_EDGE:
				MCUCR &=~0x0c;
				MCUCR |=(RISING_EDGE<<2);
				break;

			default:
				State=E_NOK;
				break;

			}
			break;

			case EXTRN_INT_2:

				switch(InterruptEvent)
				{

				case FALLING_EDGE:
					MCUCSR &=~(1<<6);
					break;

				case RISING_EDGE:
					MCUCSR |=(1<<6);
					break;

				default:
					State=E_NOK;
				}
				break;
	}
	return State;
}

/*
 * Function: ExternInt_Disable
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2)
 * Outputs:
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: Disable the required external interrupt.
 */
ERROR_STATUS ExternInt_Disable(uint8 ExternInt_No)
{
	ERROR_STATUS State=E_OK;

	switch(ExternInt_No)
	{
	case EXTRN_INT_0:
		GICR &=~(1<<6);
		break;

	case EXTRN_INT_1:
		GICR &=~(1<<7);
		break;

	case EXTRN_INT_2:
		GICR &=~(1<<5);
		break;

	default:
		State=E_NOK;
		break;
	}

return State;
}

/*
 * Function: ExternInt_GetStatus
 * Inputs: ExternInt_No -> Specify one of the external interrupt (INT_0, INT_1, INT2).
 * Outputs: *status -> points to the value of selected interrupt flag.
 * In Out:
 * Return: ERROR_STATUS -> check if there any error occurs, would return E_NOK else it would return E_OK.
 * Description: function is used to get flag of required interrupt status.
 * 				note: usually used to poll on the flag.
 */
ERROR_STATUS ExternInt_GetStatus(uint8 ExternInt_No,uint8 *Status)
{
	ERROR_STATUS State=E_OK;
	switch(ExternInt_No)
	{
	case EXTRN_INT_0:
		*Status=(GIFR &(1<<6))>>6;
		break;

	case EXTRN_INT_1:
		*Status=(GIFR &(1<<7))>>7;
		break;

	case EXTRN_INT_2:
		*Status=(GIFR &(1<<5))>>5;
		break;

	default:
		State=E_NOK;
		break;
	}
	return State;
}
/**********EXT_INT0  (ISR) **********/

ISR(INT0_vect)
{
	if(NULL !=EXT_INT_GptrCBK[0])
	{
		EXT_INT_GptrCBK[0]();
	}
}

/**********EXT_INT1  (ISR) **********/

ISR(INT1_vect)
{
	if(NULL !=EXT_INT_GptrCBK[1])
	{
		EXT_INT_GptrCBK[1]();
	}
}

/**********EXT_INT2  (ISR) **********/

ISR(INT2_vect)
{
	if(NULL !=EXT_INT_GptrCBK[2])
	{
		EXT_INT_GptrCBK[2]();
	}
}

