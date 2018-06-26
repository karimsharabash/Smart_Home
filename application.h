/*
 * application.h
 *
 *  Created on: 12/3/2018
 *      Author: karim sharabash
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_
#include <avr/io.h>
#include <avr/interrupt.h>
//////////////////////////
#include "../HAL/Ultrasonic.h"
#include "../HAL/DC_Motor.h"
#include "../HAL/Led.h"
#include "../HAL/Vibration_sensor.h"
#include "../HAL/my_lcd.h"
#include "../HAL/Switchs.h"
#include "../HAL/Light_sensor.h"
#include "../HAL/Motion_Detection.h"
#include "../HAL/RTC.h"
#include "../HAL/Smoke_detector.h"
#include "../MCAL/UART_INT.h"

///////////////////////
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
////////////////////////

EventGroupHandle_t egSmartHome;

#define US_pinflag     (1<<0)
#define CloseGarage    (1<<1)
#define Garage_open    (1<<2)
#define Open_Door      (1<<3)
#define Close_Door     (1<<4)
#define security_flag  (1<<5)
#define security_alarm (1<<6)
#define LCD_not_busy   (1<<7)

EventBits_t ebSHValues;

EventGroupHandle_t egShInterior;

#define   LightSensor (1<<0)
#define   MotionDect  (1<<1)
#define RTC_writting  (1<<2)    //RTC write on lcd
#define RTC_reading   (1<<3)   //MCU can read from RTC
#define fire_flag     (1<<4)   //flag raised when smoke is detected
#define fire_alarm    (1<<5)   //there is already fire alaraming in the place
#define MSG_falg      (1<<6)   // there is a msg from bluetooth came
EventBits_t ebIntvalues;

void T_Garage_US(void* pvData);
void T_Garage_Motor(void* pvData);
void T_Door_SW(void* pvData);
void T_Door_Motor(void* pvData);
void T_Security_check(void* pvData);
void T_security_alarm(void* pvData);
void T_lightSys(void* pvData);
void T_LightControl(void* pvData);
void T_RTC(void* pvData);
void T_LCD(void* pvData);
//void T_Fire_check(void* pvData);
//void T_Fire_alarm(void* pvData);
//void T_Bluetooth(void* pvData);
void system_init(void);

RTC Now;
unsigned char HourMode;
unsigned char AM_PM;
////////////bluetooth msgs////////
#define blight_on 'o'
#define blight_off 'f'
#define bstop_secuirty_alaram 's'
#define bclose_garage 'c'
#define bopen_door 'd'
#endif /* APPLICATION_H_ */
