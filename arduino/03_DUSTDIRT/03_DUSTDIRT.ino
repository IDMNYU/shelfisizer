//
// DUSTDIRT
// Shelfisizer 2019, Module 3
//
// six channels of noise generation, either with gate triggers
// or constant output, for analog synth. pots control noise rates
// and a single LFO (rate / depth).
//
// rld, I<3DM, 7.19
//
// assumes:
// 1 mode switch, 6 trigger inputs, and 8 potentiometers (INPUT).
// 6 AC outputs (OUTPUT) through passive analog filter blocks.
// inputs and outputs are split to banana jacks for wiring.
// potentiometers are multiplexed in through a 74HC4051 and
// read on rotation.
//

// random algorithm: linear feedback shift register (LFSR)
#define LFSR_INIT  0xCAFEBABEUL // noise init with any 32-bit UL value
/* Choose bits 32, 30, 26, 24 from  http://arduino.stackexchange.com/a/6725/6628
    or 32, 22, 2, 1 from
    http://www.xilinx.com/support/documentation/application_notes/xapp052.pdf
    or bits 32, 16, 3,2  or 0x80010006UL per http://users.ece.cmu.edu/~koopman/lfsr/index.html
    and http://users.ece.cmu.edu/~koopman/lfsr/32.dat.gz
*/
#define LFSR_MASK  ((unsigned long)( 1UL<<31 | 1UL <<15 | 1UL <<2 | 1UL <<1  ))


const boolean db = false;

const int aThresh = 50; // analog threshold

// pin outs:
const int trigA = 2;
const int trigB = 4;
const int trigC = 7;
const int trigD = 8;
const int trigE = 12;
const int trigF = A1;

const int drumA = 3; // PWM
const int drumB = 5; // PWM
const int drumC = 6; // PWM
const int drumD = 9; // PWM
const int drumE = 10; // PWM
const int drumF = 11; // PWM

const int AnalogIn = A0;
const int S0 = A3; // cd74hc4051 address select 0
const int S1 = A4; // cd74hc4051 address select 1
const int S2 = A5; // cd74hc4051 address select 2
const int MS1 = A2; // mode toggle switch

// generation clock - LOWER IS HIGHER:
int freqA = 1; // "kick" -> LPF @ 50Hz (68ohm/.47uF) - tap at 63C
int freqB = 1; // "snare" -> HPF @ 2.3kHz (60ohm/1uF) - tap at 59C
int freqC = 1; // "tom" -> BPF @ 429Hz (51ohm/10uF;68ohm/10uF) - tap at 53C
int freqD = 1; // thud -> LPF @ 14Hz (51ohm/220uF) - tap at 49C
int freqE = 1; // high scratch -> HPF @ 482Hz (1ohm/330uF) - tap at 47C
int freqF = 1; // ring -> BPF @ 4kHz (51ohm/1uF;68ohm/.47uF - tap at 40C

// envelope state:
int envA = 0, envB = 0, envC = 0, envD = 0, envE = 0, envF = 0;

// trigger state:
boolean A = 0, B = 0, C = 0, D = 0, E = 0, F = 0;
boolean lastA = 0, lastB = 0, lastC = 0, lastD = 0, lastE = 0, lastF = 0;

// timestamp for last click:
unsigned long lcA, lcB, lcC, lcD, lcE, lcF;

// TIME:
unsigned long NOW = 0;

// random registers:
boolean R0 = 0, R1 = 0, R2 = 0, R3 = 0;

// current output:
boolean Ahigh = 0, Bhigh = 0, Chigh = 0, Dhigh = 0, Ehigh = 0, Fhigh = 0;

// counting variables:
int i, up;

// inputs:
float aIn[8] = {0., 0., 0., 0., 0., 0., 0., 0.}; // analog input values
int aSelect = 0; // which pin are we reading?
// bitmask for 74HC4051:
boolean aMask[8][3] = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0}, {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1}};

// mode switch:
boolean mode = 0;

