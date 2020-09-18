// shelfisizer quantizer

#include <Wire.h>
#include <Adafruit_MCP4725.h>

// pitch class defines (with sharp/flat homonyms)
#define C 0
#define Cqs 1
#define Cs 2
#define Db 2
#define Dqb 3
#define D 4
#define Dqs 5
#define Ds 6
#define Eb 6
#define Eqb 7
#define E 8
#define Eqs 9
#define Fqb 9
#define F 10
#define Fqs 11
#define Fs 12
#define Gb 12
#define Gqb 13
#define G 14
#define Gqs 15
#define Gs 16
#define Ab 16
#define Aqb 17
#define A 18
#define Aqs 19
#define As 20
#define Bb 20
#define Bqb 21
#define B 22
#define Bqs 23
#define Cqb 23
#define Chi 24

Adafruit_MCP4725 dac1, dac2;
float ain1 = 0.; // analog read value 1
float ain2 = 0.; // analog read value 2
char qtin, o, pc, mpc, rot; // quarter-tone in, octave, pitch class, mapped pitch class, rotation
int aout, vout; // input and output voltages
byte scale = 7; // which scale
boolean doublemode = true; // single or double mode
boolean amode = 0; // acquisition mode (0 = continues; 1 = s/h)
boolean trig1, trig2, otrig1, otrig2; // trigger voltages
float smooth = 0.0; // smoothing value

byte scaledata[][24] = {
  {C, C, Cs, Cs, D, D, Ds, Ds, E, E, F, F, Fs, Fs, G, G, Gs, Gs, A, A, As, As, B, B},                       // 0: raw chromatic 12-TET
  {C, Cqs, Cs, Dqb, D, Dqs, Ds, Eqb, E, Eqs, F, Fqs, Fs, Gqb, G, Gqs, Gs, Aqb, A, Aqs, As, Bqb, B, Bqs},    // 1: raw quarter-tone 24-TET

  // Western diatonic scales and modes
  {C, C, C, C, D, D, E, E, E, E, F, F, G, G, G, G, A, A, A, A, B, B, B, B},                                 // 2: major scale / ionian
  {C, C, C, C, D, D, Eb, Eb, Eb, Eb, F, F, G, G, G, G, Ab, Ab, Ab, Ab, Bb, Bb, Bb, Bb},                     // 3: (natural) minor scale / aeolian
  {C, C, C, C, D, D, Eb, Eb, Eb, Eb, F, F, G, G, G, G, Ab, Ab, Ab, Ab, B, B, B, B},                         // 4: harmonic minor scale
  {C, C, C, C, D, D, Eb, Eb, Eb, Eb, F, F, G, G, G, G, A, A, A, A, B, B, B, B},                             // 5: melodic (ascending) / jazz minor scale

  // pentatonic scales
  {C, C, C, C, D, D, D, D, E, E, E, E, G, G, G, G, G, A, A, A, A, A, Chi, Chi},                                     // 6: major pentatonic / gong
  {C, C, C, C, D, D, D, D, Eb, Eb, Eb, Eb, G, G, G, G, G, Ab, Ab, Ab, Ab, Ab, Chi, Chi},                            // 7: minor pentatonic / yu
  {C, C, C, C, D, D, D, D, D, F, F, F, F, F, G, G, G, G, A, A, A, A, Chi, Chi},                                     // 8: japanese yo scale / "blues major"
  {C, C, C, C, Db, Db, Db, Db, Db, F, F, F, F, F, G, G, G, G, Ab, Ab, Ab, Ab, Chi, Chi},                            // 9: japanese in scale
  {C, C, C, C, Dqs, Dqs, Dqs, Dqs, Dqs, Fqb, Fqb, Fqb, Fqb, Fqb, Gqs, Gqs, Gqs, Gqs, Aqs, Aqs, Aqs, Aqs, Chi, Chi}, // 10: indonesian slendro-djawar scale

  // messaien's modes of limited transposition
  {C, C, C, C, D, D, D, D, E, E, E, E, Fs, Fs, Fs, Fs, Gs, Gs, Gs, Gs, As, As, As, As},                     // 11: first mode / whole-tone scale (TTTTTT)
  {C, C, Db, Db, Db, Db, E, E, E, E, E, E, Gb, Gb, Gb, Gb, A, A, A, A, Bb, Bb, Chi, Chi},                   // 12: second mode / octatonic diminished scale (STSTSTST)
  {C, C, C, C, D, D, Eb, Eb, E, E, E, E, Gb, Gb, G, G, Ab, Ab, A, A, Bb, Bb, B, B},                         // 13: third mode (TSSTSSTSS)
  {C, C, Db, Db, Db, Db, E, E, E, E, F, F, Gb, Gb, G, G, Ab, Ab, Ab, Ab, B, B, B, B},                       // 14: fourth mode (SSm3SSm3S)
  {C, C, Db, Db, Db, Db, Db, Db, F, F, F, F, Gb, Gb, G, G, G, G, G, G, B, B, B, B},                         // 15: fifth mode (SM3SSM3S)
  {C, C, C, C, D, D, D, D, E, E, F, F, Fs, Fs, Gs, Gs, Gs, Gs, As, As, As, As, B, B},                       // 16: sixth mode (TTSSTTSS)
  {C, C, Db, Db, D, D, Eb, Eb, Eb, Eb, F, F, Gb, Gb, G, G, Ab, Ab, A, A, A, A, B, B},                       // 17: seventh mode (SSSTSSSSTS)

  // heptatonic scales
  {C, C, Cs, Cs, Ds, Ds, Ds, Ds, E, E, E, E, Fs, Fs, G, G, G, G, G, G, Chi, Chi, Chi, Chi},                 // 18: istrian heptatonic

  {C, C, C, C, D, D, D, D, E, E, E, E, Fs, Fs, Fs, Fs, Gs, Gs, Gs, Gs, As, As, As, As},                     // 19: whole-tone scale
  {C, C, C, C, D, D, D, D, E, E, E, E, Fs, Fs, Fs, Fs, Gs, Gs, Gs, Gs, As, As, As, As},                     // 20: whole-tone scale

  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 21: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 22: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 23: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 24: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 25: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 26: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 27: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 28: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 29: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb},                  // 30: maqam hijaz (jins hijaz + jins rast)
  {C, C, C, Db, Db, Db, E, E, E, E, F, F, F, G, G, G, Aqb, Aqb, Aqb, Aqb, Bb, Bb, Bb, Bb}                   // 31: maqam hijaz (jins hijaz + jins rast)
};

