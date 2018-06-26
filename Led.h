/*
 * Led.h
 *
 *  Created on: 3/3/2018
 *      Author: Karim
 */

#ifndef LED_H_
#define LED_H_
#include "../MCAL/DIO.h"
#define  normal_light 2
#define  Fire_alarm_light  3
#define  secuirty_alarm_light 4

void Led_Init(void);

void Led_on(unsigned char Led_number);

void Led_off(unsigned char Led_number);
void Led_toggle(unsigned char Led_number);

#endif /* LED_H_ */
