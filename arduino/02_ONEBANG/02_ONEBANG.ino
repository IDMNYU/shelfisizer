//
// ONEBANG
// Shelfisizer 2019, Module 2
//
// six channels of DC input with trigger outputs for modular
// synth. outputs fire on an external clock input based on
// input voltage. different modes change algorithm determining
// if a trigger occurs on the clock.
//
// rld, I<3DM, 6.19
//
// assumes:
// 1 mode button, 6 DC inputs, and a 'clock' pin (INPUT).
// 6 trigger outputs (OUTPUT).
// inputs and outputs are split to banana jacks for wiring.
//

#define NMODES 12 // number of modes
#define MAXANALOG 750 // highest analog value on pins

const boolean db = false; // debug?

//
// modes -
// 0 - 6 channels... input goes high and sets bit for a single trigger
// 1 - 6 channels... input goes high and sets bit for a single trigger with hysteresis
// 2 - 6 channels... input value (0 - MAXANALOG/2) is probability for a trigger
// 3 = 6 channels... one trigger per clock across all channels; highest input value gets it
// 4 = 3 channels... paired inputs compared (A/B, C/D, E/F); triggers for winners
// 5 = 3 channels... paired inputs compared (A/B, C/D, E/F); triggers for winners with hysteresis
// 6 - 1 channel... input at pin A (0 - MAXANALOG/2) determines which red trigger (A-F)
// 7 - 2 channels... inputs at pins A and D (0 - MAXANALOG/2) determine which trigger (A/B/C,  D/E/F)
// 8 = 2 channels... and/or/xor - &&/||/!= - of A/B and D/E
// 9 = 2 channels... and/or/xor - &&/||/!= - of A/B and D/E with hysteresis
// 10 = 2 channels... and/or/xor - &&/||/!= - of A/B and D/E with C/F as high threshold
// 11 = 2 channels... and/or/xor - &&/||/!= - of A/B and D/E with C/F as high threshold with hysteresis
//

const byte lmask[NMODES] = {
  // LED mask for 2-LED mode indicator
  // 5-bit number - [speed A/B][2A][2B][1A][1B]
  // these are LITTLE-ENDIAN:
  B00000, // LED1 off, LED2 off
  B00011, // LED1 on, LED2 off
  B01100, // LED1 off, LED2 on
  B01111, // LED1 on, LED2 on
  B00010, // LED1 blink, LED2 off
  B01110, // LED1 blink, LED2 on
  B01010, // LED1 + LED2 blink
  B00110, // LED1 + LED2 alternate
  B10010, // LED1 fast blink, LED2 off
  B11110, // LED1 fast blink, LED2 on
  B11000, // LED1 off, LED2 fast blink
  B11011 // LED1 on, LED2 fast blink
};

const int bspeed[2] = {500, 125}; // blink speeds in ms (slow, fast)

int mode = 0; // current mode
boolean bstate = 0; // blink state
boolean op1 = 0; // prev state for LED 1
boolean op2 = 0; // prev state for LED 2

const int thresh = MAXANALOG / 2; // analog threshold for a 'hi' value - 1/2 of MAXANALOG
const int upTime = 1; // number of cycles in a trigger

// pins:
const int tPin = 2; // trigger pin
const int aPin = 3; // output for A (input is A0)
const int bPin = 4; // output for B (input is A1)
const int cPin = 5; // output for C (input is A2)
const int dPin = 6; // output for D (input is A3)
const int ePin = 7; // output for E (input is A4)
const int fPin = 8; // output for F (input is A5)
const int mPin = 9; // mode switch
const int lPin1 = 10; // light 1
const int lPin2 = 11; // light 2

// threshold values:
int at = 0, bt = 0, ct = 0, dt = 0, et = 0, ft = 0;

// hysteresis values:
int ah = 0, bh = 0, ch = 0, dh = 0, eh = 0, fh = 0;

// random values:
int pa = 0, pb = 0, pc = 0, pd = 0, pe = 0, pf = 0;

// uptime values (for output trigger):
int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;

// trigger pin:
boolean t = 0; // current
boolean ot = 0; // previous

// mode pin:
boolean m = 0; // current
boolean om = 0; // previous

int va, vb, vc, vd, ve, vf; // analog read values

int pick; // holder variable for probability modes

