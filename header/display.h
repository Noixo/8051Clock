#ifndef _DISPLAY_H_
#define _DISPLAY_H_

//constants to define how long pressure it shown before switching to humidity
#define SWAPLENGTH 6
#define SWAPRESETNUM 2*SWAPLENGTH


//no seconds due to pointer start at loc 0
#define MINUTE 1	// define DS3231 minute location
#define HOUR 2 // define DS3231 hour location
#define DAY 3 //define DS3231 day (mon,tues,wed ect) location
#define DATE 4	//DS3231 date (1-31)
#define MONTH 5	//define DS3231 month location
#define YEAR 6	//DS3231 year


extern unsigned char *p_time, eepromLocX, eepromLocY;
extern short bmpTemp;
extern unsigned long bmpPressure;
extern unsigned char *p_dht11;
extern char INTbmpTemp;

extern unsigned char printSwap;

extern void display(unsigned char number);
extern void screen1();
extern void screen2();
extern void screen3();

#endif