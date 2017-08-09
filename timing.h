#ifndef TIMING_H_
#define TIMING_H_

sbit TMOD = 0x89;
sbit TH0 = 0x8C;
sbit TL0 = 0x8A;
sbit TR0 = 0x8C;
sbit TF0 = 0x8D;

extern void ms_delay(unsigned int time);

#endif