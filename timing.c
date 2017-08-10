#include "timing.h"

void ms_delay(unsigned int time)
{
<<<<<<< HEAD
=======
	TCON = 0x01;
	
>>>>>>> 20d28dc9c3bed2fb76090137fa396f03a4a34a1c
	TMOD = 0x01;
	
	time = 0;
	
	TH0 = 0X4B;        //Load the timer value
	TL0 = 0XFD;
<<<<<<< HEAD
  TR0 = 1;           //turn ON Timer zero
  while(TF0 == 0)
	{
	}		// Wait for Timer Overflow
  TF0 = 0;           //clear the timer Over flow flag
  TR0 = 0;
=======
 // TR0 = 1;           //turn ON Timer zero
  while(TF0 == 0)
	{
	}		// Wait for Timer Overflow
  TMOD = 0x00;
	
	//TF0 = 0;           //clear the timer Over flow flag
  //TR0 = 0;
>>>>>>> 20d28dc9c3bed2fb76090137fa396f03a4a34a1c
}