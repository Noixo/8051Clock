#include "timing.h"

void ms_delay(unsigned int time)
{
	TMOD = 0x01;
	
	time = 0;
	
	TH0 = 0X4B;        //Load the timer value
	TL0 = 0XFD;
  TR0 = 1;           //turn ON Timer zero
  while(TF0 == 0);   // Wait for Timer Overflow
  TF0 = 0;           //clear the timer Over flow flag
  TR0 = 0;
}