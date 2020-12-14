
#include <Wire.h>
#include <math.h>
#include <Adafruit_MCP4725.h>
#include <Luke_RLD1015.h>

#define DEBUG false // debug flag

#define MAXKNOB 1672 // max range of knobs
#define MINSI 0.01 // smallest sampling increment
#define MAXSI 1000 // largest sampling increment
#define MAXENV 4095 // largest DAC value
#define END 0
#define ATTACK 1
#define HOLD 2
#define DECAY 3
#define SUSTAIN 4
#define RELEASE 5
#define FCURVE 1. // linear / log scaling

// pins
#define TPINA 2 // trigger input pin for envelope A
#define TPINB 3 // trigger input pin for envelope B
#define GPINA 4 // gate input pin for envelope A
#define GPINB 5 // gate input pin for envelope B
#define EPINA 7 // end trigger output pin for envelope A
#define EPINB 6 // end trigger output pin for envelope B
#define SPINA 9 // status output pin (PWM) for envelope A
#define SPINB 10 // status output pin (PWM) for envelope B

// adc/dac i2c chips
Adafruit_MCP4725 dac1, dac2;
Luke_RLD1015 adc1(0x48);
Luke_RLD1015 adc2(0x49);
Luke_RLD1015 adc3(0x4A);
Luke_RLD1015 adc4(0x4B);

float Acv = 0; // attack time
float Hcv = 0; // hold time
float Dcv = 0; // decay time
float Scv = 0; // sustain level
float Rcv = 0; // release time
float Ak = 0; // attack time
float Hk = 0; // hold time
float Dk = 0; // decay time
float Sk = 0; // sustain level
float Rk = 0; // release time
float ampcv = 0; // amp curve cv
float durcv = 0; // overall duration knob
float ampk = 0; // amp curve knob
float durk = 0; // overall duration knob
boolean durmode1 = 0; //duration switch 1
boolean durmode2 = 0; //duration switch 2
byte readptr = 0; // which pin to read

float env1 = 0; // value for env A
float envc1 = 0; // envelope stage clock A
byte envstage1 = 0; // envelope stage A
float env2 = 0; // value for env B
float envc2 = 0; // envelope stage clock B
byte envstage2 = 0; // envelope stage B
boolean T1 = 0; // trigger A
boolean OT1 = 0; // old trigger A
boolean G1 = 0; // gate A
boolean OG1 = 0; // old gate A
boolean T2 = 0; // trigger B
boolean OT2 = 0; // old trigger B
boolean G2 = 0; // gate B
boolean OG2 = 0; // old gate B
boolean E1 = 0; // end trigger A
boolean OE1 = 0; // end trigger A
boolean E2 = 0; // end trigger B
boolean OE2 = 0; // end trigger B

float SP1 = 0.; // set point for stage change A
float SP2 = 0.; // set point for stage change B
float durmult = 1.; // duration multiplier

unsigned long now, then; // millis
boolean rr = 0; // request-receive flag
boolean sampflag = 0; // sample flag

const int GAIN = 256;

void setup(void) {
  if (DEBUG) Serial.begin(9600);
  if (DEBUG) Serial.println("Hello!");

  dac1.begin(0x62);
  dac2.begin(0x63);

  adc1.begin();
  adc2.begin();
  adc3.begin();
  adc4.begin();
  adc1.setGain(GAIN);
  adc2.setGain(GAIN);
  adc3.setGain(GAIN);
  adc4.setGain(GAIN);

  // pin modes:
  pinMode(TPINA, INPUT);
  pinMode(TPINB, INPUT);
  pinMode(GPINA, INPUT);
  pinMode(GPINB, INPUT);
  pinMode(EPINA, OUTPUT);
  pinMode(EPINB, OUTPUT);
  pinMode(SPINA, OUTPUT);
  pinMode(SPINB, OUTPUT);

}

