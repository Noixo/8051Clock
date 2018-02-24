#ifndef _EEPROMSUBROUTINE_H_
#define _EEPROMSUBROUTINE_H_

//32kb eeprom
#define eepromSize 16

//WARNING 2 DECLARATIONS OF THIS DEFINE
#define eepromSensorMax 8

#define tempMax 0
#define tempMin 1

#define humidityMax 2
#define humidityMin 3

#define pressureMaxUpper 4
#define pressureMaxLower 5

#define pressureMinUpper 6
#define pressureMinLower 7

extern unsigned char *p_time, eepromLocX, eepromLocY;

extern char eepromFull;
//extern long bmpTemp;
//extern unsigned long bmpPressure;
extern unsigned char *p_dht11;
extern char INTbmpTemp;
extern unsigned short INTbmpPressure;

extern bit checkValid();
extern void compare();
extern void writeSensorData();
extern void eepromScan();
extern void writeHourData();
extern void checkEepromOverflow();


//void compare(unsigned char currentValue unsigned char eepromValue);

#endif