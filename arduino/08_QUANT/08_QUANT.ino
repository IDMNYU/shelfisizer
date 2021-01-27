// shelfisizer quantizer

#include <Wire.h>
#include <Adafruit_MCP4725.h>

// pitch class defines (with sharp/flat homonyms)
#define C 0
#define Chs 1
#define Cs 2
#define Db 2
#define Dhb 3
#define D 4
#define Dhs 5
#define Ds 6
#define Eb 6
#define Ehb 7
#define E 8
#define Ehs 9
#define Fhb 9
#define F 10
#define Fhs 11
#define Fs 12
#define Gb 12
#define Ghb 13
#define G 14
#define Ghs 15
#define Gs 16
#define Ab 16
#define Ahb 17
#define A 18
#define Ahs 19
#define As 20
#define Bb 20
#define Bhb 21
#define B 22
#define Bhs 23
#define Chb 23
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
  // chromatic scales
  {C, C, Cs, Cs, D, D, Ds, Ds, E, E, F, F, Fs, Fs, G, G, Gs, Gs, A, A, As, As, B, B},                       // 0: raw chromatic 12-TET
  {C, Chs, Cs, Dhb, D, Dhs, Ds, Ehb, E, Ehs, F, Fhs, Fs, Ghb, G, Ghs, Gs, Ahb, A, Ahs, As, Bhb, B, Bhs},    // 1: raw quarter-tone 24-TET

  // western diatonic scales and modes
  {C, C, C, C, D, D, E, E, E, E, F, F, G, G, G, G, A, A, A, A, B, B, B, B},                                 // 2: major scale / ionian
  {C, C, C, C, D, D, Eb, Eb, Eb, Eb, F, F, G, G, G, G, Ab, Ab, Ab, Ab, Bb, Bb, Bb, Bb},                     // 3: (natural) minor scale / aeolian
  {C, C, C, C, D, D, Eb, Eb, Eb, Eb, F, F, G, G, G, G, Ab, Ab, Ab, Ab, B, B, B, B},                         // 4: harmonic minor scale
  {C, C, C, C, D, D, Eb, Eb, Eb, Eb, F, F, G, G, G, G, A, A, A, A, B, B, B, B},                             // 5: melodic (ascending) / jazz minor scale

  // pentatonic scales
  {C, C, C, C, D, D, D, D, E, E, E, E, G, G, G, G, G, A, A, A, A, A, Chi, Chi},                                     // 6: major pentatonic / gong
  {C, C, C, C, D, D, D, D, Eb, Eb, Eb, Eb, G, G, G, G, G, Ab, Ab, Ab, Ab, Ab, Chi, Chi},                            // 7: minor pentatonic / yu
  {C, C, C, C, D, D, D, D, D, F, F, F, F, F, G, G, G, G, A, A, A, A, Chi, Chi},                                     // 8: japanese yo scale / "blues major"
  {C, C, C, C, Db, Db, Db, Db, Db, F, F, F, F, F, G, G, G, G, Ab, Ab, Ab, Ab, Chi, Chi},                            // 9: japanese in scale
  {C, C, C, C, Dhs, Dhs, Dhs, Dhs, Dhs, Fhb, Fhb, Fhb, Fhb, Fhb, Ghs, Ghs, Ghs, Ghs, Ahs, Ahs, Ahs, Ahs, Chi, Chi}, // 10: indonesian slendro-djawar scale

  // messaien's modes of limited transposition
  {C, C, C, C, D, D, D, D, E, E, E, E, Fs, Fs, Fs, Fs, Gs, Gs, Gs, Gs, As, As, As, As},                     // 11: first mode / whole-tone scale (TTTTTT)
  {C, C, Db, Db, Db, Db, E, E, E, E, E, E, Gb, Gb, Gb, Gb, A, A, A, A, Bb, Bb, Chi, Chi},                   // 12: second mode / octatonic diminished scale (STSTSTST)
  {C, C, C, C, D, D, Eb, Eb, E, E, E, E, Gb, Gb, G, G, Ab, Ab, A, A, Bb, Bb, B, B},                         // 13: third mode (TSSTSSTSS)
  {C, C, Db, Db, Db, Db, E, E, E, E, F, F, Gb, Gb, G, G, Ab, Ab, Ab, Ab, B, B, B, B},                       // 14: fourth mode (SSm3SSm3S)
  {C, C, Db, Db, Db, Db, Db, Db, F, F, F, F, Gb, Gb, G, G, G, G, G, G, B, B, B, B},                         // 15: fifth mode (SM3SSM3S)
  {C, C, C, C, D, D, D, D, E, E, F, F, Fs, Fs, Gs, Gs, Gs, Gs, As, As, As, As, B, B},                       // 16: sixth mode (TTSSTTSS)
  {C, C, Db, Db, D, D, Eb, Eb, Eb, Eb, F, F, Gb, Gb, G, G, Ab, Ab, A, A, A, A, B, B},                       // 17: seventh mode (SSSTSSSSTS)

  // heptatonic scales
  {C, C, Cs, Cs, Ds, Ds, Ds, Ds, E, E, E, E, Fs, Fs, G, G, G, G, G, G, Chi, Chi, Chi, Chi},                 // 18: istrian heptatonic (STSTS4th)

  // fixed pattern scales (sim. to analog 'quantizers')
  {C, C, C, C, Eb, Eb, Eb, Eb, Eb, Eb, Gb, Gb, Gb, Gb, Gb, Gb, A, A, A, A, A, A, Chi, Chi},                 // 19: minor third scale
  {C, C, C, C, C, C, E, E, E, E, E, E, E, E, Gs, Gs, Gs, Gs, Gs, Gs, Gs, Gs, Chi, Chi},                     // 20: major 3rd scale
  {C, C, C, C, Ds, Ds, Ds, Ds, E, E, E, E, G, G, G, G, Gs, Gs, Gs, Gs, B, B, B, B},                         // 21: "augmented" scale

  // maqam scales
  
  // D Ehb F G A Bb C D
  // 4 7 10 14 18 20 24 28
  // 0 3 6 10 14 16 20 24
  {0, 0, 3, 3, 3, 6, 6, 6, 6, 10, 10, 10, 10, 14, 14, 16, 16, 16, 16, 20, 20, 20, 24, 24},                   // 22: maqam bayati (jins bayati + jins nahawand)
  // D Eb F# G A Bhb C D 
  // 4 6 12 14 18 21 24 28
  // 0 2 8 10 14 17 20 24
  {0, 0, 2, 2, 2, 2, 8, 8, 8, 10, 10, 10, 10, 14, 14, 14, 17, 17, 17, 20, 20, 20, 24, 24},                  // 23: maqam hijaz (jins hijaz + jins rast)
  // Ehb F G Ahb Ahs C D Ehb
  // 7 10 14 17 19 0 4 7
  // 0 3 7 10 12 17 21 0
  {0, 0, 3, 3, 3, 3, 7, 7, 7, 10, 10, 12, 12, 12, 12, 17, 17, 17, 17, 21, 21, 21, 24, 24},                  // 24: maqam jiharkah (jins jiharkah + jins upper rast)
  // A Bhb C D Ehb F G A
  // 18 21 0 4 7 10 14 18
  // 0 3 6 10 13 16 20 0
  {0, 0, 3, 3, 3, 6, 6, 6, 6, 10, 10, 10, 13, 13, 13, 16, 16, 16, 16, 20, 20, 20, 24, 24},                  // 25: maqam husayni 'ushrayan (jins bayati on la + jins bayati on re)
  // C D Ehb F G A Bhb C
  // 0 4 7 10 14 18 21 0
  // 0 4 7 10 14 18 21 0
  {0, 0, 0, 4, 4, 4, 7, 7, 7, 10, 10, 10, 10, 14, 14, 14, 14, 18, 18, 18, 21, 21, 21, 24},                  // 26: maqam rast (jins rast + jins upper rast)
  // G Ahb B C D Eb F# G
  // 14 17 22 0 4 6 14
  // 0 3 8 10 14 16 0
  {0, 0, 3, 3, 3, 3, 8, 8, 8, 10, 10, 10, 10, 14, 14, 16, 16, 16, 16, 16, 24, 24, 24, 24},                  // 27: maqam shad 'araban (jins hizaj + jins nakriz)
  // Ehb F G Ab B C D Ehb
  // 7 10 14 16 22 0 4 7
  // 0 3 7 9 15 17 21 0
  {0, 0, 3, 3, 3, 7, 7, 7, 9, 9, 9, 9, 9, 15, 15, 15, 17, 17, 17, 17, 21, 21, 21, 24},                      // 28: maqam huzam (jins sikah + jins hijaz + jins rast)
  // C D Eb Fs G Ab B C
  // 0 4 6 12 14 16 22 0
  // 0 4 6 12 14 16 22 0
  {0, 0, 4, 4, 4, 6, 6, 6, 6, 6, 12, 12, 12, 14, 14, 16, 16, 16, 16, 22, 22, 22, 22, 24},                  // 29: maqam nawa athar (jins nikriz + jins hijazkar)
  // Ehb F G Ab B C D Ehb
  // 7 10 14 16 22 0 4 7
  // 0 3 7 9 15 17 21 0
  {0, 0, 3, 3, 3, 7, 7, 7, 9, 9, 9, 9, 9, 15, 15, 15, 17, 17, 17, 21, 21, 21, 21, 24},                      // 30: maqam rahat al-arwar (jins sikah + jins hijaz + jins rast)
  // D Ehb F Gb A Bb C Db - non octaving
  // 4 7 10 12 18 20 0 2
  // 0 3 6 8 14 16 20 22
  {0, 0, 3, 3, 3, 6, 6, 8, 8, 8, 8, 14, 14, 14, 14, 16, 16, 16, 16, 20, 20, 20, 22, 22}                   // 31: maqam saba (jins saba + jins hijaz + jins 'ajam)
};

void setup(void) {
  //Serial.begin(9600);

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
    vout = constrain(map(aout, 0, 121, 0, 4095), 0, 4095); // 121 steps over 5 octaves = quarter-tone resolution
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
      vout = constrain(map(aout, 0, 121, 0, 4095), 0, 4095); // 121 steps over 5 octaves = quarter-tone resolution
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