void loop(void) {

  now = millis();

  // set duration multiplier:
  durmult = 1.;
  if (durmode1) durmult = 0.1;
  if (durmode2) durmult = 0.01;
  durmult *= 1.0 / durk;

  // read trigger pins
  T1 = digitalRead(TPINA);
  T2 = digitalRead(TPINB);
  G1 = digitalRead(GPINA);
  G2 = digitalRead(GPINB);

  if (T1 && !OT1) // trigger chA
  {
    env1 = 0;
    envc1 = 0;
    envstage1 = ATTACK;
  }

  if (G1 && !OG1) // gate chA
  {
    if (envstage1 == END) // no trigger - do trigger
    {
      env1 = 0;
      envc1 = 0;
      envstage1 = ATTACK;
    }
  }

  if (T2 && !OT2) // trigger chB
  {
    env2 = 0;
    envc2 = 0;
    envstage2 = ATTACK;
  }

  if (G2 && !OG2) // gate chB
  {
    if (envstage2 == END) // no trigger - do trigger
    {
      env2 = 0;
      envc2 = 0;
      envstage2 = ATTACK;
    }
  }

  // envelope advance chA

  if (envstage1 == ATTACK) // rise from 0 to 1
  {
    envc1 += myfscale(Ak, 0., 1., MAXSI, MINSI, FCURVE) * durmult;
    env1 = envc1;
    if (envc1 >= MAXENV) { // advance to hold
      envc1 = 0;
      env1 = MAXENV;
      envstage1 = HOLD;
    }
  }
  else if (envstage1 == HOLD) // stay at 1
  {
    envc1 += myfscale(Hk, 0., 1., MAXSI, MINSI, FCURVE) * durmult;
    env1 = MAXENV;
    if (envc1 >= MAXENV) { // advance to release
      envc1 = 0;
      env1 = MAXENV;
      if (G1) envstage1 = DECAY; else envstage1 = RELEASE; // if gate is high go to decay
      SP1 = env1;
    }
  }
  else if (envstage1 == DECAY) // fall to sustain level
  {
    envc1 += myfscale(Dk, 0., 1., MAXSI, MINSI, FCURVE) * durmult;
    env1 = myfscale(envc1, 0., MAXENV, SP1, Sk * MAXENV, 0);
    if (envc1 >= MAXENV) { // advance to sustain
      envc1 = 0;
      env1 = Sk * MAXENV;
      SP1 = env1;
      if (G1) envstage1 = SUSTAIN; else envstage1 = RELEASE; // if gate is high go to decay
    }
    else if (!G1) // drop to release
    {
      envc1 = 0;
      SP1 = env1;
      envstage1 = RELEASE;
    }
  }
  else if (envstage1 == SUSTAIN) // hold at sustain level
  {
    env1 = Sk * MAXENV;
    if (!G1) // drop to release
    {
      envc1 = 0;
      SP1 = env1;
      envstage1 = RELEASE;
    }
  }
  else if (envstage1 == RELEASE) // fall to 0
  {
    envc1 += myfscale(Rk, 0., 1., MAXSI, MINSI, FCURVE) * durmult;
    env1 = myfscale(envc1, 0., MAXENV, SP1, 0, 0);
    if (envc1 >= MAXENV) { // advance to end
      envc1 = 0;
      env1 = 0;
      SP1 = 0;
      envstage1 = END;
    }
  }
  else if (envstage1 == END) { // park at 0
    env1 = 0;
  }

  // read CV knobs and jacks
  if (sampflag) {
    readInput(readptr, rr);
    sampflag = 0;
  }

  // envelope advance chB

  if (envstage2 == ATTACK) // rise from 0 to 1
  {
    envc2 += myfscale(Ak, 0., 1., MAXSI, MINSI, FCURVE) * durmult;
    env2 = envc2;
    if (envc2 >= MAXENV) { // advance to hold
      envc2 = 0;
      env2 = MAXENV;
      envstage2 = HOLD;
    }
  }
  else if (envstage2 == HOLD) // stay at 1
  {
    envc2 += myfscale(Hk, 0., 1., MAXSI, MINSI, FCURVE) * durmult;
    env2 = MAXENV;
    if (envc2 >= MAXENV) { // advance to release
      envc2 = 0;
      env2 = MAXENV;
      if (G2) envstage2 = DECAY; else envstage2 = RELEASE; // if gate is high go to decay
      SP2 = env2;
    }
  }
  else if (envstage2 == DECAY) // fall to sustain level
  {
    envc2 += myfscale(Dk, 0., 1., MAXSI, MINSI, FCURVE) * durmult;
    env2 = myfscale(envc2, 0., MAXENV, SP2, Sk * MAXENV, 0);
    if (envc2 >= MAXENV) { // advance to sustain
      envc2 = 0;
      env2 = Sk * MAXENV;
      SP2 = env2;
      if (G2) envstage2 = SUSTAIN; else envstage2 = RELEASE; // if gate is high go to decay
    }
    else if (!G2) // drop to release
    {
      envc2 = 0;
      SP2 = env2;
      envstage2 = RELEASE;
    }
  }
  else if (envstage2 == SUSTAIN) // hold at sustain level
  {
    env2 = Sk * MAXENV;
    if (!G2) // drop to release
    {
      envc2 = 0;
      SP2 = env2;
      envstage2 = RELEASE;
    }
  }
  else if (envstage2 == RELEASE) // fall to 0
  {
    envc2 += myfscale(Rk, 0., 1., MAXSI, MINSI, FCURVE) * durmult;
    env2 = myfscale(envc2, 0., MAXENV, SP2, 0, 0);
    if (envc2 >= MAXENV) { // advance to end
      envc2 = 0;
      env2 = 0;
      SP2 = 0;
      envstage2 = END;
    }
  }
  else if (envstage2 == END) { // park at 0
    env2 = 0;
  }


  // read CV knobs and jacks
  if (sampflag) {
    readInput(readptr, rr);
    sampflag = 0;
  }

  if (DEBUG) debug();

  // to fix:
  float outenv1 = MAXENV * myCurve(env1 / (float)MAXENV, ampk);
  float outenv2 = MAXENV * myCurve(env2 / (float)MAXENV, ampk);

  dac1.setVoltage((uint32_t)outenv1, false);
  dac2.setVoltage((uint32_t)outenv2, false);

  // end bang:
  if(envstage1==END) E1=1; else E1=0;
//  digitalWrite(EPINA, E1&&!OE1); // pulse
  digitalWrite(EPINA, E1); // gate
  if(envstage2==END) E2=1; else E2=0;
//  digitalWrite(EPINB, E2&&!OE2); // pulse
  digitalWrite(EPINB, E2); // gate

  // lights
  digitalWrite(SPINA, envstage1>0);
  digitalWrite(SPINB, envstage2>0);


  // update previous states
  OT1 = T1;
  OT2 = T2;
  OG1 = G1;
  OG2 = G2;
  OE1 = E1;
  OE2 = E2;
  if (now - then > 25) // sample all inputs 4 x second
  {
    sampflag = 1;
    rr = !rr;
    if (rr == 0) readptr = (readptr + 1) % 4;
    then = now;
  }
}

