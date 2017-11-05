#include "DHT11.h"
#include "timing.h"

char* readDHT11()
{
	unsigned char i;
	unsigned char store[4];//, arr[2];
	
	//for(i = 0; i < 8; i++)
		//ms_delay(250);	//2 second delay for device to re-test.
	
	//START TIMER TO PROTECT AGAINST GETTING STUCK.
	//dhtInterrupt1();
	
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
		
		dhtTimer();	//30us delay maybe 
		
		store[i/8] |= DHT11;	//Switch least sig bit to 1
		while(DHT11 == 1);
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
		write_char(0);
		
		//write_char('C');
		*/
		return store;
	}
	//return -1 if failed
	return -1;
}