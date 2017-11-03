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
	//TH1 = 0xFD;
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
	while(RI == 0);
	RI = 0;
	return SBUF;
}