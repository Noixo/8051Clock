#ifndef _EEPROM_H_
#define _EEPROM_H_

//size of the EEPROM
#define EEPROMSizeX 0xFF
#define EEPROMSizeY 0x0F

static code char at24 = 0x57;

extern void eepromWriteByte(unsigned char addr1, unsigned char addr2, unsigned char value);
extern unsigned char readByte();
extern unsigned char eepromRandomRead(unsigned char addr1, unsigned char addr2);

#endif