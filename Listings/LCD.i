
#line 1 "LCD.c" /0
  
#line 1 "LCD.h" /0
 
 
 
 extern bit D0;
 extern bit D1;
 extern bit D2;
 extern bit D3;
 extern bit D4;
 extern bit D5;
 extern bit D6;
 extern bit D7;
 
 extern bit RS;
 extern bit E;
 
 extern bit backlight;
 
 
 
 
 
 extern void backlight_toggle(void);
 extern void backlight_button(void);
 extern void Delay(int k);
 
 
#line 1 "LCD.c" /0
 
 
 void backlight_toggle()
 {
 sbit backlight = 0;
 backlight = ~backlight;
 
 
 }
 
 void backlight_button()
 {
 if(backlight_button == 0)
 {
 
 Delay(200);
 
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
