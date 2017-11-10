#include "LCD.h"
#include "timing.h"
#include "subroutine.h"

void init_lcd()
{
	ms_delay(15);	//Start up delay
	
	cmd(0x38);	//Function set (8 bit, 2 line, 5x7)
	lcdDelay();

	cmd(0x0E);	//display (Display on, cursor on)
	lcdDelay();
	
	cmd(0x06);	//Entry mode (Left to right, inc)
	lcdDelay();

	cmd(0x0E);	//display (Display on, cursor on)
	lcdDelay();
	
	cmd(0x06);	//Entry mode (Left to right, inc)
	lcdDelay();
	
	cmd(LCD_CLEAR);	//CLEAR
	ms_delay(2);
}

//inserts the pre-defined bitmap into the user chosen location
void customChar(unsigned char *array, char location)
{
	char i;
	cmd(0x40+(location*8));
	
	for(i = 0; i < 8; i++)
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
	lcdDelay();
	E = 0;
	
	if(cmd == LCD_CLEAR || cmd == LCD_HOME || cmd == LCD_LINE_1 || cmd == LCD_LINE_2)
		ms_delay(2);
}

void write_char(unsigned char letter)
{
	write_byte = letter;
	RS = 1;	//word
	E = 1;
	lcdDelay();
	E = 0;
	
	//give extra time to custom characters in LCD DRAM
	//if(letter >= '0' && letter <= '9')
		//ms_delay(2);
}
/*
void backlight_toggle()
{
	backlight = ~backlight;
}
*/

void write_string(unsigned char* string)
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

void write_int(unsigned char value)
{
	//converts the char number into ASCII
	//sends the ASCII array to the LCD
	write_string(convert(value));
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
