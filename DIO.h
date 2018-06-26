/*
 * DIO.h
 *
 *  Created on: 19/2/2018
 *      Author: Karim sharabash
 */

#ifndef DIO_H_
#define DIO_H_
#include <avr/io.h>
#define Make_Pin_Op(port,pin)  DDR##port |=(1<<pin)
#define Make_Pin_Ip(port,pin)  DDR##port &=~(1<<pin)
#define Set_Pin(port,pin)      PORT##port |=(1<<pin)
#define Clear_Pin(port,pin)    PORT##port &=~(1<<pin)
#define Toggle_Pin(port,pin)   PORT##port ^=(1<<pin)
#define Read_Pin(port,pin)     PIN##port &(1<<pin)

#endif /* DIO_H_ */
