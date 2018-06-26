/*
 * Motion_Dection.h
 * PIR sensor

 *  Created on: 19/2/2018
 *
 *      Author: Karim sharabash
 */

#ifndef MOTION_DETECTION_H_
#define MOTION_DETECTION_H_

#include "../MCAL/DIO.h"

#define  MD_Pin     2                    // Do is the pin for the digital output from MQ2 sensor
void Motion_Dect_Init(void);

unsigned char Motion_Dect_read(void);


#endif /* MOTION_DETECTION_H_ */
