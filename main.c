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
	
	//write_string("Hello, World!\n");
	readDHT11();
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
	-----------------------------
 * String prints on second line after first printing on first line
*/