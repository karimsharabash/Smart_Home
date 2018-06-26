/*
 * RTC.h
 *
 *  Created on: 21/2/2018
 *      Author: Karim sharabash
 */
#include "RTC.h"


void RTC_Init(void)
{
	TWI_init(0x01);
	TWI_start();
	TWI_send_address(0b01101000,Write);
	TWI_send_data(Ctrl_Ad);
	TWI_send_data(0x00);
	TWI_stop();
	_delay_ms(1);
}
/* set_data is an API take structure of all information which RTC to be set
 * H12OrH24 To choose which hour system u want
 * AMOrPM   to decide are u at AM or PM when using (12-h mode)
 *
 */
void RTC_set_Data(RTC * RTC_Now,unsigned char H12OrH24,unsigned char AMOrPM)
{
	TWI_start();
	TWI_send_address(0b01101000,Write);

	TWI_send_data(Sec_Ad);                            //initialize the rtc pointer with the seconds address
	RTC_Now->sec&=0x7F;


	TWI_send_data(RTC_int_to_BCD(RTC_Now->sec));

	TWI_send_data(RTC_int_to_BCD(RTC_Now->min));

	RTC_Send_Hours(H12OrH24, AMOrPM,RTC_Now->hours);

	TWI_send_data(RTC_int_to_BCD(RTC_Now->day));

	TWI_send_data(RTC_int_to_BCD(RTC_Now->date));

	TWI_send_data(RTC_int_to_BCD(RTC_Now->mon));

	TWI_send_data(RTC_int_to_BCD(RTC_Now->year));
	TWI_stop();
	_delay_ms(1);
}
/*  when we want to get data from RTC first we have to give it the address of the data we want to start from
 * then the RTC address pointer will increment automatic
 *
 */
RTC RTC_get_Data(unsigned char *hour_mode , unsigned char *AM_PM)
{
	RTC RTC_time;
	unsigned char Garabge =0;
	RTC_time.control=0;
	TWI_start();
	_delay_ms(1);
	TWI_send_address(0b01101000,Write);
	_delay_ms(1);
	TWI_send_data(Sec_Ad);      // initialize  the RTC pointer
	_delay_ms(1);
	TWI_stop();
	_delay_ms(1);
	TWI_start();
	_delay_ms(1);
	TWI_send_address(0b01101000,Read);
	_delay_ms(1);
	Garabge=TWI_receive_data_ACK();
	_delay_ms(1);
	RTC_time.sec=BcdToDecConvert(TWI_receive_data_ACK());
	_delay_ms(1);
	RTC_time.min=BcdToDecConvert(TWI_receive_data_ACK());
	_delay_ms(1);
	RTC_time.hours=TWI_receive_data_ACK();
	_delay_ms(1);
	RTC_time.day=BcdToDecConvert(TWI_receive_data_ACK());
	_delay_ms(1);
	RTC_time.date=BcdToDecConvert(TWI_receive_data_ACK());
	_delay_ms(1);
	RTC_time.mon=BcdToDecConvert(TWI_receive_data_ACK());
	_delay_ms(1);
	RTC_time.year=BcdToDecConvert(TWI_receive_data_NACK());
	_delay_ms(1);
	TWI_stop();
    _delay_ms(1);

    ////adjust hours///////
    if(RTC_time.hours&(1<<6)) // if 12-h system
    {
           *hour_mode=H12;
    	if(RTC_time.hours&(1<<5)) // PM
    	{
    		RTC_time.hours&=0x1F;
               *AM_PM=PM;
    	}
    	else                      //AM
    	{
    		RTC_time.hours&=0x1F;
    		*AM_PM=AM;
    	}
    }
    else
    {
    	 *hour_mode=H24;
    }

   RTC_time.hours= BcdToDecConvert(RTC_time.hours);


	return RTC_time;


}
void RTC_Start(unsigned char ReadOrWrite)   //send start bit and the determine the mood (writing or reading) data
{
	TWI_start();
	TWI_send_address(0b01101000,ReadOrWrite);  //send address of the slave(RTC) with write or Read bit
}
/*send the address of the first the byte to start with from the RTC data (0x00to 0x07)
   OR send Data to RTC to set it */
void RTC_Send_Data(unsigned char data )
{
	TWI_send_data(RTC_int_to_BCD(data));
}
void RTC_Send_Hours(unsigned char H12OrH24, unsigned char AMOrPM,unsigned char data )
{
	data = RTC_int_to_BCD(data);
	if(H12OrH24 == H12)
	{
		if(AMOrPM==AM)
		{
			data|=(1<<6);
		}
		else if(AMOrPM ==PM)
		{
			data|=(1<<5)|(1<<6);
		}
		TWI_send_data(data);
	}
	else if(H12OrH24 == H24)
	{
		TWI_send_data(data);
	}
}
void RTC_Stop(void)
{
	TWI_stop();
}
unsigned char RTC_Receive_Data(void)
{
	unsigned char data =0;

	data=TWI_receive_data_ACK();
	return data ;
}
unsigned char RTC_int_to_BCD(unsigned char integer)
{
	unsigned char x=0;
	x=integer%10;
	integer/=10;
	integer=(integer<<4)|x;
	return integer;

	//	return integer + 6 * (integer / 10);
}
unsigned char BcdToDecConvert(unsigned char val)
{
	return val - 6 * (val >> 4);
}
