/*
 * DC_Motor.h
 *
 *  Created on:2/3/2018
 *      Author: Karim Sharabash
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "../MCAL/DIO.h"
#define Relay1      6         //first relay on port d pin 6
#define Relay2      7          //second relay on port d pin 7
void DC_motor_Init(void);

void DC_motor_turn_right(void);

void DC_motor_turn_left(void);

void DC_motor_stop(void);

#endif /* DC_MOTOR_H_ */
