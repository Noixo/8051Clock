#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"

void main()
{
	readDHT11();
	backlight = 0;
	
	init();
	
	write_string("Hello, World!");
	
	while(1)
	{
	}
}

/*
	* Add timer*
	* Add interupt
	* send screen clear command, start of init()
  * Setup function to setup lcd e.g. 16x2, 40x4...
	* i2c bit banging
		-	pressure sensor
		- DS3231
*/

/*
 * String prints on second line after first printing on first line
*/