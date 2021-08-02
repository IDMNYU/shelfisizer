#include "lukephaser_field_stereo.h"

namespace lukephaser_field_stereo {

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
	Sah __m_sah_23;
	int vectorsize;
	int __exception;
	t_sample m_history_1;
	t_sample m_history_16;
	t_sample m_history_15;
	t_sample m_history_14;
	t_sample m_history_13;
	t_sample m_history_17;
	t_sample m_history_19;
	t_sample m_history_18;
	t_sample m_knob3_freq_21;
	t_sample m_history_20;
	t_sample samplerate;
	t_sample m_history_12;
	t_sample m_sw_22;
	t_sample m_history_4;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample m_history_11;
	t_sample m_history_5;
	t_sample m_history_7;
	t_sample m_history_6;
	t_sample m_history_9;
	t_sample m_history_8;
	t_sample m_history_10;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
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
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_history_20 = ((int)0);
		m_knob3_freq_21 = 60;
		m_sw_22 = ((int)0);
		__m_sah_23.reset(0);
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
		t_sample mtof_8369 = mtof(m_knob3_freq_21, ((int)440));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out6 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample sah_3366 = __m_sah_23(m_history_20, m_sw_22, ((int)0));
			t_sample gen_3368 = sah_3366;
			t_sample rsub_3364 = (((int)1) - sah_3366);
			t_sample history_3365_next_3367 = fixdenorm(rsub_3364);
			t_sample out3 = gen_3368;
			t_sample mix_8524 = (m_history_19 + (((t_sample)0.003926980723806) * (mtof_8369 - m_history_19)));
			t_sample mix_3230 = mix_8524;
			t_sample mix_8525 = (m_history_18 + (((t_sample)0.003926980723806) * (mix_3230 - m_history_18)));
			t_sample mix_3228 = mix_8525;
			t_sample mix_8526 = (m_history_17 + (((t_sample)0.003926980723806) * (mix_3228 - m_history_17)));
			t_sample mix_3226 = mix_8526;
			t_sample gen_3238 = mix_3226;
			t_sample history_3232_next_3235 = fixdenorm(mix_3230);
			t_sample history_3229_next_3236 = fixdenorm(mix_3228);
			t_sample history_3227_next_3237 = fixdenorm(mix_3226);
			t_sample frequency_in_radians = (((t_sample)6.2831853071796) * gen_3238);
			t_sample k = safediv(frequency_in_radians, tan(safediv((((t_sample)3.1415926535898) * gen_3238), samplerate)));
			t_sample temp = ((((((((int)4) * safepow(frequency_in_radians, ((int)2))) * safepow(k, ((int)2))) + ((((t_sample)2.8284271247462) * safepow(frequency_in_radians, ((int)3))) * k)) + safepow(k, ((int)4))) + ((((t_sample)2.8284271247462) * frequency_in_radians) * safepow(k, ((int)3)))) + safepow(frequency_in_radians, ((int)4)));
			t_sample a0 = safediv(safepow(frequency_in_radians, ((int)4)), temp);
			t_sample a1 = safediv((((int)4) * safepow(frequency_in_radians, ((int)4))), temp);
			t_sample a2 = safediv((((int)6) * safepow(frequency_in_radians, ((int)4))), temp);
			t_sample a0_high = safediv(safepow(k, ((int)4)), temp);
			t_sample a1_high = safediv((((int)-4) * safepow(k, ((int)4))), temp);
			t_sample a2_high = safediv((((int)6) * safepow(k, ((int)4))), temp);
			t_sample b1 = safediv(((((((int)4) * safepow(frequency_in_radians, ((int)4))) + ((((t_sample)5.6568542494924) * safepow(frequency_in_radians, ((int)3))) * k)) - (((int)4) * safepow(k, ((int)4)))) - ((((t_sample)5.6568542494924) * frequency_in_radians) * safepow(k, ((int)3)))), temp);
			t_sample b2 = safediv((((((int)6) * safepow(frequency_in_radians, ((int)4))) - ((((int)8) * safepow(frequency_in_radians, ((int)2))) * safepow(k, ((int)2)))) + (((int)6) * safepow(k, ((int)4)))), temp);
			t_sample b3 = safediv((((((((t_sample)-5.6568542494924) * safepow(frequency_in_radians, ((int)3))) * k) + (((int)4) * safepow(frequency_in_radians, ((int)4)))) + ((((t_sample)5.6568542494924) * frequency_in_radians) * safepow(k, ((int)3)))) - (((int)4) * safepow(k, ((int)4)))), temp);
			t_sample b4 = safediv(((((safepow(k, ((int)4)) - ((((t_sample)2.8284271247462) * safepow(frequency_in_radians, ((int)3))) * k)) + safepow(frequency_in_radians, ((int)4))) - ((((t_sample)2.8284271247462) * frequency_in_radians) * safepow(k, ((int)3)))) + ((((int)4) * safepow(frequency_in_radians, ((int)2))) * safepow(k, ((int)2)))), temp);
			t_sample expr_8500 = a0;
			t_sample expr_8501 = a1;
			t_sample expr_8502 = a2;
			t_sample expr_8503 = a1;
			t_sample expr_8504 = a0;
			t_sample expr_8505 = b1;
			t_sample expr_8506 = b2;
			t_sample expr_8507 = b3;
			t_sample expr_8508 = b4;
			t_sample expr_8509 = a0_high;
			t_sample expr_8510 = a1_high;
			t_sample expr_8511 = a2_high;
			t_sample expr_8512 = a1_high;
			t_sample expr_8513 = a0_high;
			t_sample expr_8514 = b1;
			t_sample expr_8515 = b2;
			t_sample expr_8516 = b3;
			t_sample expr_8517 = b4;
			t_sample add_3369 = (gen_3368 + ((int)1));
			t_sample choice_24 = int(add_3369);
			t_sample gate_3361 = (((choice_24 >= 1) && (choice_24 < 2)) ? in1 : 0);
			t_sample gate_3362 = ((choice_24 >= 2) ? in1 : 0);
			t_sample mul_3623 = (gate_3361 * expr_8509);
			t_sample mul_3622 = (m_history_10 * expr_8510);
			t_sample mul_3620 = (m_history_13 * expr_8511);
			t_sample mul_3618 = (m_history_15 * expr_8512);
			t_sample mul_3616 = (m_history_12 * expr_8513);
			t_sample mul_3607 = (m_history_14 * expr_8517);
			t_sample mul_3609 = (m_history_16 * expr_8516);
			t_sample mul_3611 = (m_history_11 * expr_8515);
			t_sample mul_3613 = (m_history_9 * expr_8514);
			t_sample sub_3615 = (((((mul_3616 + mul_3618) + mul_3620) + mul_3622) + mul_3623) - (((mul_3613 + mul_3611) + mul_3609) + mul_3607));
			t_sample gen_3634 = sub_3615;
			t_sample history_3610_next_3625 = fixdenorm(m_history_11);
			t_sample history_3619_next_3626 = fixdenorm(m_history_13);
			t_sample history_3608_next_3627 = fixdenorm(m_history_16);
			t_sample history_3621_next_3628 = fixdenorm(m_history_10);
			t_sample history_3617_next_3629 = fixdenorm(m_history_15);
			t_sample history_3612_next_3630 = fixdenorm(m_history_9);
			t_sample history_3624_next_3631 = fixdenorm(gate_3361);
			t_sample history_3614_next_3632 = fixdenorm(sub_3615);
			t_sample add_3373 = (gen_3634 + gate_3361);
			t_sample out2 = add_3373;
			t_sample mul_3588 = (m_history_5 * expr_8504);
			t_sample mul_3590 = (m_history_8 * expr_8503);
			t_sample mul_3592 = (m_history_6 * expr_8502);
			t_sample mul_3594 = (m_history_2 * expr_8501);
			t_sample mul_3595 = (gate_3361 * expr_8500);
			t_sample mul_3585 = (m_history_1 * expr_8505);
			t_sample mul_3583 = (m_history_4 * expr_8506);
			t_sample mul_3581 = (m_history_7 * expr_8507);
			t_sample mul_3579 = (m_history_3 * expr_8508);
			t_sample sub_3587 = (((((mul_3595 + mul_3594) + mul_3592) + mul_3590) + mul_3588) - (((mul_3579 + mul_3581) + mul_3583) + mul_3585));
			t_sample gen_3606 = sub_3587;
			t_sample history_3591_next_3597 = fixdenorm(m_history_6);
			t_sample history_3582_next_3598 = fixdenorm(m_history_4);
			t_sample history_3593_next_3599 = fixdenorm(m_history_2);
			t_sample history_3589_next_3600 = fixdenorm(m_history_8);
			t_sample history_3584_next_3601 = fixdenorm(m_history_1);
			t_sample history_3580_next_3602 = fixdenorm(m_history_7);
			t_sample history_3596_next_3603 = fixdenorm(gate_3361);
			t_sample history_3586_next_3604 = fixdenorm(sub_3587);
			t_sample add_3374 = (gen_3606 + gate_3361);
			t_sample out1 = add_3374;
			m_history_20 = history_3365_next_3367;
			m_history_19 = history_3232_next_3235;
			m_history_17 = history_3227_next_3237;
			m_history_18 = history_3229_next_3236;
			m_history_16 = history_3610_next_3625;
			m_history_9 = history_3614_next_3632;
			m_history_10 = history_3624_next_3631;
			m_history_11 = history_3612_next_3630;
			m_history_12 = history_3617_next_3629;
			m_history_13 = history_3621_next_3628;
			m_history_14 = history_3608_next_3627;
			m_history_15 = history_3619_next_3626;
			m_history_8 = history_3591_next_3597;
			m_history_1 = history_3586_next_3604;
			m_history_2 = history_3596_next_3603;
			m_history_3 = history_3580_next_3602;
			m_history_4 = history_3584_next_3601;
			m_history_5 = history_3589_next_3600;
			m_history_6 = history_3593_next_3599;
			m_history_7 = history_3582_next_3598;
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
	inline void set_knob3_freq(t_param _value) {
		m_knob3_freq_21 = (_value < 0 ? 0 : (_value > 127 ? 127 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
int num_params() { return 2; }

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
		case 0: self->set_knob3_freq(value); break;
		case 1: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob3_freq_21; break;
		case 1: *value = self->m_sw_22; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(2 * sizeof(ParamInfo));
	self->__commonstate.numparams = 2;
	// initialize parameter 0 ("m_knob3_freq_21")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_freq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_freq_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 127;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_sw_22")
	pi = self->__commonstate.params + 1;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_22;
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


} // lukephaser_field_stereo::
