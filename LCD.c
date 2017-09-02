#include "LCD.h"
#include "timing.h"

void lcd_init()
{
	//RS = 0;	//command
	ms_delay(50);	//Start up delay
	
	cmd(0x38);	//Function set (8 bit, 2 line, 5x7)
	ms_delay(5);

	cmd(0x06);	//Entry mode (Left to right, inc)

	cmd(0x0E);	//display (Display on, cursor on)

	cmd(LCD_CLEAR);	//CLEAR
}

void cmd(unsigned char cmd)
{
	RS = 0;
	write_byte = cmd;
	E = 0;
	ms_delay(2);//us_delay(200);	//100 microsecond
	E = 1;
}

void write_char(unsigned char letter)
{
	RS = 1; //word
	write_byte = letter;
	E = 0;
	ms_delay(2);//us_delay(200);	//100 micro
	E = 1;
}
/*
void backlight_toggle()
{
	backlight = ~backlight;
}
*/

void write_string(unsigned char* string)//[])
{
	unsigned char i;

	for(i = 0; string[i] != '\0'; i++)
	{
		if(string[i] == '\n')
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
	unsigned char array[3];
	
	for(i = 0; i < 3; i++)
	{
		//puts value to array after being split by 1 character and converted to ascii.
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
		cmd(LCD_LINE_2);
	}
	else
	{
		cmd(LCD_LINE_1);
	}
	current_line = ~current_line;
}