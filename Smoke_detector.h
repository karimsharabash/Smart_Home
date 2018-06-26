/*
 * Smoke_detector.h
 * MQ2 sensor
 * there are 4 pins :
 * vcc : (in) 5  v
 * GND : (in) 0 v
 * DO  :  (out) 0 or 5 v  (this is what i'm getting the output from)
 * AO : (out) 0 to 5 v   ( i'm not using this in  my code )
 *  Created on: 19/2/2018
 *
 *      Author: Karim sharabash
 */

#ifndef SMOKE_DETECTOR_H_
#define SMOKE_DETECTOR_H_

#include "../MCAL/DIO.h"

#define Smoke_dect_Pin    3                        // Do is the pin for the digital output from MQ2 sensor
void Smoke_Dect_Init(void);

unsigned char Smoke_Dect_read(void);


#endif /* SMOKE_DETECTOR_H_ */
