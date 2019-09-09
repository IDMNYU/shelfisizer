// ...main functions...

//
// setup:
//
void setup()
{
  // establish pin states:
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(s1Pin, INPUT_PULLUP);
  pinMode(s2Pin, INPUT_PULLUP);
  pinMode(s3Pin, INPUT_PULLUP);
  pinMode(s4Pin, INPUT_PULLUP);
  pinMode(tPin, INPUT);
  pinMode(aPin, OUTPUT);
  pinMode(bPin, OUTPUT);
  pinMode(cPin, OUTPUT);
  pinMode(dPin, OUTPUT);
  if (db) Serial.begin(9600); // launch serial only on debug
}

//
// main loop:
//
void loop()
{
  // read input pins:
  boolean s1 = !digitalRead(s1Pin); // read button 1
  boolean s2 = !digitalRead(s2Pin); // read button 2
  boolean s3 = !digitalRead(s3Pin); // read button 3
  boolean s4 = !digitalRead(s4Pin); // read button 4
  int f = analogRead(tPin); // read the trigger input (ANALOG)
  if (db) Serial.println(f);
  boolean t = f > aThresh; // is the trigger voltage above the threshold
  //boolean t = digitalRead(tPin);

  if (db) debug(s1, s2, s3, s4, t); // debug

  // buttons:

  // S1: CHANGE "VIEW"
  if (s1 == 1 & s1_o == 0)
  {
    view = (view + 1) % (NUMVIEWS + 1);
    if (view == 5) crsr = seqstart;
    else if (view == 6) crsr = seqend;
    else crsr = 0; // reset cursor
    cp = crsrtime;
  }
  s1_o = s1;

  // S2: CURSOR "UP"
  if (s2 == 1 & s2_o == 0)
  {
    crsr--;
    cp = crsrtime;
    if (crsr < 0) crsr = 15;
    if (view == 0) sptr = random(seqstart, seqend + 1);
    else if (view == 5) seqstart = crsr;
    else if (view == 6) seqend = crsr;
  }
  s2_o = s2;

  // S3: CURSOR "DOWN"
  if (s3 == 1 & s3_o == 0)
  {
    crsr++;
    cp = crsrtime;
    if (crsr > 15) crsr = 0;
    if (view == 0) dir = dir * -1;
    else if (view == 5) seqstart = crsr;
    else if (view == 6) seqend = crsr;
  }
  s3_o = s3;

  // S4: "SELECT" VALUE
  if (s4 == 1 & s4_o == 0)
  {
    if (view == 0) sptr = dir > 0 ? seqstart : seqend; // reset clock
    else if (view == 1) seqA[crsr] = !seqA[crsr];
    else if (view == 2) seqB[crsr] = !seqB[crsr];
    else if (view == 3) seqC[crsr] = !seqC[crsr];
    else if (view == 4) seqD[crsr] = !seqD[crsr];
    else if (view == 5) seqstart = 0; // reset
    else if (view == 6) seqend = 15; // reset
  }
  s4_o = s4;

  updateOutputPins(); // fire triggers

  // fire shift registers (LEDs):
  if (view == 0) shiftByte(sptr);
  else if (view == 1) shiftArray(seqA, 16);
  else if (view == 2) shiftArray(seqB, 16);
  else if (view == 3) shiftArray(seqC, 16);
  else if (view == 4) shiftArray(seqD, 16);
  else if (view == 5) shiftByte(seqstart);
  else if (view == 6) shiftByte(seqend);

  // T: CLOCK
  if (t == 1 & t_o == 0)
  {
    sptr += dir;
    if (dir == 1 && sptr > seqend)
    {
      if (seqend >= seqstart) sptr = seqstart;
      else if (sptr < seqstart) sptr = seqstart;
    }
    if (dir == -1 && sptr < seqstart)
    {
      if (seqstart <= seqend) sptr = seqend;
      else if (sptr > seqend) sptr = seqend;
    }
    if (sptr > 15) sptr = 0; // wrap
    if (sptr < 0) sptr = 15; // wrap
    //sptr = (sptr + 1) % 16; // increment sequence

    // pull triggers high:
    Ap = seqA[sptr] * ptime;
    Bp = seqB[sptr] * ptime;
    Cp = seqC[sptr] * ptime;
    Dp = seqD[sptr] * ptime;
  }
  t_o = t;

}