void readInput(byte _ptr, boolean _rr)
{
  int16_t rpin;

  switch (_ptr)
  {
    case 0:
      if (!_rr) {
        adc1.requestADC_SingleEnded(0); // attack cv
        adc2.requestADC_SingleEnded(0); // release cv
        adc3.requestADC_SingleEnded(0); // attack knob
        adc4.requestADC_SingleEnded(0); // release knob
      }
      else if (_rr) {
        rpin = adc1.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Acv = rpin / (float)MAXKNOB;
        rpin = adc2.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Rcv = rpin / (float)MAXKNOB;
        rpin = adc3.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Ak = rpin / (float)MAXKNOB;
        rpin = adc4.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Rk = rpin / (float)MAXKNOB;
      }
      break;
    case 1:
      if (!_rr) {
        adc1.requestADC_SingleEnded(1); // hold cv
        adc2.requestADC_SingleEnded(1); // amp cv (attenuator)
        adc3.requestADC_SingleEnded(1); // hold knob
        adc4.requestADC_SingleEnded(1); // amp knob (attenuator)
      }
      else if (_rr) {
        rpin = adc1.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Hcv = rpin / (float)MAXKNOB;
        rpin = adc2.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        ampcv = 1.0 - (rpin / (float)MAXKNOB);
        rpin = adc3.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Hk = rpin / (float)MAXKNOB;
        rpin = adc4.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        ampk = 1.0 - (rpin / (float)MAXKNOB);
      }
      break;
    case 2:
      if (!_rr) {
        adc1.requestADC_SingleEnded(2); // decay cv
        adc2.requestADC_SingleEnded(2); // dur cv
        adc3.requestADC_SingleEnded(2); // decay knob
        adc4.requestADC_SingleEnded(2); // dur knob
      }
      else if (_rr) {
        rpin = adc1.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Dcv = rpin / (float)MAXKNOB;
        rpin = adc2.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        durcv = myfscale(rpin, 0., (float)MAXKNOB, 1., 10., 0.);
        rpin = adc3.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Dk = rpin / (float)MAXKNOB;
        rpin = adc4.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        durk = myfscale(rpin, 0., (float)MAXKNOB, 1., 10., 0.);
      }
      break;
    case 3:
      if (!_rr) {
        adc1.requestADC_SingleEnded(3); // sustain cv
        adc2.requestADC_SingleEnded(3); // dur switch 1
        adc3.requestADC_SingleEnded(3); // sustain knob
        adc4.requestADC_SingleEnded(3); // dur switch 2
      }
      else if (_rr) {
        rpin = adc1.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Scv = rpin / (float)MAXKNOB;
        rpin = adc2.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        durmode1 = rpin > 500;
        rpin = adc3.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        Sk = rpin / (float)MAXKNOB;
        rpin = adc4.receiveADC_SingleEnded();
        if (rpin > MAXKNOB) rpin = 0; // catch
        durmode2 = rpin > 500;
      }
      break;
  }

}


