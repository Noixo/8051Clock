#include "serial.h"
#include "timing.h"

#include "lcd.h"

//9600 baurd
void init_serial()
{
	TMOD |= 0x20;	//mode 2: 8 bit auto reload
	SCON = 0x50;
	TH1 = 0xFF;
	//TH1 = 0xFD;
	TR1 = 1;
}


void serial_convert(unsigned char value)	//Rewrite later
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
	
	serial_send_array(array);
}

void serial_send_array(unsigned char* array)
{
	unsigned char i;
	for(i = 0; array[i] != '\0'; i++)
	{
		SBUF = array[i];
		while(TI == 0);
		TI = 0;
	}
}

void serial_send(unsigned char byte)
{
	SBUF = byte;
	while(TI == 0);
	TI = 0;
}

unsigned char serial_receive()
{
	while(RI == 0)
	RI = 0;
	return SBUF;
}