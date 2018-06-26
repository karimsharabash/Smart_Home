/*
 * application.c
 *
 *  Created on: 12/3/2018
 *      Author: karim sharabash
 */

#include "application.h"
volatile unsigned short int Distance;
volatile unsigned char Recieved_MSG=0;

/*ISR(USART_RXC_vect)  //to recieve the byte from the bluetooth
{
	Recieved_MSG=UDR;
	xEventGroupSetBits(egShInterior,MSG_falg);
}*/

 ISR(INT1_vect)  //hardware interrupt to recieve the coming echo pulse from ultrasonic pulses and calculate the distance in cm s
{
	unsigned char counter=0;
	double Distance_Cm=0;


		if(Read_Pin(D,3))
		{
			Timer2_start();
		}
		else
		{
			counter=0;
			Timer2_stop();
			counter =Timer2_read();
			Distance_Cm=((counter*128)/58.4);      //the distance in cm
			/*cast the result and put it in 16 bit variable
			 * -1 because the body of the senso r take 1 Cm  */
			Distance=(short int)(Distance_Cm -1);
			Timer2_clear();
		}

}

ISR(TIMER2_COMP_vect)         //if the echo pulse exceeded the range >25ms then raise the flag and restart the counter
{
	Timer2_stop();
	Timer2_clear();
}
/* void T_Fire_check(void* pvData)
{
	while(1)
	{
		if(Smoke_Dect_read())
		{
			xEventGroupSetBits(egShInterior,fire_flag);
		}
		else
		{


			xEventGroupSetBits(egSmartHome,LCD_not_busy);
			xEventGroupSetBits(egShInterior,RTC_reading);  //rtc is free to work now
			xEventGroupClearBits(egShInterior,RTC_writting); //lcd wait the rtc to get the reading first
			xEventGroupClearBits(egShInterior,fire_flag);

		}
		vTaskDelay(200);
	}
}
void T_Fire_alarm(void* pvData)
{
	while(1)
	{
		ebIntvalues=xEventGroupWaitBits(egShInterior,fire_flag,0,0,5000);
		if(ebIntvalues&fire_flag)
		{
			Led_toggle(Fire_alarm_light);
			LCD_clear_screen();
			LCD_goto_loaction(0,0);
			LCD_write_string("Fire Alarm");
			vTaskDelay(100);
		}
		else
		{

			Led_off(Fire_alarm_light);
			LCD_clear_screen();
		}
	}
} */


/* void T_Bluetooth(void* pvData)
{
	while(1)
	{
		ebIntvalues=xEventGroupWaitBits(egShInterior,MSG_falg,1,0,0xFFFF);
		if(ebIntvalues&MSG_falg)
		{
			if(Recieved_MSG==blight_on)
			{
				Led_toggle(normal_light);

				vTaskDelay(100);
			}
			else if(Recieved_MSG==blight_off)
			{
				Led_off(normal_light);
			}
			else if (Recieved_MSG==bstop_secuirty_alaram)
			{
				xEventGroupClearBits(egSmartHome,security_alarm);  //so check for the vibration sensor not the sw that stop the alarm
				xEventGroupClearBits(egSmartHome,security_flag);   //stop the alram
				xEventGroupSetBits(egSmartHome,LCD_not_busy);
				xEventGroupSetBits(egShInterior,RTC_reading);  //rtc is free to work now
				xEventGroupClearBits(egShInterior,RTC_writting); //lcd wait the rtc to get the reading first
			}
			else if(Recieved_MSG==bclose_garage)
			{
				xEventGroupSetBits(egSmartHome,CloseGarage);
			}
			else if(Recieved_MSG==bopen_door)
			{
				xEventGroupSetBits(egSmartHome,Open_Door);
			}
		}
	}
} */

