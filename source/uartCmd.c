/* V1.0, by Matthew Whiteley
Purpose: Read UART and perform
operations based on that.

COMMANDS:
d = dump EEPROM contents
e = erase EEPROM contents (11-END)

c = clear max/min sensor data, locations: 0-10
s = set time
*/

#include "uartCmd.h"
#include "eeprom.h"
#include "serial.h"
#include "timing.h"

//#define ENDSENSORDATA 8
extern bit eepromFull;
//Erase the EEPROM contents exclusing sensor data
void eepromClear()
{
	//j starts at 8 to avoid erasing sensor data
	unsigned char i, j = eepromSensorMax;
	
	eepromFull = 0;
	for(i = 0; i <= 0x0F; i++)
	{
		for(j; j < 0xFF; j++)
		{
			eepromWriteByte(i, j, 0xFF);
			ms_delay(15);
		}
		//change j to 0 to reset and let it erase 0-9 after sensor data
		j = 0;
	}
	serial_send('D');
	serial_send('\r');
	serial_send('\n');
}

//dumps entire EEPROM through UART
void dumpRom()
{
	unsigned char i, j;
	
	for(i = 0; i <= 0x0F; i++)
		{
			for(j = 0; j < 0xFF; j++)
			{
				serial_convert(eepromRandomRead(i,j));
				serial_send(' ');
			}
			serial_send('\r');
			serial_send('\n');
		}
}

//erase only the sensor portion of data
void eraseSensors()
{
	unsigned char j;
	
	for(j = 0; j < eepromSensorMax; j++)
	{
		//20 is chosen to ensure temp readings can erase it as it goes higher and lower
		eepromWriteByte(0, j, 20);
		ms_delay(15);
	}
	/*
	//clearing 
	for(j = 0; j < )
	*/
	serial_send('D');
	serial_send('\r');
	serial_send('\n');
}

//main program to check and run subprocedures.
void uartCheck()
{
	switch(serial_receive())
	{
		case 'd':
			dumpRom();
			break;
		
		case 'e':
			eepromClear();
			break;
		
		case 'c':
			eraseSensors();
			break;
		
		//default:
			//break;
	}
}
