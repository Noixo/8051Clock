#ifndef _DISPLAY_H_
#define _DISPLAY_H_

extern unsigned char *p_time, eepromLocX, eepromLocY;
extern short bmpTemp;
extern unsigned long bmpPressure;
extern unsigned char *p_dht11;
extern char INTbmpTemp;
extern unsigned short INTbmpPressure;

extern unsigned char printSwap;

extern void check0(unsigned char number);
extern void screen1();
extern void screen2();
extern void screen3();

#endif