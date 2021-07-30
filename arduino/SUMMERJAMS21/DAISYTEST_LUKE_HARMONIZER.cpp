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
	Change __m_change_16;
	DCBlock __m_dcblock_19;
	DCBlock __m_dcblock_18;
	Delay m_delay_1;
	Phasor __m_phasor_17;
	Sah __m_sah_13;
	int __exception;
	int vectorsize;
	t_sample m_history_2;
	t_sample m_history_5;
	t_sample m_knob5_delay_12;
	t_sample samplerate;
	t_sample samples_to_seconds;
	t_sample m_history_4;
	t_sample m_knob2_wet_11;
	t_sample m_knob6_feedback_9;
	t_sample m_sw_6;
	t_sample m_knob1_windowsize_10;
	t_sample m_knob4_fine_7;
	t_sample m_history_3;
	t_sample m_knob3_coarse_8;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_delay_1.reset("m_delay_1", ((int)48000));
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_sw_6 = ((int)0);
		m_knob4_fine_7 = ((int)0);
		m_knob3_coarse_8 = ((int)0);
		m_knob6_feedback_9 = ((int)0);
		m_knob1_windowsize_10 = ((int)0);
		m_knob2_wet_11 = 1;
		m_knob5_delay_12 = ((int)0);
		__m_sah_13.reset(0);
		__m_change_16.reset(0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_17.reset(0);
		__m_dcblock_18.reset();
		__m_dcblock_19.reset();
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
		t_sample rdiv_294 = safediv((-3.795), m_knob1_windowsize_10);
		t_sample rsub_293 = (((int)1) - m_knob2_wet_11);
		t_sample sqrt_291 = sqrt(rsub_293);
		t_sample round_303 = round(m_knob3_coarse_8);
		t_sample mul_302 = (round_303 * ((int)100));
		t_sample add_301 = (mul_302 + m_knob4_fine_7);
		int min_15 = (-2400);
		t_sample clamp_300 = ((add_301 <= min_15) ? min_15 : ((add_301 >= ((int)2400)) ? ((int)2400) : add_301));
		int eq_275 = (clamp_300 == ((int)0));
		t_sample add_299 = (clamp_300 + ((int)6000));
		t_sample mul_298 = (add_299 * ((t_sample)0.01));
		t_sample mtof_297 = mtof(mul_298, ((int)440));
		t_sample sub_296 = (mtof_297 - ((t_sample)261.625977));
		t_sample mul_295 = (sub_296 * rdiv_294);
		samples_to_seconds = (1 / samplerate);
		t_sample sqrt_290 = sqrt(m_knob2_wet_11);
		t_sample mstosamps_281 = (m_knob1_windowsize_10 * (samplerate * 0.001));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out4 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample sah_179 = __m_sah_13(m_history_5, m_sw_6, ((int)0));
			t_sample gen_260 = sah_179;
			t_sample rsub_177 = (((int)1) - sah_179);
			t_sample history_178_next_180 = fixdenorm(rsub_177);
			t_sample out3 = gen_260;
			t_sample add_261 = (gen_260 + ((int)1));
			t_sample choice_14 = int(add_261);
			t_sample gate_257 = (((choice_14 >= 1) && (choice_14 < 2)) ? in1 : 0);
			t_sample gate_258 = ((choice_14 >= 2) ? in1 : 0);
			t_sample mul_292 = (gate_258 * sqrt_291);
			int change_274 = __m_change_16(eq_275);
			if ((change_274 != 0)) {
				__m_phasor_17.phase = 0;
				
			};
			t_sample phasor_278 = __m_phasor_17(mul_295, samples_to_seconds);
			t_sample expr_306 = ((((t_sample)1.1) * sin(((phasor_278 * ((t_sample)0.5)) * ((t_sample)6.2831852)))) - ((t_sample)0.1));
			t_sample clamp_264 = ((expr_306 <= ((int)0)) ? ((int)0) : ((expr_306 >= ((int)1)) ? ((int)1) : expr_306));
			t_sample add_277 = (phasor_278 + ((t_sample)0.5));
			t_sample mod_276 = safemod(add_277, ((int)1));
			t_sample expr_305 = ((((t_sample)1.1) * sin(((mod_276 * ((t_sample)0.5)) * ((t_sample)6.2831852)))) - ((t_sample)0.1));
			t_sample clamp_262 = ((expr_305 <= ((int)0)) ? ((int)0) : ((expr_305 >= ((int)1)) ? ((int)1) : expr_305));
			t_sample mul_289 = (gate_258 * sqrt_290);
			t_sample mul_279 = (phasor_278 * mstosamps_281);
			t_sample mul_280 = (mod_276 * mstosamps_281);
			t_sample mix_316 = (m_history_4 + (((t_sample)0.003926980723806) * (m_knob5_delay_12 - m_history_4)));
			t_sample mix_248 = mix_316;
			t_sample mix_317 = (m_history_3 + (((t_sample)0.003926980723806) * (mix_248 - m_history_3)));
			t_sample mix_246 = mix_317;
			t_sample mix_318 = (m_history_2 + (((t_sample)0.003926980723806) * (mix_246 - m_history_2)));
			t_sample mix_244 = mix_318;
			t_sample gen_256 = mix_244;
			t_sample history_250_next_253 = fixdenorm(mix_248);
			t_sample history_247_next_254 = fixdenorm(mix_246);
			t_sample history_245_next_255 = fixdenorm(mix_244);
			t_sample mstosamps_270 = (gen_256 * (samplerate * 0.001));
			t_sample add_283 = (mul_279 + mstosamps_270);
			t_sample add_282 = (mul_280 + mstosamps_270);
			t_sample tap_287 = m_delay_1.read_step(add_283);
			t_sample tap_288 = m_delay_1.read_step(add_282);
			t_sample mul_273 = (tap_287 * clamp_264);
			t_sample dcblock_267 = __m_dcblock_18(mul_273);
			t_sample mul_272 = (tap_288 * clamp_262);
			t_sample dcblock_266 = __m_dcblock_19(mul_272);
			t_sample add_271 = (dcblock_267 + dcblock_266);
			t_sample add_304 = (mul_292 + add_271);
			t_sample out1 = (gate_257 + add_304);
			t_sample out2 = (gate_257 + add_304);
			t_sample mul_284 = (add_271 * m_knob6_feedback_9);
			t_sample add_285 = (mul_289 + mul_284);
			m_history_5 = history_178_next_180;
			m_history_4 = history_250_next_253;
			m_history_2 = history_245_next_255;
			m_history_3 = history_247_next_254;
			m_delay_1.write(add_285);
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
	inline void set_sw1(t_param _value) {
		m_sw_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_fine(t_param _value) {
		m_knob4_fine_7 = (_value < -50 ? -50 : (_value > 50 ? 50 : _value));
	};
	inline void set_knob3_coarse(t_param _value) {
		m_knob3_coarse_8 = (_value < -24 ? -24 : (_value > 24 ? 24 : _value));
	};
	inline void set_knob6_feedback(t_param _value) {
		m_knob6_feedback_9 = (_value < 0 ? 0 : (_value > 0.99 ? 0.99 : _value));
	};
	inline void set_knob1_windowsize(t_param _value) {
		m_knob1_windowsize_10 = (_value < 120 ? 120 : (_value > 240 ? 240 : _value));
	};
	inline void set_knob2_wet(t_param _value) {
		m_knob2_wet_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_delay(t_param _value) {
		m_knob5_delay_12 = (_value < 0 ? 0 : (_value > 1000 ? 1000 : _value));
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
int num_params() { return 7; }

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
		case 0: self->set_knob1_windowsize(value); break;
		case 1: self->set_knob2_wet(value); break;
		case 2: self->set_knob3_coarse(value); break;
		case 3: self->set_knob4_fine(value); break;
		case 4: self->set_knob5_delay(value); break;
		case 5: self->set_knob6_feedback(value); break;
		case 6: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_windowsize_10; break;
		case 1: *value = self->m_knob2_wet_11; break;
		case 2: *value = self->m_knob3_coarse_8; break;
		case 3: *value = self->m_knob4_fine_7; break;
		case 4: *value = self->m_knob5_delay_12; break;
		case 5: *value = self->m_knob6_feedback_9; break;
		case 6: *value = self->m_sw_6; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(7 * sizeof(ParamInfo));
	self->__commonstate.numparams = 7;
	// initialize parameter 0 ("m_knob1_windowsize_10")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_windowsize";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_windowsize_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 120;
	pi->outputmax = 240;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_wet_11")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_wet";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_wet_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_coarse_8")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_coarse";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_coarse_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -24;
	pi->outputmax = 24;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_fine_7")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_fine";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_fine_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -50;
	pi->outputmax = 50;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob5_delay_12")
	pi = self->__commonstate.params + 4;
	pi->name = "knob5_delay";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_delay_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_knob6_feedback_9")
	pi = self->__commonstate.params + 5;
	pi->name = "knob6_feedback";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob6_feedback_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_sw_6")
	pi = self->__commonstate.params + 6;
	pi->name = "sw1";
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


} // DAISYTEST_LUKE_HARMONIZER::
