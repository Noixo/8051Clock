#include "display.h"
#include "lcd.h"
#include "eeprom.h"

//if time is < 10 add 0. e.g. 05
void check0(unsigned char number)
{
	if(number < 10)
		write_char('0');
}

//display general items, time, pressure, temp
void screen1()
{
	//static short hPa = bmpPressure/1000;
	//reset to line 1 of LCD, pos 0
	cmd(LCD_HOME);

	//--------------print the time-------------
	//hours
	check0(*(p_time + 2));
	
	write_int(*(p_time+2));
	write_char(':');
	//minutes
	check0(*(p_time + 1));
	write_int(*(p_time+1));	
	write_char(':');
	//seconds
	check0(*(p_time));
	write_int(*(p_time));
	write_char(' ');
	
	//print temp
	//if(bmpTemp > 0)
	write_int(bmpTemp/100);
	
	write_char('.');
	check0(bmpTemp % 100);
	write_int(bmpTemp % 100);
	//write temperature symbol *c
	write_char(0);
	
	cmd(LCD_LINE_2);
	
	//day
	check0(*(p_time+4));
	write_int(*(p_time+4));	
	write_char('/');
	//month
	check0(*(p_time+5));
	write_int(*(p_time+5));
	write_char('/');
	//year
	check0(*(p_time+6));
	write_int(*(p_time+6));
	write_char(' ');

	//pressure
	write_int(bmpPressure/1000);
	write_int((bmpPressure % 1000) / 100);
	write_char('.');
	check0(bmpPressure % 100);
	write_int(bmpPressure % 100);
	write_char(' ');
}

//display max and min temp/%
void screen2()
{
	const char code max[] = "MAX/MIN: ";
	unsigned char value;
	
	cmd(LCD_HOME);

	write_string(max);
	
	//get max temp
	value = eepromRandomRead(0,0);
	write_int(value);
	//serial_convert(value);
	write_char(0);
	
	write_char(' ');
	
	//get min temp
	value = eepromRandomRead(0,1);
	write_int(value);
	//serial_convert(value);
	write_char(0);
	
	//get humidity
	cmd(LCD_LINE_2);
	write_string(max);
	
	value = eepromRandomRead(0,2);
	write_int(value);
	//serial_convert(value);
	write_char('%');
	write_char(' ');
	
	value = eepromRandomRead(0,3);
	write_int(value);
	//serial_convert(value);
	write_char('%');
	
	//DHT11 humidity
}

//display pressure
void screen3()
{
	char i;
	
	cmd(LCD_HOME);
	write_string("MAX: ");
	
	for(i = 4; i < 6; i++)
	{
		write_int(eepromRandomRead(0,i));
	}
	
	cmd(LCD_LINE_2);
	
	write_string("MIN: ");
	
	for(i = 6; i < 8; i++)
	{
		write_int(eepromRandomRead(0,i));
	}
}