#include "DHT11.h"
#include "timing.h"
#include "LCD.h"

void readDHT11()
{
	bit state = 0;
	unsigned char i, MAXTIMING;
	unsigned char count;
	unsigned char store[5];
	
	//a = 0;	//debug
	DHT11 = 1;	//Reset to high
	
	for(i = 0; i < 6; i++)
		ms_delay(250);	//1 second delay for device to re-test.
	
	//CHECK IF DEVICE ON
	while(DHT11 == 0)
	{
		if(MAXTIMING > 20)
		{
			write_string("DEVICE NOT CONNE\nCTED/ON\n");
			return;
		}
		MAXTIMING++;
		us_delay(0);
	}
	
	MAXTIMING = 0;
	
	//SEND INITAL SIGNAL
	DHT11 = 0;
	ms_delay(20);	//delay 20ms
	DHT11 = 1;
	//DHT11 = 0;	
	//a = 1;	//debug
	//us_delay(10);	//Let DHT11 know that pin was pulled high before setting to input.
	while(DHT11 == 1);
	while(DHT11 == 0);
	while(DHT11 == 1);
	
	/*
	
	//CONFIRMATION SIGNAL CHECKING
	for(i = 0; i < 3; i++)	//Check for when DHT11 is LOW, confirmation signal.
	{
		while(DHT11 == state)
		{
			
			MAXTIMING++;
			if(MAXTIMING > 160)	//DHT11 should go up after 54us (low) + 80us (high)
			{
				write_string("ERROR\nCONFIRMATION SIGNAL\n");
				return;
			}
			
			//us_delay(1);
		}
		state = ~state;
		//us_delay(8);
	}
	//a = 0;	//debug
	
	MAXTIMING = 0;
	*/
	//READ DATA
	for(i = 0; i < 40; i++)
	{
		while(DHT11 == 0)	//Loop to skip when pin is pulled low.
		{
			/*
			MAXTIMING++;
			if(MAXTIMING > 128)
			{
				write_string("READING DATA LOW\n");
				return;
			}	*/
			//us_delay(0);
		}
		
		//MAXTIMING = 0;
		a = 0;
		
		while(DHT11 == 1)	//Count number of microseconds pin is high. If 70 microseconds
		{									//bit is 1, lower is 0.
			count++;
			
			//MAXTIMING++;
			
			//if(MAXTIMING > 250)
			//{
				//write_string("READING DATA HIGH\n");
				//return;
			//}
			
			//us_delay(0);
		}
		//us_delay(0);
		a = 1;
		//write_int(count);
		//write_char(' ');
		if(count < 50)//DHT11 == 1)	//if 1
		{
			store[i/8] |= 1;	//Push 0
		}
		else
		{
			store[i/8] <<= 1;	//Set least sig bit to 0
		}
		//count = 0;
	}
	
	if(1)	//validate(store) == 
	{
		for(i = 0; i < 5; i++)
		{
			write_char(' ');
			//write_int(store[i]);
		}
	}
	else
	{
			//ms_delay();
		//readDHT11();
		//new_line();
		for(i = 0; i < 5; i++)
		{
			write_char(' ');
			write_int(store[i]);
		}
	}
	new_line();
}


void bin_to_int(unsigned char *array)
{
	unsigned char num = 8, rem, decimal, base = 1, i;
	
	for(i = 0; i < 5; i++)
	{	//add another loop to go through all 8 bits
		num = 8, rem = 0, decimal = 0, base = 1;
		while(array[i] != '\0')
		{
			if(array[i] == 1)
				decimal *= 2 + 1;
			else
				decimal *= 2;
			
			//rem = num % 10;
			//array[i] += rem * base;
			//base *= 2;
			//num /= 10;
		}
		array[i] = decimal;
	}
}

char validate(unsigned char store[])
{
	if((store[0] + store[2]) != store[4])
	{
		//write_string("CHECKSUM, ERROR!\n");
		return -1;
	}
	else
		return 1;
}