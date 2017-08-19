#ifndef EXTERNAL_H_
#define EXTERNAL_H_

sbit comparator = 0x93;
sbit next = 0x94;

extern void photoresistor(void);
extern void lcd_button_press(void);
extern void next_screen(void);

#endif