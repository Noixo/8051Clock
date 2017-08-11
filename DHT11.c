#include "DHT11.h"
#include "timing.h"

char *readDHT11()
{
	char i;
	char count;
	char *store;
	
	store = (50,25);
	return store;
	
	DHT11 = 0;
	ms_delay(18);	//delay 18ms
	DHT11 = 1;
	
	us_delay(20);
	
	for(i = 0; i < 40; i++)
	{
		while(DHT11 == 0)
		{
		}
		while(DHT11 == 1)
		{
			count++;
			us_delay(1);
		}
		if(count > 40)
		{
			store[i] <<= 1;
		}
		else
		{
			store[i] <<= 0;
		}
		count = 0;
	}
	return store;
	//validate(store);
}

/*char validate(char store[])
{
	char i;
	
	return -1;
}*/