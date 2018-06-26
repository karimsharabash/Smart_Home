/*
 * Smoke_detector.c
  MQ2 sensor
 *
 *  Created on: 19/2/2018
 *
 *      Author: Karim sharabash
 */

#include "Smoke_detector.h"


void Smoke_Dect_Init(void)
{
	Make_Pin_Ip(B,Smoke_dect_Pin);      //make PORTA pin Do  input
//	Set_Pin(B,Smoke_dect_Pin);          //connect the pin to internal PULL UP resistor
}

unsigned char Smoke_Dect_read(void)
{
	if((Read_Pin(B,Smoke_dect_Pin))==0)     // when the sensor detect a gas or smoke its output will be zero
	{
     return 1;
	}
	else                 // the sensor give (1) as a digital output in the normal conditions (when there is no gas or smoke detected )
	{
		return 0;
	}
}
