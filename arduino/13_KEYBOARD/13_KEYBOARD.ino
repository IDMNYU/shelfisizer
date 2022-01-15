// pins:
// A0 - rate knob (input)
// D2 - trigger out A
// D3 - gate out A
// D4 - start/stop button (input)
// D5 - pressure out A
// D6 - pressure out B
// D7 - trigger out B
// D8 - gate out B
// D9 - clock out

#include <Wire.h>
#include "Adafruit_MPR121.h"
#include <Adafruit_MCP4725.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

#define DEBUG false

// four capacitive touch chips:
Adafruit_MPR121 cap1 = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
Adafruit_MPR121 cap3 = Adafruit_MPR121();
Adafruit_MPR121 cap4 = Adafruit_MPR121();
// two 12-bit dacs:
Adafruit_MCP4725 dac1, dac2;
// LED
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

int vout1, vout2;
float pressureval; // pressure value
float psmooth = 0.9; // y(n-1) coefficient
int ptemp; // raw pressure
byte curkey; // current key
int pcount; //polyphony count
int drefresh = true; // display refresh
int tlen1, tlen2; // trigger length
int TDUR = 1; // trigger length
int POFF = 40; // pressure offset value
float VPST = 68.25; // volts per semitone

// sequencer:
bool gogogo = false; // sequencer / arp state
bool oldss; // old start/stop button state
float rate = 0; // sequencer rate
int pulseout = 0; // pulse value
unsigned long now = 0; // current time
unsigned long then = 0; // previous time
char seq[256]; // sequencer
char seqlen = 0; // sequencer length
char seqptr = 0; // sequencer position
bool arp[37]; // arpeggiator
int arpcount; // arpeggio count
char arpptr = 0; // arpeggiator position
bool arpdir = false; // arp updown direction

// function keys:
bool latch = false; // hold/latch key flip (A4)
int arpmode = 0; // arpeggio mode (A3) - UP, DN, UP/DN, RND

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched1 = 0;
uint16_t currtouched1 = 0;
uint16_t lasttouched2 = 0;
uint16_t currtouched2 = 0;
uint16_t lasttouched3 = 0;
uint16_t currtouched3 = 0;
uint16_t lasttouched4 = 0;
uint16_t currtouched4 = 0;

