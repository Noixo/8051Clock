#include "eepromSubroutine.h"
#include "eeprom.h"
//#include "timing.h"

//stores location of first blank eeprom location
 unsigned char eepromLocX, eepromLocY;

/**
* @return returns 0 to indicate valid. 1 invalid.
* 
*/
bit checkBMPValid()
{
	//BMP280 temp stored in unsigned state, even though signed
	if(INTbmpTemp > 85 || INTbmpPressure > 1100 || INTbmpPressure < 300)
		return 1;
	return 0;
}

void compare(unsigned char currentValue, unsigned char eepromValue, char eepromLoc)
{
	if(currentValue > eepromValue)
	{
		eepromWriteByte(0, eepromLoc, currentValue);
	}
	
	if(currentValue < eepromValue)
	{
		eepromWriteByte(0, eepromLoc+1, currentValue);
	}
}

//check and update data if necessary
void writeSensorData()
{
	//array to store data in
	unsigned char sensorData[eepromSensorMax];
	char i;
	//unsigned char *pointer = &INTbmpTemp;
	
	//cancel if invalid readings
	if(checkBMPValid() == 1)
		return;
	
	//loop to put sensor data in
	for(i = 0; i < eepromSensorMax; i++)
	{
		sensorData[i] = eepromRandomRead(0,i);
	}
	
	//check if INTbmpTemp is 0xFF, if so then data has be wiped
	if(INTbmpTemp == 0xFF)
	{
		//compare(INTbmpTemp, 0, );
		/*
		eepromWriteByte(0, 0, INTbmpTemp);
		eepromWriteByte(0, 1, INTbmpTemp);
		
		//humidity
		eepromWriteByte(0, 2, *(p_dht11));
		eepromWriteByte(0, 3, *(p_dht11));
		
		eepromWriteByte(0, 4, INTbmpPressure);
		eepromWriteByte(0, 5, INTbmpPressure);
		
		eepromWriteByte(0, 6, INTbmpPressure);
		eepromWriteByte(0, 7, INTbmpPressure);
		*/
	}
	else
	{
		compare(INTbmpTemp, sensorData[0], tempMax);
	
		compare(p_dht11[2], sensorData[2], humidityMax);
		
		//????
		compare(INTbmpPressure / 100, sensorData[4], pressureMaxUpper);
		compare(INTbmpPressure % 100, sensorData[5], pressureMaxUpper);
		
		compare(INTbmpPressure / 100, sensorData[6], pressureMinUpper);
		compare(INTbmpPressure % 100, sensorData[7], pressureMinUpper);
	}
	
	/*
	//write data if larger or smaller
	for(pointer; pointer != 0x80; pointer++)
	{
		if(&pointer > sensorData[i])
		{
			//return 
			eepromWriteByte(0, i, *pointer);
		}
		if(&pointer < sensorData[i])
		{
			//return 
			eepromWriteByte(0, i, *pointer);
		}
	}
	*/
	
	//-----------------------------------------------------------
/*
	//if current temp is greater than the highest recorded temp
	if(INTbmpTemp > sensorData[tempMax])
	{
		eepromWriteByte(0, tempMax, INTbmpTemp);
	}
	
	//if current temp is less than the lowest recorded temp
	if(INTbmpTemp < sensorData[tempMin])
	{
		eepromWriteByte(0, tempMin, INTbmpTemp);
	}
	//-----------------------------------------------------------
	
	//DHT11 PRESSURE DATA
	//--
	//--
	
	//-----------------------------------------------------------
	//if latest pressure is bigger than eeprom pressure
	//checks first 2 values
	if(INTbmpPressure / 100 > sensorData[pressureMaxUpper])
	{
		eepromWriteByte(0, pressureMaxUpper, INTbmpPressure/100);
	}
	
	// checks if lower two values are larger
	if(INTbmpPressure % 100 > sensorData[pressureMaxLower])
	{
		eepromWriteByte(0, pressureMaxLower, INTbmpPressure % 100);
	}
	//-----------------------------------------------------------
	if(INTbmpPressure / 100 < sensorData[pressureMinUpper])
	{
		eepromWriteByte(0, pressureMinUpper, INTbmpPressure / 100);
	}
	
	if(INTbmpPressure % 100 < sensorData[pressureMinLower])
	{
		eepromWriteByte(0, pressureMinLower, INTbmpPressure % 100);
	}
	*/
}
/*
//scans EEPROM to find and record 0xFF location
void eepromScan()
{
	eepromFull = 0;
	
	for(eepromLocY = 0; eepromLocY < eepromSize; eepromLocY++)
	{
		//start at end of sensor data +1 to avoid getting last byte of data
		for(eepromLocX = eepromSensorMax+1; eepromLocX < 0xFF; eepromLocX++)
		{
			//loop till find empty location
			if(eepromRandomRead(eepromLocY, eepromLocX) == 0xFF)
				return;	//empty location found
		}
	}
	eepromFull = 1;
}
*/
/*
void writeHourData()
{
	//cancel if invalid readings
	if(checkBMPValid == 1 || eepromFull == 1)
		return;
	
	//write temp
	eepromWriteByte(eepromLocY, eepromLocX, INTbmpTemp);
	checkEepromOverflow();
	
	/*
	//write humidity
	eepromWriteByte(eepromLocY, eepromLocX, bmpTemp/100);
	checkEepromOverflow();
	
	//write pressure
	eepromWriteByte(eepromLocY, eepromLocX, bmpTemp/100);
	checkEepromOverflow();
	eepromWriteByte(eepromLocY, eepromLocX, bmpTemp/100);
	checkEepromOverflow();
	eepromWriteByte(eepromLocY, eepromLocX, bmpTemp/100);
	checkEepromOverflow();
	
}
*/
/*
//turn on LED if running out of room and make sure location
//doesn't overflow
void checkEepromOverflow()
{
	//sink current if EEPROM running out of room
	if(eepromLocY > 0x0E)
		EEPROMSizeLED = 0;
	//increment to next page
	if(eepromLocX == 0xFF)
		eepromLocY++;
}
*/
/*
char wearCheck()
{
	unsigned char i, j, wear = 0;
	
	// fill each location in eeprom, alternating 0 and 1
	for(i = 0; i <  0xF; i++)
	{
		for(j = 0; j < 0xFF; j++)
		{
			eepromWriteByte(i, j, wear);
			wear ^= 1;
			
			serial_convert(i);
			serial_send(' ');
			//if(eepromReadByte() != wear)
				//return -1;
			ms_delay(10);
		}
	}
	//check if value is not 1 or 0
	return 0;
}
*/
