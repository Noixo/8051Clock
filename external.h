#ifndef _EXTERNAL_H_
#define _EXTERNAL_H_

sfr TCON = 0x88;	//interrupt
sfr IE = 0xA8;	//interrupt enable
sfr IP = 0xB8;	//Interrupt priority

sbit IT0 = 0x88;
sbit IT1 = 0x8A;
sbit EX0 = 0xA8;
sbit EX1 = 0xAA;
sbit EA = 0xAF;

sbit backlight = 0x91;//B2;	//Port 3, bit 2
//sbit lcd_button = 0x91;	//Port 1, bit 1	

sbit comparator = 0x92;
sbit next = 0x94;

extern void check_night(void);
extern void ex0_isr();
extern void next_screen(void);

#endif