#include "DaisyDuino.h"

static DaisyHardware petal;


float lfoposition = 0.; // this is the phase of the LFO
float lforate, lfodepth;
bool bypass;

static void AudioCallback(float **in, float **out, size_t size) {
  petal.ProcessAllControls();

  lforate = petal.controls[2].Value() / 10.; // control[2] is KNOB 3 because it starts at 0
  lfodepth = petal.controls[3].Value(); // control[23] is KNOB 4 because it starts at 0

  float amp = 1.0-(lfodepth*(sin(lfoposition)+1.)/2.); // make it 0-1


 if (petal.buttons[0].RisingEdge()) bypass = !bypass; // flip the bypass switch
 
  for (size_t i = 0; i < size; i++) { // go through every sample
    for (int chn = 0; chn < 2; chn++) { // alternate channels (left & right)



      out[chn][i] = in[chn][i] * amp; // amplitude modulation

      if(bypass) out[chn][i] = in[chn][i]; // passthrough

    }
  }

  lfoposition = lfoposition+lforate;
  
}

void setup() {
  petal = DAISY.init(DAISY_PETAL, AUDIO_SR_48K);

  // start callback
  DAISY.begin(AudioCallback);

  //Serial.begin(9600);
}

void loop() {

  //Serial.println(lforate);

  petal.ClearLeds();
  petal.SetFootswitchLed(0, bypass ? 0.0f : 1.0f);
  petal.UpdateLeds();

  
  delay(6);
}
