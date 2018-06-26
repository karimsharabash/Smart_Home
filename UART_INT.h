/*
 * UART_INT.h
 *
 *  Created on: 5/3/2018
 *      Author: karim sharabash
 */

#ifndef UART_INT_H_
#define UART_INT_H_



void Uart_init(long BaudRate);


void UART_send_byte( char byte);
void UART_send_string( char *ptr);

#endif /* UART_INT_H_ */
