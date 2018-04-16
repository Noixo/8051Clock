#include "eepromSubroutine.h"
#include "eeprom.h"

/**
* @return returns 0 to indicate valid. 1 invalid.
* 
*/

char checkValid()
{
	if(INTbmpTemp > 85 || bmpPressure > 110000 || bmpPressure < 300
		|| (*(p_dht11)+2) > 100 || (*(p_dht11)+2) == 0)
		return 1;
	return 0;
}

void compare(unsigned char currentValue, char max, char min)
{
		//if the latest sensor data is larger than the value currenly stored inside EEPROM
		if(currentValue > eepromRandomRead(0, max))
		{
			//replace with latest data
			eepromWriteByte(0, max, currentValue);
		}
		
		//same but for minimum value
		if(currentValue < eepromRandomRead(0, min))
		{
			eepromWriteByte(0, min, currentValue);
		}
}

void forceStore()
{
	if (checkValid() == 1)
		return;

	eepromWriteByte(0, tempMax, INTbmpTemp);
	eepromWriteByte(0, tempMin, INTbmpTemp);
	eepromWriteByte(0, humidityMax, *(p_dht11)+2);
	eepromWriteByte(0, humidityMin, *(p_dht11)+2);
		
	//max and min of pressure takes up 2 spaces each
	eepromWriteByte(0, pressureMaxUpper, bmpPressure / 1000);	//gets first 3 digits
	eepromWriteByte(0, pressureMaxLower, (bmpPressure % 1000) / 100);	//gets last 3 digits then converts to hPa
	
	eepromWriteByte(0, pressureMinUpper, bmpPressure / 1000);
	eepromWriteByte(0, pressureMinLower, (bmpPressure % 1000) / 100);
}

//check and update data if necessary
void writeSensorData()
{
	//cancel if invalid readings
	if(checkValid() == 1)
		return;
	
	//if none of the values are invalid, compare values against EEPROM values and save if needed
	
	compare(INTbmpTemp, tempMax, tempMin);
	compare(*(p_dht11+2), humidityMax, humidityMin);
	
	compare(bmpPressure / 1000, pressureMaxUpper, pressureMinUpper);
	compare((bmpPressure % 1000) / 100, pressureMaxLower, pressureMinLower);
}