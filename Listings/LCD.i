
#line 1 "LCD.c" /0
  
#line 1 "LCD.h" /0
 
 
 
 sfr write_byte = 0xA0;
 
 sbit D0 = 0xA1;
 sbit D1 = 0xA2;
 sbit D2 = 0xA3;
 sbit D3 = 0xA4;
 sbit D4 = 0xA5;
 sbit D5 = 0xA6;
 sbit D6 = 0xA7;
 sbit D7 = 0xA8;
 
 sbit RS = 0x81;
 sbit E = 0x82;
 
 sbit backlight = 0xA8;	 
 sbit lcd_button = 0xA7;
 
 
 
 extern void backlight_toggle(void);
 extern void backlight_button(void);
 extern void delay(int t);
 
 
#line 1 "LCD.c" /0
 
 
 void backlight_toggle()
 {
 backlight = ~backlight;
 }
 
 void delay(unsigned int t)
 {
 int i, j;
 for(i = 0; i < t; i++)
 {
 for(j = 0; j < 100; j++)
 {
 }
 }
 }
