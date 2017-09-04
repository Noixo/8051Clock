#ifndef _DS3231_H_
#define _DS3231_H_

extern const unsigned char time[];	//6
extern const unsigned char temp[];	//1

unsigned char* rtc_get_temp();
extern unsigned char* rtc_get_time();
extern void test();
extern unsigned char decToBcd(unsigned char convert);
extern unsigned char bcdToDec(unsigned char convert);
extern void rtc_set_time();
//extern void time rtc_get_time();


#endif