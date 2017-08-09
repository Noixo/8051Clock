#include "LCD.h"
#include "DHT11.h"
#include "external.h"

void main()
{
	backlight = 0;
	
	init();
	
	while(1)
	{
		//cmd(HOME);
		//cmd(LINE_1);
		//write_string("Hello, World!");
		write_string("123456789");
		//cmd(CLEAR);
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
*/

/*
 * String prints on second line after first printing on first line
*/