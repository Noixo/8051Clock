#ifndef _TIMING_H_
#define _TIMING_H_

sfr TMOD = 0x89;
sfr TH0 = 0x8C;
sfr TL0 = 0x8A;

sbit TR0 = 0x8C;
sbit TF0 = 0x8D;

extern void ms_delay(unsigned char num);
extern void us_delay(unsigned char num);
extern void timer2(void);
#endif