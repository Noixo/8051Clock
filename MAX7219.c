#include "MAX7219.h"

void matrixInit()
{
	//clear the display
	matrixClear();
	
	//Change intensity, 0 lowest - F brightest
	matrixSend(0x0A, 0x01);
	//Take out of shutdown mode
	matrixSend(0x0C, 0x01);
	//Scan limit. 8 lines
	matrixSend(0x0B, 0x07);
}

void matrixClear()
{
	char i;
	
	for(i = 1; i < 9; i++)
		matrixSend(i, 0x00);
}

void matrixSend(unsigned char address, unsigned char byte)
{
	char i;
	
	CS = 0;
	for(i = 0; i < 8; i++)
	{
		DIN = address & 0x80;
		CLK = 1;
		address <<= 1;
		CLK = 0;
	}
	for(i = 0; i < 8; i++)
	{
		DIN = byte & 0x80;
		CLK = 1;
		byte <<= 1;
		CLK = 0;
	}
	CS = 1;
}