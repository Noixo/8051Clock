#ifndef _BMP280_H_
#define _BMP280_H_

static code char bmp280 = 0x76;

static code unsigned short dig_T1 = 27504;
static code short dig_T2 = 26435;
static code short dig_T3 = -1000;
/*
struct bmp280calibration
{
};
*/
static code short dig_P1 = 36477;
	static code unsigned short dig_P2 = -10685;
	static code short dig_P3 = 3024;
	static code short dig_P4 = 2855;
	static code short dig_P5 = 140;
	static code short dig_P6 = -7;
	static code short dig_P7 = 15500;
	static code short dig_P8 = -14600;
	static code short dig_P9 = 6000;

extern long t_fine;

//extern const unsigned char* bmp280Temp();
extern const void bmpReset();
extern const void bmpCalibration();
extern unsigned char* bmp280GetPressure();
extern int bmp280GetTemp();
extern void bmpSet(unsigned char settings, unsigned char reg);

//unsigned char*

#endif