// put debug shit here:
void debug()
{

//  Serial.print("A: Trig: ");
//  Serial.print(T1);
//  Serial.print(" Gate: ");
//  Serial.print(G1);
//  Serial.print("  B: Trig: ");
//  Serial.print(T2);
//  Serial.print(" Gate: ");
//  Serial.println(G2);

  Serial.print("Stage: ");
  Serial.println(envstage1);

//  Serial.print("A: ");
//  Serial.print(Acv);
//  Serial.print(" H: ");
//  Serial.print(Hcv);
//  Serial.print(" D: ");
//  Serial.print(Dcv);
//  Serial.print(" S: ");
//  Serial.print(Scv);
//  Serial.print(" R: ");
//  Serial.print(Rcv);

//  Serial.print(" A: ");
//  Serial.print(Ak);
//  Serial.print(" H: ");
//  Serial.print(Hk);
//  Serial.print(" D: ");
//  Serial.print(Dk);
//  Serial.print(" S: ");
//  Serial.print(Sk);
//  Serial.print(" R: ");
//  Serial.print(Rk);
//  Serial.println();

//  Serial.print(" amp: ");
//  Serial.print(ampk);
//  Serial.print(" dur: ");
//  Serial.print(durk);
//  Serial.print(" amp: ");
//  Serial.print(ampcv);
//  Serial.print(" dur: ");
//  Serial.print(durcv);
//  Serial.print(" durmode1: ");
//  Serial.print(durmode1);
//  Serial.print(" durmode2: ");
//  Serial.print(durmode2);
//  Serial.println();

//  Serial.print(env1);
//  Serial.print(" ");
//  Serial.print(env2);
//  Serial.println();

}
