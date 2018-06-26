/*
 * Led.h
 *
 *  Created on: 3/3/2018
 *      Author: Karim
 */
#include "Led.h"

void Led_Init(void)
{
	Make_Pin_Op(C,normal_light);
	Make_Pin_Op(C,Fire_alarm_light);
	Make_Pin_Op(C,secuirty_alarm_light);
}

void Led_on(unsigned char Led_number)
{
    Set_Pin(C,Led_number);
}

void Led_off(unsigned char Led_number)
{
	Clear_Pin(C,Led_number);
}

void Led_toggle(unsigned char Led_number)
{
	Toggle_Pin(C,Led_number);
}
