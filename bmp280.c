#include "bmp280.h"
#include "i2c.h"

unsigned char* bmp280GetData()
{
	i2c_start();
	
	(void) i2c_device_id(0x77, 0);
	//get temp
	i2c_write(0x2E);
}

//void unsigned char*