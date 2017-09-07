#include "LCD.h"
#include "timing.h"

void lcd_init()
{
	//RS = 0;	//command
	ms_delay(15);	//Start up delay
	
	cmd(0x38);	//Function set (8 bit, 2 line, 5x7)
<<<<<<< HEAD
	us_delay(1);
	us_delay(1);

	cmd(0x0E);	//display (Display on, cursor on)
	us_delay(1);
	us_delay(1);
	
	cmd(0x06);	//Entry mode (Left to right, inc)
	us_delay(1);
	us_delay(1);

	//us_delay(1);
=======
	us_delay();
	//us_delay();

	cmd(0x0E);	//display (Display on, cursor on)
	us_delay();
	//us_delay();
	
	cmd(0x06);	//Entry mode (Left to right, inc)
	us_delay();
	//us_delay();

	//us_delay();
>>>>>>> ds3231
	//cmd(0x80);
	
	cmd(LCD_CLEAR);	//CLEAR
	ms_delay(2);
}

void customChar(unsigned char* array, char location)
{
	char i;
	cmd(0x40+(location*8));
	//cmd(0x40 + (location*8));
	
	for(i = 0; i < 8; i++)//array[i] != '\0'; i++)
	{
		write_char(array[i]);
	}
	cmd(0x80);
}

void cmd(unsigned char cmd)
{
	write_byte = cmd;
	RS = 0;
	E = 1;
<<<<<<< HEAD
=======
	E = 0;
>>>>>>> ds3231
	if(cmd == LCD_CLEAR || cmd == LCD_HOME)
		ms_delay(2);
	else
	{
<<<<<<< HEAD
		us_delay(1);//us_delay(200);	//100 microsecond
		us_delay(1);
	}
	E = 0;
=======
		us_delay();//us_delay(200);	//100 microsecond
		//us_delay();
	}
>>>>>>> ds3231
}

void write_char(unsigned char letter)
{
	write_byte = letter;
	RS = 1;	//word
	
	E = 1;
<<<<<<< HEAD
	us_delay(1);// approx 25 micro
	us_delay(1);
	E = 0;
=======
	E = 0;
	us_delay();// approx 25 micro
	//us_delay();
>>>>>>> ds3231
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