//
// SHIFT
// Shelfisizer 2019, Module 6
//
// two-channel four-stage ASR (analog shift register), using 8 sample-and-hold ICs.
//
// rld, I<3DM, 8.19
//
// assumes:
// 2 DC inputs, 2 triggers (INPUT).
// 4 DC outputs via 8xLF398 (OUTPUT).
// inputs and outputs are split to banana jacks for wiring.
// requires 9V power.
//

const boolean db = false; // debug state
const int tPinL = A2; // trigger input L
const int tPinR = A3; // trigger input R
const int mPinL = A4; // manual trigger L
const int mPinR = A5; // manual trigger R
const int aPin = 2; // ASR A
const int bPin = 3; // ASR B
const int cPin = 4; // ASR C
const int dPin = 5; // ASR D
const int LendPin = 6; // end trigger L
const int ePin = 7; // ASR E
const int fPin = 8; // ASR F
const int gPin = 9; // ASR G
const int hPin = 10; // ASR H
const int RendPin = 11; // end trigger R

boolean oldtL = false;
boolean oldtR = false;
int thresh = 5;
int stime = 1000; // sample time (microseconds)

void setup() {
  // put your setup code here, to run once:
  if(db) Serial.begin(9600); // launch serial only on debug
  pinMode(mPinL, INPUT_PULLUP);
  pinMode(mPinR, INPUT_PULLUP);
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  boolean tL = digitalRead(tPinL)||!digitalRead(mPinL);
  boolean tR = digitalRead(tPinR)||!digitalRead(mPinR);


  // LEFT
  if(tL==1&&oldtL==0)
  {
    if(db) Serial.println("LEFT!");

    // cascade up D to A:
    digitalWrite(dPin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(dPin, LOW);
    digitalWrite(cPin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(cPin, LOW);
    digitalWrite(bPin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(bPin, LOW);
    digitalWrite(aPin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(aPin, LOW);
    digitalWrite(LendPin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(LendPin, LOW);

  }
  oldtL = tL;

   // RIGHT
  if(tR==1&&oldtR==0)
  {
    if(db) Serial.println("RIGHT!");

    // cascade up H to E:
    digitalWrite(hPin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(hPin, LOW);
    digitalWrite(gPin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(gPin, LOW);
    digitalWrite(fPin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(fPin, LOW);
    digitalWrite(ePin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(ePin, LOW);
    digitalWrite(RendPin, HIGH);
    delayMicroseconds(stime);
    digitalWrite(RendPin, LOW);

  }
  oldtR = tR;

}
