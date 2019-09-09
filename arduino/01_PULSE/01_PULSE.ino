//
// PULSE
// Shelfisizer 2019, Module 1
//
// 4-voice, 16-step pulse sequencer for
// modular synth triggering by arduino
// clocked with external input.
//
// rld, I<3DM, 5.19
//
// sequencer uses 16 LEDs as a 7-view interface
// controlled by 4 momentary switches and a clock pulse in.
//
// assumes:
// 4 buttons and a 'clock' pin (INPUT).
// 16 stage leds (via 2x74HC595) and 4 trigger leds (OUTPUT).
// inputs and outputs are split to banana jacks for wiring.
//

const boolean db = false; // debug state

// pins:
const int latchPin = 12; // shift register latch
const int clockPin = 13; // shift register clock
const int dataPin = 11; // shift register data
const int s1Pin = 2; // button input 1
const int s2Pin = 3; // button input 2
const int s3Pin = 4; // button input 3
const int s4Pin = 5; // button input 4
const int tPin = A0; // input pin for external pulses
//const int tPin = 6; // input pin for external pulses
const int aPin = 7; // output for sequence A pulses
const int bPin = 8; // output for sequence B pulses
const int cPin = 9; // output for sequence C pulses
const int dPin = 10; // output for sequence D pulses

const int aThresh = 512; // analog voltage threshold for pulse input

// sequencer:
char sptr = 0; // sequence ptr
byte seqstart = 0; // sequence start
byte seqend = 15; // sequence end
byte led1 = 0; // first 8 lights
byte led2 = 0; // second 8 lights

// initial sequences:
//unsigned int s1 = 0b1000100010001000;
//unsigned int s2 = 0b0010001000100010;
//unsigned int s3 = 0b1100110001000010;
//unsigned int s4 = 0b0010001110100001;
boolean seqA[] = {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
boolean seqB[] = {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0};
boolean seqC[] = {1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
boolean seqD[] = {0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1};

// pulse output pins
const int ptime = 100; // pulse high time
int Ap = 0; // pulse state for sequence A
int Bp = 0; // pulse state for sequence B
int Cp = 0; // pulse state for sequence C
int Dp = 0; // pulse state for sequence D

// view:
// 0 = sequence position
// 1-4 = sequence bank A-D
// 5 = sequence start
// 6 = sequence end
byte view = 0;
byte NUMVIEWS = 6;
// old button / trigger states:
boolean s1_o = 0;
boolean s2_o = 0;
boolean s3_o = 0;
boolean s4_o = 0;
boolean t_o = 0;

char crsr = 0; // current "cursor" for sequence editing
char dir = 1; // direction of sequencer
int cp = 0; // cursor blink state
const int crsrtime = 1000; // cursor blink time

// see tabs for routines...
