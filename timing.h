#ifndef _TIMING_H_
#define _TIMING_H_

sbit TR0 = 0x8C;
sbit TF0 = 0x8D;

sbit TMOD = 0x89;
sbit TH0 = 0x8C;
sbit TL0 = 0x8A;

extern void ms_delay(unsigned int ms_delay);
extern void us_delay(unsigned int us_delay);
#endif