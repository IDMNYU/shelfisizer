float myfscale( float inputValue, float originalMin, float originalMax, float newBegin, float
                newEnd, float curve) {

  float OriginalRange = 0;
  float NewRange = 0;
  float zeroRefCurVal = 0;
  float normalizedCurVal = 0;
  float rangedValue = 0;
  boolean invFlag = 0;


  // condition curve parameter
  // limit range

  if (curve > 10) curve = 10;
  if (curve < -10) curve = -10;

  curve = (curve * -.1) ; // - invert and scale - this seems more intuitive - postive numbers give more weight to high end on output
  curve = pow(10, curve); // convert linear scale into logarithmic exponent for other pow function

  // Check for out of range inputValues
  if (inputValue < originalMin) {
    inputValue = originalMin;
  }
  if (inputValue > originalMax) {
    inputValue = originalMax;
  }

  // Zero Reference the values
  OriginalRange = originalMax - originalMin;

  if (newEnd > newBegin) {
    NewRange = newEnd - newBegin;
  }
  else
  {
    NewRange = newBegin - newEnd;
    invFlag = 1;
  }

  zeroRefCurVal = inputValue - originalMin;
  normalizedCurVal = zeroRefCurVal / OriginalRange; // normalize to 0 - 1 float



  // Check for originalMin > originalMax - the math for all other cases i.e. negative numbers seems to work out fine
  if (originalMin > originalMax ) {
    return 0;
  }

  if (invFlag == 0) {
    rangedValue = (pow(normalizedCurVal, curve) * NewRange) + newBegin;

  }
  else // invert the ranges
  {
    rangedValue = newBegin - (pow(normalizedCurVal, curve) * NewRange);
  }

  // constrain
  float highout = newBegin>newEnd?newBegin:newEnd;
  float lowout = newBegin<=newEnd?newBegin:newEnd;
  rangedValue = rangedValue>highout?highout:rangedValue;
  rangedValue = rangedValue<lowout?lowout:rangedValue;

  return rangedValue;
  //;
}

float myCurve(float x, float fac)
{
  float f = fac * 2.0 - 1.0;
  float qIn = x * x * x * x; // exp
  float v = (x - 1.0);
  float qOut = v * v * v * (1.0 - x) + 1.0; // log
  float out = 0.;
  if (f < 0.) // fade exp
  {
    out = (fabs(f) * qIn) + ((1.0-fabs(f)) * x);
  }
  else // fade log
  {
    out = (f * qOut) + ((1.0 - f) * x);
  }
  return (out);
}
