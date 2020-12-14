//
// shift out an array to a 2-byte shift register
// (view 1-4):
//
void shiftArray(int s[], int n)
{
  byte l1 = 0;
  byte l2 = 0;
  int i;
  for (i = 0; i < n; i++)
  {
    if (i < 8) {
      bitWrite(l1, i, s[i]>0);
    }
    else {
      bitWrite(l2, i - 8, s[i]>0);
    }
  }

  updateShiftRegister(l1, l2);
}

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
