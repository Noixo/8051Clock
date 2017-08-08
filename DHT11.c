#include "DHT11.h"

void readDHT11()
{
	DHT11 = 0;
	//delay(18);	//delay 18ms
	DHT11 = 1;
	
	DHT11 = 0;
	//delay(80); // 80 microseconds
	DHT11 = 1;
}