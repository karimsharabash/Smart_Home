/*
 * my_ADC.h
 *
 *  Created on: 1/2/2018
 *      Author: karim sharabash
 */

#ifndef MY_ADC_H_
#define MY_ADC_H_

void ADC_Init();
unsigned int ADC_Read(unsigned char channel,float Vref );

#endif /* MY_ADC_H_ */
