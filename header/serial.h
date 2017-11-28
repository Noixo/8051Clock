#ifndef _SERIAL_H_
#define _SERIAL_H_

sbit TI = 0x99;
sbit RI = 0x98;

sfr SBUF = 0x99;


extern void init_serial();
extern void serial_send(unsigned char byte);
extern void serial_send_array(unsigned char* array);
extern unsigned char serial_receive();
extern void serial_convert(unsigned char value);
extern unsigned char* serial_recieve_array();

#endif