/*
 * Light_sensor.c
 *
 *  Created on:2/3/2018
 *      Author: karim sharabash
 */
#include "Light_sensor.h"

void Light_Sensor_Init(void)
{
	ADC_Init();
}

unsigned char  Light_Sensor_Read(void)
{
	short int light=0;
	light=ADC_Read(0,5);     //get the value of the ADC on channel 0 with 5v vcc as vref
	if(light>200)             // if there is light return 1
	return 1;
    else
	return 0;
}
