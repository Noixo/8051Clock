#include "DHT11.h"
#include "timing.h"

char *readDHT11()
{
	unsigned char i;
	static unsigned char store[5];
	
	//SEND INITAL SIGNAL
	DHT11 = 0;
	ms_delay(20);	//delay 20ms
	DHT11 = 1;
	
	while(DHT11 == 1);
	while(DHT11 == 0);
	while(DHT11 == 1);

	//READ DATA
	for(i = 0; i < 40; i++)
	{
		store[i/8] <<= 1;	//Push value to the right by 1 bit

		while(DHT11 == 0);	//Loop to skip when pin is pulled low.
			
		//approx 30us?
		dht11Delay();

		store[i/8] |= DHT11;	//Switch least sig bit to 1
		//loop to sync back up to logic high
		while(DHT11 == 1);
	}
	
	if(store[0] + store[2] == store[4])	//Validate the recieved values checksum
	{
		return store;
	}
	
	//return -1 if failed idk if this works
	return -1;
}