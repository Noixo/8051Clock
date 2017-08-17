#include "LCD.h"
#include "DHT11.h"
//#include "external.h"
#include "timing.h"
#include "i2c.h"

void main()
{
	unsigned int i = 0;
	backlight = 0;
	
	init();
	write_string("Hello, World!\n");
	
	while(1)
	{
		a = 1;
		ms_delay(1);
		a = 0;
		ms_delay(10);
		
		//readDHT11();
		//write_string("\n");
		//write_char('1');
	}
}

/*
	--------------TODO---------------
	* Add interupt
  * Setup function to setup lcd e.g. 16x2, 40x4...
	* i2c bit banging
		-	BMP280
		- DS3231
*/

/*
	---------------Small issues--------------
	* timer not accurate
*/

/* Boot idea
	image appearing in middle of lcd
	made out of bitmaps.
	Load 8 bitmaps into lcd.
	Run them and then reload next 8.
*/