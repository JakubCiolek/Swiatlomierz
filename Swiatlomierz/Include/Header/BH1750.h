
#ifndef BH1750_h
#define BH1750_h

#include "twi_master.h"
#include <util/delay.h>
//#define BH1750_DEFAULT_MTREG 69
//#define BH1750_MTREG_MIN 31
//#define BH1750_MTREG_MAX 254

// Measurement at 1 lux resolution. Measurement time is approx 120ms.
//#define	ONE_TIME_HIGH_RES_MODE = 0x20,
//
//
//uint8_t BH1750_I2CADDR = 0x23;
//uint8_t BH1750_MTreg = (uint8_t)BH1750_DEFAULT_MTREG;
//uint8_t ONE_TIME_HIGH_RES_MODE = 0x20;
// Correction factor used to calculate lux. Typical value is 1.2 but can
// range from 0.96 to 1.44. See the data sheet (p.2, Measurement Accuracy)
// for more information.

float ReadLight();
//short begin( ONE_TIME_HIGH_RES_MODE , uint8_t addr = 0x23);
//short configure();
//short setMTreg(uint8_t MTreg);
//short measurementReady(short maxWait = false);
//float readLightLevel();
#endif