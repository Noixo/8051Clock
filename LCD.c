//#include <stdio.h>
#include "LCD.h"
#include "timing.h"

//current_line = 0;

void init()
{
	//RS = 0;	//command
	ms_delay();
	
	cmd(0x38);	//Function set (8 bit, 2 line, 5x7)
	ms_delay(2);	//approx 15 ms

	cmd(0x06);	//Entry mode (Left to right, inc)

	cmd(0x0F);	//display (Display on, cursor blinking)

	cmd(LCD_CLEAR);	//CLEAR
}

void cmd(unsigned char cmd)
{
	RS = 0;
	write_byte = cmd;
	E = 0;
	us_delay();
	E = 1;
}

void write_char(unsigned char letter)
{
	/* if(letter > 0x7F)	//127
		cmd(0x39);	//8 bit, 2 line, 5x10
	else
		cmd(0x38);	*/
	//letter += '0';	//Convert all chars to ASCII.
	
	RS = 1; //word;
	write_byte = letter;
	E = 0;
	us_delay();
	E = 1;
}

void backlight_toggle()
{
	backlight = ~backlight;
}	

void write_string(unsigned char *string)//[])
{
	//unsigned char string[8];
	unsigned char i = 0;
	
	//if(array == (int) array)
	//iota(array, string, 10);
	//sprintf(string, "%u", array);	//Convert everything to string
	
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

void write_int(unsigned char value)	//Rewrite later
{
	char i;
	unsigned char temp = value;
	unsigned char array[3];
	
	for(i = 0; i < 3; i++)
	{
		array[i] = value % 10 + '0';
		if(value / 10 == 0 && i < 3)
		{
			array[i+1] = '\0';
			break;
		}
		value /= 10;
	}
	
	reverse_array(array, i);
	
	write_string(array);
}

void reverse_array(unsigned char *array, unsigned char end)
{
	unsigned char start = 0, temp = 0;
	while(start < end)
	{
		temp = array[start];
		array[start] = array[end];
		array[end] = temp;
		start++;
		end--;
	}
}

void new_line()
{
	if(!current_line)
	{
		cmd(LCD_LINE_2);//^ 0xC0);
	}
	else
	{
		cmd(LCD_LINE_1);
	}
	current_line = ~current_line;
}