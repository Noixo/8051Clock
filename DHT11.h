#ifndef DHT11_H_
#define DHT11_H_

sbit DHT11 = 0x90;
extern char DHTArray[40];

//----------------

extern void readDHT11();


#endif