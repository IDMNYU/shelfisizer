// ...helper functions...

//
// shift out any byte to a 2-byte shift register
// (view 0, 5, 6):
//
void shiftByte(byte _ptr)
{
  led1 = 0;
  led2 = 0;
  if (_ptr < 8) {
    bitSet(led1, _ptr);
  }
  else {
    bitSet(led2, _ptr - 8);
  }
  updateShiftRegister(led1, led2);
}

//
// shift out an array to a 2-byte shift register
// (view 1-4):
//
void shiftArray(boolean s[], int n)
{
  led1 = 0;
  led2 = 0;
  int i;
  for (i = 0; i < n; i++)
  {
    if (i < 8) {
      if (i == crsr && cp > 0) {
        bitWrite(led1, i, millis() % 200 > 100);
        cp--;
      }
      else bitWrite(led1, i, s[i]);
    }
    else {
      if (i == crsr && cp > 0) {
        bitWrite(led2, i - 8, millis() % 200 > 100);
        cp--;
      }
      else bitWrite(led2, i - 8, s[i]);
    }
  }

  updateShiftRegister(led1, led2);
}

//
// pulse outputs:
//
void updateOutputPins()
{
  // update output pins
  digitalWrite(aPin, Ap > 0);
  digitalWrite(bPin, Bp > 0);
  digitalWrite(cPin, Cp > 0);
  digitalWrite(dPin, Dp > 0);
  Ap--;
  Bp--;
  Cp--;
  Dp--;
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

//
// debug routine:
//

void debug(int _a, int _b, int _c, int _d, int _e)
{
  Serial.print(_a);
  Serial.print(" ");
  Serial.print(_b);
  Serial.print(" ");
  Serial.print(_c);
  Serial.print(" ");
  Serial.print(_d);
  Serial.print(" ");
  Serial.println(_e);
}
