#ifndef TIMING_H_
#define TIMING_H_

<<<<<<< HEAD
sbit TMOD = 0x89;
sbit TH0 = 0x8C;
sbit TL0 = 0x8A;
sbit TR0 = 0x8C;
sbit TF0 = 0x8D;
=======
sfr TCON = 0x88;
sbit TR0 = 0x8C;
sbit TF0 = 0x8D;

sbit TMOD = 0x89;
sbit TH0 = 0x8C;
sbit TL0 = 0x8A;

>>>>>>> 20d28dc9c3bed2fb76090137fa396f03a4a34a1c

extern void ms_delay(unsigned int time);

#endif