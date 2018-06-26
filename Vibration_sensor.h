/*
 * Vibration_sensor.c
 *
 *  Created on: 12/3/2018
 *      Author: karim sharabash
 */

#ifndef VIBRATION_SENSOR_H_
#define VIBRATION_SENSOR_H_
#include "../MCAL/my_ADC.h"

void Vibration_Sensor_Init(void);

unsigned char Vibration_Sensor_Read(void);


#endif /* VIBRATION_SENSOR_H_ */
