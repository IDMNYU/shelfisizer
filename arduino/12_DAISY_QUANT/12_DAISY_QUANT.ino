#include "DaisyDuino.h"

DaisyHardware hw;


void setup() {
  // put your setup code here, to run once:
  hw  = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
  analogReadResolution(16);
  analogWriteResolution(12);
  pinMode(D23, OUTPUT); // "DAC 1"
  pinMode(D22, OUTPUT); // "DAC 2"
  //Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  float foo = analogRead(A0)/65535.f;
  int bar = foo*4095.f;
  analogWrite(D23, bar);
  analogWrite(D22, random(4096));
  //Serial.println(bar);
  //delay(10);
}
