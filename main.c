#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"
#include "i2c.h"

void main()
{
	//SETUP
	
	//INTERRUPTS
		//EXT0 for backlight
	IT0 = 1;
	EX0 = 1;
	EA = 1;
	
	//EXT1 for next screen
	IT1 = 1;
	EX1 = 1;
	//--------------
	
	backlight = 0;	//Turn on display

	init();
	
	//write_string("Hello, World!\n");
	
	while(1)
	{
		check_night();
		readDHT11();
	}
}

/*
	--------------TODO---------------
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