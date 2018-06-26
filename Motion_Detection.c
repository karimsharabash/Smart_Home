/*
 * Motion_Dection.c
 *
 *  Created on: 19/2/2018
 *
 *      Author: Karim sharabash
 */

#include "Motion_Detection.h"

void Motion_Dect_Init(void)
{
	/* make PIR_PIN ( PORTD , pin 3 )as  input  */
	Make_Pin_Ip(B,MD_Pin);        //make PORTA PIR_output   input
}

unsigned char Motion_Dect_read(void)
{
	if(Read_Pin(B,MD_Pin))     // when the sensor detect a person will return 1
	{
     return 1;
	}
	else
	{
		return 0;
	}
}
