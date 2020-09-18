#define MAXANALOG 1023 // highest analog value on pins

const boolean db = false; // debug flag
const boolean selfrun = false; // internal clock for testing
const boolean lighttest = false;


// pins:
const int mPin1L = 2; // mode pin 1, left
const int mPin1R = 3; // mode pin 1, right
const int mPin2L = 4; // mode pin 2, left
const int mPin2R = 5; // mode pin 2, right
const int mPin3L = 6; // mode pin 3, left
const int mPin3R = 7; // mode pin 3, right
const int tPinA = 8; // trigger pin A
const int tPinB = 9; // trigger pin B
const int tPinC = 10; // trigger pin C
const int rPin = 11; // reset Pin
const int dataPin = A3; // shift register data
const int latchPin = A4; // shift register latch
const int clockPin = A5; // shift register clock
const int aPinA = A0; // CV pin A
const int aPinB = A1; // CV pin B
const int aPinC = A2; // CV pin C

// variables:
byte mode = 0;
boolean trigA = 0;
boolean trigB = 0;
boolean trigC = 0;
boolean trigA_o = 0;
boolean trigB_o = 0;
boolean trigC_o = 0;
boolean reset = 0;
byte fireA = 0;
byte fireB = 0;
byte fireC = 0;
byte led1 = 0;
byte led2 = 0;
byte led3 = 0;
byte led4 = 0;
byte led5 = 0;
byte led6 = 0;
byte sptrA = 0;
byte sptrB = 0;
byte sptrC = 0;
byte sptrA_o = 0;
byte sptrB_o = 0;
byte sptrC_o = 0;
char lightA[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char lightB[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char lightC[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int loopcount = 0;
int Aspeed = 200;
int Bspeed = 300;
int Cspeed = 400;
int vA, vB, vC; // analog read values

const int firelen = 10;

//
// modes -
// 0 (CCC) -  pulse   forward   rows
// 1 (LCC) -  gate    forward   rows
// 2 (RCC) -  hpulse  forward   rows
//
// 4 (CLC) -  pulse   index     rows
// 5 (LLC) -  gate    index     rows
// 6 (RLC) -  hpulse  index     rows
//
// 8 (CRC) -  pulse   direction rows
// 9 (LRC) -  gate    direction rows
// 10 (RRC) - hpulse  direction rows
//
// 16 (CCL) - pulse   forward   horizontal
// 17 (LCL) - gate    forward   horizontal
// 18 (RCL) - hpulse  forward   horizontal
//
// 20 (CLL) - pulse   index     horizontal
// 21 (LLL) - gate    index     horizontal
// 22 (RLL) - hpulse  index     horizontal
//
// 24 (CRL) - pulse   direction horizontal
// 25 (LRL) - gate    direction horizontal
// 26 (RRL) - hpulse  direction horizontal
//
// 32 (CCR) - pulse   forward   vertical
// 33 (LCR) - gate    forward   vertical
// 34 (RCR) - hpulse  forward   vertical
//
// 36 (CLR) - pulse   index     vertical
// 37 (LLR) - gate    index     vertical
// 38 (RLR) - hpulse  index     vertical
//
// 40 (CRR) - pulse   direction vertical
// 41 (LRR) - gate    direction vertical
// 42 (RRR) - hpulse  direction vertical

void(* resetFunc) (void) = 0;//declare reset function at address 0

void setup() {
  // put your setup code here, to run once:
  if (db) Serial.begin(9600);

  pinMode(mPin1L, INPUT_PULLUP);
  pinMode(mPin1R, INPUT_PULLUP);
  pinMode(mPin2L, INPUT_PULLUP);
  pinMode(mPin2R, INPUT_PULLUP);
  pinMode(mPin3L, INPUT_PULLUP);
  pinMode(mPin3R, INPUT_PULLUP);
  pinMode(tPinA, INPUT);
  pinMode(tPinB, INPUT);
  pinMode(tPinC, INPUT);
  pinMode(rPin, INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  boolean p1 = !digitalRead(mPin1L);
  boolean p2 = !digitalRead(mPin1R);
  boolean p3 = !digitalRead(mPin2L);
  boolean p4 = !digitalRead(mPin2R);
  boolean p5 = !digitalRead(mPin3L);
  boolean p6 = !digitalRead(mPin3R);
  mode = (p1<<0) + (p2<<1) + (p3<<2) + (p4<<3) + (p5<<4) + (p6<<5);
//  if (db) Serial.println(mode);

  trigA = digitalRead(tPinA);
  trigB = digitalRead(tPinB);
  trigC = digitalRead(tPinC);
  reset = !digitalRead(rPin);
//  if (db) Serial.print(trigA);
//  if (db) Serial.print(" ");
//  if (db) Serial.print(trigB);
//  if (db) Serial.print(" ");
//  if (db) Serial.print(trigC);
//  if (db) Serial.print(" ");
//  if (db) Serial.print(reset);
//  if (db) Serial.println();

  if(trigA==1 && trigA_o==0) fireA = 1;
  if(trigB==1 && trigB_o==0) fireB = 1;
  if(trigC==1 && trigC_o==0) fireC = 1;

  vA = analogRead(aPinA);
  vB = analogRead(aPinB);
  vC = analogRead(aPinC);
//  if (db) Serial.print(vA);
//  if (db) Serial.print(" ");
//  if (db) Serial.print(vB);
//  if (db) Serial.print(" ");
//  if (db) Serial.print(vC);
//  if (db) Serial.println();

if((mode&4)==4) {
  if(fireA>0) sptrA = map(vA, 0, MAXANALOG, 0, 15);
  if(fireB>0) sptrB = map(vB, 0, MAXANALOG, 0, 15);
  if(fireC>0) sptrC = map(vC, 0, MAXANALOG, 0, 15);
}

  // figure out lights:
  // decrement existing values if 'gate' is off
  if((mode&1)==0)
  {
    for(byte i = 0;i<16;i++)
    {
      lightA[i]--;
      if(lightA[i]<0) lightA[i]=0;
      lightB[i]--;
      if(lightB[i]<0) lightB[i]=0;
      lightC[i]--;
      if(lightC[i]<0) lightC[i]=0;
    } 
    if(fireA) lightA[sptrA] = firelen;
    if(fireB) lightB[sptrB] = firelen;
    if(fireC) lightC[sptrC] = firelen;
    
    // inhibit firing on hysteresis switch:
    if((mode&2)==2) {
      if(sptrA==sptrA_o) lightA[sptrA] = 0;
      if(sptrB==sptrB_o) lightB[sptrB] = 0;
      if(sptrC==sptrC_o) lightC[sptrC] = 0;
    }
  
  }
  // gate mode -- one light at a time
  else { 
    for(byte i = 0;i<16;i++)
    {
      lightA[i] = 0;
      lightB[i] = 0;
      lightC[i] = 0;
    } 
    lightA[sptrA] = firelen;
    lightB[sptrB] = firelen;
    lightC[sptrC] = firelen;
  }


  
  shiftLights(lightA, lightB, lightC);
  if (db) Serial.print("NEW: ");
  if (db) Serial.print(sptrA);
  if (db) Serial.print(" ");
  if (db) Serial.print(sptrB);
  if (db) Serial.print(" ");
  if (db) Serial.print(sptrC);
  if (db) Serial.println();
  if (db) Serial.print("OLD: ");
  if (db) Serial.print(sptrA_o);
  if (db) Serial.print(" ");
  if (db) Serial.print(sptrB_o);
  if (db) Serial.print(" ");
  if (db) Serial.print(sptrC_o);
  if (db) Serial.println();

  // ADVANCE

  // trigger hysteresis:
  trigA_o = trigA;
  trigB_o = trigB;
  trigC_o = trigC;

  if(fireA>0)
  {
    sptrA_o = sptrA;
    if((mode&4)==0 && (mode&8)==0) sptrA=(sptrA+1)%16;
    if((mode&8)==8) sptrA = (sptrA+map(vA,0,MAXANALOG,-16, 16)+32)%16;
    fireA=0;
  }
  if(fireB>0)
  {
    sptrB_o = sptrB;
    if((mode&4)==0 && (mode&8)==0) sptrB=(sptrB+1)%16; 
    if((mode&8)==8) sptrB = (sptrB+map(vB,0,MAXANALOG,-16, 16)+32)%16;
    fireB=0;
  }
  if(fireC>0)
  {
    sptrC_o = sptrC;
    if((mode&4)==0 && (mode&8)==0) sptrC=(sptrC+1)%16; 
    if((mode&8)==8) sptrC = (sptrC+map(vC,0,MAXANALOG,-16, 16)+32)%16;
    fireC=0;
  }


  if(selfrun) {
    if(loopcount%Aspeed==0) { fireA = 1; }
    if(loopcount%Bspeed==0) { fireB = 1; }
    if(loopcount%Cspeed==0) { fireC = 1; }
    loopcount++;
  }

  if((mode&4)==0 && (mode&8)==0) // analog in is a reset pin
  {
    if(vA==MAXANALOG) sptrA = 0;
    if(vB==MAXANALOG) sptrB = 0;
    if(vC==MAXANALOG) sptrC = 0;
  }

  if(reset) {
    resetFunc(); //call reset 
  }





}

void shiftLights(byte _lightA[], byte _lightB[], byte _lightC[])
{
  led1 = 0;
  led2 = 0;
  led3 = 0;
  led4 = 0;
  led5 = 0;
  led6 = 0;
  for(byte i = 0;i<16;i++)
  {
    if(i<8) {
      if(_lightA[i]>0) bitSet(led1, i);
      if(_lightB[i]>0) bitSet(led2, i);
      if(_lightC[i]>0) bitSet(led3, i);
    }
    else {
      if(_lightA[i]>0) bitSet(led4, i-8);
      if(_lightB[i]>0) bitSet(led5, i-8);
      if(_lightC[i]>0) bitSet(led6, i-8);
    }
  }

  if(!lighttest) {
    updateShiftRegister(led1, led2, led3, led4, led5, led6);
  }
  else {
    updateShiftRegister(255, 255, 255, 255, 255, 255);
  }
}


//
// update shift register LEDs:
//
void updateShiftRegister(byte _l1, byte _l2, byte _l3, byte _l4, byte _l5, byte _l6)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, _l6);
  shiftOut(dataPin, clockPin, MSBFIRST, _l5);
  shiftOut(dataPin, clockPin, MSBFIRST, _l4);
  shiftOut(dataPin, clockPin, MSBFIRST, _l3);
  shiftOut(dataPin, clockPin, MSBFIRST, _l2);
  shiftOut(dataPin, clockPin, MSBFIRST, _l1);
  digitalWrite(latchPin, HIGH);
}
