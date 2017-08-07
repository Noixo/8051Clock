#ifndef LCD_h_
#define LCD_h_

extern bit D0;
extern bit D1;
extern bit D2;
extern bit D3;
extern bit D4;
extern bit D5;
extern bit D6;
extern bit D7;

extern bit RS;
extern bit E;

extern bit backlight;
//#define backlight P2^3;
//extern bit lcd_button;

//---------------

extern void backlight_toggle(void);
extern void backlight_button(void);
extern void Delay(int k);

#endif