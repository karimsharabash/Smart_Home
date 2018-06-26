/*
 * DC_Motor.h
 *
 *  Created on:2/3/2018
 *      Author: Karim Sharabash
 */
#include "DC_Motor.h"

void DC_motor_Init(void)
{
	Make_Pin_Op(D,Relay1);
	Make_Pin_Op(D,Relay2);
	DC_motor_stop();
}

void DC_motor_turn_right(void)
{
	Clear_Pin(D,Relay2);
	Set_Pin(D,Relay1);

}

void DC_motor_turn_left(void)
{
	Clear_Pin(D,Relay1);
	Set_Pin(D,Relay2);

}

void DC_motor_stop(void)
{
	Clear_Pin(D,Relay2);
	Clear_Pin(D,Relay1);
}
