/*
 * EXT_Interrupt.c
 *
 *  Created on: 12/3/2018
 *      Author: karim sharabash
 */
#include "EXT_Interrupt.h"

void EXT_interrupt_Config(unsigned char mode,unsigned char INT_number)
{
	switch (INT_number)
	{
	case 0:{
		GICR|=(1<<INT0);
		switch(mode)
		{
		case low_level_mode:{
			MCUCR&=~((1<<ISC00)|(1<<ISC01)); //clear the two bits to get this mode
		}break;
		case logical_change_mode:{
			MCUCR|=(1<<ISC00);
			MCUCR&=~(1<<ISC01);
		}break;
		case falling_edge_mode:{
			MCUCR&=~(1<<ISC00);
			MCUCR|=(1<<ISC01);
		}break;
		case rising_edge_mode:{
			MCUCR|=(1<<ISC00)|(1<<ISC01);
		}break;
		}
	}break;

	case 1:{
		GICR|=(1<<INT1);
		switch(mode)
		{
		case low_level_mode:{
			MCUCR&=~((1<<ISC10)|(1<<ISC11));
		}break;
		case logical_change_mode:{
			MCUCR|=(1<<ISC10);
			MCUCR&=~(1<<ISC11);
		}break;
		case falling_edge_mode:{
			MCUCR&=~(1<<ISC10);
			MCUCR|=(1<<ISC11);
		}break;
		case rising_edge_mode:{
			MCUCR|=(1<<ISC10)|(1<<ISC11);
		}break;
		}
	}break;
	case 2:{
		GICR|=(1<<INT2);
		switch(mode)
		{
		case falling_edge_mode:{
			MCUCSR&=~(1<<ISC2);
		}break;
		case rising_edge_mode:{
			MCUCSR|=(1<<ISC2);
		}break;
		}
	}break;
	}
}
