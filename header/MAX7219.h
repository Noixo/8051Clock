#ifndef _MAX7219_H_
#define _MAX7219_H_

sbit DIN = 0xB7;
sbit CS = 0xB6;
sbit CLK = 0xB5;

extern void matrixInit();
extern void matrixClear();
extern void matrixSend(unsigned char address, unsigned char byte);
//static code char maxIntensity = 0xA;

#endif