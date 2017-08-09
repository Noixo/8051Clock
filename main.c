#include "LCD.h"
#include "DHT11.h"
#include "external.h"
#include "timing.h"

void main()
{
	backlight = 0;
	
	init();
	
	while(1)
	{
		unsigned int i = 0;
		//cmd(HOME);
		//cmd(LINE_1);
		ms_delay();
		write_string("Hello, World!");
		ms_delay();
		/*for(i = 0; i < 1024; i++)
		{
			//char x = i;
			write_char(i+'0');
			cmd(CLEAR);
		}*/
		//write_char(128+'0');
		//delay(1000);
		//cmd(CLEAR);
		//write_char(154243+'0');
		//delay(2000);
		//write_string("123456789");
		//cmd(LINE_2);
		//cmd(CLEAR);
		//write_string("Test");
		//write_char('A',1);
	}
}

/*
	* Add timer
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