void T_Garage_US(void* pvData)
{

	while(1)
	{
		ebSHValues=xEventGroupWaitBits(egSmartHome,Garage_open,0,0,200);
		vTaskDelay(2);             // to take a look on the other tasks when the garage is open
		if(ebSHValues&Garage_open)  // if the garage is already open scan for the closing switch
		{
			if(Switch_Read(Garage_sw_pin))
			{
				xEventGroupSetBits(egSmartHome,CloseGarage);
				while(Switch_Read(Garage_sw_pin));
			}

		}
		else                       // if the garage is closed scan for the ultrasonic reading
		{
			Ultrasonic_Read();
			vTaskDelay(20);
			if(Distance<50)
			{

				xEventGroupSetBits(egSmartHome,US_pinflag);
			}
		}
		vTaskDelay(2);
	}
}
void T_Garage_Motor(void* pvData)
{
	while(1)
	{
		ebSHValues=xEventGroupWaitBits(egSmartHome,(US_pinflag|CloseGarage),1,0,0xFFFF);
		if(ebSHValues&US_pinflag)      // if the ultrasonic sensor detected a thing in a ragne of (100 m)
		{
			DC_motor_turn_right();      // open the garage
			xEventGroupSetBits(egSmartHome,Garage_open);  //raise the flag (garage is open )
			vTaskDelay(2000);
			DC_motor_stop();           //keep the garage open (till the user press the closing switch
		}
		else if(ebSHValues&CloseGarage)     // if the user press th closing sw
		{
			DC_motor_turn_left();         //close the garage


			vTaskDelay(2000);
			DC_motor_stop();
			xEventGroupClearBits(egSmartHome,Garage_open); //clear the flag ( garage is closed )
		}

	}
}
void T_Door_SW(void* pvData)
{
	while(1)
	{

		if(Switch_Read(Door_sw_Pin))
		{
			xEventGroupSetBits(egSmartHome,Open_Door);
			while(Switch_Read(Door_sw_Pin));
		}
		vTaskDelay(1);
	}
}
void T_Door_Motor(void* pvData)
{

	unsigned char i=0;
	while(1)
	{
		ebSHValues=xEventGroupWaitBits(egSmartHome,Open_Door,1,0,0xFFFF);
		if(ebSHValues&Open_Door)
		{
			/*	OCR1A=175;
            vTaskDelay(1000);
			OCR1A=65;  */
			for(i=0;i<5;i++)
			{
				Set_Pin(D,5);
				vTaskDelay(1);
				Clear_Pin(D,5);
				vTaskDelay(20);
			}

			vTaskDelay(2000);
			for(i=0;i<5;i++)
			{
				Set_Pin(D,5);
				vTaskDelay(2);
				Clear_Pin(D,5);
				vTaskDelay(19);
			}

		}
	}
}


void T_Security_check(void* pvData)
{
	while(1)
	{
		ebSHValues=xEventGroupWaitBits(egSmartHome,security_alarm,0,0,200);
		if((ebSHValues&security_alarm)==0)
		{
			if(Vibration_Sensor_Read())
			{
				xEventGroupSetBits(egSmartHome,security_flag); //raise the security flag
				xEventGroupClearBits(egSmartHome,LCD_not_busy);  //the lcd is busy now
			}
		}
		else   /* if the sw pressed or msg came from the mobile clear the secuiry flag */
		{
			if (Switch_Read(security_sw_Pin))
			{
				xEventGroupClearBits(egSmartHome,security_alarm);
				xEventGroupClearBits(egSmartHome,security_flag);
				xEventGroupSetBits(egSmartHome,LCD_not_busy);
				xEventGroupSetBits(egShInterior,RTC_reading);  //rtc is free to work now
				xEventGroupClearBits(egShInterior,RTC_writting); //lcd wait the rtc to get the reading first
				while(Switch_Read(security_sw_Pin));
			}
		}
	}
}
void T_security_alarm(void* pvData)
{
	while(1)
	{

		ebSHValues=xEventGroupWaitBits(egSmartHome,security_flag,0,0,1000);
		if(ebSHValues&security_flag)
		{
			xEventGroupSetBits(egSmartHome,security_alarm);

			LCD_clear_screen();
			LCD_goto_loaction(0,0);
			LCD_write_string("alaram");

			Led_toggle(secuirty_alarm_light);

			vTaskDelay(100);


		}
		else
		{
			Led_off(secuirty_alarm_light);

		}
	}
}

