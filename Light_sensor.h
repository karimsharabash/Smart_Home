/*
 * Light_sensor.h
 *
 *  Created on:2/3/2018
 *      Author: karim sharabash
 */

#ifndef LIGHT_SENSOR_H_
#define LIGHT_SENSOR_H_
#include "../MCAL/my_ADC.h"

void Light_Sensor_Init(void);

unsigned char Light_Sensor_Read(void);


#endif /* LIGHT_SENSOR_H_ */
