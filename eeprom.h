#ifndef _EEPROM_H_
#define _EEPROM_H_

static code char at24 = 0x57;

extern void eepromWriteByte(unsigned char addr1, unsigned char addr2, unsigned char value);
extern void eepromWritePage(unsigned char* addr, unsigned char value);
unsigned char readByte();
char wearCheck();
void eepromClear();
extern unsigned char eepromRandomRead(unsigned char addr1, unsigned char addr2);
//extern unsigned char* eepromReadPage(unsigned char* addr);

#endif