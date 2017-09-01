#ifndef _DS3231_H_
#define _DS3231_H_

struct time
{
	char seconds;
	char minutes;
	char hours;
	
	//char *day[7];
	
	char date;
	unsigned char month;
	unsigned char year;
	
	char temp;
}getTime, setTime;

extern void test();
extern unsigned char rtcDecToBcd(unsigned char convert);
extern unsigned char rtcBcdToDec(unsigned char convert);
extern void rtc_set_time();
extern void rtc_get_time();
extern void rtc_temp();

#endif