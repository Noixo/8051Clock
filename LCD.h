#ifndef _LCD_H_
#define _LCD_H_

sfr write_byte = 0xA0;

/*
sbit D0 = 0xA0;
sbit D1 = 0xA1;
sbit D2 = 0xA2;
sbit D3 = 0xA3;
sbit D4 = 0xA4;
sbit D5 = 0xA5;
sbit D6 = 0xA6;
sbit D7 = 0xA7;
*/


sbit a = 0xB7;	//Port 3 bit 7

sbit RS = 0x93;	//Port 0, bit 0
sbit E = 0x94;	//Port 0 bit 1

//sbit a = 0xB7;

//---------------

static unsigned char LCD_DEGREE = 0xDF;
static unsigned char LCD_NEG_ONE = 0xE9;
/*
static unsigned char LCD_ARROW_RIGHT = 0x7E;
static unsigned char LCD_ARROW_LEFT = 0x7F;
*/

static char LCD_CLEAR = 0x01;
static char LCD_HOME = 0x02;

static char LCD_LINE_1 = 0x80;
static char LCD_LINE_2 = 0xC0;

//const char array;

//static char array[];

/*
const char HOME = 0x02;

const char ENTRY_INC_L = 0x07;
const char ENTRY_INC_R = 0x06;
const char ENTRY_DEC_L = 0x05;
const char ENTRY_DEC_R = 0x04;

const char LINE_1 = 0x80; //first line
const char LINE_2 = 0xC0;	//Second line	*/

//extern unsigned int location_count;
extern bit current_line;
//const DISPLAY.ON = 
//---------------

extern void init();
extern void write_char(unsigned char hex);
extern void cmd(unsigned char cmd);
extern void backlight_toggle(void);
extern void backlight_light(void);
extern void write_string(unsigned char string[]);
extern void new_line(void);
extern void int_to_ascii(unsigned char decimal, unsigned char size);
extern void write_int(unsigned char value);
extern void reverse_array(unsigned char array[], char i);
#endif