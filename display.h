#ifndef _DISPLAY_H_
#define _DISPLAY_H_

extern unsigned char *p_time, eepromLocX, eepromLocY;
extern long bmpTemp;
extern long bmpPressure;

extern void check0(unsigned char number);
extern void screen1();
extern void screen2();
extern void screen3();

#endif