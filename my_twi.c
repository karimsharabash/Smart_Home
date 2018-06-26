/*
 * TWI driver
 *
 *  Created on:  21/1/2018
 *      Author: karim
 *
 *
*/


#include "my_twi.h"
#include  <util/delay.h>
void TWI_init(unsigned char my_address)
{

#if TWI_SPEED == 100
	TWBR=32;   // to set the speed 100kb/s

#elif TWI_SPEED == 400
	TWBR=2;   // to set the Speed 400khz
#endif

	TWSR=0; //twsp0 and twsp1 ==0 for prescaler 1:1

	TWCR=(1<<TWEA)|(1<<TWEN); //enable twi and enable ack maybe this mcu will be slave it won't now when it called

	TWAR=((my_address<<1)&(0xfe)); // the LSB for the group call( broadcasting ) make sure it will be 0 if you don't want it

}


void TWI_start(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // clear the flag send start and enable twi
   //check for the flag and start or repeated start
	  while((!(TWCR&(1<<TWINT)))||((((TWSR&0xF8)!=0x08))&&(((TWSR&0xF8)!=0x10))));

}


void TWI_send_address(unsigned char address , char ReadorWrite)
{
	 TWDR=((address<<1)|(ReadorWrite));
	 if(ReadorWrite==Write)
	 {
		 TWCR=(1<<TWINT)|(1<<TWEN);
	 }
	 else
	 {
		 TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	 }


//check for the flag and address+r or address+w send
 while((!(TWCR&(1<<TWINT)))||((((TWSR&0xF8)!=0x18))&&(((TWSR&0xF8)!=0x40))));

}

void TWI_send_data(unsigned char data)
{
	  TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
  //check for the data send and ack received for the master and slave
     while((!(TWCR&(1<<TWINT)))||((((TWSR&0xF8)!=0x28))&&(((TWSR&0xF8)!=0xB8))));


}
void TWI_check_slave_Tx(void)
{
	while((TWSR&0xf8)!=0xA8); //check if the address+r received by the slave and ack send
}

unsigned char TWI_receive_data_ACK(void)
{

	/* wait the flag and any event from these events to happen (data received by the slave and ack send or
	  data received by the master and ack send or slave address received and ack send  or address +r send)    */
	 while(  ( !(TWCR&(1<<TWINT)) )||( (((TWSR&0xf8)!=0x80))&&(((TWSR&0xf8)!=0x50))&&((TWSR&0xf8)!=0x60)&&((TWSR&0xf8)!=0x40) )  );

  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);

  return TWDR;

}

unsigned char TWI_receive_data_NACK(void)
{
	/* wait the flag and any event from these events to happen (data received by the slave and ack send or
	  data received by the master and ack send or slave address received and ack send  or address +r send)
	  and also all these cases without ACK
	  */
	 while(  ( !(TWCR&(1<<TWINT)) )||( (((TWSR&0xf8)!=0x58))&&(((TWSR&0xf8)!=0x88))&&(((TWSR&0xf8)!=0x50))&&((TWSR&0xf8)!=0x80)&&((TWSR&0xf8)!=0x60)&&((TWSR&0xf8)!=0x40)&&((TWSR&0xf8)!=0x48)) )  ;

	 //while (!(TWCR&(1<<TWINT)));
  TWCR=(1<<TWINT)|(1<<TWEN);

  return TWDR;

}


void TWI_stop(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	_delay_ms(1);
}
