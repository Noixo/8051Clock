#ifndef _DS3231_H_
#define _DS3231_H_

#define ds3231 0x68

extern const unsigned char time[];
extern const unsigned char temp[];

extern unsigned char* rtc_get_temp();
extern unsigned char* rtc_get_time();
//extern void ds3231Alarm();
extern unsigned char decToBcd(unsigned char convert);
extern unsigned char bcdToDec(unsigned char convert);
extern void rtc_set_time(unsigned char *time);
//extern void time rtc_get_time();

#endif