/*
 * INT_interface.c
 *
 *  Created on: 30/12/2019
 *      Author: Sherif Adel
 */

/************************************************************************/
/*				               Includes                                 */
/************************************************************************/
#include "ExternalInterrupt.h"



/************************************************************************/
/*		               FUNCTIONS' Definition		                    */
/************************************************************************/

/**
 * Input:
 * Output:
 * In/Out:
 * Return: The error status of the function.
 * Description: Intialize  External interrupt 2
 *
 */
void INT_interface_init(void (*PtrFunc)(void))
{
	ExternInt_Cfg_s EXT_INT1;
	EXT_INT1.ExternInt_No=EXTRN_INT_1;
	EXT_INT1.ExternInt_Event=RISING_EDGE;
	EXT_INT1.ExternInt_CBF_Ptr=PtrFunc;

	ExternInt_Init(&EXT_INT1);
	ExternInt_Enable(EXTRN_INT_1);
}
