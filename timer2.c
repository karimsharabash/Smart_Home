/*
 * timer2.c
 *
 *  Created on: 15/3/2018
 *      Author: karim sharabash
 */
#include "timer2.h"

void Timer2_Init(void)
{
	Timer2_clear();
	TIMSK|=(1<<OCIE2);
	OCR2=180;
}

void Timer2_clear(void)
{
	TCNT2=0;      //clear the counter
}

unsigned char Timer2_read(void)
{
	return TCNT2;
}

void  Timer2_start(void)
{
TCCR2=(1<<CS20)|(1<<CS21)|(1<<CS22);  //make the prescaler /1024(128 us per step ) and start counting
}

void  Timer2_stop(void)
	 {
	 	 TCCR2=0;                     //clear the prescaler which make the timer stop counting
	 }
