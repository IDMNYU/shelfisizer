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
	Phasor __m_phasor_15;
	Sah __m_sah_10;
	SineCycle __m_cycle_16;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_3;
	t_sample __m_slide_12;
	t_sample samples_to_seconds;
	t_sample samplerate;
	t_sample m_history_2;
	t_sample m_history_9;
	t_sample m_knob3_depth_7;
	t_sample m_sw_4;
	t_sample m_knob4_rate_8;
	t_sample m_knob5_shape_5;
	t_sample m_history_1;
	t_sample m_sw_6;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_sw_4 = ((int)0);
		m_knob5_shape_5 = 1;
		m_sw_6 = ((int)0);
		m_knob3_depth_7 = 1;
		m_knob4_rate_8 = 0.1;
		m_history_9 = ((int)0);
		__m_sah_10.reset(0);
		__m_slide_12 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_15.reset(0);
		__m_cycle_16.reset(samplerate, 0);
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
		t_sample mstosamps_5909 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_5908 = (((int)100) * (samplerate * 0.001));
		t_sample iup_13 = (1 / maximum(1, abs(mstosamps_5909)));
		t_sample idown_14 = (1 / maximum(1, abs(mstosamps_5908)));
		samples_to_seconds = (1 / samplerate);
		int min_17 = (-1);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_5850 = __m_sah_10(m_history_9, m_sw_4, ((int)0));
			t_sample gen_5852 = sah_5850;
			t_sample rsub_5848 = (((int)1) - sah_5850);
			t_sample history_5849_next_5851 = fixdenorm(rsub_5848);
			t_sample out3 = gen_5852;
			t_sample out6 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample add_5853 = (gen_5852 + ((int)1));
			t_sample choice_11 = int(add_5853);
			t_sample gate_5845 = (((choice_11 >= 1) && (choice_11 < 2)) ? in1 : 0);
			t_sample gate_5846 = ((choice_11 >= 2) ? in1 : 0);
			t_sample switch_5912 = (m_sw_6 ? gate_5846 : ((int)1));
			t_sample abs_5914 = fabs(switch_5912);
			t_sample mul_5905 = (abs_5914 * ((int)100));
			__m_slide_12 = fixdenorm((__m_slide_12 + (((mul_5905 > __m_slide_12) ? iup_13 : idown_14) * (mul_5905 - __m_slide_12))));
			t_sample slide_5913 = __m_slide_12;
			t_sample clamp_5910 = ((slide_5913 <= ((int)0)) ? ((int)0) : ((slide_5913 >= ((int)1)) ? ((int)1) : slide_5913));
			t_sample mul_5841 = (m_knob3_depth_7 * clamp_5910);
			t_sample mix_5957 = (m_history_3 + (((t_sample)0.003926980723806) * (m_knob4_rate_8 - m_history_3)));
			t_sample mix_5824 = mix_5957;
			t_sample mix_5958 = (m_history_2 + (((t_sample)0.003926980723806) * (mix_5824 - m_history_2)));
			t_sample mix_5822 = mix_5958;
			t_sample mix_5959 = (m_history_1 + (((t_sample)0.003926980723806) * (mix_5822 - m_history_1)));
			t_sample mix_5820 = mix_5959;
			t_sample gen_5832 = mix_5820;
			t_sample history_5826_next_5829 = fixdenorm(mix_5824);
			t_sample history_5823_next_5830 = fixdenorm(mix_5822);
			t_sample history_5821_next_5831 = fixdenorm(mix_5820);
			t_sample rsub_5858 = (((int)1) - gen_5832);
			t_sample sqrt_5857 = sqrt(rsub_5858);
			t_sample rsub_5856 = (((int)1) - sqrt_5857);
			t_sample mul_5862 = (rsub_5856 * ((int)12));
			t_sample phasor_5861 = __m_phasor_15(mul_5862, samples_to_seconds);
			__m_cycle_16.phase(phasor_5861);
			t_sample cycle_5818 = __m_cycle_16(__sinedata);
			t_sample cycleindex_5819 = __m_cycle_16.phase();
			t_sample mul_5813 = (cycle_5818 * m_knob5_shape_5);
			t_sample clamp_5814 = ((mul_5813 <= min_17) ? min_17 : ((mul_5813 >= ((int)1)) ? ((int)1) : mul_5813));
			t_sample sub_5963 = (clamp_5814 - (-1));
			t_sample scale_5960 = ((safepow((sub_5963 * ((t_sample)0.5)), ((int)1)) * ((int)1)) + ((int)0));
			t_sample mul_5816 = (scale_5960 * mul_5841);
			t_sample rsub_5815 = (((int)1) - mul_5816);
			t_sample mul_5854 = (gate_5846 * rsub_5815);
			t_sample add_5859 = (mul_5854 + gate_5845);
			t_sample out2 = add_5859;
			t_sample mul_5855 = (gate_5846 * rsub_5815);
			t_sample add_5860 = (mul_5855 + gate_5845);
			t_sample out1 = add_5860;
			m_history_9 = history_5849_next_5851;
			m_history_3 = history_5826_next_5829;
			m_history_1 = history_5821_next_5831;
			m_history_2 = history_5823_next_5830;
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
	inline void set_sw1(t_param _value) {
		m_sw_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_shape(t_param _value) {
		m_knob5_shape_5 = (_value < 1 ? 1 : (_value > 10 ? 10 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_depth(t_param _value) {
		m_knob3_depth_7 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_rate(t_param _value) {
		m_knob4_rate_8 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
int num_params() { return 5; }

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
		case 2: self->set_knob5_shape(value); break;
		case 3: self->set_sw1(value); break;
		case 4: self->set_sw5(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob3_depth_7; break;
		case 1: *value = self->m_knob4_rate_8; break;
		case 2: *value = self->m_knob5_shape_5; break;
		case 3: *value = self->m_sw_4; break;
		case 4: *value = self->m_sw_6; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(5 * sizeof(ParamInfo));
	self->__commonstate.numparams = 5;
	// initialize parameter 0 ("m_knob3_depth_7")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_depth_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_rate_8")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_rate_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_shape_5")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_shape";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_shape_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_sw_4")
	pi = self->__commonstate.params + 3;
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
	// initialize parameter 4 ("m_sw_6")
	pi = self->__commonstate.params + 4;
	pi->name = "sw5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_6;
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
