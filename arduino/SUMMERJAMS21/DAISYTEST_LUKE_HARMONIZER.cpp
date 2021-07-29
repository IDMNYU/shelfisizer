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
	Sah __m_sah_16;
	SineCycle __m_cycle_19;
	SineCycle __m_cycle_18;
	SineCycle __m_cycle_25;
	SineCycle __m_cycle_20;
	SineCycle __m_cycle_22;
	SineCycle __m_cycle_21;
	SineCycle __m_cycle_24;
	SineCycle __m_cycle_23;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_4;
	t_sample m_history_10;
	t_sample m_history_3;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample m_history_5;
	t_sample m_history_9;
	t_sample m_history_6;
	t_sample m_history_15;
	t_sample m_history_8;
	t_sample m_history_7;
	t_sample m_sw_12;
	t_sample m_knob4_rate_14;
	t_sample m_knob3_depth_13;
	t_sample m_knob5_breadth_11;
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
		m_knob5_breadth_11 = ((int)0);
		m_sw_12 = ((int)0);
		m_knob3_depth_13 = ((int)0);
		m_knob4_rate_14 = ((int)0);
		m_history_15 = ((int)0);
		__m_sah_16.reset(0);
		__m_cycle_18.reset(samplerate, 0);
		__m_cycle_19.reset(samplerate, 0);
		__m_cycle_20.reset(samplerate, 0);
		__m_cycle_21.reset(samplerate, 0);
		__m_cycle_22.reset(samplerate, 0);
		__m_cycle_23.reset(samplerate, 0);
		__m_cycle_24.reset(samplerate, 0);
		__m_cycle_25.reset(samplerate, 0);
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
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_314 = __m_sah_16(m_history_15, m_sw_12, ((int)0));
			t_sample gen_316 = sah_314;
			t_sample rsub_312 = (((int)1) - sah_314);
			t_sample history_313_next_315 = fixdenorm(rsub_312);
			t_sample out3 = gen_316;
			t_sample out4 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample add_317 = (gen_316 + ((int)1));
			t_sample choice_17 = int(add_317);
			t_sample gate_309 = (((choice_17 >= 1) && (choice_17 < 2)) ? in1 : 0);
			t_sample gate_310 = ((choice_17 >= 2) ? in1 : 0);
			t_sample mix_377 = (m_history_10 + (((t_sample)0.003926980723806) * (m_knob3_depth_13 - m_history_10)));
			t_sample mix_109 = mix_377;
			t_sample mix_378 = (m_history_9 + (((t_sample)0.003926980723806) * (mix_109 - m_history_9)));
			t_sample mix_107 = mix_378;
			t_sample mix_379 = (m_history_8 + (((t_sample)0.003926980723806) * (mix_107 - m_history_8)));
			t_sample mix_105 = mix_379;
			t_sample gen_319 = mix_105;
			t_sample history_111_next_114 = fixdenorm(mix_109);
			t_sample history_108_next_115 = fixdenorm(mix_107);
			t_sample history_106_next_116 = fixdenorm(mix_105);
			t_sample mix_380 = (m_history_7 + (((t_sample)0.003926980723806) * (m_knob4_rate_14 - m_history_7)));
			t_sample mix_322 = mix_380;
			t_sample mix_381 = (m_history_6 + (((t_sample)0.003926980723806) * (mix_322 - m_history_6)));
			t_sample mix_326 = mix_381;
			t_sample mix_382 = (m_history_5 + (((t_sample)0.003926980723806) * (mix_326 - m_history_5)));
			t_sample mix_323 = mix_382;
			t_sample gen_249 = mix_323;
			t_sample history_111_next_325 = fixdenorm(mix_322);
			t_sample history_108_next_321 = fixdenorm(mix_326);
			t_sample history_106_next_320 = fixdenorm(mix_323);
			t_sample mix_383 = (m_history_4 + (((t_sample)0.003926980723806) * (m_knob5_breadth_11 - m_history_4)));
			t_sample mix_342 = mix_383;
			t_sample mix_384 = (m_history_3 + (((t_sample)0.003926980723806) * (mix_342 - m_history_3)));
			t_sample mix_336 = mix_384;
			t_sample mix_385 = (m_history_2 + (((t_sample)0.003926980723806) * (mix_336 - m_history_2)));
			t_sample mix_341 = mix_385;
			t_sample gen_248 = mix_341;
			t_sample history_111_next_338 = fixdenorm(mix_342);
			t_sample history_108_next_340 = fixdenorm(mix_336);
			t_sample history_106_next_337 = fixdenorm(mix_341);
			t_sample mul_245 = (gen_248 * ((int)0));
			t_sample add_244 = (mul_245 + ((int)1));
			t_sample mul_253 = (gen_249 * add_244);
			__m_cycle_18.freq(mul_253);
			t_sample cycle_298 = __m_cycle_18(__sinedata);
			t_sample cycleindex_299 = __m_cycle_18.phase();
			t_sample mul_296 = (cycle_298 * gen_319);
			t_sample add_297 = (mul_296 + ((int)127));
			t_sample mul_247 = (gen_248 * ((t_sample)0.1));
			t_sample add_246 = (mul_247 + ((int)1));
			t_sample mul_288 = (gen_249 * add_246);
			__m_cycle_19.freq(mul_288);
			t_sample cycle_294 = __m_cycle_19(__sinedata);
			t_sample cycleindex_295 = __m_cycle_19.phase();
			t_sample mul_292 = (cycle_294 * gen_319);
			t_sample add_293 = (mul_292 + ((int)127));
			t_sample mul_241 = (gen_248 * ((int)0));
			t_sample rsub_240 = (((int)1) - mul_241);
			t_sample mul_252 = (gen_249 * rsub_240);
			__m_cycle_20.freq(mul_252);
			t_sample cycle_284 = __m_cycle_20(__sinedata);
			t_sample cycleindex_285 = __m_cycle_20.phase();
			t_sample mul_282 = (cycle_284 * gen_319);
			t_sample add_283 = (mul_282 + ((int)255));
			t_sample mul_243 = (gen_248 * ((t_sample)0.1));
			t_sample rsub_242 = (((int)1) - mul_243);
			t_sample mul_276 = (gen_249 * rsub_242);
			__m_cycle_21.freq(mul_276);
			t_sample cycle_280 = __m_cycle_21(__sinedata);
			t_sample cycleindex_281 = __m_cycle_21.phase();
			t_sample mul_278 = (cycle_280 * gen_319);
			t_sample add_279 = (mul_278 + ((int)255));
			t_sample mul_237 = (gen_248 * ((t_sample)0.05));
			t_sample add_236 = (mul_237 + ((int)1));
			t_sample mul_251 = (gen_249 * add_236);
			__m_cycle_22.freq(mul_251);
			t_sample cycle_272 = __m_cycle_22(__sinedata);
			t_sample cycleindex_273 = __m_cycle_22.phase();
			t_sample mul_270 = (cycle_272 * gen_319);
			t_sample add_271 = (mul_270 + ((int)191));
			t_sample mul_239 = (gen_248 * ((t_sample)0.05));
			t_sample rsub_238 = (((int)1) - mul_239);
			t_sample mul_264 = (gen_249 * rsub_238);
			__m_cycle_23.freq(mul_264);
			t_sample cycle_268 = __m_cycle_23(__sinedata);
			t_sample cycleindex_269 = __m_cycle_23.phase();
			t_sample mul_266 = (cycle_268 * gen_319);
			t_sample add_267 = (mul_266 + ((int)191));
			t_sample mul_233 = (gen_248 * ((t_sample)0.2));
			t_sample add_232 = (mul_233 + ((int)1));
			t_sample mul_250 = (gen_249 * add_232);
			__m_cycle_24.freq(mul_250);
			t_sample cycle_262 = __m_cycle_24(__sinedata);
			t_sample cycleindex_263 = __m_cycle_24.phase();
			t_sample mul_260 = (cycle_262 * gen_319);
			t_sample add_261 = (mul_260 + ((int)383));
			t_sample mul_235 = (gen_248 * ((t_sample)0.2));
			t_sample rsub_234 = (((int)1) - mul_235);
			t_sample mul_254 = (gen_249 * rsub_234);
			__m_cycle_25.freq(mul_254);
			t_sample cycle_258 = __m_cycle_25(__sinedata);
			t_sample cycleindex_259 = __m_cycle_25.phase();
			t_sample mul_256 = (cycle_258 * gen_319);
			t_sample add_257 = (mul_256 + ((int)383));
			t_sample tap_301 = m_delay_1.read_linear(add_297);
			t_sample tap_302 = m_delay_1.read_linear(add_293);
			t_sample tap_303 = m_delay_1.read_linear(add_283);
			t_sample tap_304 = m_delay_1.read_linear(add_279);
			t_sample tap_305 = m_delay_1.read_linear(add_271);
			t_sample tap_306 = m_delay_1.read_linear(add_267);
			t_sample tap_307 = m_delay_1.read_linear(add_261);
			t_sample tap_308 = m_delay_1.read_linear(add_257);
			t_sample mul_275 = ((((tap_301 + tap_304) + tap_305) + tap_308) * ((t_sample)0.5));
			t_sample add_318 = (gate_310 + mul_275);
			t_sample out1 = (gate_309 + add_318);
			t_sample mul_274 = ((((tap_302 + tap_303) + tap_306) + tap_307) * ((t_sample)0.5));
			t_sample add_286 = (gate_310 + mul_274);
			t_sample out2 = (add_286 + gate_309);
			t_sample mul_290 = ((((((((tap_301 + tap_302) + tap_303) + tap_304) + tap_305) + tap_306) + tap_307) + tap_308) * ((t_sample)0.07));
			t_sample mul_287 = (mul_290 * (-1));
			m_history_15 = history_313_next_315;
			m_history_10 = history_111_next_114;
			m_history_8 = history_106_next_116;
			m_history_9 = history_108_next_115;
			m_history_7 = history_111_next_325;
			m_history_5 = history_106_next_320;
			m_history_6 = history_108_next_321;
			m_history_4 = history_111_next_338;
			m_history_2 = history_106_next_337;
			m_history_3 = history_108_next_340;
			m_delay_1.write((gate_310 + mul_287));
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
	inline void set_knob5_breadth(t_param _value) {
		m_knob5_breadth_11 = (_value < 0 ? 0 : (_value > 5 ? 5 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_depth(t_param _value) {
		m_knob3_depth_13 = (_value < 2 ? 2 : (_value > 50 ? 50 : _value));
	};
	inline void set_knob4_rate(t_param _value) {
		m_knob4_rate_14 = (_value < 0.01 ? 0.01 : (_value > 10 ? 10 : _value));
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
int num_params() { return 4; }

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
		case 3: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob3_depth_13; break;
		case 1: *value = self->m_knob4_rate_14; break;
		case 2: *value = self->m_knob5_breadth_11; break;
		case 3: *value = self->m_sw_12; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_knob3_depth_13")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_depth_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 2;
	pi->outputmax = 50;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_rate_14")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_rate_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_breadth_11")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_breadth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_breadth_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_sw_12")
	pi = self->__commonstate.params + 3;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_12;
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
