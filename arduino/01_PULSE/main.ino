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
  pinMode(aPin, INPUT_PULLUP);
  pinMode(bPin, INPUT_PULLUP);
  pinMode(cPin, INPUT_PULLUP);
  pinMode(dPin, INPUT_PULLUP);
  pinMode(tPin, INPUT);
  pinMode(s1Pin, OUTPUT);
  pinMode(s2Pin, OUTPUT);
  pinMode(s3Pin, OUTPUT);
  pinMode(s4Pin, OUTPUT);
  if (db) Serial.begin(9600); // launch serial only on debug
}

//
// main loop:
//
void loop()
{
  // read input pins:
  boolean a = !digitalRead(aPin); // read button 1
  boolean b = !digitalRead(bPin); // read button 2
  boolean c = !digitalRead(cPin); // read button 3
  boolean d = !digitalRead(dPin); // read button 4
  int f = analogRead(tPin); // read the trigger input (ANALOG)
  if (db) Serial.println(f);
  boolean t = f > aThresh; // is the trigger voltage above the threshold
  //boolean t = digitalRead(tPin);

  if (db) debug(a, b, c, d, t); // debug

  // buttons:

  // A: CHANGE "VIEW"
  if (a == 1 & a_o == 0)
  {
    view = (view + 1) % (NUMVIEWS + 1);
    if (view == 5) crsr = seqstart;
    else if (view == 6) crsr = seqend;
    else crsr = 0; // reset cursor
    cp = crsrtime;
  }
  a_o = a;

  // B: CURSOR LEFT
  if (b == 1 & b_o == 0)
  {
    crsr--;
    cp = crsrtime;
    if (crsr < 0) crsr = 15;
    if (view == 0) sptr = random(seqstart, seqend + 1);
    else if (view == 5) seqstart = crsr;
    else if (view == 6) seqend = crsr;
  }
  b_o = b;

  // C: CURSOR RIGHT
  if (c == 1 & c_o == 0)
  {
    crsr++;
    cp = crsrtime;
    if (crsr > 15) crsr = 0;
    if (view == 0) dir = dir * -1;
    else if (view == 5) seqstart = crsr;
    else if (view == 6) seqend = crsr;
  }
  c_o = c;

  // D: FLIP VALUE
  if (d == 1 & d_o == 0)
  {
    if (view == 0) sptr = dir > 0 ? seqstart : seqend; // reset clock
    else if (view == 1) s1[crsr] = !s1[crsr];
    else if (view == 2) s2[crsr] = !s2[crsr];
    else if (view == 3) s3[crsr] = !s3[crsr];
    else if (view == 4) s4[crsr] = !s4[crsr];
    else if (view == 5) seqstart = 0; // reset
    else if (view == 6) seqend = 15; // reset
  }
  d_o = d;

  updateOutputPins(); // fire triggers

  // fire shift registers (LEDs):
  if (view == 0) shiftByte(sptr);
  else if (view == 1) shiftArray(s1, 16);
  else if (view == 2) shiftArray(s2, 16);
  else if (view == 3) shiftArray(s3, 16);
  else if (view == 4) shiftArray(s4, 16);
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
    s1p = s1[sptr] * ptime;
    s2p = s2[sptr] * ptime;
    s3p = s3[sptr] * ptime;
    s4p = s4[sptr] * ptime;
  }
  t_o = t;

}
