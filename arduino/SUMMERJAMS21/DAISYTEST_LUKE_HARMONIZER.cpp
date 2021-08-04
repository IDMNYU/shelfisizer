#include "DAISYTEST_LUKE_HARMONIZER.h"

namespace DAISYTEST_LUKE_HARMONIZER {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_delay_1;
	Sah __m_sah_21;
	SineCycle __m_cycle_24;
	SineCycle __m_cycle_23;
	SineCycle __m_cycle_30;
	SineCycle __m_cycle_25;
	SineCycle __m_cycle_27;
	SineCycle __m_cycle_26;
	SineCycle __m_cycle_29;
	SineCycle __m_cycle_28;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_10;
	t_sample m_history_5;
	t_sample m_history_6;
	t_sample m_history_4;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample m_history_7;
	t_sample samplerate;
	t_sample m_history_9;
	t_sample m_history_20;
	t_sample m_knob4_rate_18;
	t_sample m_history_13;
	t_sample m_history_12;
	t_sample m_history_11;
	t_sample m_sw_19;
	t_sample m_history_8;
	t_sample m_knob3_depth_16;
	t_sample m_sw_15;
	t_sample m_knob5_breadth_17;
	t_sample m_knob6_taps_14;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_delay_1.reset("m_delay_1", ((int)10000));
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_knob6_taps_14 = ((int)0);
		m_sw_15 = ((int)0);
		m_knob3_depth_16 = ((int)0);
		m_knob5_breadth_17 = 127;
		m_knob4_rate_18 = ((int)0);
		m_sw_19 = ((int)0);
		m_history_20 = ((int)0);
		__m_sah_21.reset(0);
		__m_cycle_23.reset(samplerate, 0);
		__m_cycle_24.reset(samplerate, 0);
		__m_cycle_25.reset(samplerate, 0);
		__m_cycle_26.reset(samplerate, 0);
		__m_cycle_27.reset(samplerate, 0);
		__m_cycle_28.reset(samplerate, 0);
		__m_cycle_29.reset(samplerate, 0);
		__m_cycle_30.reset(samplerate, 0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		t_sample * __out5 = __outs[4];
		t_sample * __out6 = __outs[5];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample sub_6402 = (m_knob6_taps_14 - ((int)0));
		t_sample scale_6399 = ((safepow((sub_6402 * ((t_sample)1)), ((int)1)) * ((t_sample)-0.5)) + ((int)1));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_112 = __m_sah_21(m_history_20, m_sw_19, ((int)0));
			t_sample gen_114 = sah_112;
			t_sample rsub_110 = (((int)1) - sah_112);
			t_sample history_111_next_113 = fixdenorm(rsub_110);
			t_sample out3 = gen_114;
			t_sample out5 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample add_115 = (gen_114 + ((int)1));
			t_sample choice_22 = int(add_115);
			t_sample gate_107 = (((choice_22 >= 1) && (choice_22 < 2)) ? in1 : 0);
			t_sample gate_108 = ((choice_22 >= 2) ? in1 : 0);
			t_sample switch_29 = (m_sw_15 ? ((int)0) : gate_108);
			t_sample mix_6403 = (m_history_13 + (((t_sample)0.0042742627044161) * (m_knob6_taps_14 - m_history_13)));
			t_sample mix_19 = mix_6403;
			t_sample mix_6404 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_19 - m_history_12)));
			t_sample mix_17 = mix_6404;
			t_sample mix_6405 = (m_history_11 + (((t_sample)0.0042742627044161) * (mix_17 - m_history_11)));
			t_sample mix_15 = mix_6405;
			t_sample gen_27 = mix_15;
			t_sample history_21_next_24 = fixdenorm(mix_19);
			t_sample history_18_next_25 = fixdenorm(mix_17);
			t_sample history_16_next_26 = fixdenorm(mix_15);
			t_sample sub_6409 = (gen_27 - ((int)0));
			t_sample scale_6406 = ((safepow((sub_6409 * ((t_sample)1)), ((int)1)) * ((int)4)) + (-3));
			t_sample clamp_2405 = ((scale_6406 <= ((int)0)) ? ((int)0) : ((scale_6406 >= ((int)1)) ? ((int)1) : scale_6406));
			t_sample sub_6413 = (gen_27 - ((int)0));
			t_sample scale_6410 = ((safepow((sub_6413 * ((t_sample)1)), ((int)1)) * ((int)4)) + (-2));
			t_sample clamp_2367 = ((scale_6410 <= ((int)0)) ? ((int)0) : ((scale_6410 >= ((int)1)) ? ((int)1) : scale_6410));
			t_sample sub_6417 = (gen_27 - ((int)0));
			t_sample scale_6414 = ((safepow((sub_6417 * ((t_sample)1)), ((int)1)) * ((int)4)) + (-1));
			t_sample clamp_2329 = ((scale_6414 <= ((int)0)) ? ((int)0) : ((scale_6414 >= ((int)1)) ? ((int)1) : scale_6414));
			t_sample mix_6418 = (m_history_10 + (((t_sample)0.0042742627044161) * (m_knob3_depth_16 - m_history_10)));
			t_sample mix_6269 = mix_6418;
			t_sample mix_6419 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_6269 - m_history_9)));
			t_sample mix_6279 = mix_6419;
			t_sample mix_6420 = (m_history_8 + (((t_sample)0.0042742627044161) * (mix_6279 - m_history_8)));
			t_sample mix_6273 = mix_6420;
			t_sample gen_117 = mix_6273;
			t_sample history_21_next_6277 = fixdenorm(mix_6269);
			t_sample history_18_next_6276 = fixdenorm(mix_6279);
			t_sample history_16_next_6274 = fixdenorm(mix_6273);
			t_sample mix_6421 = (m_history_7 + (((t_sample)0.0042742627044161) * (m_knob5_breadth_17 - m_history_7)));
			t_sample mix_6284 = mix_6421;
			t_sample mix_6422 = (m_history_6 + (((t_sample)0.0042742627044161) * (mix_6284 - m_history_6)));
			t_sample mix_6294 = mix_6422;
			t_sample mix_6423 = (m_history_5 + (((t_sample)0.0042742627044161) * (mix_6294 - m_history_5)));
			t_sample mix_6288 = mix_6423;
			t_sample gen_4436 = mix_6288;
			t_sample history_21_next_6292 = fixdenorm(mix_6284);
			t_sample history_18_next_6290 = fixdenorm(mix_6294);
			t_sample history_16_next_6291 = fixdenorm(mix_6288);
			t_sample mul_4680 = (gen_4436 * ((int)1));
			t_sample pass_5086 = mul_4680;
			t_sample mul_4028 = (gen_4436 * ((int)2));
			t_sample pass_5168 = mul_4028;
			t_sample mul_4110 = (gen_4436 * ((int)3));
			t_sample pass_5250 = mul_4110;
			t_sample mul_4192 = (gen_4436 * ((int)4));
			t_sample pass_5332 = mul_4192;
			t_sample mix_6424 = (m_history_4 + (((t_sample)0.0042742627044161) * (m_knob4_rate_18 - m_history_4)));
			t_sample mix_6299 = mix_6424;
			t_sample mix_6425 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_6299 - m_history_3)));
			t_sample mix_6309 = mix_6425;
			t_sample mix_6426 = (m_history_2 + (((t_sample)0.0042742627044161) * (mix_6309 - m_history_2)));
			t_sample mix_6306 = mix_6426;
			t_sample gen_47 = mix_6306;
			t_sample history_21_next_6303 = fixdenorm(mix_6299);
			t_sample history_18_next_6308 = fixdenorm(mix_6309);
			t_sample history_16_next_6302 = fixdenorm(mix_6306);
			t_sample mul_51 = (gen_47 * ((int)1));
			__m_cycle_23.freq(mul_51);
			t_sample cycle_96 = __m_cycle_23(__sinedata);
			t_sample cycleindex_97 = __m_cycle_23.phase();
			t_sample mul_94 = (cycle_96 * gen_117);
			t_sample add_95 = (mul_94 + pass_5086);
			t_sample mul_86 = (gen_47 * ((t_sample)1.5));
			__m_cycle_24.freq(mul_86);
			t_sample cycle_92 = __m_cycle_24(__sinedata);
			t_sample cycleindex_93 = __m_cycle_24.phase();
			t_sample mul_90 = (cycle_92 * gen_117);
			t_sample add_91 = (mul_90 + pass_5086);
			t_sample mul_50 = (gen_47 * ((t_sample)0.5));
			__m_cycle_25.freq(mul_50);
			t_sample cycle_82 = __m_cycle_25(__sinedata);
			t_sample cycleindex_83 = __m_cycle_25.phase();
			t_sample mul_80 = (cycle_82 * gen_117);
			t_sample add_81 = (mul_80 + pass_5168);
			t_sample mul_74 = (gen_47 * ((int)1));
			__m_cycle_26.freq(mul_74);
			t_sample cycle_78 = __m_cycle_26(__sinedata);
			t_sample cycleindex_79 = __m_cycle_26.phase();
			t_sample mul_76 = (cycle_78 * gen_117);
			t_sample add_77 = (mul_76 + pass_5168);
			t_sample mul_49 = (gen_47 * ((t_sample)1.25));
			__m_cycle_27.freq(mul_49);
			t_sample cycle_70 = __m_cycle_27(__sinedata);
			t_sample cycleindex_71 = __m_cycle_27.phase();
			t_sample mul_68 = (cycle_70 * gen_117);
			t_sample add_69 = (mul_68 + pass_5250);
			t_sample mul_62 = (gen_47 * ((t_sample)0.8));
			__m_cycle_28.freq(mul_62);
			t_sample cycle_66 = __m_cycle_28(__sinedata);
			t_sample cycleindex_67 = __m_cycle_28.phase();
			t_sample mul_64 = (cycle_66 * gen_117);
			t_sample add_65 = (mul_64 + pass_5250);
			t_sample mul_48 = (gen_47 * ((t_sample)1.95));
			__m_cycle_29.freq(mul_48);
			t_sample cycle_60 = __m_cycle_29(__sinedata);
			t_sample cycleindex_61 = __m_cycle_29.phase();
			t_sample mul_58 = (cycle_60 * gen_117);
			t_sample add_59 = (mul_58 + pass_5332);
			t_sample mul_52 = (gen_47 * ((int)0));
			__m_cycle_30.freq(mul_52);
			t_sample cycle_56 = __m_cycle_30(__sinedata);
			t_sample cycleindex_57 = __m_cycle_30.phase();
			t_sample mul_54 = (cycle_56 * gen_117);
			t_sample add_55 = (mul_54 + pass_5332);
			t_sample tap_99 = m_delay_1.read_linear(add_95);
			t_sample tap_100 = m_delay_1.read_linear(add_91);
			t_sample tap_101 = m_delay_1.read_linear(add_81);
			t_sample tap_102 = m_delay_1.read_linear(add_77);
			t_sample tap_103 = m_delay_1.read_linear(add_69);
			t_sample tap_104 = m_delay_1.read_linear(add_65);
			t_sample tap_105 = m_delay_1.read_linear(add_59);
			t_sample tap_106 = m_delay_1.read_linear(add_55);
			t_sample mul_1492 = (tap_105 * clamp_2405);
			t_sample mul_1601 = (tap_104 * clamp_2367);
			t_sample mul_1928 = (tap_101 * clamp_2329);
			t_sample mul_2037 = (tap_100 * ((int)1));
			t_sample mul_72 = ((((mul_2037 + mul_1928) + mul_1601) + mul_1492) * scale_6399);
			t_sample add_84 = (switch_29 + mul_72);
			t_sample out2 = (add_84 + gate_107);
			t_sample mul_1383 = (tap_106 * clamp_2405);
			t_sample mul_1710 = (tap_103 * clamp_2367);
			t_sample mul_1819 = (tap_102 * clamp_2329);
			t_sample mul_2146 = (tap_99 * ((int)1));
			t_sample mul_73 = ((((mul_2146 + mul_1819) + mul_1710) + mul_1383) * scale_6399);
			t_sample add_116 = (switch_29 + mul_73);
			t_sample out1 = (gate_107 + add_116);
			m_history_20 = history_111_next_113;
			m_history_13 = history_21_next_24;
			m_history_11 = history_16_next_26;
			m_history_12 = history_18_next_25;
			m_history_10 = history_21_next_6277;
			m_history_8 = history_16_next_6274;
			m_history_9 = history_18_next_6276;
			m_history_7 = history_21_next_6292;
			m_history_5 = history_16_next_6291;
			m_history_6 = history_18_next_6290;
			m_history_4 = history_21_next_6303;
			m_history_2 = history_16_next_6302;
			m_history_3 = history_18_next_6308;
			m_delay_1.write(gate_108);
			m_delay_1.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			
		};
		return __exception;
		
	};
	inline void set_knob6_taps(t_param _value) {
		m_knob6_taps_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_depth(t_param _value) {
		m_knob3_depth_16 = (_value < 2 ? 2 : (_value > 500 ? 500 : _value));
	};
	inline void set_knob5_breadth(t_param _value) {
		m_knob5_breadth_17 = (_value < 120 ? 120 : (_value > 1200 ? 1200 : _value));
	};
	inline void set_knob4_rate(t_param _value) {
		m_knob4_rate_18 = (_value < 0.01 ? 0.01 : (_value > 10 ? 10 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 6;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 6; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "led3", "led4" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_knob3_depth(value); break;
		case 1: self->set_knob4_rate(value); break;
		case 2: self->set_knob5_breadth(value); break;
		case 3: self->set_knob6_taps(value); break;
		case 4: self->set_sw1(value); break;
		case 5: self->set_sw5(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob3_depth_16; break;
		case 1: *value = self->m_knob4_rate_18; break;
		case 2: *value = self->m_knob5_breadth_17; break;
		case 3: *value = self->m_knob6_taps_14; break;
		case 4: *value = self->m_sw_19; break;
		case 5: *value = self->m_sw_15; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(6 * sizeof(ParamInfo));
	self->__commonstate.numparams = 6;
	// initialize parameter 0 ("m_knob3_depth_16")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_depth_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 2;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_rate_18")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_rate_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_breadth_17")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_breadth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_breadth_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 120;
	pi->outputmax = 1200;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob6_taps_14")
	pi = self->__commonstate.params + 3;
	pi->name = "knob6_taps";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob6_taps_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_19")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_sw_15")
	pi = self->__commonstate.params + 5;
	pi->name = "sw5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // DAISYTEST_LUKE_HARMONIZER::