void setup() {
  // put your setup code here, to run once:
  pinMode(tPin, INPUT);
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);
  pinMode(ePin, OUTPUT);
  pinMode(fPin, OUTPUT);
  pinMode(mPin, INPUT_PULLUP);
  pinMode(lPin1, OUTPUT);
  pinMode(lPin2, OUTPUT);
  if (db) Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // analog ins:
  va = analogRead(A0);
  vb = analogRead(A1);
  vc = analogRead(A2);
  vd = analogRead(A3);
  ve = analogRead(A4);
  vf = analogRead(A5);

  // EACH CYCLE: modes 0, 1, 4, 5, 8, 9, 10, 11:

  if (mode == 0) { // threshold trigger
    if (va > thresh) at = 1;
    if (vb > thresh) bt = 1;
    if (vc > thresh) ct = 1;
    if (vd > thresh) dt = 1;
    if (ve > thresh) et = 1;
    if (vf > thresh) ft = 1;
  }
  else if (mode == 1) { // threshold trigger w/ hysteresis
    if (va > thresh) {
      if (ah == 0) {
        at = 1;
        ah = 1;
      }
    } else {
      ah = 0;
    }
    if (vb > thresh) {
      if (bh == 0) {
        bt = 1;
        bh = 1;
      }
    } else {
      bh = 0;
    }
    if (vc > thresh) {
      if (ch == 0) {
        ct = 1;
        ch = 1;
      }
    } else {
      ch = 0;
    }
    if (vd > thresh) {
      if (dh == 0) {
        dt = 1;
        dh = 1;
      }
    } else {
      dh = 0;
    }
    if (ve > thresh) {
      if (eh == 0) {
        et = 1;
        eh = 1;
      }
    } else {
      eh = 0;
    }
    if (vf > thresh) {
      if (fh == 0) {
        ft = 1;
        fh = 1;
      }
    } else {
      fh = 0;
    }
  }
  else if (mode == 4) { // paired comparison trigger
    if (va >= vb) at = 1; else bt = 1;
    if (vc >= vd) ct = 1; else dt = 1;
    if (ve >= vf) et = 1; else ft = 1;
  }
  else if (mode == 5) { // paired comparison trigger w/ hysteresis
    if (va >= vb) {
      if (ah == 0) {
        at = 1;
        ah = 1;
      }
    } else {
      ah = 0;
    }
    if (vb > va) {
      if (bh == 0) {
        bt = 1;
        bh = 1;
      }
    } else {
      bh = 0;
    }
    if (vc >= vd) {
      if (ch == 0) {
        ct = 1;
        ch = 1;
      }
    } else {
      ch = 0;
    }
    if (vd > vc) {
      if (dh == 0) {
        dt = 1;
        dh = 1;
      }
    } else {
      dh = 0;
    }
    if (ve >= vf) {
      if (eh == 0) {
        et = 1;
        eh = 1;
      }
    } else {
      eh = 0;
    }
    if (vf > ve) {
      if (fh == 0) {
        ft = 1;
        fh = 1;
      }
    } else {
      fh = 0;
    }
  }
  else if (mode == 8) { // two-channel boolean ops
    if ((va > thresh) && (vb > thresh)) at = 1;
    if ((va > thresh) || (vb > thresh)) bt = 1;
    if ((va > thresh) != (vb > thresh)) ct = 1;
    if ((vd > thresh) && (ve > thresh)) dt = 1;
    if ((vd > thresh) || (ve > thresh)) et = 1;
    if ((vd > thresh) != (ve > thresh)) ft = 1;
  }
  else if (mode == 9) { // two-channel boolean ops with hysteresis
    if ((va > thresh) || (vb > thresh)) {
      if (ah == 0) {
        at = 1;
        ah = 1;
      }
    } else {
      ah = 0;
    }
    if ((va > thresh) || (vb > thresh)) {
      if (bh == 0) {
        bt = 1;
        bh = 1;
      }
    } else {
      bh = 0;
    }
    if ((va > thresh) != (vb > thresh)) {
      if (ch == 0) {
        ct = 1;
        ch = 1;
      }
    } else {
      ch = 0;
    }
    if ((vd > thresh) && (ve > thresh)) {
      if (dh == 0) {
        dt = 1;
        dh = 1;
      }
    } else {
      dh = 0;
    }
    if ((vd > thresh) || (ve > thresh)) {
      if (eh == 0) {
        et = 1;
        eh = 1;
      }
    } else {
      eh = 0;
    }
    if ((vd > thresh) != (ve > thresh)) {
      if (fh == 0) {
        ft = 1;
        fh = 1;
      }
    } else {
      fh = 0;
    }
  }
  else if (mode == 10) { // two-channel boolean ops around threshold
    if ((va > vc) && (vb > vc)) at = 1;
    if ((va > vc) || (vb > vc)) bt = 1;
    if ((va > vc) != (vb > vc)) ct = 1;
    if ((vd > vc) && (ve > vc)) dt = 1;
    if ((vd > vc) || (ve > vc)) et = 1;
    if ((vd > vc) != (ve > vc)) ft = 1;
  }
  else if (mode == 11) { // two-channel boolean ops around threshold with hysteresis
    if ((va > vc) || (vb > vc)) {
      if (ah == 0) {
        at = 1;
        ah = 1;
      }
    } else {
      ah = 0;
    }
    if ((va > vc) || (vb > vc)) {
      if (bh == 0) {
        bt = 1;
        bh = 1;
      }
    } else {
      bh = 0;
    }
    if ((va > vc) != (vb > vc)) {
      if (ch == 0) {
        ct = 1;
        ch = 1;
      }
    } else {
      ch = 0;
    }
    if ((vd > vc) && (ve > vc)) {
      if (dh == 0) {
        dt = 1;
        dh = 1;
      }
    } else {
      dh = 0;
    }
    if ((vd > vc) || (ve > vc)) {
      if (eh == 0) {
        et = 1;
        eh = 1;
      }
    } else {
      eh = 0;
    }
    if ((vd > vc) != (ve > vc)) {
      if (fh == 0) {
        ft = 1;
        fh = 1;
      }
    } else {
      fh = 0;
    }
  }

  // mode switch:
  m = !digitalRead(mPin);
  if (m == 1 && om == 0) mode = (mode + 1) % NMODES;
  om = m;

  // status lights:
  millis() % bspeed[(lmask[mode] & 16) == 16] > bspeed[(lmask[mode] & 16) == 16] / 2 ? bstate = 0 : bstate = 1;
  boolean p1 = bstate ? (lmask[mode] & 1) == 1 : (lmask[mode] & 2) == 2;
  boolean p2 = bstate ? (lmask[mode] & 4) == 4 : (lmask[mode] & 8) == 8;
  if (p1 != op1) digitalWrite(lPin1, p1);
  if (p2 != op2) digitalWrite(lPin2, p2);
  op1 = p1;
  op2 = p2;

  // clock:
  t = digitalRead(tPin);
  if (t == 1 && ot == 0)
  {
    // ON TRIGGER: modes 2, 3, 6, 7:
    if (mode == 2) // probability trigger
    {
      pa = random(0, MAXANALOG);
      pb = random(0, MAXANALOG);
      pc = random(0, MAXANALOG);
      pd = random(0, MAXANALOG);
      pe = random(0, MAXANALOG);
      pf = random(0, MAXANALOG);
      if (pa < va) at = 1;
      if (pb < vb) bt = 1;
      if (pc < vc) ct = 1;
      if (pd < vd) dt = 1;
      if (pe < ve) et = 1;
      if (pf < vf) ft = 1;
    }
    else if (mode == 3) // highest channel triggers
    {
      int highest = -1;
      pick = -1;
      if (va > highest) {
        pick = 0;
        highest = va;
      }
      if (vb > highest) {
        pick = 1;
        highest = vb;
      }
      if (vc > highest) {
        pick = 2;
        highest = vc;
      }
      if (vd > highest) {
        pick = 3;
        highest = vd;
      }
      if (ve > highest) {
        pick = 4;
        highest = ve;
      }
      if (vf > highest) {
        pick = 5;
        highest = vf;
      }
      if (pick == 0) at = 1;
      else if (pick == 1) bt = 1;
      else if (pick == 2) ct = 1;
      else if (pick == 3) dt = 1;
      else if (pick == 4) et = 1;
      else if (pick == 5) ft = 1;
    }
    else if (mode == 6) // A jack determines A-F trigger
    {
      pick = constrain((int)floor(va / (float)MAXANALOG * 6.), 0, 5);
      if (pick == 0) at = 1;
      else if (pick == 1) bt = 1;
      else if (pick == 2) ct = 1;
      else if (pick == 3) dt = 1;
      else if (pick == 4) et = 1;
      else if (pick == 5) ft = 1;
    }
    else if (mode == 7) // A jack determines A-C trigger, D jack determines D-F trigger
    {
      pick = constrain((int)floor(va / (float)MAXANALOG * 3.), 0, 2);
      if (pick == 0) at = 1;
      else if (pick == 1) bt = 1;
      else if (pick == 2) ct = 1;
      pick = constrain((int)floor(vd / (float)MAXANALOG * 3.), 0, 2);
      if (pick == 0) dt = 1;
      else if (pick == 1) et = 1;
      else if (pick == 2) ft = 1;
    }

    // DO THE STUFF:

    if (at == 1) {
      a = upTime;
      at = 0;
    }
    if (bt == 1) {
      b = upTime;
      bt = 0;
    }
    if (ct == 1) {
      c = upTime;
      ct = 0;
    }
    if (dt == 1) {
      d = upTime;
      dt = 0;
    }
    if (et == 1) {
      e = upTime;
      et = 0;
    }
    if (ft == 1) {
      f = upTime;
      ft = 0;
    }
  }
  ot = t;

  // digital writes:
  digitalWrite(aPin, a > 0);
  digitalWrite(bPin, b > 0);
  digitalWrite(cPin, c > 0);
  digitalWrite(dPin, d > 0);
  digitalWrite(ePin, e > 0);
  digitalWrite(fPin, f > 0);

  // countdown:
  a--;
  b--;
  c--;
  d--;
  e--;
  f--;

  // debugging:
  if (db) Serial.print(mode);
  if (db) Serial.print(" ");
  if (db) Serial.print(lmask[mode]);
  if (db) Serial.print(" ");
  if (db) Serial.print(lmask[mode] & 16);
  if (db) Serial.print(" ");
  if (db) Serial.print((lmask[mode] & 16) == 16);
  if (db) Serial.println();

  // short pause:
  delayMicroseconds(50);
}
