#include "DaisyDuino.h"

static DaisyHardware petal;


float clip1, clip2, clip3, clip4;
float insamp1, insamp2, insamp3, insamp4;
bool fx1, fx2, fx3, fx4;

static void AudioCallback(float **in, float **out, size_t size) {
  petal.ProcessAllControls();

  clip1 = petal.controls[2].Value(); // control[2] is KNOB 3 because it starts at 0
  clip2 = petal.controls[3].Value(); // control[3] is KNOB 4 because it starts at 0
  clip3 = petal.controls[4].Value(); // control[4] is KNOB 5 because it starts at 0
  clip4 = petal.controls[5].Value(); // control[5] is KNOB 6 because it starts at 0


 if (petal.buttons[0].RisingEdge()) fx1 = !fx1; // flip the bypass switch
 if (petal.buttons[1].RisingEdge()) fx2 = !fx2; // flip the bypass switch
 if (petal.buttons[2].RisingEdge()) fx3 = !fx3; // flip the bypass switch
 if (petal.buttons[3].RisingEdge()) fx4 = !fx4; // flip the bypass switch
 
  for (size_t i = 0; i < size; i++) { // go through every sample
    for (int chn = 0; chn < 2; chn++) { // alternate channels (left & right)

      if(fx1) // process the first stage - HARD CLIP DISTORTION
      {
        // make knob three go up instead of down and clip it to prevent a divide by 0
        clip1 = constrain(1.0-clip1, 0.001, 1.); 
        insamp1 = in[chn][i];
        if(fabs(insamp1)>clip1) insamp1=clip1*(insamp1>0?1:-1);
        
        in[chn][i] = insamp1 * (1.0/sqrt(clip1)); // do something here
      }
      
      if(fx2) // process the second stage - SINE FOLDING
      {
        insamp2 = in[chn][i];
        float sinesamp = sin(insamp2*PI*3.0);
        in[chn][i] = insamp2*(1.0-clip2) + sinesamp*clip2; // do something here        
      }
      
      if(fx3) // process the third stage
      {
        in[chn][i] = in[chn][i] * clip3; // do something here                
      }
      
      if(fx4) // process the fourth stage
      {
        in[chn][i] = in[chn][i] * clip4; // do something here                        
      }
      
      out[chn][i] = in[chn][i]; // copy to output

    }
  }

}

void setup() {
  petal = DAISY.init(DAISY_PETAL, AUDIO_SR_48K);

  // start callback
  DAISY.begin(AudioCallback);

  Serial.begin(9600);
}

void loop() {

  Serial.println(clip2);

  petal.ClearLeds();
  petal.SetFootswitchLed(0, fx1 ? 1.0f : 0.0f);
  petal.SetFootswitchLed(1, fx2 ? 1.0f : 0.0f);
  petal.SetFootswitchLed(2, fx3 ? 1.0f : 0.0f);
  petal.SetFootswitchLed(3, fx4 ? 1.0f : 0.0f);
  petal.UpdateLeds();

  
  delay(100);
}
