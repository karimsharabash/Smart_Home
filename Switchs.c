/*
 * Switchs.c
 *
 *  Created on: 3/3/2018
 *      Author: Karim sharabash
 */

#include "Switchs.h"
void Switch_Init(void)
{
	Garage_sw_DDR&=~(1<<Garage_sw_pin);
	Door_sw_DDR&=~(1<<Door_sw_Pin);
	security_sw_DDR&=~(1<<security_sw_Pin);
}

unsigned char Switch_Read(unsigned char Sw_number)
{

	switch(Sw_number)
	{
	case Garage_sw_pin:{
		if((Garage_sw_port&(1<<Garage_sw_pin)))
		{
			return 1;
		}
		else
		{
			return 0;
		}

	}break;
	case Door_sw_Pin:{
		if((Door_sw_Port&(1<<Door_sw_Pin)))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}break;
	case security_sw_Pin:{
		if((security_sw_Port&(1<<security_sw_Pin)))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}break;
	default:
	{
		return 0;
	}
	}
}
