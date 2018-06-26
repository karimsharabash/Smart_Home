/*
 * timer2.h
 *
 *  Created on: 15/3/2018
 *      Author: karim sharabash
 */

#ifndef TIMER2_H_
#define TIMER2_H_

#include <avr/io.h>
void Timer2_Init(void);
 void  Timer2_start(void);
 void  Timer2_stop(void);
 void  Timer2_clear(void);
 unsigned char Timer2_read(void);

#endif /* TIMER2_H_ */
