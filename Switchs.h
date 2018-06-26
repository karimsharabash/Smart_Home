/*
 * Switchs.h
 *
 *  Created on: 3/3/2018
 *      Author: Karim sharabash
 */


#ifndef SWITCHS_H_
#define SWITCHS_H_
#include "../MCAL/DIO.h"
#define  Door_sw_Pin  0
#define  Door_sw_Port PINB
#define  Door_sw_DDR  DDRB
#define  Garage_sw_pin 2
#define  Garage_sw_port PIND
#define  Garage_sw_DDR  DDRD
#define  security_sw_Pin  1
#define  security_sw_Port  PINB
#define  security_sw_DDR   DDRB

void Switch_Init(void);

unsigned char Switch_Read(unsigned char Sw_number);


#endif /* SWITCHS_H_ */
