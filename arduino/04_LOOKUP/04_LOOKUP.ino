//
// LOOKUP
// Shelfisizer 2019, Module 4
//
// three channels of DC input, indexed against 16 potentiometers
// for three channels of output. four modes of operation.
//
// rld, I<3DM, 8.19
//
// assumes:
// 3 DC inputs, 2 switches, and 16 potentiometers (INPUT).
// 3 DC outputs and 12 LEDs (via 2x74HC595) (OUTPUT).
// inputs and outputs are split to banana jacks for wiring.
// potentiometers are multiplexed in (via 3xCD74HC4067).
//

#define MAXANALOG 1023 // highest analog value on pins

const boolean db = false; // debug state

// pins:
const int latchPin = A4; // shift register latch
const int clockPin = A5; // shift register clock
const int dataPin = A3; // shift register data
const int s0 = 0, s1 = 1; // mode switches - don't activate when serial live
const int xA0 = 2, xA1 = 3, xA2 = 4, xA3 = 5; // multiplexer A, 4 bits
const int xB0 = 6, xB1 = 7, xB2 = 8, xB3 = 9; // multiplexer B, 4 bits
const int xC0 = 10, xC1 = 11, xC2 = 12, xC3 = 13; // multiplexer C, 4 bits
const int aPin = A0, bPin = A1, cPin = A2; // analog inputs (A, B, C)

int mode = 0, sv0 = 0, sv1 = 0;
float a = 0, b = 0, c = 0; // analog input values
const float smooth_y = 0.99; // smoothing coefficient (0 is raw input, 0.99 is very smooth)
const float smooth_x = 1.0-smooth_y; // inverse smoothing coefficient
const float d_t = 0.1; // delta threshold: amount of shift between reads to escape smoothing
float a_i = 0, b_i = 0, c_i = 0; // raw analog inputs
int aSelect = 0, bSelect = 0, cSelect = 0; // analog output selections
int aPrev = -1, bPrev = -1, cPrev = -1; // previous analog output selections
int rc = 0, rw = 0, rmin = 0, rmax = 0; // mode 3 variables
boolean oa = 0; // hsysteresis

const int gc[16] = { B0000, B0001, B0011, B0010,
                     B0110, B0111, B0101, B0100,
                     B1100, B1101, B1111, B1110,
                     B1010, B1011, B1001, B1000
                   }; // gray code 0-15
byte b0 = 0, b1 = 0; // shift register bytes

