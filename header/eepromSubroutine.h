#ifndef _EEPROMSUBROUTINE_H_
#define _EEPROMSUBROUTINE_H_

sbit EEPROMSizeLED = 0x82;

extern unsigned char *p_time, eepromLocX, eepromLocY;
extern long bmpTemp;
extern long bmpPressure;

extern void writeSensorData();
extern void eepromScan();
extern void writeHourData();
extern void checkEepromOverflow();

#endif