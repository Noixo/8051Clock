#include "LCD.h"
#include "DHT11.h"
//#include "external.h"
#include "timing.h"

void main()
{
	backlight = 0;
	
	init();
	
	//write_string("Hello, World!\n");
	
	write_int(0xFF);
	//readDHT11();
	while(1)
	{
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