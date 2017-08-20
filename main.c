#include "LCD.h"
#include "DHT11.h"
//#include "external.h"
#include "timing.h"
#include "i2c.h"

// us_delay(1) is 23us
// us_delay(0) is ~17us

void main()
{
	backlight = 0;

	init();
	//write_string("Hello, World!\n");
	
	while(1)
	{
		readDHT11();
	}
}

/*
	--------------TODO---------------
	* Add interupt
  * Setup function to setup lcd e.g. 16x2, 40x4...
	* i2c bit banging
		-	BMP280
		- DS3231
	* Add interupt to break DHT11 if stuck for too long
*/

/*
	---------------Small issues--------------
	* timer not accurate
	* i2c.c needs lcd.c to print variable. Not efficient
*/

/* Boot idea
	image appearing in middle of lcd
	made out of bitmaps.
	Load 8 bitmaps into lcd.
	Run them and then reload next 8.
*/