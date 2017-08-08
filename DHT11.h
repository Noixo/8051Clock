#ifndef DHT11_h_
#define DHT11_h_

sbit DHT11 = 0x90;
extern char DHTArray[40];

//----------------

void readDHT11();


#endif