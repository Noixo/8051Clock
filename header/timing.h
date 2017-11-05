#ifndef _TIMING_H_
#define _TIMING_H_

sfr TMOD = 0x89;
sfr SCON = 0x98;

sfr TH0 = 0x8C;
sfr TL0 = 0x8A;
sfr TH1 = 0x8D;
sfr TL1 = 0x8B;

sbit TR0 = 0x8C;
sbit TF0 = 0x8D;

sbit TR1 = 0x8E;
sbit TF1 = 0x8F;

sbit ET1 = 0xAB;
sbit EA = 0xAF;

extern void init_timing();
extern void ms_delay(unsigned char num);
extern void msDelayCheck();
extern void backlightInterrupt();
extern void us_delay();
extern void dhtTimer();
extern void us();
extern void dhtInterrupt1();
extern void dhtInterrupt();
extern void timout();
#endif