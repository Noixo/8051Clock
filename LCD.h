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

sbit RS = 0x81;
sbit E = 0x82;

sbit backlight = 0xA7;	//Reusing location
sbit lcd_button = 0xA6;

//---------------

extern void init();
extern void write_char(char hex, bit command);
extern void backlight_toggle(void);
extern void backlight_light(void);
extern void write_string(char string[]);
extern void delay(int t);
extern void write_string(char string[]);

//#endif