void setup() {
  // establish pin states:
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  if (db) Serial.begin(9600); // launch serial only on debug
  if (!db) pinMode(s0, INPUT_PULLUP);
  if (!db) pinMode(s1, INPUT_PULLUP);
  pinMode(xA0, OUTPUT);
  pinMode(xA1, OUTPUT);
  pinMode(xA2, OUTPUT);
  pinMode(xA3, OUTPUT);
  pinMode(xB0, OUTPUT);
  pinMode(xB1, OUTPUT);
  pinMode(xB2, OUTPUT);
  pinMode(xB3, OUTPUT);
  pinMode(xC0, OUTPUT);
  pinMode(xC1, OUTPUT);
  pinMode(xC2, OUTPUT);
  pinMode(xC3, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  //  mode switches:
  //  sv0   sv1   A     B     C
  //  0     0     0-15  0-15  0-15
  //  1     0     0-15  0-7   8-15
  //  0     1     0-7   8-11  12-15
  //  1     1     trig  ctr   bw
  if (!db) sv0 = digitalRead(s0); // LSB
  if (!db) sv1 = digitalRead(s1); // HSB
  mode = sv0 + (2 * sv1);

  a_i = analogRead(aPin) / (float)MAXANALOG;
  b_i = analogRead(bPin) / (float)MAXANALOG;
  c_i = analogRead(cPin) / (float)MAXANALOG;
  if(fabs(a_i-a)>d_t) a=a_i;
  if(fabs(b_i-b)>d_t) b=b_i;
  if(fabs(c_i-c)>d_t) c=c_i;
  a = smooth_x*a_i + smooth_y*a;
  b = smooth_x*b_i + smooth_y*b;
  c = smooth_x*c_i + smooth_y*c;

  if (mode == 0)
  {
    aSelect = constrain((int)floor(a * 16.), 0, 15); // full range
    bSelect = constrain((int)floor(b * 16.), 0, 15); // full range
    cSelect = constrain((int)floor(c * 16.), 0, 15); // full range
  }
  if (mode == 1)
  {
    aSelect = constrain((int)floor(a * 16.), 0, 15); // full range
    bSelect = constrain(0 + (int)floor(b * 8.), 0, 7); // bottom 8
    cSelect = constrain(8 + (int)floor(c * 8.), 8, 15); // top 8
  }
  if (mode == 2)
  {
    aSelect = constrain((int)floor(a * 8.), 0, 7); // bottom 8
    bSelect = constrain(8 + (int)floor(b * 4.), 8, 11); // 8-11
    cSelect = constrain(12 + (int)floor(c * 4.), 12, 15); // 9-15
  }
  if (mode == 3) // a is trigger, b and c are probability
  {
    if (a > 0.5 && oa == 0) // TRIGGER
    {
      rc = constrain((int)floor(b * 16.), 0, 15);
      rw = constrain((int)floor(c * 16.), 0, 15);
      rmin = max(rc - rw, 0);
      rmax = min(rc + rw, 16);
      aSelect =  random(rmin, rmax); // wide
      bSelect = (random(rmin, rmax) + random(rmin, rmax) + random(rmin, rmax)) / 3; // gaussian
      cSelect = (random(rmin, rmax) + random(rmin, rmax) + random(rmin, rmax) + random(rmin, rmax) + random(rmin, rmax)) / 5; // narrow
      oa = 1;
    }
    else if (a <= 0.5) {
      oa = 0;
    }
  }

  // multiplexer outs:
  if (aSelect != aPrev) {
    digitalWrite(xA0, (aSelect & 1) == 1);
    digitalWrite(xA1, (aSelect & 2) == 2);
    digitalWrite(xA2, (aSelect & 4) == 4);
    digitalWrite(xA3, (aSelect & 8) == 8);
  }
  if (bSelect != bPrev) {
    digitalWrite(xB0, (bSelect & 1) == 1);
    digitalWrite(xB1, (bSelect & 2) == 2);
    digitalWrite(xB2, (bSelect & 4) == 4);
    digitalWrite(xB3, (bSelect & 8) == 8);
  }
  if (cSelect != cPrev) {
    digitalWrite(xC0, (cSelect & 1) == 1);
    digitalWrite(xC1, (cSelect & 2) == 2);
    digitalWrite(xC2, (cSelect & 4) == 4);
    digitalWrite(xC3, (cSelect & 8) == 8);
  }

  aPrev = aSelect;
  bPrev = bSelect;
  cPrev = cSelect;

  // shift register led outs:
  b0 = gc[cSelect] << 4;
  b1 = gc[bSelect] + (gc[aSelect] << 4);
  updateShiftRegister(b0, b1);

  // debugging
  if (db) {
    Serial.print("ins: ");
    Serial.print(a);
    Serial.print(" ");
    Serial.print(b);
    Serial.print(" ");
    Serial.println(c);

    Serial.print("out: ");
    Serial.print(aSelect);
    Serial.print(" ");
    Serial.print(bSelect);
    Serial.print(" ");
    Serial.println(cSelect);

  }


  // short pause:
  //delay(20);
  delayMicroseconds(5);

}

// ...helper functions...

//
// update shift register LEDs:
//
void updateShiftRegister(byte _l1, byte _l2)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, _l1);
  shiftOut(dataPin, clockPin, LSBFIRST, _l2);
  digitalWrite(latchPin, HIGH);
}

//
// shift out any byte to a 2-byte shift register
// (view 0, 5, 6):
//
void shiftByte(byte _ptr)
{
  byte led1 = 0;
  byte led2 = 0;
  if (_ptr < 8) {
    bitSet(led1, _ptr);
  }
  else {
    bitSet(led2, _ptr - 8);
  }
  updateShiftRegister(led1, led2);
}
