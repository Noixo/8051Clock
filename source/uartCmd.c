/*
Purpose: Read UART and perform
operations based on that.

COMMANDS:
d = dump EEPROM contents
e = erase EEPROM contents (11-END)

c = clear max/min sensor data, locations: 0-8
s = set time
*/

#include "uartCmd.h"
#include "eeprom.h"
#include "serial.h"
#include "eepromSubroutine.h"
#include "ds3231.h"

/*
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
*/

//erase only the sensor portion of data
void eraseSensors()
{
	//force the EEPROM data to be replaced
	forceStore();
}

/*FORMAT SEQUENCE: 1. Enter 's'
2. type in date in format: sec (00), min (00), hour (00) month(00), year(00), day/century(00)
no spaces*/
/*
void setTime()
{
	//set up array to store time in
	unsigned char *time;
	
	time = serial_recieve_array();
	
	rtc_set_time(time);
}
*/
//main program to check and run subprocedures.
void uartCheck()
{
	switch(serial_receive())
	{
		/*
		case 'd':
			dumpRom();
			break;
		*/
		/*
		case 'e':
			eepromClear();
			break;
		*/
		case 'c':
			eraseSensors();
			break;
		/*
		case 's':
			setTime();
			break;
		*/
		default:
			break;
	}
	serial_send_array("D\r\n");
}
