#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"
#include "i2c.h"

// us_delay(1) is 23us
// us_delay(0) is ~17us

void main()
{
	TCON = 0x01;
	IP = 0x01;	//Highest priority
	IE = 0x81;	//Turns on external interrupt 0
	
	backlight = 0;

	init();
	//i2c_setup();
	
	//i2c_start();
	//write_string("Hello, World!\n");
	
	//i2c_read_id();
	while(1)
	{
		readDHT11();
		check_night();
	}
}

/*
	--------------TODO---------------
	* Add interupt
		- Setup counter to go back to main during backlight lighting
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