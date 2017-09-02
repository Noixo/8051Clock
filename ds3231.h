#ifndef _DS3231_H_
#define _DS3231_H_
/*
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
*/

extern const unsigned char time[6];
unsigned char* rtc_temp();
extern unsigned char* rtc_get_time();
extern void test();
extern unsigned char rtcDecToBcd(unsigned char convert);
extern unsigned char rtcBcdToDec(unsigned char convert);
extern void rtc_set_time();
//extern void time rtc_get_time();


#endif