/*
 * my_lcd.c
 *
 *  Created on: 20/2/2018
 *      Author: karim sharabash
 */

#include "my_lcd.h"
unsigned char location[2]={0x80,0xc0};
unsigned char curcor_counter;
unsigned char toggle_counter;
void LCD_Init()
{
	LCD_Data_DDR|=0xf0; // Make PORT output
	LCD_Data_PORT&=0x0F;   // Init PORT
	////////////////////////////////////////
	LCD_Control_DDR|=(1<<RS)|(1<<E);   // Make RS and e Output
	//////////////Send command for init lcd //////////////////////

	LCD_Write_Command(0x02);	// Return Home
	LCD_Write_Command(0x28);    // 4 bit mode 5*8 dispaly  2 line
	//LCD_Write_Command(0x24);    // 4 bit mode 5*11 dispaly  1 line

	Delay(1);
	LCD_Write_Command(0x01);    // Clear All Display Data
	//LCD_Write_Command(0x0E);    // Display on-Cursor on-Blink off
	LCD_Write_Command(0x0C);    // Display on-Cursor off-Blink off

	LCD_Write_Command(0x06);    // after every character cursor will move to right


	Delay(1); // delay again...
}
void LCD_Write_Command(unsigned char CMD)
{
	LCD_Control_PORT&=~(1<<RS); // Init RS " Command mode "
	////////////////////////////////////
	LCD_Data_PORT&=0X0F;
	 //initilaize the lcd 4 bit port
	//_delay_us(10);
	LCD_Control_PORT|=(1<<E); //  Init EN
	_delay_us(5);
	LCD_Data_PORT|=(CMD&0xF0);
	LCD_Control_PORT&=~(1<<E); // Init EN
	//_delay_us(10);


//	LCD_Control_PORT&=~(1<<RS); // Init RS " Command mode "
	/////////////////////////////////
	LCD_Data_PORT&=0X0F;

	LCD_Control_PORT|=(1<<E); //  Init EN
	_delay_us(5);
	LCD_Data_PORT|=((CMD<<4)&0xF0);
	LCD_Control_PORT&=~(1<<E); // Init EN
//	_delay_us(10);
	//////////////////////////////////
	_delay_ms(2);
}
void LCD_Write_Data(unsigned char data)
{
	LCD_Control_PORT|=(1<<RS); // Init RS " data mode "
	////////////////////////////////////
	LCD_Data_PORT&=0X0F;

	/////////////////////////////////
	LCD_Control_PORT|=(1<<E); //  Init EN
	_delay_us(5);
	LCD_Data_PORT |=(data&0xF0) ;
	LCD_Control_PORT&=~(1<<E); // Init EN
	//_delay_us(5);

//	LCD_Control_PORT|=(1<<RS); // Init RS " data mode "
	/////////////////////////////////
	LCD_Data_PORT&=0X0F;

	LCD_Control_PORT|=(1<<E); //  Init EN
	_delay_us(5);
	LCD_Data_PORT|=((data<<4)&0xF0);
	LCD_Control_PORT&=~(1<<E); // Init EN
	Delay(1);
	//////////////////////////////////
//	Delay(10);

}

void cursor_shift_left(unsigned char steps)
{
	do
	{
		LCD_Write_Command(0x10);
		steps--;
		Delay(1);
	}
	while(steps>0);
}

void cursor_shift_right(unsigned char steps)
{
	do
	{
		LCD_Write_Command(0x14);
		steps--;
		Delay(1);
	}
	while(steps>0);
}


void display_shift_right(unsigned char steps)
{
	do
	{
		LCD_Write_Command(0x1C);
		steps--;
		Delay(1);
	}
	while(steps>0);
}

void display_shift_left(unsigned char steps)
{
	do
	{
		LCD_Write_Command(0x18);
		steps--;
		Delay(1);
	}
	while(steps>0);
}


void LCD_goto_loaction(unsigned char row , unsigned char column)
{
	LCD_Write_Command((location[row]+column));
//	Delay(1);
}

void LCD_write_string(char *string)
{
	while(*string!='\0')
		{
			 LCD_Write_Data(*string++);
		}

  _delay_us(10);

}

void Toggle_Curcor_Pos()
{

	curcor_counter++;
	if(curcor_counter==16)
	{
		LCD_goto_loaction(1,0);
		curcor_counter=0;
		toggle_counter++;
	}
	if(toggle_counter==2)
	{
		LCD_goto_loaction(0,0);
		toggle_counter=0;
	}
}

void LCD_clear_screen(void)
{
	LCD_Write_Command(0x01);    // Clear All Display Data
}

short int LCD_string2int(char *str)
{
	unsigned char i=0,x=0;
	   while(str[i] != '\0')
	   {
	       x=((x*10)+(str[i++]-'0'));

	   }
	   return x;
}

void LCD_IntToString(int integer,char *String)
{
	itoa(integer,String,10);
}


