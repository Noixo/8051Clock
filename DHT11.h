#ifndef _DHT11_H_
#define _DHT11_H_

sbit DHT11 = 0x87;
extern char DHTArray[5];
extern char dht11[2];

//----------------

extern char* readDHT11();

#endif
