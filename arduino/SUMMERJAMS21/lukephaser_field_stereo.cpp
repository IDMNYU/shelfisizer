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
		t_sample mtof_1 = mtof(m_knob3_freq_21, ((int)440));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample sah_92 = __m_sah_23(m_history_20, m_sw_22, ((int)0));
			t_sample gen_94 = sah_92;
			t_sample rsub_90 = (((int)1) - sah_92);
			t_sample history_91_next_93 = fixdenorm(rsub_90);
			t_sample out3 = gen_94;
			t_sample mix_212 = (m_history_19 + (((t_sample)0.0042742627044161) * (mtof_1 - m_history_19)));
			t_sample mix_78 = mix_212;
			t_sample mix_213 = (m_history_18 + (((t_sample)0.0042742627044161) * (mix_78 - m_history_18)));
			t_sample mix_76 = mix_213;
			t_sample mix_214 = (m_history_17 + (((t_sample)0.0042742627044161) * (mix_76 - m_history_17)));
			t_sample mix_74 = mix_214;
			t_sample gen_86 = mix_74;
			t_sample history_80_next_83 = fixdenorm(mix_78);
			t_sample history_77_next_84 = fixdenorm(mix_76);
			t_sample history_75_next_85 = fixdenorm(mix_74);
			t_sample frequency_in_radians = (((t_sample)6.2831853071796) * gen_86);
			t_sample k = safediv(frequency_in_radians, tan(safediv((((t_sample)3.1415926535898) * gen_86), samplerate)));
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
			t_sample expr_191 = a0;
			t_sample expr_192 = a1;
			t_sample expr_193 = a2;
			t_sample expr_194 = a1;
			t_sample expr_195 = a0;
			t_sample expr_196 = b1;
			t_sample expr_197 = b2;
			t_sample expr_198 = b3;
			t_sample expr_199 = b4;
			t_sample expr_200 = a0_high;
			t_sample expr_201 = a1_high;
			t_sample expr_202 = a2_high;
			t_sample expr_203 = a1_high;
			t_sample expr_204 = a0_high;
			t_sample expr_205 = b1;
			t_sample expr_206 = b2;
			t_sample expr_207 = b3;
			t_sample expr_208 = b4;
			t_sample add_95 = (gen_94 + ((int)1));
			t_sample choice_24 = int(add_95);
			t_sample gate_87 = (((choice_24 >= 1) && (choice_24 < 2)) ? in1 : 0);
			t_sample gate_88 = ((choice_24 >= 2) ? in1 : 0);
			t_sample mul_63 = (gate_87 * expr_191);
			t_sample mul_62 = (m_history_10 * expr_192);
			t_sample mul_60 = (m_history_14 * expr_193);
			t_sample mul_58 = (m_history_11 * expr_194);
			t_sample mul_56 = (m_history_13 * expr_195);
			t_sample mul_47 = (m_history_16 * expr_199);
			t_sample mul_49 = (m_history_15 * expr_198);
			t_sample mul_51 = (m_history_12 * expr_197);
			t_sample mul_53 = (m_history_9 * expr_196);
			t_sample sub_55 = (((((mul_56 + mul_58) + mul_60) + mul_62) + mul_63) - (((mul_53 + mul_51) + mul_49) + mul_47));
			t_sample gen_73 = sub_55;
			t_sample history_48_next_65 = fixdenorm(m_history_15);
			t_sample history_50_next_66 = fixdenorm(m_history_12);
			t_sample history_61_next_67 = fixdenorm(m_history_10);
			t_sample history_57_next_68 = fixdenorm(m_history_11);
			t_sample history_52_next_69 = fixdenorm(m_history_9);
			t_sample history_59_next_70 = fixdenorm(m_history_14);
			t_sample history_64_next_71 = fixdenorm(gate_87);
			t_sample history_54_next_72 = fixdenorm(sub_55);
			t_sample add_97 = (gen_73 + gate_87);
			t_sample out1 = add_97;
			t_sample mul_36 = (gate_87 * expr_200);
			t_sample mul_35 = (m_history_2 * expr_201);
			t_sample mul_33 = (m_history_8 * expr_202);
			t_sample mul_31 = (m_history_3 * expr_203);
			t_sample mul_29 = (m_history_5 * expr_204);
			t_sample mul_20 = (m_history_4 * expr_208);
			t_sample mul_22 = (m_history_7 * expr_207);
			t_sample mul_24 = (m_history_6 * expr_206);
			t_sample mul_26 = (m_history_1 * expr_205);
			t_sample sub_28 = (((((mul_29 + mul_31) + mul_33) + mul_35) + mul_36) - (((mul_26 + mul_24) + mul_22) + mul_20));
			t_sample gen_46 = sub_28;
			t_sample history_34_next_38 = fixdenorm(m_history_2);
			t_sample history_23_next_39 = fixdenorm(m_history_6);
			t_sample history_25_next_40 = fixdenorm(m_history_1);
			t_sample history_30_next_41 = fixdenorm(m_history_3);
			t_sample history_21_next_42 = fixdenorm(m_history_7);
			t_sample history_32_next_43 = fixdenorm(m_history_8);
			t_sample history_37_next_44 = fixdenorm(gate_87);
			t_sample history_27_next_45 = fixdenorm(sub_28);
			t_sample add_96 = (gen_46 + gate_87);
			t_sample out2 = add_96;
			m_history_20 = history_91_next_93;
			m_history_19 = history_80_next_83;
			m_history_17 = history_75_next_85;
			m_history_18 = history_77_next_84;
			m_history_16 = history_48_next_65;
			m_history_9 = history_54_next_72;
			m_history_10 = history_64_next_71;
			m_history_11 = history_59_next_70;
			m_history_12 = history_52_next_69;
			m_history_13 = history_57_next_68;
			m_history_14 = history_61_next_67;
			m_history_15 = history_50_next_66;
			m_history_8 = history_34_next_38;
			m_history_1 = history_27_next_45;
			m_history_2 = history_37_next_44;
			m_history_3 = history_32_next_43;
			m_history_4 = history_21_next_42;
			m_history_5 = history_30_next_41;
			m_history_6 = history_25_next_40;
			m_history_7 = history_23_next_39;
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
