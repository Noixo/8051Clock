#include "display.h"
#include "lcd.h"
#include "eeprom.h"
#include "eepromSubroutine.h"	//sharing define statements

volatile unsigned char printSwap;

void display(unsigned char number)
{
	if(number < 10)	//if time is < 10 add 0. e.g. 05
		write_char('0');

	write_int(number);	//displays value
}

//display general items, time, pressure, temp
void screen1()
{
	unsigned char i;
	
	//reset to line 1 of LCD, pos 0
	cmd(LCD_HOME);

	//--------------print time-------------
	
	for(i = 2; i != -1; i--)	// print HH:MM:SS
	{
		display(*(p_time + i));
		
		if(i != 0)
			write_char(':');
	}

	write_char(' ');
	
	//--------------print temperature-------------

	//check if temperature is negative or positive
	if(bmpTemp < 0)
	{
		write_char('-');
		//convert negative value into a positive
		write_int((!INTbmpTemp) + 1); //((INTbmpTemp ^ 0xFF) & 0x7F) + 1 );
	}
	else
	{
		//buffer space
		write_char(' ');
		
		//print positive value
		display(INTbmpTemp);
	}
	
	//print decimal value
	write_char('.');
	display(bmpTemp % 100);

	//write temperature symbol *c
	write_char(0);
	
	cmd(LCD_LINE_2);

	//--------------print date-------------
	
	for(i = DATE; i <= YEAR; i++)	// print DD:MM:YY
	{
		display(*(p_time + i));
	
		if(i != YEAR)
			write_char('/');
	}
	
	write_char(' ');
	
	//--------------print pressure or humidity-------------
	
	printSwap++;
	
	//reset when printSwap has been going for too long
	if(printSwap > SWAPRESETNUM)
		printSwap = 0;
	
	//if x refreshes have occured print pressure
	if(printSwap > SWAPLENGTH)
	{
		write_int(bmpPressure / 1000);
		write_int((bmpPressure % 1000) / 100);
		write_char('.');
		display(bmpPressure % 100);
	}
	else
	{
		//print humidity
		write_char(' ');
		write_int(*(p_dht11)+2);
		write_string("%RH");
	}
	write_char(' ');
}

//display max and min temp/%
void screen2()
{
	const char code max[] = "MAX/MIN:";
	unsigned char value, i;
	
	cmd(LCD_HOME);

	write_string(max);
	
	for(i = tempMax; i <= humidityMin; i++)
	{
		write_char(' ');
		
		value = eepromRandomRead(0,i);
		display(value);
		
		if(i < 3)
			write_char(0);
		
		//if temperature has been printed, move to next line
		if(i == 2)
		{
			cmd(LCD_LINE_2);
			write_string(max);
		}
		
		//humidity max and min
		if(i == 3 || i == 4)
		{
			write_char('%');
		}
	}
}

//display pressure
void screen3()
{
	cmd(LCD_HOME);
	write_string("MAX: ");
	
	write_int(eepromRandomRead(0,pressureMaxUpper));
	write_int(eepromRandomRead(0,pressureMaxLower));
	write_string("hPa");
	
	cmd(LCD_LINE_2);
	
	write_string("MIN: ");
	
	write_int(eepromRandomRead(0,pressureMinUpper));
	write_int(eepromRandomRead(0,pressureMinLower));
	write_string("hPa");
}
