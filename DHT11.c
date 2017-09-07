#include "DHT11.h"
#include "timing.h"
#include "i2c.h"

char* readDHT11()
{
	unsigned char i;
	unsigned char store[4];//, arr[2];
	
	//for(i = 0; i < 8; i++)
		//ms_delay(250);	//2 second delay for device to re-test.
	
	//START TIMER TO PROTECT AGAINST GETTING STUCK.
	//timer2();
	
	//SEND INITAL SIGNAL
	DHT11 = 0;
	ms_delay(20);	//delay 20ms
	DHT11 = 1;

	//Skip DHT11 confirmation transistion
	while(DHT11 == 1);
	while(DHT11 == 0);
	while(DHT11 == 1);

	//READ DATA
	for(i = 0; i < 40; i++)
	{
		store[i/8] <<= 1;	//Push value to the right by 1 bit
		while(DHT11 == 0);	//Loop to skip when pin is pulled low.
	
<<<<<<< HEAD
		us_delay(1);	//30us delay maybe 
=======
		us_delay();	//30us delay maybe 
>>>>>>> ds3231
		
		if(DHT11 == 1)
		{
			SCL = 1;
			store[i/8] |= 1;	//Switch least sig bit to 1
			SCL = 0;
			
			while(DHT11 == 1);	//TO sync back to DHT11
		}
	}
	
	if(store[0] + store[2] == store[4])	//Validate the recieved values checksum
	{
		//arr[0] = store[0];
		//arr[1] = store[2];
		/*
		write_int(store[0]);
		write_char('%');
		
		write_char(' ');
	 	
		write_int(store[2]);
		write_char(LCD_DEGREE);
		*/
		//write_char('C');
		
		return store;
	}
	else
	{
		//FIX
		return -1;
	}
}