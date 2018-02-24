#ifndef _DHT11_H_
#define _DHT11_H_

sbit DHT11 = 0x85;

extern unsigned char timeout;

extern const unsigned char store[];

//----------------

extern char *readDHT11();

#endif