void setup(void) {
//  Serial.begin(9600);

  pinMode(2, INPUT); // channel A sample
  pinMode(3, INPUT); // channel B sample
  pinMode(4, INPUT_PULLUP); // switch 1
  pinMode(5, INPUT_PULLUP); // switch 2
  pinMode(6, INPUT_PULLUP); // switch 3
  pinMode(7, INPUT_PULLUP); // switch 4
  pinMode(8, INPUT_PULLUP); // switch 5
  pinMode(9, INPUT_PULLUP); // double switch
  pinMode(10, INPUT_PULLUP); // mode switch

  dac1.begin(0x62);
  dac2.begin(0x63);

}

void loop(void) {

  boolean a = digitalRead(4);
  boolean b = digitalRead(5);
  boolean c = !digitalRead(6);
  boolean d = !digitalRead(7);
  boolean e = !digitalRead(8);
  scale = e * 1 + d * 2 + c * 4 + b * 8 + a * 16;

  rot = map(1023 - analogRead(A3), 0, 1023, 0, 24); // backwards
  smooth = 0.99*(1023 - analogRead(A2)) / 1023.; // backwards

  doublemode = !digitalRead(9);
  amode = !digitalRead(10);
  if (amode) // sample and hold
  {
    trig1 = digitalRead(2);
    if (doublemode) {
      trig2 = digitalRead(3);
    }
  }

  // DAC1
  if (!amode || (trig1 == 1 && otrig1 == 0)) {
    ain1 = smooth * ain1 + (1.0 - smooth) * (float)(analogRead(A0) / 1023.); // 1 volt-per-octave pitch translation
    qtin = (char)(ain1 * 121);
    o = qtin / 24; // octave
    pc = qtin % 24; // pitch class (quarter-tone)
    pc += rot;
    if (pc > 23) o += 1;
    mpc = scaledata[scale][pc % 24]; // lookup against scale
    aout = (o * 24) + mpc - rot; // recombine
    vout = map(aout, 0, 121, 0, 4095); // 121 steps over 5 octaves = quarter-tone resolution
    dac1.setVoltage(vout, false); // update dac
  }

  if (doublemode) { // second dac engaged
    // DAC2
    if (!amode || (trig2 == 1 && otrig2 == 0)) {
      ain2 = smooth * ain2 + (1.0 - smooth) * (float)(analogRead(A1) / 1023.); // 1 volt-per-octave pitch translation
      qtin = (char)(ain2 * 121);
      o = qtin / 24; // octave
      pc = qtin % 24; // pitch class (quarter-tone)
      pc += rot;
      if (pc > 23) o += 1;
      mpc = scaledata[scale][pc % 24]; // lookup against scale
      aout = (o * 24) + mpc - rot; // recombine
      vout = map(aout, 0, 121, 0, 4095); // 121 steps over 5 octaves = quarter-tone resolution
      dac2.setVoltage(vout, false); // update dac
    }
  }

  if (amode) // store previous trigger for sample and hold
  {
    otrig1 = trig1;
    if (doublemode) {
      otrig2 = trig2;
    }
  }
}
