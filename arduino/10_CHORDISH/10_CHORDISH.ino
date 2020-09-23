#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>

#define m3 6/5
#define M3 5/4
#define P4 4/3
#define P5 3/2

Adafruit_MCP4725 dac1, dac2;
Adafruit_ADS1015 ads;
float ain = 0.; // analog read value from ADC range of 4095
int aout1, aout2, vout1, vout2; // input and output voltages
float smooth = 0.0; // smoothing value
float step = 4095/5/12;

// for toggles later
// float intervals[4]= {m3, M3, P4, P5};

void setup() {

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac1.begin(0x62);
  dac2.begin(0x63);
  ads.begin();

}

void loop() {

  int16_t adc0, adc1, adc2, adc3;
  adc0 = ads.readADC_SingleEnded(0);
  //  adc1 = ads.readADC_SingleEnded(1);
  //  adc2 = ads.readADC_SingleEnded(2);
  //  adc3 = ads.readADC_SingleEnded(3);

  smooth = 0.99 * (4095 - adc0) / 4095.; // backwards

  ain = smooth * ain + (1.0 - smooth) * (float)(adc0 / 4095.); // 1 volt-per-octave pitch translation
  aout1 = ain * M3; // major 3rd ratio
  aout2 = ain * P5; // major 5th ratio
  if (aout1 > 1.) aout1 *= 0.5;
  if (aout2 > 1.) aout2 *= 0.5;
  vout1 = map(vout1, 0, 1, 0, 4095);
  vout2 = map(vout2, 0, 1, 0, 4095);
  dac1.setVoltage(vout1, false); // update dac
  dac2.setVoltage(vout2, false); // update dac

}
