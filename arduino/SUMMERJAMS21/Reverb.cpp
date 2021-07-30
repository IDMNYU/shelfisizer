#include "Reverb.h"

namespace Reverb {

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
	Delay m_delay_14;
	Delay m_delay_18;
	Delay m_delay_8;
	Delay m_delay_20;
	Delay m_delay_10;
	Delay m_delay_12;
	Delay m_delay_16;
	Delay m_delay_31;
	Delay m_delay_22;
	Delay m_delay_25;
	Delay m_delay_29;
	Delay m_delay_30;
	Delay m_delay_24;
	Delay m_delay_28;
	Delay m_delay_26;
	Delay m_delay_27;
	Sah __m_sah_32;
	int __exception;
	int vectorsize;
	t_sample m_knob5_fb_3;
	t_sample m_history_11;
	t_sample m_knob3_damp_2;
	t_sample m_knob6_spread_1;
	t_sample samplerate;
	t_sample m_sw_4;
	t_sample m_history_13;
	t_sample m_knob1_wetdry_5;
	t_sample m_knob4_fb_6;
	t_sample m_history_9;
	t_sample m_history_17;
	t_sample m_history_23;
	t_sample m_history_19;
	t_sample m_history_21;
	t_sample m_history_7;
	t_sample m_history_15;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_knob6_spread_1 = ((int)0);
		m_knob3_damp_2 = ((t_sample)0.5);
		m_knob5_fb_3 = ((t_sample)0.5);
		m_sw_4 = ((int)0);
		m_knob1_wetdry_5 = ((int)0);
		m_knob4_fb_6 = ((t_sample)0.9);
		m_history_7 = ((int)0);
		m_delay_8.reset("m_delay_8", ((int)2000));
		m_history_9 = ((int)0);
		m_delay_10.reset("m_delay_10", ((int)2000));
		m_history_11 = ((int)0);
		m_delay_12.reset("m_delay_12", ((int)2000));
		m_history_13 = ((int)0);
		m_delay_14.reset("m_delay_14", ((int)2000));
		m_history_15 = ((int)0);
		m_delay_16.reset("m_delay_16", ((int)2000));
		m_history_17 = ((int)0);
		m_delay_18.reset("m_delay_18", ((int)2000));
		m_history_19 = ((int)0);
		m_delay_20.reset("m_delay_20", ((int)2000));
		m_history_21 = ((int)0);
		m_delay_22.reset("m_delay_22", ((int)2000));
		m_history_23 = ((int)0);
		m_delay_24.reset("m_delay_24", ((int)2000));
		m_delay_25.reset("m_delay_25", ((int)2000));
		m_delay_26.reset("m_delay_26", ((int)2000));
		m_delay_27.reset("m_delay_27", ((int)2000));
		m_delay_28.reset("m_delay_28", ((int)2000));
		m_delay_29.reset("m_delay_29", ((int)2000));
		m_delay_30.reset("m_delay_30", ((int)2000));
		m_delay_31.reset("m_delay_31", ((int)2000));
		__m_sah_32.reset(0);
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
		t_sample sqrt_3688 = sqrt(m_knob1_wetdry_5);
		t_sample rsub_3692 = (((int)1) - m_knob1_wetdry_5);
		t_sample sqrt_3691 = sqrt(rsub_3692);
		t_sample mul_2398 = (m_knob5_fb_3 * ((t_sample)0.5));
		t_sample mul_10655 = (m_knob5_fb_3 * ((t_sample)0.5));
		t_sample add_6279 = (((int)225) + m_knob6_spread_1);
		t_sample add_10649 = (((int)228) + m_knob6_spread_1);
		t_sample add_6176 = (((int)341) + m_knob6_spread_1);
		t_sample add_10651 = (((int)338) + m_knob6_spread_1);
		t_sample add_6073 = (((int)441) + m_knob6_spread_1);
		t_sample add_10653 = (((int)444) + m_knob6_spread_1);
		t_sample add_5970 = (((int)556) + m_knob6_spread_1);
		t_sample add_10647 = (((int)553) + m_knob6_spread_1);
		t_sample add_4948 = (((int)1557) + m_knob6_spread_1);
		t_sample rsub_2335 = (((int)1) - m_knob3_damp_2);
		t_sample add_4949 = (((int)1617) + m_knob6_spread_1);
		t_sample rsub_13877 = (((int)1) - m_knob3_damp_2);
		t_sample add_4947 = (((int)1491) + m_knob6_spread_1);
		t_sample rsub_13888 = (((int)1) - m_knob3_damp_2);
		t_sample add_4946 = (((int)1422) + m_knob6_spread_1);
		t_sample rsub_13900 = (((int)1) - m_knob3_damp_2);
		t_sample add_4945 = (((int)1356) + m_knob6_spread_1);
		t_sample rsub_13912 = (((int)1) - m_knob3_damp_2);
		t_sample add_4944 = (((int)1277) + m_knob6_spread_1);
		t_sample rsub_13924 = (((int)1) - m_knob3_damp_2);
		t_sample add_4943 = (((int)1188) + m_knob6_spread_1);
		t_sample rsub_13936 = (((int)1) - m_knob3_damp_2);
		t_sample add_4942 = (((int)1116) + m_knob6_spread_1);
		t_sample rsub_13948 = (((int)1) - m_knob3_damp_2);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample sah_1259 = __m_sah_32(m_history_7, m_sw_4, ((int)0));
			t_sample gen_1261 = sah_1259;
			t_sample rsub_1257 = (((int)1) - sah_1259);
			t_sample history_1258_next_1260 = fixdenorm(rsub_1257);
			t_sample out3 = gen_1261;
			t_sample add_1264 = (gen_1261 + ((int)1));
			t_sample choice_33 = int(add_1264);
			t_sample gate_1262 = (((choice_33 >= 1) && (choice_33 < 2)) ? in1 : 0);
			t_sample gate_1263 = ((choice_33 >= 2) ? in1 : 0);
			t_sample mul_3690 = (gate_1263 * sqrt_3691);
			t_sample mul_2400 = (gate_1263 * ((t_sample)0.015));
			t_sample tap_2342 = m_delay_8.read_linear(add_4948);
			t_sample gen_2380 = tap_2342;
			t_sample mul_2340 = (tap_2342 * m_knob3_damp_2);
			t_sample mul_2338 = (m_history_9 * rsub_2335);
			t_sample add_2339 = (mul_2340 + mul_2338);
			t_sample mul_2336 = (add_2339 * m_knob4_fb_6);
			t_sample add_2343 = (mul_2400 + mul_2336);
			t_sample history_2337_next_2344 = fixdenorm(add_2339);
			t_sample tap_13876 = m_delay_10.read_linear(add_4949);
			t_sample gen_2399 = tap_13876;
			t_sample mul_13875 = (tap_13876 * m_knob3_damp_2);
			t_sample mul_13874 = (m_history_11 * rsub_13877);
			t_sample add_13873 = (mul_13875 + mul_13874);
			t_sample mul_13872 = (add_13873 * m_knob4_fb_6);
			t_sample add_13871 = (mul_2400 + mul_13872);
			t_sample history_2337_next_13870 = fixdenorm(add_13873);
			t_sample tap_13886 = m_delay_12.read_linear(add_4947);
			t_sample gen_2379 = tap_13886;
			t_sample mul_13890 = (tap_13886 * m_knob3_damp_2);
			t_sample mul_13889 = (m_history_13 * rsub_13888);
			t_sample add_13882 = (mul_13890 + mul_13889);
			t_sample mul_13883 = (add_13882 * m_knob4_fb_6);
			t_sample add_13884 = (mul_2400 + mul_13883);
			t_sample history_2337_next_13885 = fixdenorm(add_13882);
			t_sample tap_13898 = m_delay_14.read_linear(add_4946);
			t_sample gen_2378 = tap_13898;
			t_sample mul_13902 = (tap_13898 * m_knob3_damp_2);
			t_sample mul_13901 = (m_history_15 * rsub_13900);
			t_sample add_13894 = (mul_13902 + mul_13901);
			t_sample mul_13895 = (add_13894 * m_knob4_fb_6);
			t_sample add_13896 = (mul_2400 + mul_13895);
			t_sample history_2337_next_13897 = fixdenorm(add_13894);
			t_sample tap_13910 = m_delay_16.read_linear(add_4945);
			t_sample gen_2377 = tap_13910;
			t_sample mul_13914 = (tap_13910 * m_knob3_damp_2);
			t_sample mul_13913 = (m_history_17 * rsub_13912);
			t_sample add_13906 = (mul_13914 + mul_13913);
			t_sample mul_13907 = (add_13906 * m_knob4_fb_6);
			t_sample add_13908 = (mul_2400 + mul_13907);
			t_sample history_2337_next_13909 = fixdenorm(add_13906);
			t_sample tap_13923 = m_delay_18.read_linear(add_4944);
			t_sample gen_2376 = tap_13923;
			t_sample mul_13926 = (tap_13923 * m_knob3_damp_2);
			t_sample mul_13925 = (m_history_19 * rsub_13924);
			t_sample add_13918 = (mul_13926 + mul_13925);
			t_sample mul_13919 = (add_13918 * m_knob4_fb_6);
			t_sample add_13920 = (mul_2400 + mul_13919);
			t_sample history_2337_next_13921 = fixdenorm(add_13918);
			t_sample tap_13934 = m_delay_20.read_linear(add_4943);
			t_sample gen_2375 = tap_13934;
			t_sample mul_13938 = (tap_13934 * m_knob3_damp_2);
			t_sample mul_13937 = (m_history_21 * rsub_13936);
			t_sample add_13930 = (mul_13938 + mul_13937);
			t_sample mul_13931 = (add_13930 * m_knob4_fb_6);
			t_sample add_13932 = (mul_2400 + mul_13931);
			t_sample history_2337_next_13933 = fixdenorm(add_13930);
			t_sample tap_13949 = m_delay_22.read_linear(add_4942);
			t_sample gen_13865 = tap_13949;
			t_sample mul_13950 = (tap_13949 * m_knob3_damp_2);
			t_sample mul_13943 = (m_history_23 * rsub_13948);
			t_sample add_13944 = (mul_13950 + mul_13943);
			t_sample mul_13942 = (add_13944 * m_knob4_fb_6);
			t_sample add_13945 = (mul_2400 + mul_13942);
			t_sample history_2337_next_13946 = fixdenorm(add_13944);
			t_sample pass_11028 = (((((((gen_13865 + gen_2375) + gen_2376) + gen_2377) + gen_2378) + gen_2379) + gen_2399) + gen_2380);
			t_sample tap_2333 = m_delay_24.read_linear(add_5970);
			t_sample sub_2329 = (pass_11028 - tap_2333);
			t_sample mul_2331 = (tap_2333 * mul_2398);
			t_sample add_2330 = (pass_11028 + mul_2331);
			t_sample tap_13953 = m_delay_25.read_linear(add_6073);
			t_sample sub_13956 = (sub_2329 - tap_13953);
			t_sample mul_13955 = (tap_13953 * mul_2398);
			t_sample add_13954 = (sub_2329 + mul_13955);
			t_sample tap_13959 = m_delay_26.read_linear(add_6176);
			t_sample sub_13962 = (sub_13956 - tap_13959);
			t_sample mul_13961 = (tap_13959 * mul_2398);
			t_sample add_13960 = (sub_13956 + mul_13961);
			t_sample tap_13965 = m_delay_27.read_linear(add_6279);
			t_sample sub_13968 = (sub_13962 - tap_13965);
			t_sample mul_13967 = (tap_13965 * mul_2398);
			t_sample add_13966 = (sub_13962 + mul_13967);
			t_sample mul_3693 = (sub_13968 * sqrt_3688);
			t_sample add_3689 = (mul_3690 + mul_3693);
			t_sample out1 = (add_3689 + gate_1262);
			t_sample tap_13971 = m_delay_28.read_linear(add_10647);
			t_sample sub_13974 = (pass_11028 - tap_13971);
			t_sample mul_13973 = (tap_13971 * mul_10655);
			t_sample add_13972 = (pass_11028 + mul_13973);
			t_sample tap_13977 = m_delay_29.read_linear(add_10653);
			t_sample sub_13980 = (sub_13974 - tap_13977);
			t_sample mul_13979 = (tap_13977 * mul_10655);
			t_sample add_13978 = (sub_13974 + mul_13979);
			t_sample tap_13983 = m_delay_30.read_linear(add_10651);
			t_sample sub_13984 = (sub_13980 - tap_13983);
			t_sample mul_13986 = (tap_13983 * mul_10655);
			t_sample add_13985 = (sub_13980 + mul_13986);
			t_sample tap_13989 = m_delay_31.read_linear(add_10649);
			t_sample sub_13992 = (sub_13984 - tap_13989);
			t_sample mul_13991 = (tap_13989 * mul_10655);
			t_sample add_13990 = (sub_13984 + mul_13991);
			t_sample mul_12021 = (sub_13992 * sqrt_3688);
			t_sample add_12394 = (mul_3690 + mul_12021);
			t_sample out2 = (add_12394 + gate_1262);
			m_history_7 = history_1258_next_1260;
			m_delay_31.write(add_13990);
			m_delay_30.write(add_13985);
			m_delay_29.write(add_13978);
			m_delay_28.write(add_13972);
			m_delay_27.write(add_13966);
			m_delay_26.write(add_13960);
			m_delay_25.write(add_13954);
			m_delay_24.write(add_2330);
			m_history_23 = history_2337_next_13946;
			m_delay_22.write(add_13945);
			m_history_21 = history_2337_next_13933;
			m_delay_20.write(add_13932);
			m_history_19 = history_2337_next_13921;
			m_delay_18.write(add_13920);
			m_history_17 = history_2337_next_13909;
			m_delay_16.write(add_13908);
			m_history_15 = history_2337_next_13897;
			m_delay_14.write(add_13896);
			m_history_13 = history_2337_next_13885;
			m_delay_12.write(add_13884);
			m_history_11 = history_2337_next_13870;
			m_delay_10.write(add_13871);
			m_history_9 = history_2337_next_2344;
			m_delay_8.write(add_2343);
			m_delay_8.step();
			m_delay_10.step();
			m_delay_12.step();
			m_delay_14.step();
			m_delay_16.step();
			m_delay_18.step();
			m_delay_20.step();
			m_delay_22.step();
			m_delay_24.step();
			m_delay_25.step();
			m_delay_26.step();
			m_delay_27.step();
			m_delay_28.step();
			m_delay_29.step();
			m_delay_30.step();
			m_delay_31.step();
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
	inline void set_knob6_spread(t_param _value) {
		m_knob6_spread_1 = (_value < 0 ? 0 : (_value > 400 ? 400 : _value));
	};
	inline void set_knob3_damp(t_param _value) {
		m_knob3_damp_2 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_fb2(t_param _value) {
		m_knob5_fb_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1_wetdry(t_param _value) {
		m_knob1_wetdry_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_fb1(t_param _value) {
		m_knob4_fb_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: self->set_knob1_wetdry(value); break;
		case 1: self->set_knob3_damp(value); break;
		case 2: self->set_knob4_fb1(value); break;
		case 3: self->set_knob5_fb2(value); break;
		case 4: self->set_knob6_spread(value); break;
		case 5: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_wetdry_5; break;
		case 1: *value = self->m_knob3_damp_2; break;
		case 2: *value = self->m_knob4_fb_6; break;
		case 3: *value = self->m_knob5_fb_3; break;
		case 4: *value = self->m_knob6_spread_1; break;
		case 5: *value = self->m_sw_4; break;
		
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
	// initialize parameter 0 ("m_knob1_wetdry_5")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_wetdry";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_wetdry_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob3_damp_2")
	pi = self->__commonstate.params + 1;
	pi->name = "knob3_damp";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_damp_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob4_fb_6")
	pi = self->__commonstate.params + 2;
	pi->name = "knob4_fb1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_fb_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob5_fb_3")
	pi = self->__commonstate.params + 3;
	pi->name = "knob5_fb2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_fb_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob6_spread_1")
	pi = self->__commonstate.params + 4;
	pi->name = "knob6_spread";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob6_spread_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 400;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_sw_4")
	pi = self->__commonstate.params + 5;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_4;
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


} // Reverb::
