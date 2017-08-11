#include "LCD.h"
#include "timing.h"

//current_line = 0;

void init()
{
	//RS = 0;	//command
	ms_delay(15);
	
	cmd(0x38);	//Function set (8 bit, 2 line, 5x7)
	ms_delay(5);

	cmd(0x06);	//Entry mode (Left to right, inc)

	cmd(0x0F);	//display (Display on, cursor blinking)

	cmd(CLEAR);
}

void cmd(char cmd)
{
	RS = 0;
	write_byte = cmd;
	E = 0;
	us_delay(100);
	E = 1;
}

void write_char(char letter)
{
	RS = 1; //word;
	write_byte = letter;
	E = 0;
	us_delay(100);
	E = 1;
}

void backlight_toggle()
{
	backlight = ~backlight;
}	

void write_string(char *string)//[])
{
	char i = 0;
	
	//RS = 1;	//ensure we are writing string
	for(i = 0; string[i] != '\0'; i++)
	{
		if(string[i] == '\n')//0x5C 0x6E)	// 0x5c is '\', 0x6E is 'n'
		{
			new_line();
		}
		else
		{
			write_char(string[i]);
		}
	}
}


void new_line()
{
	if(!current_line)
	{
		cmd(0xC0);//^ 0xC0);
		//cmd(0xC0);
	}
	else
	{
		cmd(0x80);
	}
	current_line = ~current_line;
}

char int_to_ascii(char integer)
{
	return integer + '0';
}