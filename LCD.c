#include "LCD.h"

void backlight_toggle()
{
	sbit backlight = 0;
	backlight = ~backlight;
	//~backlight;
	//!backlight;
}

void backlight_button()
{
	if(backlight_button == 0)
	{
		//backlight = 1;
		Delay(200);
		//backlight = 0;
	}
}

void Delay(int k)
{
  int j;
  int i;
  for(i=0;i<k;i++)
  {
    for(j=0;j<1000;j++)
    {
    }
  }
}