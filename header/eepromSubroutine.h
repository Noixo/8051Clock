#ifndef _EEPROMSUBROUTINE_H_
#define _EEPROMSUBROUTINE_H_

//32kb eeprom
//#define EEPROMSIZE 16

#define tempMax 1
#define tempMin 2

#define humidityMax 3
#define humidityMin 4

#define pressureMaxUpper 5
#define pressureMaxLower 6

#define pressureMinUpper 7
#define pressureMinLower 8

extern char eepromFull;
extern unsigned char *p_dht11;
extern char INTbmpTemp;
extern unsigned long bmpPressure;

extern char checkValid();
extern void compare(unsigned char currentValue, char max, char min);
extern void writeSensorData();
extern void eepromScan();
extern void writeHourData();
extern void checkEepromOverflow();

#endif