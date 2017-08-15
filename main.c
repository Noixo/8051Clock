#include "LCD.h"
#include "DHT11.h"
//#include "external.h"
#include "timing.h"

void main()
{
	//char *store;
	//write_string(readDHT11());
	
	backlight = 0;
	
	init();
	//write_int(0xFF);
	write_int(0x01);
	write_char(0x00);
	write_int(0xF);
	write_char(0x00);
	write_int(0xFF);
	write_char(0x00);
	//write_char(0x8E | 0x30);
	//write_string("\n");
	//int_to_ascii(0x01);
	//write_char(223);
	//int_to_ascii(0xFA);
	//write_string(0xF);
	//int_to_ascii(0xF, array_size(0xF));
	//write_string(0x0F);
	
	//write_string("\n");
	//int_to_ascii(0xFA);
	//write_int(0xFF);
	//write_string(255);
	//write_string("Hello, World!\n");
	//write_char(0xCC + '0');
	//write_char(0xFC);
	//readDHT11();
	while(1)
	{
		//write_string("a\n");
		//write_string("Hello, World!\n");
		//DHT11[] = readDHT11();
		//write_string(DHT11());
		//store = readDHT11();
		//char *store = readDHT11();
		//write_string(readDHT11(store));
		//ms_delay(1);
	}
}

/*
	--------------TODO---------------
	* Add timer*
	* Add interupt
	* send screen clear command, start of init()
  * Setup function to setup lcd e.g. 16x2, 40x4...
	* i2c bit banging
		-	pressure sensor
		- DS3231
*/

/*
	---------------Small issues--------------
	* int_to_ascii: i underflows
 * String prints on second line after first printing on first line
*/	