#include "serial.h"
#include "timing.h"
#include "subroutine.h"

//0xFD = 9600 baurd

//0xFF = 	28,800 baurd
void init_serial()
{
	
	TMOD |= 0x20;	//mode 2: 8 bit auto reload
	SCON = 0x50;
	TH1 = 0xFF;
	//TH1 = 256 - (11059200UL)/(long)(32*12*baudrate);
	TR1 = 1;
}

void serial_convert(unsigned char value)
{
	//converts the char number into ASCII
	//sends the ASCII array to UART
	serial_send_array(convert(value));
}

void serial_send_array(unsigned char* array)
{
	unsigned char i;
	for(i = 0; array[i] != '\0'; i++)
	{
		serial_send(array[i]);
	}
}

void serial_send(unsigned char byte)
{
	//load data into register
	SBUF = byte;
	//wait till data is transmitted
	while(TI == 0);
	//clear Tx for next transmission
	TI = 0;
}

unsigned char serial_receive()
{
	unsigned char test = 0;
	
	//if there is a character in the buffer
	if(RI == 1)
	{
		RI = 0;
	//while(RI == 0);
	//RI = 0;
		test = SBUF;
	}
	return test;
}

unsigned char* serial_recieve_array()
{
	unsigned char arr[12];
	char i;
	
	for(i = 0; i < 12; i++)
	{
		arr[i % 2] <<= serial_receive();
	}
	return arr;
}