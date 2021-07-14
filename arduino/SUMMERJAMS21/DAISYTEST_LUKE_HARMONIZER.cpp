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
	Sah __m_sah_15;
	Sah __m_sah_14;
	int __exception;
	int vectorsize;
	t_sample m_history_8;
	t_sample __m_slide_11;
	t_sample m_knob4_smooth_9;
	t_sample m_history_7;
	t_sample m_knob3_sub_10;
	t_sample m_history_6;
	t_sample m_history_4;
	t_sample samplerate;
	t_sample m_history_5;
	t_sample m_history_1;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample __m_slide_16;
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
		m_knob4_smooth_9 = ((int)0);
		m_knob3_sub_10 = ((int)0);
		__m_slide_11 = 0;
		__m_sah_14.reset(0);
		__m_sah_15.reset(1);
		__m_slide_16 = 0;
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
		t_sample iup_12 = (1 / maximum(1, abs(((int)1))));
		t_sample idown_13 = (1 / maximum(1, abs(((int)200))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out5 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample mul_82 = (m_history_1 * (-1));
			t_sample mix_400 = (m_history_8 + (((t_sample)0.003926980723806) * (m_knob4_smooth_9 - m_history_8)));
			t_sample mix_198 = mix_400;
			t_sample mix_401 = (m_history_7 + (((t_sample)0.003926980723806) * (mix_198 - m_history_7)));
			t_sample mix_196 = mix_401;
			t_sample mix_402 = (m_history_6 + (((t_sample)0.003926980723806) * (mix_196 - m_history_6)));
			t_sample mix_194 = mix_402;
			t_sample gen_237 = mix_194;
			t_sample history_200_next_203 = fixdenorm(mix_198);
			t_sample history_197_next_204 = fixdenorm(mix_196);
			t_sample history_195_next_205 = fixdenorm(mix_194);
			t_sample add_87 = (m_history_2 + ((int)1));
			int gt_90 = (in1 > ((int)0));
			t_sample abs_94 = fabs(in1);
			__m_slide_11 = fixdenorm((__m_slide_11 + (((abs_94 > __m_slide_11) ? iup_12 : idown_13) * (abs_94 - __m_slide_11))));
			t_sample slide_364 = __m_slide_11;
			t_sample mix_403 = (m_history_5 + (((t_sample)0.003926980723806) * (m_knob3_sub_10 - m_history_5)));
			t_sample mix_372 = mix_403;
			t_sample mix_404 = (m_history_4 + (((t_sample)0.003926980723806) * (mix_372 - m_history_4)));
			t_sample mix_373 = mix_404;
			t_sample mix_405 = (m_history_3 + (((t_sample)0.003926980723806) * (mix_373 - m_history_3)));
			t_sample mix_374 = mix_405;
			t_sample gen_206 = mix_374;
			t_sample history_200_next_367 = fixdenorm(mix_372);
			t_sample history_197_next_365 = fixdenorm(mix_373);
			t_sample history_195_next_370 = fixdenorm(mix_374);
			t_sample round_85 = round(gen_206);
			t_sample mod_86 = safemod(add_87, round_85);
			t_sample sah_89 = __m_sah_14(mod_86, gt_90, ((int)0));
			int eq_84 = (mod_86 == ((int)0));
			t_sample sah_83 = __m_sah_15(mul_82, eq_84, ((int)0));
			t_sample iup_17 = (1 / maximum(1, abs(gen_237)));
			t_sample idown_18 = (1 / maximum(1, abs(gen_237)));
			__m_slide_16 = fixdenorm((__m_slide_16 + (((sah_83 > __m_slide_16) ? iup_17 : idown_18) * (sah_83 - __m_slide_16))));
			t_sample slide_80 = __m_slide_16;
			t_sample mul_104 = (slide_364 * slide_80);
			t_sample out1 = mul_104;
			t_sample history_88_next_380 = fixdenorm(sah_89);
			t_sample history_81_next_381 = fixdenorm(sah_83);
			m_history_8 = history_200_next_203;
			m_history_6 = history_195_next_205;
			m_history_7 = history_197_next_204;
			m_history_5 = history_200_next_367;
			m_history_3 = history_195_next_370;
			m_history_4 = history_197_next_365;
			m_history_2 = history_88_next_380;
			m_history_1 = history_81_next_381;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = 0;
			(*(__out3++)) = 0;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			
		};
		return __exception;
		
	};
	inline void set_knob4_smooth(t_param _value) {
		m_knob4_smooth_9 = (_value < 1 ? 1 : (_value > 50 ? 50 : _value));
	};
	inline void set_knob3_sub(t_param _value) {
		m_knob3_sub_10 = (_value < 2 ? 2 : (_value > 20 ? 20 : _value));
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
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "led2", "led3", "led4" };

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
		case 0: self->set_knob3_sub(value); break;
		case 1: self->set_knob4_smooth(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob3_sub_10; break;
		case 1: *value = self->m_knob4_smooth_9; break;
		
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
	// initialize parameter 0 ("m_knob3_sub_10")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_sub";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_sub_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 2;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_smooth_9")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_smooth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_smooth_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 50;
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
