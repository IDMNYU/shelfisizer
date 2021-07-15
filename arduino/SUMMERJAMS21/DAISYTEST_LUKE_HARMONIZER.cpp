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
	Sah __m_sah_10;
	int vectorsize;
	int __exception;
	t_sample m_knob5_xover_1;
	t_sample m_sw_6;
	t_sample m_history_7;
	t_sample m_d_8;
	t_sample samplerate;
	t_sample m_knob3_threshold_5;
	t_sample m_knob1_input_3;
	t_sample m_d_9;
	t_sample m_knob2_output_2;
	t_sample m_knob4_ratio_4;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_knob5_xover_1 = ((int)0);
		m_knob2_output_2 = ((int)0);
		m_knob1_input_3 = ((int)0);
		m_knob4_ratio_4 = ((int)0);
		m_knob3_threshold_5 = ((int)0);
		m_sw_6 = ((int)0);
		m_history_7 = ((int)0);
		m_d_8 = ((int)0);
		m_d_9 = ((int)0);
		__m_sah_10.reset(0);
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
		t_sample mtof_284 = mtof(m_knob5_xover_1, ((int)440));
		t_sample dbtoa_314 = dbtoa(m_knob2_output_2);
		t_sample dbtoa_316 = dbtoa(m_knob1_input_3);
		t_sample freq = mtof_284;
		t_sample f1 = sin(safediv((((t_sample)6.2831853071796) * freq), samplerate));
		t_sample rdiv_293 = safediv(((int)1), m_knob4_ratio_4);
		t_sample rsub_292 = (((int)1) - rdiv_293);
		t_sample rdiv_276 = safediv(((int)1), m_knob4_ratio_4);
		t_sample rsub_275 = (((int)1) - rdiv_276);
		t_sample rdiv_260 = safediv(((int)1), m_knob4_ratio_4);
		t_sample rsub_259 = (((int)1) - rdiv_260);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out6 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample sah_308 = __m_sah_10(m_history_7, m_sw_6, ((int)0));
			t_sample gen_310 = sah_308;
			t_sample rsub_306 = (((int)1) - sah_308);
			t_sample history_307_next_309 = fixdenorm(rsub_306);
			t_sample out3 = gen_310;
			t_sample add_313 = (gen_310 + ((int)1));
			t_sample choice_11 = int(add_313);
			t_sample gate_311 = (((choice_11 >= 1) && (choice_11 < 2)) ? in1 : 0);
			t_sample gate_312 = ((choice_11 >= 2) ? in1 : 0);
			t_sample mul_317 = (gate_312 * dbtoa_316);
			t_sample L = (m_d_9 + (f1 * m_d_8));
			t_sample H = ((mul_317 - L) - (((t_sample)0.2) * m_d_8));
			t_sample B = ((f1 * H) + m_d_8);
			m_d_8 = B;
			m_d_9 = L;
			t_sample add_297 = (L + ((int)0));
			t_sample abs_298 = fabs(add_297);
			t_sample atodb_296 = atodb(abs_298);
			int gt_294 = (atodb_296 > m_knob3_threshold_5);
			t_sample sub_295 = (m_knob3_threshold_5 - atodb_296);
			t_sample mul_291 = (sub_295 * rsub_292);
			t_sample dbtoa_290 = dbtoa(mul_291);
			t_sample rsub_289 = (((int)1) - dbtoa_290);
			t_sample mul_288 = (rsub_289 * (-1));
			t_sample mul_287 = (gt_294 * mul_288);
			t_sample add_286 = (mul_287 + ((int)1));
			t_sample clamp_285 = ((add_286 <= ((int)0)) ? ((int)0) : ((add_286 >= ((int)1)) ? ((int)1) : add_286));
			t_sample mul_299 = (L * clamp_285);
			t_sample add_280 = (H + ((int)0));
			t_sample abs_281 = fabs(add_280);
			t_sample atodb_279 = atodb(abs_281);
			int gt_277 = (atodb_279 > m_knob3_threshold_5);
			t_sample sub_278 = (m_knob3_threshold_5 - atodb_279);
			t_sample mul_274 = (sub_278 * rsub_275);
			t_sample dbtoa_273 = dbtoa(mul_274);
			t_sample rsub_272 = (((int)1) - dbtoa_273);
			t_sample mul_271 = (rsub_272 * (-1));
			t_sample mul_270 = (gt_277 * mul_271);
			t_sample add_269 = (mul_270 + ((int)1));
			t_sample clamp_268 = ((add_269 <= ((int)0)) ? ((int)0) : ((add_269 >= ((int)1)) ? ((int)1) : add_269));
			t_sample mul_282 = (H * clamp_268);
			t_sample add_264 = (B + ((int)0));
			t_sample abs_265 = fabs(add_264);
			t_sample atodb_263 = atodb(abs_265);
			int gt_261 = (atodb_263 > m_knob3_threshold_5);
			t_sample sub_262 = (m_knob3_threshold_5 - atodb_263);
			t_sample mul_258 = (sub_262 * rsub_259);
			t_sample dbtoa_257 = dbtoa(mul_258);
			t_sample rsub_256 = (((int)1) - dbtoa_257);
			t_sample mul_255 = (rsub_256 * (-1));
			t_sample mul_254 = (gt_261 * mul_255);
			t_sample add_253 = (mul_254 + ((int)1));
			t_sample clamp_252 = ((add_253 <= ((int)0)) ? ((int)0) : ((add_253 >= ((int)1)) ? ((int)1) : add_253));
			t_sample mul_266 = (B * clamp_252);
			t_sample mul_315 = (((mul_266 + mul_282) + mul_299) * dbtoa_314);
			t_sample out1 = (gate_311 + mul_315);
			t_sample out2 = (gate_311 + mul_315);
			m_history_7 = history_307_next_309;
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
	inline void set_knob5_xover(t_param _value) {
		m_knob5_xover_1 = (_value < 20 ? 20 : (_value > 100 ? 100 : _value));
	};
	inline void set_knob2_output(t_param _value) {
		m_knob2_output_2 = (_value < -70 ? -70 : (_value > 15 ? 15 : _value));
	};
	inline void set_knob1_input(t_param _value) {
		m_knob1_input_3 = (_value < -70 ? -70 : (_value > 15 ? 15 : _value));
	};
	inline void set_knob4_ratio(t_param _value) {
		m_knob4_ratio_4 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_knob3_threshold(t_param _value) {
		m_knob3_threshold_5 = (_value < -70 ? -70 : (_value > 6 ? 6 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: self->set_knob1_input(value); break;
		case 1: self->set_knob2_output(value); break;
		case 2: self->set_knob3_threshold(value); break;
		case 3: self->set_knob4_ratio(value); break;
		case 4: self->set_knob5_xover(value); break;
		case 5: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_input_3; break;
		case 1: *value = self->m_knob2_output_2; break;
		case 2: *value = self->m_knob3_threshold_5; break;
		case 3: *value = self->m_knob4_ratio_4; break;
		case 4: *value = self->m_knob5_xover_1; break;
		case 5: *value = self->m_sw_6; break;
		
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
	// initialize parameter 0 ("m_knob1_input_3")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_input";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_input_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 15;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_output_2")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_output_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 15;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_threshold_5")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_threshold";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_threshold_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_ratio_4")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_ratio";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_ratio_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob5_xover_1")
	pi = self->__commonstate.params + 4;
	pi->name = "knob5_xover";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_xover_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_sw_6")
	pi = self->__commonstate.params + 5;
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
