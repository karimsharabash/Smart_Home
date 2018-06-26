/*
 * RTC.h
 *
 *  Created on: 21/2/2018
 *      Author: Karim sharabash
 */

#ifndef RTC_H_
#define RTC_H_
#define Sec_Ad   0x00
#define Min_Ad   0x01
#define Hour_Ad  0x02
#define Day_Ad   0x03
#define Date_Ad  0x04
#define Mon_Ad   0x05
#define Year_A   0x06
#define Ctrl_Ad  0x07
#define H12      1    //12 - h sys
#define H24      0    //24 - h sys
#define AM       0
#define PM       1
typedef struct rtc
{
	unsigned char sec;
	unsigned char min;
	unsigned char hours;
	unsigned char day;
	unsigned char date;
	unsigned char mon;
	unsigned char year;
	unsigned char control;
}RTC


;

#include "../MCAL/my_twi.h"
#include <util/delay.h>
unsigned char RTC_int_to_BCD(unsigned char);
 unsigned char BcdToDecConvert(unsigned char val);
 void RTC_set_Data(RTC * RTC_Now,unsigned char H12OrH24,unsigned char AMOrPM);
 RTC RTC_get_Data(unsigned char *hour_mode , unsigned char* AM_PM);
 void RTC_Init(void);
void RTC_Start(unsigned char  ReadOrWrite);

 void RTC_Send_Data(unsigned char data );
 void RTC_Send_Hours(unsigned char H12OrH24, unsigned char AMOrBM,unsigned char data );
 void RTC_Stop(void);
 unsigned char RTC_Receive_Data(void);



#endif /* RTC_H_ */
