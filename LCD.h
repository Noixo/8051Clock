#ifndef LCD_h_
#define LCD_h_

sfr write_byte = 0xA0;

sbit D0 = 0xA0;
sbit D1 = 0xA1;
sbit D2 = 0xA2;
sbit D3 = 0xA3;
sbit D4 = 0xA4;
sbit D5 = 0xA5;
sbit D6 = 0xA6;
sbit D7 = 0xA7;

sbit RS = 0x80;
sbit E = 0x81;

sbit backlight = 0x90;
sbit lcd_button = 0x91;		
//---------------
/*
const HOME = 0x02;
const CLEAR = 0x01;

const char ENTRY.INC.L = 0x07;
const char ENTRY.INC.R = 0x06;
const char ENTRY.DEC.L = 0x05;
const char ENTRY.DEC.R = 0x04;
0x80 //first line
*/

//const DISPLAY.ON = 
//---------------

extern void init();
extern void write_char(char hex, bit command);
extern void backlight_toggle(void);
extern void backlight_light(void);
extern void write_string(char string[]);
extern void delay(unsigned int t);
extern void write_string(char string[]);

#endif