// LFO
float lptr = 0.;
float lfo = 0.;
float l1 = 0.;
float l2 = 0.;

void setup() {

  if (db)  Serial.begin(9600);

  pinMode(trigA, INPUT);
  pinMode(trigB, INPUT);
  pinMode(trigC, INPUT);
  pinMode(trigD, INPUT);
  pinMode(trigE, INPUT);
  pinMode(trigF, INPUT);
  pinMode(drumA, OUTPUT);
  pinMode(drumB, OUTPUT);
  pinMode(drumC, OUTPUT);
  pinMode(drumD, OUTPUT);
  pinMode(drumE, OUTPUT);
  pinMode(drumF, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(MS1, INPUT_PULLUP);

  lcA = 0;
  lcB = 0;
  lcC = 0;
  lcD = 0;
  lcE = 0;
  lcF = 0;

  if (!db) noInterrupts(); // shut off interrupts
}

void loop() {

  NOW = micros();

  // trigger pins:
  A = digitalRead(trigA);
  B = digitalRead(trigB);
  C = digitalRead(trigC);
  D = digitalRead(trigD);
  E = digitalRead(trigE);
  F = digitalRead(trigF);

  // sample pots:
  digitalWrite(S0, aMask[aSelect][0]);
  digitalWrite(S1, aMask[aSelect][1]);
  digitalWrite(S2, aMask[aSelect][2]);
  aIn[aSelect] = (float)analogRead(AnalogIn) / 1023.;
  aSelect = (aSelect + 1) % 8;

  // test mode switch:
  mode = !digitalRead(MS1);

  // debugging:
  if (db) debug();

  if (mode) {
    if (A == 1 && lastA == 0) {
      up = (int)(aIn[0] * 30.) + l1 * 15.;
      envA = random(1 + (up / 2), 1 + up);
      Ahigh = 1;
    }
    lastA = A;
    if (B == 1 && lastB == 0) {
      up = (int)(aIn[1] * 60.) + l2 * 30.;
      envB = random(1 + (up / 2), 1 + up);
      Bhigh = 1;
    }
    lastB = B;
    if (C == 1 && lastC == 0) {
      up = (int)(aIn[2] * 40.) + l1 * 20.;
      envC = random(5 + (up / 2), 5 + up);
      Chigh = 1;
    }
    lastC = C;
    if (D == 1 && lastD == 0) {
      up = (int)(aIn[3] * 20.) + l2 * 10.;
      envD = random(1 + (up / 3), 1 + up); // click
      Dhigh = 1;
    }
    lastD = D;
    if (E == 1 && lastE == 0) {
      up = (int)(aIn[4] * 300.) + l1 * 150.;
      envE = random(1 + (up / 8), 1 + up);
      Ehigh = 1;
    }
    lastE = E;
    if (F == 1 && lastF == 0) {
      up = (int)(aIn[5] * 400.) + l2 * 200.;
      envF = random(1 + (up / 10), 1 + up);
      Fhigh = 1;
    }
    lastF = F;
  }

  R0 = generateNoise();
  R1 = generateNoise();
  R2 = generateNoise();
  R3 = generateNoise();

  freqA = mode ? 1 : 1 + aIn[0] * 1000. + l1 * 500.;
  if ((NOW - lcA) > freqA ) { // Changing this value changes the frequency.
    lcA = NOW;
    digitalWrite(drumA, Ahigh && (mode ? envA > 0 : 1));;
    Ahigh = R0 && R2 && R3 ? !Ahigh : Ahigh;
  }

  freqB = mode ? 1 : 1 + aIn[1] * 1000. + l2 * 500.;
  if ((NOW - lcB) > freqB ) { // Changing this value changes the frequency.
    lcB = NOW;
    digitalWrite(drumB, Bhigh && (mode ? envB > 0 : 1));
    Bhigh = R0 && R1 ? !Bhigh : Bhigh;
  }

  freqC = mode ? 1 : 1 + aIn[2] * 1000. + l1 * 500.;
  if ((NOW - lcC) > freqC ) { // Changing this value changes the frequency.
    lcC = NOW;
    digitalWrite (drumC, Chigh && (mode ? envC > 0 : 1));
    Chigh = R2 && R3 ? !Chigh : Chigh;
  }

  freqD = mode ? 1 : 1 + aIn[3] * 1000. + l2 * 500.;
  if ((NOW - lcD) > freqD ) { // Changing this value changes the frequency.
    lcD = NOW;
    digitalWrite (drumD, Dhigh && (mode ? envD > 0 : 1));
    Dhigh = R0 || R1 || R2 || R3 ? Dhigh : !Dhigh;
    //Dhigh = !Dhigh; // click
  }

  freqE = mode ? 1 : 1 + aIn[4] * 1000. + l1 * 500.;
  if ((NOW - lcE) > freqE ) { // Changing this value changes the frequency.
    lcE = NOW;
    digitalWrite(drumE, Ehigh * (mode ? envE > 0 : 1));
    Ehigh = R0 || R3 ? Ehigh : !Ehigh;
  }

  freqF = mode ? 1 : 1 + aIn[5] * 1000. + l2 * 500.;
  if ((NOW - lcF) > freqF ) { // Changing this value changes the frequency.
    lcF = NOW;
    R1 = 1;
    for (i = 0; i < 10; i++)
    {
      R0 = generateNoise();
      R1 = R1 || R0;
    }
    digitalWrite (drumF, Fhigh && (mode ? envF > 0 : 1));
    Fhigh = R1 ? !Fhigh : Fhigh;
  }

  // update envelopes:
  if (envA > 0) envA--;
  if (envB > 0) envB--;
  if (envC > 0) envC--;
  if (envD > 0) envD--;
  if (envE > 0) envE--;
  if (envF > 0) envF--;

  // update LFO:
  lptr = (lptr + aIn[6]); // rate
  if (lptr > TWO_PI) lptr = 0.;
  lfo = ((sin(lptr) + 1.) / 2.); // depth
  l1 = lfo * aIn[7]; // 0
  l2 = (1. - lfo ) * aIn[7]; // 180
}

//
// generate noise:
//

unsigned int generateNoise() {
  // See https://en.wikipedia.org/wiki/Linear_feedback_shift_register#Galois_LFSRs
  static unsigned long int lfsr = LFSR_INIT;  /* 32 bit init, nonzero */
  /* If the output bit is 1, apply toggle mask.
     The value has 1 at bits corresponding
     to taps, 0 elsewhere.
  */
  if (lfsr & 1) {
    lfsr =  (lfsr >> 1) ^ LFSR_MASK ;
    return (1);
  }
  else         {
    lfsr >>= 1;
    return (0);
  }
}

//
// debug routine:
//

void debug()
{
  // debugging:
  Serial.print("TRIG: ");
  Serial.print(A);
  Serial.print(" ");
  Serial.print(B);
  Serial.print(" ");
  Serial.print(C);
  Serial.print(" ");
  Serial.print(D);
  Serial.print(" ");
  Serial.print(E);
  Serial.print(" ");
  Serial.print(F);
  Serial.println();
  Serial.print("MODE: ");
  Serial.println(mode);
  Serial.print("POTS: ");
  Serial.print(aIn[0]);
  Serial.print(" ");
  Serial.print(aIn[1]);
  Serial.print(" ");
  Serial.print(aIn[2]);
  Serial.print(" ");
  Serial.print(aIn[3]);
  Serial.print(" ");
  Serial.print(aIn[4]);
  Serial.print(" ");
  Serial.print(aIn[5]);
  Serial.print(" ");
  Serial.print(aIn[6]);
  Serial.print(" ");
  Serial.print(aIn[7]);
  Serial.println();
  Serial.print("LFO: ");
  Serial.print(l1);
  Serial.print(" ");
  Serial.print(l2);
  Serial.println();
}
