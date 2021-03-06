#ifndef _BMP280_H_
#define _BMP280_H_

//define the i2c address for the BMP280
#define bmp280 0x76

//global variable to store temperature in (used for pressure)
extern long t_fine;

//factory calibration data
#define dig_T1 27314
#define dig_T2 26369
#define dig_T3 -1000

#define dig_P1 38955
#define dig_P2 -10633
#define dig_P3 3024
#define dig_P4 2484
#define dig_P5 118
#define dig_P6 -7
#define dig_P7 15500
#define dig_P8 -14600
#define dig_P9 6000

extern const void bmpReset();
extern const void bmpCalibration();
extern unsigned long bmp280GetPressure();
extern long bmp280GetTemp();
extern void bmpSet(unsigned char settings, unsigned char reg);

#endif