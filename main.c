/*
 * main.c
 *
 *  Created on: 28/12/2019
 *      Author: Sherif Adel
 */

#include "interrupt.h"
#include "DIO.h"
#include "Timer.h"
#include "spi.h"
#include "Estimater_ECU.h"
#include <stdlib.h>
#include "char_lcd .h"
#include "softwareDelay.h"

#include"pushButton.h"




int main(void)
{

	extern uint8 gu8_Speed;
	extern  uint8 gu8_Time;
	sei();
	LCD_init();



	Estimator_init();

	char LCD_buffer[20];
	char LCD_buffer2[20];



while(1)
{

	Estimator_Update();

	LCD_goto_xy(0,0);
	LCD_send_string("time : ");
	LCD_goto_xy(10,0);
	itoa(gu8_Time,LCD_buffer2,10);
	LCD_send_string(LCD_buffer2);

	LCD_goto_xy(0,1);
	LCD_send_string("speed : ");
	LCD_goto_xy(10,1);
	itoa(gu8_Speed,LCD_buffer,10);
	LCD_send_string(LCD_buffer);

SwDelay_ms(50);
	LCD_clear();



}
	return 0;
}



