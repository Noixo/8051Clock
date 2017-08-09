#ifndef TIMING_H_
#define TIMING_H_

sfr TMOD = 0x89;
sfr TH0 = 0x8C;
sfr TL0 = 0x8A;
sfr TR0 = 0x8C;
sfr TF0 = 0x8D;

extern void ms_delay(unsigned int time);

#endif