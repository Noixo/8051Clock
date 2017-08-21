#ifndef EXTERNAL_H_
#define EXTERNAL_H_

sfr TCON = 0x88;	//interrupt
sfr IE = 0xA8;	//interrupt enable
sfr IP = 0xB8;	//Interrupt priority

sbit comparator = 0x93;
sbit next = 0x94;

extern void photoresistor(void);
extern void lcd_button_press(void);
extern void next_screen(void);

#endif