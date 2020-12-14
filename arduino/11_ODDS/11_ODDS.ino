// odds and evens

#define DEBUG false
#define MINANALOG 100
#define MAXANALOG 1000
// shift register outs:
#define M1 0
#define M2 1
#define M3 2
#define M4 3
#define X0 4
#define X1 5
#define B0 6
#define B1 7
#define C0 8
#define C1 9
#define D0 10
#define D1 11
#define E0 12
#define E1 13
#define F0 14
#define F1 15

// pins:
const int latchPin = 11; // shift register latch
const int clockPin = 12; // shift register clock
const int dataPin = 10; // shift register data
const int trigCOM = 2; // common trigger pin
const int trigF = 3; // trigger pin F
const int trigE = 4; // trigger pin E
const int trigD = 5; // trigger pin D
const int trigC = 6; // trigger pin C
const int trigB = 7; // trigger pin B
const int trigA = 8; // trigger pin A
const int modepin = 9; // mode switch input

const int trigdur = 10; // duration of triggers

int lights[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mode = 0; // trig (0) versus gate (1)
int oa = 0, ob = 0, oc = 0, od = 0, oe = 0, of = 0, ocom = 0; // prev states
int comptr = 0; // common sequence pointer
char aptr = 0; // which analog pin to read
int ka = 0, kb = 0, kc = 0, kd = 0, ke = 0, kf = 0; // odds
int i, a, b, c, d, e, f, com; // digital values

boolean test[] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
byte testptr = 0;

void setup() {
  // put your setup code here, to run once:

  if (DEBUG) Serial.begin(9600);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(trigA, INPUT);
  pinMode(trigB, INPUT);
  pinMode(trigC, INPUT);
  pinMode(trigD, INPUT);
  pinMode(trigE, INPUT);
  pinMode(trigF, INPUT);
  pinMode(trigCOM, INPUT);
  pinMode(modepin, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  a = digitalRead(trigA);
  b = digitalRead(trigB);
  c = digitalRead(trigC);
  d = digitalRead(trigD);
  e = digitalRead(trigE);
  f = digitalRead(trigF);
  com = digitalRead(trigCOM);
  mode = !digitalRead(modepin); // backwards

  if(DEBUG&&a) Serial.println('A');
  switch (aptr) { // read one analog pin per pass
    case 0:
      ka = analogRead(A0);
      break;
    case 1:
      kb = analogRead(A1);
      break;
    case 2:
      kc = analogRead(A2);
      break;
    case 3:
      kd = analogRead(A3);
      break;
    case 4:
      ke = analogRead(A4);
      break;
    case 5:
      kf = analogRead(A5);
      break;
  }
  aptr = (aptr + 1) % 6;

  if (mode == 0) // trig
  {
    // clear:
    for (i = 0; i < 16; i++)
    {
      lights[i]--;
      if (lights[i] < 0) lights[i] = 0;
    }
  }

  if (com && !ocom) { // common bang
    a = b = c = d = e = f = 1;
    oa = ob = oc = od = oe = of = 0;
  }

  if (a && !oa)
  {
    if (random(MINANALOG, MAXANALOG) < ka) {
      lights[X0] = trigdur;
      lights[X1] = 0;
    }
    else {
      lights[X0] = 0;
      lights[X1] = trigdur;
    }
  }
  if (b && !ob)
  {
    if (random(MINANALOG, MAXANALOG) < kb) {
      lights[B0] = trigdur;
      lights[B1] = 0;
    }
    else {
      lights[B0] = 0;
      lights[B1] = trigdur;
    }
  }
  if (c && !oc)
  {
    if (random(MINANALOG, MAXANALOG) < kc) {
      lights[C0] = trigdur;
      lights[C1] = 0;
    }
    else {
      lights[C0] = 0;
      lights[C1] = trigdur;
    }
  }
  if (d && !od)
  {
    if (random(MINANALOG, MAXANALOG) < kd) {
      lights[D0] = trigdur;
      lights[D1] = 0;
    }
    else {
      lights[D0] = 0;
      lights[D1] = trigdur;
    }
  }
  if (e && !oe)
  {
    if (random(MINANALOG, MAXANALOG) < ke) {
      lights[E0] = trigdur;
      lights[E1] = 0;
    }
    else {
      lights[E0] = 0;
      lights[E1] = trigdur;
    }
  }
  if (f && !of)
  {
    if (random(MINANALOG, MAXANALOG) < kf) {
      lights[F0] = trigdur;
      lights[F1] = 0;
    }
    else {
      lights[F0] = 0;
      lights[F1] = trigdur;
    }
  }

  if ((a && !oa) || (b && !ob) || (c && !oc) || (d && !od) || (e && !oe) || (f && !of))
  {
    lights[0] = 0;
    lights[1] = 0;
    lights[2] = 0;
    lights[3] = 0;
    lights[comptr] = trigdur;
    comptr = (comptr + 1) % 4;
  }

  shiftArray(lights, 16);

  oa = a;
  ob = b;
  oc = c;
  od = d;
  oe = e;
  of = f;
  ocom = com;

}
