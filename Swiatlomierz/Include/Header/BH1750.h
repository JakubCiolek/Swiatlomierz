
#ifndef BH1750_h
#define BH1750_h

//#if (ARDUINO >= 100)
//#  include <Arduino.h>
//#else
//#  include <WProgram.h>
//#endif

#include "i2c.h"

// Uncomment, to enable debug messages
// #define BH1750_DEBUG

// No active state
#define BH1750_POWER_DOWN 0x00

// Waiting for measurement command
#define BH1750_POWER_ON 0x01

// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_RESET 0x07

// Default MTreg value
#define BH1750_DEFAULT_MTREG 69
#define BH1750_MTREG_MIN 31
#define BH1750_MTREG_MAX 254

enum Mode {
	// same as Power Down
	UNCONFIGURED = 0,
	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
	CONTINUOUS_HIGH_RES_MODE = 0x10,
	// Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
	CONTINUOUS_HIGH_RES_MODE_2 = 0x11,
	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
	CONTINUOUS_LOW_RES_MODE = 0x13,
	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
	ONE_TIME_HIGH_RES_MODE = 0x20,
	// Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
	ONE_TIME_HIGH_RES_MODE_2 = 0x21,
	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
	ONE_TIME_LOW_RES_MODE = 0x23
};
struct BH1750 {
  uint8_t BH1750_I2CADDR;
  uint8_t BH1750_MTreg = (uint8_t)BH1750_DEFAULT_MTREG;
  // Correction factor used to calculate lux. Typical value is 1.2 but can
  // range from 0.96 to 1.44. See the data sheet (p.2, Measurement Accuracy)
  // for more information.
  const float BH1750_CONV_FACTOR = 1.2;
  Mode BH1750_MODE = UNCONFIGURED;
  unsigned long lastReadTimestamp;
};

BH1750* setup_BH1750(uint8_t addr = 0x23);
short begin(BH1750* bh1750, Mode mode = CONTINUOUS_HIGH_RES_MODE, uint8_t addr = 0x23);
short configure(BH1750* bh1750,Mode mode);
short setMTreg(BH1750* bh1750,uint8_t MTreg);
short measurementReady(BH1750* bh1750,short maxWait = false);
float readLightLevel(); 
#endif