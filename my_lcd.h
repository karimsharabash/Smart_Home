/*
 * my_lcd.h
 *
 *  Created on:20/2/2018
 *      Author: karim sharabash
 */

#ifndef MY_LCD_H_
#define MY_LCD_H_

#define Delay(x)  _delay_ms(x)         //to make it easy to chane when using RTOS
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#define LCD_Data_DDR  DDRB
#define LCD_Data_PORT PORTB
#define LCD_Control_DDR DDRC
#define LCD_Control_PORT PORTC
#define E              7
#define RS             6

void LCD_Init();
void LCD_Write_Command(unsigned char CMD);
void LCD_Write_Data(unsigned char data);
void cursor_shift_left(unsigned char steps);
void cursor_shift_right(unsigned char steps);
void display_shift_right(unsigned char steps);
void display_shift_left(unsigned char steps);
void LCD_goto_loaction(unsigned char row , unsigned char column);
void LCD_write_string(char *string);
void Toggle_Curcor_Pos(void);
void LCD_clear_screen(void);
short int LCD_string2int(char *str);
void LCD_IntToString(int integer,char *String);




#endif /* MY_LCD_H_ */
