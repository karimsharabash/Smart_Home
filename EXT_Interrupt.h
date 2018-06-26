/*
 * EXT_Interrupt.h
 *
 *  Created on: 12/3/2018
 *      Author: karim sharabash
 */

#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_
#include <avr/io.h>
#define INT0_Pin 2   //portd
#define INT1_Pin 3   //portd
#define INT2_pin 2   //portb

#define rising_edge_mode 1
#define falling_edge_mode 2
#define logical_change_mode 3
#define low_level_mode 4

/*
 * please notice that only INT0 and INT1 have logical change and low level modes
 * where INT2 has rising and falling edges modes
 * */
void EXT_interrupt_Config(unsigned char mode,unsigned char INT_number);


#endif /* EXT_INTERRUPT_H_ */
