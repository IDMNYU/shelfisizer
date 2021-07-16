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
	t_sample m_sw_15;
	t_sample m_history_8;
	t_sample m_history_7;
	t_sample m_knob4_rate_12;
	t_sample m_knob3_depth_14;
	t_sample m_knob5_breadth_13;
	t_sample m_history_11;
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
		m_knob4_rate_12 = ((int)0);
		m_knob5_breadth_13 = ((int)0);
		m_knob3_depth_14 = ((int)0);
		m_sw_15 = ((int)0);
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
			t_sample out6 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample sah_78 = __m_sah_16(m_history_11, m_sw_15, ((int)0));
			t_sample gen_80 = sah_78;
			t_sample rsub_76 = (((int)1) - sah_78);
			t_sample history_77_next_79 = fixdenorm(rsub_76);
			t_sample out3 = gen_80;
			t_sample add_81 = (gen_80 + ((int)1));
			t_sample choice_17 = int(add_81);
			t_sample gate_73 = (((choice_17 >= 1) && (choice_17 < 2)) ? in1 : 0);
			t_sample gate_74 = ((choice_17 >= 2) ? in1 : 0);
			t_sample mix_1586 = (m_history_10 + (((t_sample)0.0042742627044161) * (m_knob3_depth_14 - m_history_10)));
			t_sample mix_5 = mix_1586;
			t_sample mix_1587 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_5 - m_history_9)));
			t_sample mix_3 = mix_1587;
			t_sample mix_1588 = (m_history_8 + (((t_sample)0.0042742627044161) * (mix_3 - m_history_8)));
			t_sample mix_1 = mix_1588;
			t_sample gen_83 = mix_1;
			t_sample history_7_next_10 = fixdenorm(mix_5);
			t_sample history_4_next_11 = fixdenorm(mix_3);
			t_sample history_2_next_12 = fixdenorm(mix_1);
			t_sample mix_1589 = (m_history_7 + (((t_sample)0.0042742627044161) * (m_knob4_rate_12 - m_history_7)));
			t_sample mix_1527 = mix_1589;
			t_sample mix_1590 = (m_history_6 + (((t_sample)0.0042742627044161) * (mix_1527 - m_history_6)));
			t_sample mix_1523 = mix_1590;
			t_sample mix_1591 = (m_history_5 + (((t_sample)0.0042742627044161) * (mix_1523 - m_history_5)));
			t_sample mix_1529 = mix_1591;
			t_sample gen_13 = mix_1529;
			t_sample history_7_next_1526 = fixdenorm(mix_1527);
			t_sample history_4_next_1522 = fixdenorm(mix_1523);
			t_sample history_2_next_1521 = fixdenorm(mix_1529);
			t_sample mix_1592 = (m_history_4 + (((t_sample)0.0042742627044161) * (m_knob5_breadth_13 - m_history_4)));
			t_sample mix_1543 = mix_1592;
			t_sample mix_1593 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_1543 - m_history_3)));
			t_sample mix_1542 = mix_1593;
			t_sample mix_1594 = (m_history_2 + (((t_sample)0.0042742627044161) * (mix_1542 - m_history_2)));
			t_sample mix_1536 = mix_1594;
			t_sample gen_129 = mix_1536;
			t_sample history_7_next_1541 = fixdenorm(mix_1543);
			t_sample history_4_next_1540 = fixdenorm(mix_1542);
			t_sample history_2_next_1539 = fixdenorm(mix_1536);
			t_sample mul_300 = (gen_129 * ((int)0));
			t_sample add_329 = (mul_300 + ((int)1));
			t_sample mul_743 = (gen_13 * add_329);
			__m_cycle_18.freq(mul_743);
			t_sample cycle_62 = __m_cycle_18(__sinedata);
			t_sample cycleindex_63 = __m_cycle_18.phase();
			t_sample mul_60 = (cycle_62 * gen_83);
			t_sample add_61 = (mul_60 + ((int)127));
			t_sample mul_214 = (gen_129 * ((t_sample)0.1));
			t_sample add_243 = (mul_214 + ((int)1));
			t_sample mul_744 = (gen_13 * add_243);
			__m_cycle_19.freq(mul_744);
			t_sample cycle_58 = __m_cycle_19(__sinedata);
			t_sample cycleindex_59 = __m_cycle_19.phase();
			t_sample mul_56 = (cycle_58 * gen_83);
			t_sample add_57 = (mul_56 + ((int)127));
			t_sample mul_387 = (gen_129 * ((int)0));
			t_sample rsub_511 = (((int)1) - mul_387);
			t_sample mul_746 = (gen_13 * rsub_511);
			__m_cycle_20.freq(mul_746);
			t_sample cycle_48 = __m_cycle_20(__sinedata);
			t_sample cycleindex_49 = __m_cycle_20.phase();
			t_sample mul_46 = (cycle_48 * gen_83);
			t_sample add_47 = (mul_46 + ((int)255));
			t_sample mul_389 = (gen_129 * ((t_sample)0.1));
			t_sample rsub_482 = (((int)1) - mul_389);
			t_sample mul_745 = (gen_13 * rsub_482);
			__m_cycle_21.freq(mul_745);
			t_sample cycle_44 = __m_cycle_21(__sinedata);
			t_sample cycleindex_45 = __m_cycle_21.phase();
			t_sample mul_42 = (cycle_44 * gen_83);
			t_sample add_43 = (mul_42 + ((int)255));
			t_sample mul_540 = (gen_129 * ((t_sample)0.05));
			t_sample add_418 = (mul_540 + ((int)1));
			t_sample mul_747 = (gen_13 * add_418);
			__m_cycle_22.freq(mul_747);
			t_sample cycle_36 = __m_cycle_22(__sinedata);
			t_sample cycleindex_37 = __m_cycle_22.phase();
			t_sample mul_34 = (cycle_36 * gen_83);
			t_sample add_35 = (mul_34 + ((int)191));
			t_sample mul_569 = (gen_129 * ((t_sample)0.05));
			t_sample rsub_598 = (((int)1) - mul_569);
			t_sample mul_748 = (gen_13 * rsub_598);
			__m_cycle_23.freq(mul_748);
			t_sample cycle_32 = __m_cycle_23(__sinedata);
			t_sample cycleindex_33 = __m_cycle_23.phase();
			t_sample mul_30 = (cycle_32 * gen_83);
			t_sample add_31 = (mul_30 + ((int)191));
			t_sample mul_627 = (gen_129 * ((t_sample)0.2));
			t_sample add_450 = (mul_627 + ((int)1));
			t_sample mul_749 = (gen_13 * add_450);
			__m_cycle_24.freq(mul_749);
			t_sample cycle_26 = __m_cycle_24(__sinedata);
			t_sample cycleindex_27 = __m_cycle_24.phase();
			t_sample mul_24 = (cycle_26 * gen_83);
			t_sample add_25 = (mul_24 + ((int)383));
			t_sample mul_656 = (gen_129 * ((t_sample)0.2));
			t_sample rsub_685 = (((int)1) - mul_656);
			t_sample mul_750 = (gen_13 * rsub_685);
			__m_cycle_25.freq(mul_750);
			t_sample cycle_22 = __m_cycle_25(__sinedata);
			t_sample cycleindex_23 = __m_cycle_25.phase();
			t_sample mul_20 = (cycle_22 * gen_83);
			t_sample add_21 = (mul_20 + ((int)383));
			t_sample tap_1512 = m_delay_1.read_linear(add_61);
			t_sample tap_1513 = m_delay_1.read_linear(add_57);
			t_sample tap_1514 = m_delay_1.read_linear(add_47);
			t_sample tap_1515 = m_delay_1.read_linear(add_43);
			t_sample tap_1516 = m_delay_1.read_linear(add_35);
			t_sample tap_1517 = m_delay_1.read_linear(add_31);
			t_sample tap_1518 = m_delay_1.read_linear(add_25);
			t_sample tap_1519 = m_delay_1.read_linear(add_21);
			t_sample mul_39 = ((((tap_1519 + tap_1516) + tap_1515) + tap_1512) * ((t_sample)0.5));
			t_sample add_82 = (gate_74 + mul_39);
			t_sample out1 = (gate_73 + add_82);
			t_sample mul_38 = ((((tap_1518 + tap_1517) + tap_1514) + tap_1513) * ((t_sample)0.5));
			t_sample add_50 = (gate_74 + mul_38);
			t_sample out2 = (add_50 + gate_73);
			t_sample mul_54 = ((((((((tap_1519 + tap_1518) + tap_1517) + tap_1516) + tap_1515) + tap_1514) + tap_1513) + tap_1512) * ((t_sample)0.07));
			t_sample mul_51 = (mul_54 * (-1));
			m_history_11 = history_77_next_79;
			m_history_10 = history_7_next_10;
			m_history_8 = history_2_next_12;
			m_history_9 = history_4_next_11;
			m_history_7 = history_7_next_1526;
			m_history_5 = history_2_next_1521;
			m_history_6 = history_4_next_1522;
			m_history_4 = history_7_next_1541;
			m_history_2 = history_2_next_1539;
			m_history_3 = history_4_next_1540;
			m_delay_1.write((mul_51 + gate_74));
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
	inline void set_knob4_rate(t_param _value) {
		m_knob4_rate_12 = (_value < 0.01 ? 0.01 : (_value > 10 ? 10 : _value));
	};
	inline void set_knob5_breadth(t_param _value) {
		m_knob5_breadth_13 = (_value < 0 ? 0 : (_value > 5 ? 5 : _value));
	};
	inline void set_knob3_depth(t_param _value) {
		m_knob3_depth_14 = (_value < 2 ? 2 : (_value > 50 ? 50 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: *value = self->m_knob3_depth_14; break;
		case 1: *value = self->m_knob4_rate_12; break;
		case 2: *value = self->m_knob5_breadth_13; break;
		case 3: *value = self->m_sw_15; break;
		
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
	// initialize parameter 0 ("m_knob3_depth_14")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_depth_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 2;
	pi->outputmax = 50;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_rate_12")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_rate_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_breadth_13")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_breadth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_breadth_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_sw_15")
	pi = self->__commonstate.params + 3;
	pi->name = "sw1";
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
