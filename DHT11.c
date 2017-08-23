#include "DHT11.h"
#include "timing.h"
#include "LCD.h"

void readDHT11()
{
	unsigned char i;
	unsigned char store[5];
	
	for(i = 0; i < 8; i++)
		ms_delay(250);	//2 second delay for device to re-test.
	
	//START TIMER TO PROTECT AGAINST STUCK.
	
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
		while(DHT11 == 0);	//Loop to skip when pin is pulled low.
		
		us_delay(1);	//30us delay maybe 
		
		store[i/8] <<= 1;	//Push value to the right by 1 bit
		
		if(DHT11 == 1)//DHT11 == 1)	//if 1
		{
			store[i/8] |= 1;	//Switch least sig bit to 1
			while(DHT11 == 1);
		}
	}
	
	if(store[0] + store[2] == store[4])
	{
		//write_string("H: ");
		write_int(store[0]);
		write_char('%');
		
		write_char(' ');
	 	
		//write_string("C: ");
		write_int(store[2]);
		write_char(LCD_DEGREE);
		write_char('C');
	}
	else
	{
		write_string("BAD CHECK");
	}
	new_line();
}