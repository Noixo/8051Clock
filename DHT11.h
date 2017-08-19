#ifndef _DHT11_H_
#define _DHT11_H_

sbit DHT11 = 0x87;
extern char DHTArray[5];

//----------------

extern void readDHT11();
extern char validate(unsigned char store[]);
extern void bin_to_int(unsigned char *array);

#endif