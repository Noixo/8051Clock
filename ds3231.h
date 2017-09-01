#ifndef _DS3231_H_
#define _DS3231_H_

//unsigned char [7];


struct time
{
	//unsigned char bcd : 4;
//	unsigned char bcd : 4;
	
	char seconds;
	char minutes;
	char hours;
	
	//char *day[7];
	
	char date;
	unsigned char month;
	unsigned char year;
	
	char temp;
	
};//getTime;//, setTime;

void rtc_get_time(struct time *getTime);
//extern struct time *getTime;

extern void test();
//extern unsigned char rtcDecToBcd(unsigned char convert);
//extern unsigned char rtcBcdToDec(unsigned char convert);
extern void rtc_set_time();
extern struct time rtc_get_time();
extern void rtc_temp();

#endif