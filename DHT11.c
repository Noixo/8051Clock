#include "DHT11.h"
#include "timing.h"
#include "LCD.h"

void readDHT11()
{
	char i, MAXTIMING;
	char count;
	char store[5] = {0, 0, 0, 0, 0};
	
	//write_string(store);
	//store = {'50','25'};
	//return; //store;

	DHT11 = 0;
	ms_delay(18);	//delay 18ms
	DHT11 = 1;
	
	us_delay(20);
	
	for(i = 0; i < 40; i++)
	{
		while(DHT11 == 0)
		{
			MAXTIMING++;
			us_delay(1);
			if(MAXTIMING > 128)
				break;
		}
		MAXTIMINGS = 0;
		while(DHT11 == 1)
		{
			count++;
			us_delay(1);
			
			MAXTIMINGS++;
			if(MAXTIMING > 128)
				break;
		}
		if(count > 40)
		{
			store[i/8] = 1;
		}
		else
		{
			store[i/8] = 0;
		}
		count = 0;
	}
	
	if(validate(store) == 1)
	{
		store[0] = int_to_ascii(store[0]);
		write_char(store[0]);
		//write_char('\n');
		write_char(store[2]);
	}
	else
	{
		//idk, redo?-*
	}
}

char validate(char store[])
{
	if((store[0] + store[2]) != store[4])
		return -1;
	else
		return 1;
}