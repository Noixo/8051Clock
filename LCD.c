#include "LCD.h"
#include "timing.h"

void init()
{
	RS = 0;	//command
	ms_delay(15);
	
	write_byte = 0x38;	//Function set (8 bit, 2 line, 5x7)
	E = 0;
	ms_delay(5);
	E = 1;
	
	write_byte = 0x06;	//Entry mode (Left to right, inc)
	E = 0;
	us_delay(110);
	E = 1;
	
	write_byte = 0x0F;	//display (Display on, cursor blinking)
	E = 0;
	us_delay(110);
	E = 1;
	
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

void write_string(char string[])
{
	unsigned char i = 0;
	//location_count = 0;
	
	RS = 1;	//ensure we are writing string
	for(i = 0; i < string[i] != '\0'; i++)
	{
		write_byte = string[i];
		E = 0;
		us_delay(100);
		E = 1;
	}
	new_line();
}


void new_line()
{
	if(!current_line)
	{
		cmd(0xC0);
	}
	else
	{
		cmd(0x80);
	}
	current_line = ~current_line;
}
	/*
	if(location_count == 32)
	{
		cmd(0x02);
		cmd(0x80);	//LINE_1
		
		location_count = 0;
	}
	else if(location_count == 16)
	{
		cmd(0x02);
		cmd(0xC0);	//LINE_2
	}
}*/

void int_to_ascii()
{
	
}