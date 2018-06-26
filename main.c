/*
 * main.c
 *
 *  Created on: 12/3/2018
 *      Author: karim sharabash
 */


#include "application.h"



int main(void)
{
	/*  system init. (pheriphal)*/
	system_init();
	/* OS service create and init */
	egSmartHome= xEventGroupCreate();
	egShInterior= xEventGroupCreate();
	/* Task create */
	xTaskCreate(T_Garage_US,NULL,70,NULL,3,NULL);
	xTaskCreate(T_Garage_Motor,NULL,70,NULL,7,NULL);
	xTaskCreate(T_Door_SW,NULL,70,NULL,1,NULL);
	xTaskCreate(T_Door_Motor,NULL,70,NULL,9,NULL);
	xTaskCreate(T_Security_check,NULL,70,NULL,4,NULL);
	xTaskCreate(T_security_alarm,NULL,70,NULL,10,NULL);
	xTaskCreate(T_LightControl,NULL,85,NULL,2,NULL);
	xTaskCreate(T_lightSys,NULL,85,NULL,6,NULL);
	xTaskCreate(T_RTC,NULL,85,NULL,5,NULL);
	xTaskCreate(T_LCD,NULL,100,NULL,8,NULL);
//	xTaskCreate(T_Fire_check,NULL,85,NULL,4,NULL);
//	xTaskCreate(T_Fire_alarm,NULL,85,NULL,11,NULL);
 // xTaskCreate(T_Bluetooth,NULL,85,NULL,13,NULL);
	/////////////////////////////////////
	xEventGroupSetBits(egShInterior,RTC_reading);  //to give the rtc opportunity to get the first readings
	xEventGroupSetBits(egSmartHome,LCD_not_busy);  //the lcd at the beginning is not busy so the rtc is free to take reading and lcd display it
	/* start OS or scheduler */
	vTaskStartScheduler();
	return 0;
}


