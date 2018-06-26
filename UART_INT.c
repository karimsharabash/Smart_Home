/*
 * UART_INT.c
 *
 *  Created on: 5/3/2018
 *      Author: karim sharabash
 */



#include <avr/io.h>
#include "UART_INT.h"
volatile unsigned char Uart_data=0;
void Uart_init(long BaudRate)
{
	unsigned short int BRvalue=0;
	UCSRB=(1<<RXCIE)|(1<<RXEN)|(1<<TXEN); //enable tx , rx and rx complete interrupt
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1); //choose urcsc , and 8bit size
	BRvalue=(unsigned char)(((F_CPU)/(16*BaudRate))-1); // to calculate the value of the baud rate reg
	UBRRL=BRvalue; 			//low byte
    UBRRH=(BRvalue>>8);     //high byte
}

void UART_send_byte( char byte)
 {
	while(!(UCSRA &(1<<UDRE))); // while shift register flag != 1 (not empty))
	UDR=byte;
 }

void UART_send_string( char *ptr)
 {
	unsigned char  i=0;

		while(ptr[i] != '\0')
		 {
			UART_send_byte(ptr[i]);
			i++;
		 }
	UART_send_byte(ptr[i]);
 }



