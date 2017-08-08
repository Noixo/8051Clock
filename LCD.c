#include "LCD.h"

void init()
{
	RS = 0;	//command
	write_byte = 0x38;
	delay(10);
	RS = 1;
	//write_byte(0x30);
	//delay(10);
	//write_byte(0x30);
	//delay(10);
}

void write_char(char hex, bit command)
{
	RS = command;
	E = 0;
	write_byte = hex;
	E = 1;
}

void backlight_toggle()
{
	backlight = ~backlight;
}

void backlight_light()
{
	if(lcd_button == 1)
	{
		backlight = 1;
		delay(2000);
		backlight = 0;
	}
}

void write_string(char string[])
{
	int i;
	RS = 1;	//ensure we are writing string
	E = 0;
	
	for(i = 0; i < sizeof(string); i++)
	{
		write_byte = string[i];
	}
	E = 1;
}

void delay(unsigned int t)
{
	int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 100; j++)
		{
		}
	}
}