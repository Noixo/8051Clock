#include "DHT11.h"
#include "timing.h"

#include "i2c.h"
/*
unsigned char *readDHT11()
{
	//start timer here
	
	//start DHT11 reading
	return startDHT11();
}
*/

unsigned char timeout = 0;

#define TIMEOUTNUM 30
/*
void DHT11Timeout() interrupt 3
{
	timeout++;
	//restart timer
	dhtInterrupt();
}
*/

char *readDHT11()
{
	unsigned char i;
	static unsigned char store[5];
	
	//SEND INITAL SIGNAL
	DHT11 = 0;
	ms_delay(20);	//delay 20ms
	DHT11 = 1;

	//start timer to prevent getting stuck
	//dhtInterrupt();
	
	//Skip DHT11 confirmation transistion
	//SDA = 0;
	//dht11Delay();
	//for(i = TIMEOUTNUM; i > 0; i--);
	//SDA = 1;
	while(DHT11 == 1);
	//{
		//if(timout == TIMEOUTNUM)
		//	return 0;
	//}
	//for(i = TIMEOUTNUM; i >= 0; i--);
	while(DHT11 == 0);
	//{
		//if(timeout == TIMEOUTNUM)
		//	return 0;
	//}
	//for(i = TIMEOUTNUM; i >= 0; i--);
	while(DHT11 == 1);
	//{
	//	if(timeout == TIMEOUTNUM)
	//		return 0;
	//}

	//READ DATA
	for(i = 0; i < 40; i++)
	{
		store[i/8] <<= 1;	//Push value to the right by 1 bit

		while(DHT11 == 0);	//Loop to skip when pin is pulled low.
		//{
			//if(timeout == TIMEOUTNUM)
			//	return 0;
		//}
			
		//approx 40us
		dht11Delay();

		store[i/8] |= DHT11;	//Switch least sig bit to 1
		//loop to sync back up to logic high
		while(DHT11 == 1);
		//{
			//if(timeout == TIMEOUTNUM)
			//	return 0;
	//	}
	}
	
	if(store[0] + store[2] == store[4])	//Validate the recieved values checksum
	{
		return store;
	}
	
	//return -1 if failed idk if this works
	return -1;
}