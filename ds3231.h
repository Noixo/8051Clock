#ifndef _DS3231_H_
#define _DS3231_H_

unsigned char time[];

extern void ds3231_set_time();
extern char* ds3231_get_time();

#endif