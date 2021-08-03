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
	t_sample m_knob6_taps_20;
	t_sample m_sw_18;
	t_sample m_history_13;
	t_sample m_history_12;
	t_sample m_history_11;
	t_sample m_sw_19;
	t_sample m_history_8;
	t_sample m_knob5_breadth_16;
	t_sample m_knob3_depth_15;
	t_sample m_knob4_rate_17;
	t_sample m_history_14;
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
		m_history_14 = ((int)0);
		m_knob3_depth_15 = ((int)0);
		m_knob5_breadth_16 = ((int)0);
		m_knob4_rate_17 = ((int)0);
		m_sw_18 = ((int)0);
		m_sw_19 = ((int)0);
		m_knob6_taps_20 = ((int)0);
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
		t_sample sub_6849 = (m_knob6_taps_20 - ((int)0));
		t_sample scale_6846 = ((safepow((sub_6849 * ((t_sample)1)), ((int)1)) * ((t_sample)-0.5)) + ((int)1));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out5 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample sah_743 = __m_sah_21(m_history_14, m_sw_18, ((int)0));
			t_sample gen_745 = sah_743;
			t_sample rsub_741 = (((int)1) - sah_743);
			t_sample history_742_next_744 = fixdenorm(rsub_741);
			t_sample out3 = gen_745;
			t_sample add_746 = (gen_745 + ((int)1));
			t_sample choice_22 = int(add_746);
			t_sample gate_738 = (((choice_22 >= 1) && (choice_22 < 2)) ? in1 : 0);
			t_sample gate_739 = ((choice_22 >= 2) ? in1 : 0);
			t_sample switch_864 = (m_sw_19 ? ((int)0) : gate_739);
			t_sample mix_6850 = (m_history_13 + (((t_sample)0.003926980723806) * (m_knob6_taps_20 - m_history_13)));
			t_sample mix_669 = mix_6850;
			t_sample mix_6851 = (m_history_12 + (((t_sample)0.003926980723806) * (mix_669 - m_history_12)));
			t_sample mix_667 = mix_6851;
			t_sample mix_6852 = (m_history_11 + (((t_sample)0.003926980723806) * (mix_667 - m_history_11)));
			t_sample mix_665 = mix_6852;
			t_sample gen_1325 = mix_665;
			t_sample history_671_next_674 = fixdenorm(mix_669);
			t_sample history_668_next_675 = fixdenorm(mix_667);
			t_sample history_666_next_676 = fixdenorm(mix_665);
			int gte_2956 = (gen_1325 >= ((int)0));
			int gt_1474 = (gen_1325 > ((t_sample)0.25));
			int gt_1524 = (gen_1325 > ((t_sample)0.5));
			int gt_1623 = (gen_1325 > ((t_sample)0.75));
			t_sample mix_6853 = (m_history_10 + (((t_sample)0.003926980723806) * (m_knob3_depth_15 - m_history_10)));
			t_sample mix_6779 = mix_6853;
			t_sample mix_6854 = (m_history_9 + (((t_sample)0.003926980723806) * (mix_6779 - m_history_9)));
			t_sample mix_6777 = mix_6854;
			t_sample mix_6855 = (m_history_8 + (((t_sample)0.003926980723806) * (mix_6777 - m_history_8)));
			t_sample mix_6772 = mix_6855;
			t_sample gen_748 = mix_6772;
			t_sample history_671_next_6778 = fixdenorm(mix_6779);
			t_sample history_668_next_6768 = fixdenorm(mix_6777);
			t_sample history_666_next_6770 = fixdenorm(mix_6772);
			t_sample mix_6856 = (m_history_7 + (((t_sample)0.003926980723806) * (m_knob4_rate_17 - m_history_7)));
			t_sample mix_6794 = mix_6856;
			t_sample mix_6857 = (m_history_6 + (((t_sample)0.003926980723806) * (mix_6794 - m_history_6)));
			t_sample mix_6785 = mix_6857;
			t_sample mix_6858 = (m_history_5 + (((t_sample)0.003926980723806) * (mix_6785 - m_history_5)));
			t_sample mix_6787 = mix_6858;
			t_sample gen_678 = mix_6787;
			t_sample history_671_next_6791 = fixdenorm(mix_6794);
			t_sample history_668_next_6783 = fixdenorm(mix_6785);
			t_sample history_666_next_6790 = fixdenorm(mix_6787);
			t_sample mix_6859 = (m_history_4 + (((t_sample)0.003926980723806) * (m_knob5_breadth_16 - m_history_4)));
			t_sample mix_6809 = mix_6859;
			t_sample mix_6860 = (m_history_3 + (((t_sample)0.003926980723806) * (mix_6809 - m_history_3)));
			t_sample mix_6803 = mix_6860;
			t_sample mix_6861 = (m_history_2 + (((t_sample)0.003926980723806) * (mix_6803 - m_history_2)));
			t_sample mix_6805 = mix_6861;
			t_sample gen_677 = mix_6805;
			t_sample history_671_next_6800 = fixdenorm(mix_6809);
			t_sample history_668_next_6798 = fixdenorm(mix_6803);
			t_sample history_666_next_6799 = fixdenorm(mix_6805);
			t_sample mul_662 = (gen_677 * ((int)0));
			t_sample add_661 = (mul_662 + ((int)1));
			t_sample mul_682 = (gen_678 * add_661);
			__m_cycle_23.freq(mul_682);
			t_sample cycle_727 = __m_cycle_23(__sinedata);
			t_sample cycleindex_728 = __m_cycle_23.phase();
			t_sample mul_725 = (cycle_727 * gen_748);
			t_sample add_726 = (mul_725 + ((int)127));
			t_sample mul_664 = (gen_677 * ((t_sample)0.1));
			t_sample add_663 = (mul_664 + ((int)1));
			t_sample mul_717 = (gen_678 * add_663);
			__m_cycle_24.freq(mul_717);
			t_sample cycle_723 = __m_cycle_24(__sinedata);
			t_sample cycleindex_724 = __m_cycle_24.phase();
			t_sample mul_721 = (cycle_723 * gen_748);
			t_sample add_722 = (mul_721 + ((int)127));
			t_sample mul_6530 = (gen_677 * ((t_sample)0.1));
			t_sample rsub_657 = (((int)1) - mul_6530);
			t_sample mul_681 = (gen_678 * rsub_657);
			__m_cycle_25.freq(mul_681);
			t_sample cycle_713 = __m_cycle_25(__sinedata);
			t_sample cycleindex_714 = __m_cycle_25.phase();
			t_sample mul_711 = (cycle_713 * gen_748);
			t_sample add_712 = (mul_711 + ((int)255));
			t_sample mul_6609 = (gen_677 * ((int)0));
			t_sample rsub_659 = (((int)1) - mul_6609);
			t_sample mul_705 = (gen_678 * rsub_659);
			__m_cycle_26.freq(mul_705);
			t_sample cycle_709 = __m_cycle_26(__sinedata);
			t_sample cycleindex_710 = __m_cycle_26.phase();
			t_sample mul_707 = (cycle_709 * gen_748);
			t_sample add_708 = (mul_707 + ((int)255));
			t_sample mul_654 = (gen_677 * ((t_sample)0.05));
			t_sample add_653 = (mul_654 + ((int)1));
			t_sample mul_680 = (gen_678 * add_653);
			__m_cycle_27.freq(mul_680);
			t_sample cycle_701 = __m_cycle_27(__sinedata);
			t_sample cycleindex_702 = __m_cycle_27.phase();
			t_sample mul_699 = (cycle_701 * gen_748);
			t_sample add_700 = (mul_699 + ((int)191));
			t_sample mul_6688 = (gen_677 * ((t_sample)0.04));
			t_sample rsub_655 = (((int)1) - mul_6688);
			t_sample mul_693 = (gen_678 * rsub_655);
			__m_cycle_28.freq(mul_693);
			t_sample cycle_697 = __m_cycle_28(__sinedata);
			t_sample cycleindex_698 = __m_cycle_28.phase();
			t_sample mul_695 = (cycle_697 * gen_748);
			t_sample add_696 = (mul_695 + ((int)191));
			t_sample mul_6767 = (gen_677 * ((t_sample)0.19));
			t_sample add_649 = (mul_6767 + ((int)1));
			t_sample mul_679 = (gen_678 * add_649);
			__m_cycle_29.freq(mul_679);
			t_sample cycle_691 = __m_cycle_29(__sinedata);
			t_sample cycleindex_692 = __m_cycle_29.phase();
			t_sample mul_689 = (cycle_691 * gen_748);
			t_sample add_690 = (mul_689 + ((int)383));
			t_sample mul_652 = (gen_677 * ((t_sample)0.2));
			t_sample rsub_651 = (((int)1) - mul_652);
			t_sample mul_683 = (gen_678 * rsub_651);
			__m_cycle_30.freq(mul_683);
			t_sample cycle_687 = __m_cycle_30(__sinedata);
			t_sample cycleindex_688 = __m_cycle_30.phase();
			t_sample mul_685 = (cycle_687 * gen_748);
			t_sample add_686 = (mul_685 + ((int)383));
			t_sample tap_730 = m_delay_1.read_linear(add_726);
			t_sample tap_731 = m_delay_1.read_linear(add_722);
			t_sample tap_732 = m_delay_1.read_linear(add_712);
			t_sample tap_733 = m_delay_1.read_linear(add_708);
			t_sample tap_734 = m_delay_1.read_linear(add_700);
			t_sample tap_735 = m_delay_1.read_linear(add_696);
			t_sample tap_736 = m_delay_1.read_linear(add_690);
			t_sample tap_737 = m_delay_1.read_linear(add_686);
			t_sample switch_2465 = (gte_2956 ? tap_730 : ((int)0));
			t_sample switch_2462 = (gt_1474 ? tap_733 : ((int)0));
			t_sample switch_1869 = (gt_1524 ? tap_734 : ((int)0));
			t_sample switch_2117 = (gt_1623 ? tap_737 : ((int)0));
			t_sample mul_6216 = ((((switch_2117 + switch_1869) + switch_2462) + switch_2465) * scale_6846);
			t_sample add_747 = (switch_864 + mul_6216);
			t_sample out1 = (gate_738 + add_747);
			t_sample switch_2464 = (gte_2956 ? tap_731 : ((int)0));
			t_sample switch_2463 = (gt_1474 ? tap_732 : ((int)0));
			t_sample switch_2067 = (gt_1524 ? tap_735 : ((int)0));
			t_sample switch_2118 = (gt_1623 ? tap_736 : ((int)0));
			t_sample mul_6287 = ((((switch_2118 + switch_2067) + switch_2463) + switch_2464) * scale_6846);
			t_sample add_715 = (switch_864 + mul_6287);
			t_sample out2 = (add_715 + gate_738);
			t_sample mul_719 = ((((((((switch_2465 + switch_2464) + switch_2463) + switch_2462) + switch_1869) + switch_2067) + switch_2118) + switch_2117) * ((t_sample)0.07));
			t_sample mul_716 = (mul_719 * (-1));
			m_history_14 = history_742_next_744;
			m_history_13 = history_671_next_674;
			m_history_11 = history_666_next_676;
			m_history_12 = history_668_next_675;
			m_history_10 = history_671_next_6778;
			m_history_8 = history_666_next_6770;
			m_history_9 = history_668_next_6768;
			m_history_7 = history_671_next_6791;
			m_history_5 = history_666_next_6790;
			m_history_6 = history_668_next_6783;
			m_history_4 = history_671_next_6800;
			m_history_2 = history_666_next_6799;
			m_history_3 = history_668_next_6798;
			m_delay_1.write((gate_739 + mul_716));
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
	inline void set_knob3_depth(t_param _value) {
		m_knob3_depth_15 = (_value < 2 ? 2 : (_value > 50 ? 50 : _value));
	};
	inline void set_knob5_breadth(t_param _value) {
		m_knob5_breadth_16 = (_value < 0 ? 0 : (_value > 5 ? 5 : _value));
	};
	inline void set_knob4_rate(t_param _value) {
		m_knob4_rate_17 = (_value < 0.01 ? 0.01 : (_value > 10 ? 10 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob6_taps(t_param _value) {
		m_knob6_taps_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: *value = self->m_knob3_depth_15; break;
		case 1: *value = self->m_knob4_rate_17; break;
		case 2: *value = self->m_knob5_breadth_16; break;
		case 3: *value = self->m_knob6_taps_20; break;
		case 4: *value = self->m_sw_18; break;
		case 5: *value = self->m_sw_19; break;
		
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
	// initialize parameter 0 ("m_knob3_depth_15")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_depth_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 2;
	pi->outputmax = 50;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_rate_17")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_rate_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.01;
	pi->outputmax = 10;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_breadth_16")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_breadth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_breadth_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob6_taps_20")
	pi = self->__commonstate.params + 3;
	pi->name = "knob6_taps";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob6_taps_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_18")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_sw_19")
	pi = self->__commonstate.params + 5;
	pi->name = "sw5";
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // DAISYTEST_LUKE_HARMONIZER::
