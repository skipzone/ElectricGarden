/* This is Single_Buzzer.ino by Michael Spindler 12-11-2019
 * exactly the same sketch is listed as Theramin.ino in 
 * .../ElectricGarden/Arduino/Theramin/
 * 
 *  
 *  This sketch was operationally checked on a NANO on 1-5-2020
 *  and it worked.  
 *  
 *  Pin 9, the speaker output, is pin D9.
 *  DON'T USE THE OUTPUT ON AN 8 OHM SPEAKER WITHOUT A
 *  (220 OHM ?) RESISTOR IN SERIES TO LIMIT CURRENT 
 *  
 *  SDA is A4 
 *  SCL is A5
 *  VIN is 5v
 *  GND is GND
 *  
 *  See the wiring diagram DUAL_XL53L0X, sketch # CFS-1-5-2020-B.
 *
 *  You can expect similar execution of the sketch on Mega 2560  
 *  and Uno dev boards, but pin names may vary.
 *
 *  This example shows how to get single-shot range
 measurements from the VL53L0X. The sensor can optionally be
 configured with different ranging profiles, as described in
 the VL53L0X API user manual, to get better performance for
 a certain application. This code is based on the four
 "SingleRanging" examples in the VL53L0X API.

 The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;


// Uncomment this line to use long range mode. This
// increases the sensitivity of the sensor and extends its
// potential range, but increases the likelihood of getting
// an inaccurate reading because of reflections from objects
// other than the intended target. It works best in dark
// conditions.

// #define LONG_RANGE


// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

#define HIGH_SPEED  // if you choose HIGH_ACCURACY you can hear the steps in pitch
// #define HIGH_ACCURACY  

const int SPEAKER = 9; // use pin D9 on Nano

const int MAXFREQUENCY = 1200;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
}

void loop()
{
  int dist = sensor.readRangeSingleMillimeters();
  
  Serial.print(dist);
  if (sensor.timeoutOccurred()) { 
        Serial.print(" TIMEOUT"); 
        }
  Serial.println();

 if(dist <= MAXFREQUENCY ){
        tone(SPEAKER, dist );
        } else {
              noTone(SPEAKER); // comment out noTone() to sustain last tone
        }
        
}