void T_LightControl(void* pvData)
{

	while(1)
	{
		if(!(Light_Sensor_Read()))  //if there is no light
		{
			xEventGroupSetBits(egShInterior,LightSensor);
		}
		if(Motion_Dect_read())   // if there  is a person in the place
		{
			xEventGroupSetBits(egShInterior,MotionDect);
			while(Motion_Dect_read());           // because i'm using switch
		}
		vTaskDelay(1);
	}
}
void T_lightSys(void* pvData)
{
	while(1)
	{
		//wait for PIR and LDR sensor if there's light and there is a person in the place then turn on the light
		//  and make a periodic check every 5 sec if one condition is not true turn off the lamp

		ebIntvalues=xEventGroupWaitBits(egShInterior,(LightSensor|MotionDect),1,1,4000); //auto clear , wait for all , time our = 5sec
		if((ebIntvalues&(LightSensor|MotionDect))==(LightSensor|MotionDect))
		{
			Led_on(normal_light);
		}
		else
		{
			Led_off(normal_light);
		}
	}
}

void T_RTC(void* pvData)
{


	while(1)
	{

		ebIntvalues=xEventGroupWaitBits(egShInterior,RTC_reading,1,0,0xFFFF);  //wait until the lcd display the pervious data
		if(ebIntvalues&RTC_reading)
		{
			Now=RTC_get_Data(&HourMode,&AM_PM);
			vTaskDelay(600);
			xEventGroupSetBits(egShInterior,RTC_writting);

		}
	}
}
void T_LCD(void* pvData)
{
	char arr[3]={0},arr1[3]={0},arr2[3]={0},arr3[3]={0},arr4[3]={0},arr5[3];
	while(1)
	{
		ebSHValues =xEventGroupWaitBits(egSmartHome,LCD_not_busy,0,0,0xFFFF); //wait until the lcd become not busy
		if(ebSHValues&LCD_not_busy)  //if the lcd not busy with the alaram
		{
			ebIntvalues=xEventGroupWaitBits(egShInterior,RTC_writting,1,0,0xFFFF);
			if(ebIntvalues&RTC_writting)
			{
				LCD_clear_screen();
				LCD_goto_loaction(0,0);
				LCD_IntToString(Now.hours,arr);
				LCD_write_string(arr);
				////////////////////////////////
				LCD_Write_Data(':');

				///////////////////////////
				LCD_goto_loaction(0,3);

				if (Now.min==0){
					LCD_write_string("  ");
				}
				else
				{
					LCD_IntToString(Now.min,arr1);
					LCD_write_string(arr1);
				}
				////////////////////////////////
				LCD_Write_Data(':');

				///////////////////////////

				LCD_goto_loaction(0,6);
				if (Now.sec==0){
					LCD_write_string("  ");
				}
				else
				{
					LCD_IntToString(Now.sec,arr2);
					LCD_write_string(arr2);
				}
				////////////////////////////////
				LCD_goto_loaction(0,8);

				if(HourMode)
				{
					if(AM_PM)
					{
						LCD_write_string("PM");
					}
					else
						LCD_write_string("AM");
				}
				else
					LCD_write_string("  ");

				///////////////////////////
				LCD_goto_loaction(1,0);
				LCD_IntToString(Now.date,arr3);
				LCD_write_string(arr3);
				////////////////////////////////
				LCD_Write_Data('/');

				///////////////////////////
				LCD_goto_loaction(1,3);
				LCD_IntToString(Now.mon,arr4);
				LCD_write_string(arr4);
				////////////////////////////////
				LCD_Write_Data('/');
				///////////////////////////
				LCD_goto_loaction(1,6);
				LCD_IntToString(Now.year,arr5);
				LCD_write_string(arr5);


				xEventGroupSetBits(egShInterior,RTC_reading);
				vTaskDelay(10);

			}
		}
	}
}
void system_init(void)
{
	LCD_Init();
	sei();
	Ultrasonic_Init();
	DC_motor_Init();
	Switch_Init();
	DDRD|=(1<<5); //for the servo motor
	Vibration_Sensor_Init();
	Led_Init();

	Light_Sensor_Init();
	Motion_Dect_Init();
	RTC_Init();
//	Smoke_Dect_Init();
//	Uart_init(9600);

	RTC set_RTC;
	set_RTC.sec=0;
	set_RTC.min=45;
	set_RTC.hours=4;
	set_RTC.day=5;
	set_RTC.date=28;
	set_RTC.mon=2;
	set_RTC.year=18;
	RTC_set_Data(&set_RTC,H12,PM);
}


