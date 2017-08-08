#include "LCD.h"

void init()
{
	RS = 0;	//command
	
	write_byte = 0x38;	//Function set (8 bit, 2 line, 5x7)
	E = 0;
	delay(50);
	E = 1;
	delay(50);
	
	write_byte = 0x06;	//Entry mode (Left to right, inc)
	E = 0;
	delay(50);
	E = 1;
	delay(50);
	
	write_byte = 0x0F;	//display (Display on, cursor blinking)
	E = 0;
	delay(50);
	E = 1;
	delay(50);
	
}

void write_char(char hex, bit command)
{
	RS = command;
	write_byte = hex;
	E = 0;
	delay(50);
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
		delay(50);
		backlight = 0;
	}
}

void write_string(char string[])
{
	unsigned int i = 0;

	RS = 1;	//ensure we are writing string
	for(i = 0; i < string[i] != '\0'; i++)
	{
			write_byte = string[i];
			E = 0;
			delay(50);
			E = 1;
			delay(50);
	}
	//write_char(0x02, 0);	//Return to 0,0
	//write_char(0x01, 0);	//Clear display
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