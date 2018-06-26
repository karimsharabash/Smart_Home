/*
 * Vibration_sensor.c
 *
 *  Created on: 12/3/2018
 *      Author: karim sharabash
 */
#include "Vibration_sensor.h"

void Vibration_Sensor_Init(void)
{
	ADC_Init();
}

unsigned char  Vibration_Sensor_Read(void)
{
	short int Vibration=0;
	Vibration=ADC_Read(1,5);     //get the value of the ADC on channel 0 with 5v vcc as vref
	if(Vibration>600)             // if there are a huge vibration  return 1
	return 1;
    else
	return 0;
}
