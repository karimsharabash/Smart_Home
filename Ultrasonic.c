/*
 * Ultrasonic.c
 *
 *  Created on: 18/2/2018
 *      Author: Karim sharabash
 */

#include "Ultrasonic.h"

void Ultrasonic_Init(void)
{
	EXT_interrupt_Config(logical_change_mode,1); //init INT1 with any logical change mode to detect the echo coming pulse
	Timer2_Init();        //clear the counter
	US_DDR|=(1<<Trigger);    //make trigger pin output
	US_DDR&=~(1<<Echo);      // make echo pin input
}

void Ultrasonic_Read(void)
{
	US_PORT|=(1<<Trigger);
	_delay_us(12);
	US_PORT&=~(1<<Trigger);
}
