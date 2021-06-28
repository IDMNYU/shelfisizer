#include "DaisyDuino.h"

static DaisyHardware petal;


float clip1, clip2, clip3, clip4;
float insamp1, insamp2, insamp3, insamp4;
bool fx1, fx2, fx3, fx4;
float lfoposition = 0.; // this is the phase of the LFO
float lforate, lfodepth;

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

 lforate = petal.controls[0].Value() / 10.; // control[2] is KNOB 3 because it starts at 0
 lfodepth = petal.controls[1].Value(); // control[3] is KNOB 4 because it starts at 0
 float amp = 1.0-(lfodepth*(sin(lfoposition)+1.)/2.); // make it 0-1
          
 
  for (size_t i = 0; i < size; i++) { // go through every sample
    for (int chn = 0; chn < 2; chn++) { // alternate channels (left & right)

      if(fx1) // process the first stage - HARD CLIP DISTORTION
      {
        // make knob three go up instead of down and clip it to prevent a divide by 0
        clip1 = constrain(1.0-clip1, 0.001, 1.); 
        insamp1 = in[chn][i];
        // if |sampleValue|>whereWeSetTheClip, set the sampleValue to the clipValue
        if(fabs(insamp1)>clip1) insamp1=clip1*(insamp1>0?1:-1);
        in[chn][i] = insamp1 * (1.0/sqrt(clip1));
      }
      
      if(fx2) // process the second stage - SINE FOLDING
      {
        insamp2 = in[chn][i];
        float sinesamp = sin(insamp2*PI*3.0);
        in[chn][i] = insamp2*(1.0-clip2) + sinesamp*clip2; // do something here        
      }
      
      if(fx3) // process the third stage - Vibrato?
      {
//        insamp3=in[chn][i];
//        if(insamp3!=0) insamp3=1-sqrt(insamp3); 
//        in[chn][i]=insamp3;   
          
          in[chn][i] = in[chn][i] * amp;
      }
      
      if(fx4) // process the fourth stage - experiment
      {
        insamp4=in[chn][i];
        if((int)(insamp4*100)%2==0) insamp4+=in[chn][i-1];
        else insamp4-=in[chn][i-1];  
        //insamp4=constrain(insamp4,-.02,.02);
        in[chn][i]=insamp4*.7;                     
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
  Serial.println(lfodepth);

  petal.ClearLeds();
  petal.SetFootswitchLed(0, fx1 ? 1.0f : 0.0f);
  petal.SetFootswitchLed(1, fx2 ? 1.0f : 0.0f);
  petal.SetFootswitchLed(2, fx3 ? 1.0f : 0.0f);
  petal.SetFootswitchLed(3, fx4 ? 1.0f : 0.0f);
  petal.UpdateLeds();

  
  delay(100);
}
