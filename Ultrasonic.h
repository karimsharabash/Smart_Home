/*
 * Ultrasonic.h
 *
 *  Created on: 18/2/2018
 *      Author: Karim sharabash
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#include "../MCAL/timer2.h"
#include <util/delay.h>
#include "../MCAL/EXT_Interrupt.h"
#define US_DDR     DDRD
#define US_PORT    PORTD
#define US_PIN     PIND
#define Trigger    4
#define Echo       3



void Ultrasonic_Init(void);

void Ultrasonic_Read(void);



#endif /* ULTRASONIC_H_ */
