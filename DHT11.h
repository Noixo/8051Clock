#ifndef _DHT11_H_
#define _DHT11_H_

sbit DHT11 = 0x87;
extern char DHTArray[40];

//----------------

extern char *readDHT11();
extern void validate(char store[]);

#endif