char *notes[] = {"C", "C#/Db", "D", "D#/Eb", "E", "F", "F#/Gb", "G", "G#/Ab", "A", "A#/Bb", "B"};
char *arpmodes[] = {"UP ", "DN ", "UP/DN ", "RND "};

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
    while (!Serial) { // needed to keep leonardo/micro from starting too fast!
      delay(10);
    }
  }

  pinMode(2, OUTPUT); // trigger A
  pinMode(3, OUTPUT); // gate A
  pinMode(5, OUTPUT); // pressure A
  pinMode(7, OUTPUT); // trigger B
  pinMode(8, OUTPUT); // gate B
  pinMode(6, OUTPUT); // pressure B
  pinMode(4, INPUT_PULLUP); // start/stop
  pinMode(9, OUTPUT); // clock

  if (DEBUG) Serial.println("YAY KEYBOARD");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap1.begin(0x5D)) {
    //if(DEBUG) Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 A found!");
  if (!cap2.begin(0x5C)) {
    //if(DEBUG) Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 B found!");
  if (!cap3.begin(0x5B)) {
    //if(DEBUG) Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 C found!");
  if (!cap4.begin(0x5A)) {
    //if(DEBUG) Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 D found!");

  // start DACs:
  dac1.begin(0x62);
  dac2.begin(0x63);

  // start LED:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Hi there");
  display.println("YAY");
  display.setCursor(0, 0);
  display.display(); // actually display all of the above


  pressureval = 0.;
  curkey = 0;
  vout1 = 0;
  vout2 = 0;
}

void loop() {

  //
  // INPUTS
  //

  // PADS
  
  // Get the currently touched pads
  currtouched1 = cap1.touched(); // bitmask
  currtouched2 = cap2.touched(); // bitmask
  currtouched3 = cap3.touched(); // bitmask
  currtouched4 = cap4.touched(); // bitmask

  for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched1 & _BV(i)) && !(lasttouched1 & _BV(i)) ) {
      if (DEBUG) Serial.print("keydown A "); Serial.println(i);
      if (i == 4) latch = !latch; // latch key
      if (i == 3) arpmode = (arpmode + 1) % 4; // arpeggio mode
      if (latch == false) // clear arp queue
      {
        pcount = 0;
        for (int i = 0; i < 37; i++)
        {
          arp[i] = false;
        }
      }
      if (i > 4) // notes only
      {
        pcount++; // polyphony count up
        tlen1 = TDUR; // new trigger
        curkey = i - 5;
        arp[curkey] = latch ? !arp[curkey] : true;
      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched1 & _BV(i)) && (lasttouched1 & _BV(i)) ) {
      if (DEBUG) Serial.print("keyup A "); Serial.println(i);
      if (i > 4) // notes only
      {
        pcount--; // polyphony count down
        if(!latch) arp[i - 5] = false;
      }
    }

    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched2 & _BV(i)) && !(lasttouched2 & _BV(i)) ) {
      if (DEBUG) Serial.print("keydown B "); Serial.println(i);
      pcount++; // polyphony count up
      tlen1 = TDUR; // new trigger
      curkey = i - 5 + 12;
      arp[curkey] = latch ? !arp[curkey] : true;
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched2 & _BV(i)) && (lasttouched2 & _BV(i)) ) {
      if (DEBUG) Serial.print("keyup B "); Serial.println(i);
      pcount--; // polyphony count down
      if (!latch)
      {
        arp[i - 5 + 12] = false;
      }
    }
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched3 & _BV(i)) && !(lasttouched3 & _BV(i)) ) {
      if (DEBUG) Serial.print("keydown C "); Serial.println(i);
      pcount++; // polyphony count up
      tlen1 = TDUR; // new trigger
      curkey = i - 5 + 24;
      arp[curkey] = latch ? !arp[curkey] : true;
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched3 & _BV(i)) && (lasttouched3 & _BV(i)) ) {
      if (DEBUG) Serial.print("keyup C "); Serial.println(i);
      pcount--; // polyphony count down
      if (!latch)
      {
        arp[i - 5 + 24] = false;
      }
    }
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched4 & _BV(i)) && !(lasttouched4 & _BV(i)) ) {
      if (DEBUG) Serial.print("keydown D "); Serial.println(i);
      if (i < 6) // notes only
      {
        pcount++; // polyphony count up
        tlen1 = TDUR; // new trigger
        curkey = i - 5 + 36;
        arp[curkey] = latch ? !arp[curkey] : true;
      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched4 & _BV(i)) && (lasttouched4 & _BV(i)) ) {
      if (DEBUG) Serial.print("keyup D "); Serial.println(i);
      if (i < 6) // notes only
      {
        pcount--; // polyphony count down
        if(!latch) arp[i - 5 + 36] = false;
      }
    }
  }

  // reset our state
  lasttouched1 = currtouched1;
  lasttouched2 = currtouched2;
  lasttouched3 = currtouched3;
  lasttouched4 = currtouched4;

  // SEQUENCER CONTROLS
  
  // start/stop and rate controls
  bool ss = !digitalRead(4);
  if (ss == true && oldss == false)
  {
    gogogo = !gogogo;
    //    if(DEBUG) Serial.println(gogogo);
  }
  oldss = ss;

  int r = analogRead(A0);
  r = map(r, 0, 1023, 25, 2000);
  rate = psmooth * rate + (1.0 - psmooth) * r;
  //if(DEBUG) Serial.println(rate);

  //
  // OUTPUTS
  //
  
  // LIVE KEYBOARD (UPPER OUTS)

  // triggers and gates (2, 3, 7, 8)
  if (tlen1 > 0) digitalWrite(2, HIGH); else digitalWrite(2, LOW);
  if (pcount > 0) digitalWrite(3, HIGH); else digitalWrite(3, LOW);

  // cv pitch out
  vout1 = round((float)curkey * VPST);
  dac1.setVoltage(vout1, false);

  // pressure value (RC'ed through an 8k2 and a .22uF)
  if (curkey < 7) {
    ptemp = map(cap1.filteredData(curkey + 5) - POFF, 0, cap1.baselineData(curkey + 5), 255, 0);
  }
  else if (curkey >= 7 && curkey < 19) {
    ptemp = map(cap2.filteredData(curkey + 5 - 12) - POFF, 0, cap2.baselineData(curkey + 5 - 12), 255, 0);
  }
  else if (curkey >= 19 && curkey < 31) {
    ptemp = map(cap3.filteredData(curkey + 5 - 24) - POFF, 0, cap3.baselineData(curkey + 5 - 24), 255, 0);
  }
  else if (curkey < 37) {
    ptemp = map(cap4.filteredData(curkey + 5 - 36) - POFF, 0, cap4.baselineData(curkey + 5 - 36), 255, 0);
  }
  ptemp = constrain(ptemp, 0, 255);
  pressureval = psmooth * pressureval + (1.0 - psmooth) * ptemp;
  //  if(DEBUG) {
  //        Serial.print("press ");
  //        Serial.println(pressureval);
  //  }

  // CV pressure (5, 6)
  analogWrite(5, (int)pressureval);


  // SEQUENCER (LOWER OUTS)

  if (gogogo) {
    now = millis();
    if (now - then > rate)
    {
      // arp sum
      arpcount = 0;
      for (int i = 0; i < 37; i++)
      {
        if (arp[i]) arpcount++;
      }
      pulseout = TDUR;
      then = now;
      if (arpcount > 0) { // arpegiate
        tlen2 = TDUR;

        if (arpmode == 0) // ARP UP
        {
          for (int i = 0; i < 37; i++)
          {
            int nn = (i + arpptr + 1) % 37; // next note?
            if (arp[nn]) { // found the next note
              arpptr = nn;
              break;
            }
          }
        }

        if (arpmode == 1) // ARP DOWN
        {
          for (int i = 36; i >= 0; i--)
          {
            int nn = (i + arpptr - 1 + 37) % 37; // next note?
            if (arp[nn]) { // found the next note
              arpptr = nn;
              break;
            }
          }
        }

        if (arpmode == 2) // ARP UP/DOWN
        {
          if (!arpdir) // up
          {
            for (int i = 0; i < 37; i++)
            {
              int nn = (i + arpptr + 1) % 37; // next note?
              if (arp[nn]) { // found the next note
                arpptr = nn;
                break;
              }
              if (nn == 36) arpdir = true;
            }
          }
          else { // down
            for (int i = 36; i >= 0; i--)
            {
              int nn = (i + arpptr - 1 + 37) % 37; // next note?
              if (arp[nn]) { // found the next note
                arpptr = nn;
                break;
              }
              if (nn == 0) arpdir = false;
            }
          }
        }

        if (arpmode == 3) // ARP RANDOM
        {
          int spoint = random(37);
          for (int i = 0; i < 37; i++)
          {
            int nn = (i + arpptr + spoint) % 37; // next note?
            if (arp[nn]) { // found the next note
              arpptr = nn;
              break;
            }
          }
        }

      }
    }
  }

  // triggers and gates (2, 3, 7, 8)
  if (tlen2 > 0) digitalWrite(7, HIGH); else digitalWrite(7, LOW);
  if (gogogo && arpcount > 0) digitalWrite(8, HIGH); else digitalWrite(8, LOW);

  // cv pitch out
  vout2 = round(arpptr * VPST);
  dac2.setVoltage(vout2, false);

  if (gogogo) digitalWrite(9, pulseout > 0);



  // display
  display.clearDisplay();

  display.setCursor(0, 0);
  display.print("KEY: ");
  display.print(notes[curkey % 12]);
  display.print(curkey / 12);
  display.println();

  display.print("ARP: ");
  display.print(gogogo ? arpmodes[arpmode] : "OFF ");
  if (gogogo) display.print(notes[arpptr % 12]);
  if (gogogo) display.print(arpptr / 12);
  display.println();

  display.print("rate: ");
  display.print(round(rate));

  display.setCursor(90, 0);
  display.print(latch ? "LATCH" : "");


  display.display(); // actually display all of the above

  tlen1--;
  if (tlen1 < 0) tlen1 = 0;
  tlen2--;
  if (tlen2 < 0) tlen2 = 0;
  pulseout--;
  if (pulseout < 0) pulseout = 0;
}
