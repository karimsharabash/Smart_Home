
/*
 * i2c.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ascom
 */

#ifndef MY_TWI_H_
#define MY_TWI_H_
#include<avr/io.h>
#define TWI_SPEED 100

#define Read 0x01
#define Write 0x00

void TWI_init(unsigned char my_address);

void TWI_start(void);

void TWI_send_address(unsigned char address , char readorwrite);

void TWI_send_data(unsigned char data);
void TWI_check_slave_Tx(void);

unsigned char TWI_receive_data_ACK(void); // for slave to send ack after the recieve
unsigned char TWI_receive_data_NACK(void); // for slave to don't send ack after the recieve
void TWI_stop(void);

#endif /* MY_TWI_H_ */
