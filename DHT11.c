#include "DHT11.h"
#include "timing.h"
#include "LCD.h"

void readDHT11()
{
	unsigned char i, MAXTIMING;
	unsigned char count;
	unsigned char store[5] = {0, 0, 0, 0, 0};
	
	ms_delay();	//1 second delay for device to re-test.
	
	DHT11 = 0;
	ms_delay();	//delay 18ms
	DHT11 = 1;
	
	us_delay();	//Let DHT11 know that pin was pulled high before setting to input.
	
	DHT11 = 0;
	
	for(i = 0; i < 2; i++)	//Check for when DHT11 is LOW, confirmation signal.
	{
		while(DHT11 == 0)
		{
			MAXTIMING++;
			if(MAXTIMING > 128)
				break;
			us_delay();
		}
		us_delay();
	}
	MAXTIMING = 0;
	
	for(i = 0; i < 40; i++)
	{
		while(DHT11 == 0)	//Loop to skip when pin is pulled low.
		{
			MAXTIMING++;
			if(MAXTIMING > 128)
				break;
			us_delay();
		}
		
		MAXTIMING = 0;
		
		while(DHT11 == 1)	//Count number of microseconds pin is high. If 70 microseconds
		{									//bit is 1, lower is 0.
			count++;
			
			MAXTIMING++;
			if(MAXTIMING > 128)
				break;
			us_delay();
		}
		
		
		if(count > 40)
		{
			store[i/8] <<= 1;	//Since integer division rounds down. Can split 40 data into 5 8-bit segments.
		}
		else
		{
			store[i/8] |= 1;
		}
		count = 0;
	}
	
	if(validate(store) == 1)
	{
		for(i = 0; i < 5; i++)
			write_int(store[i]);
	}
	else
	{
			ms_delay();
			readDHT11();
	}
}

char validate(unsigned char store[])
{
	if((store[0] + store[2]) != store[4])
	{
		write_string("CHECKSUM, ERROR!\n");
		return -1;
	}
	else
		return 1;
}