#ifndef _BMP280_H_
#define _BMP280_H_

static code char bmp280 = 0x76;

static code unsigned short dig_T1 = 27504;//27314;
static code short dig_T2 = 26435;//26369;
static code short dig_T3 = -1000;

//extern const unsigned char* bmp280Temp();
extern const void bmpReset();
extern const void bmpCalibration();
extern unsigned char* bmp280GetData();
extern int bmp280GetTemp();
extern void bmpSet(unsigned char settings, unsigned char reg);

//unsigned char*

#endif