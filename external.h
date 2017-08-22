#ifndef _EXTERNAL_H_
#define _EXTERNAL_H_

sfr TCON = 0x88;	//interrupt
sfr IE = 0xA8;	//interrupt enable
sfr IP = 0xB8;	//Interrupt priority

sbit backlight = 0xB2;	//Port 3, bit 2
//sbit lcd_button = 0x91;	//Port 1, bit 1	

sbit comparator = 0x93;
sbit next = 0x94;

extern void check_night(void);
extern void extern_int0(void);
extern void next_screen(void);

#endif