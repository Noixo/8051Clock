#ifndef _EEPROMSUBROUTINE_H_
#define _EEPROMSUBROUTINE_H_

//32kb eeprom
#define eepromSize 16

//WARNING 2 DECLARATIONS OF THIS DEFINE
#define eepromSensorMax 8

sbit EEPROMSizeLED = 0x82;

extern unsigned char *p_time, eepromLocX, eepromLocY;

extern bit eepromFull;
extern unsigned long bmpTemp;
extern unsigned long bmpPressure;

extern bit checkBMPValid();
extern void writeSensorData();
extern void eepromScan();
extern void writeHourData();
extern void checkEepromOverflow();

#endif