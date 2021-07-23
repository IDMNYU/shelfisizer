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
	Phasor __m_phasor_31;
	Sah __m_sah_26;
	SineCycle __m_cycle_32;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_sw_21;
	t_sample m_s_3;
	t_sample m_knob4_depth_22;
	t_sample m_sw_20;
	t_sample m_history_19;
	t_sample m_knob5_rate_23;
	t_sample m_knob3_manual_24;
	t_sample m_knob6_res_25;
	t_sample samples_to_seconds;
	t_sample m_history_18;
	t_sample __m_slide_28;
	t_sample samplerate;
	t_sample m_s_2;
	t_sample m_history_17;
	t_sample m_history_15;
	t_sample m_s_7;
	t_sample m_slim_8;
	t_sample m_s_6;
	t_sample m_s_4;
	t_sample m_s_5;
	t_sample m_history_16;
	t_sample m_s_9;
	t_sample m_rc_11;
	t_sample m_s_1;
	t_sample m_previn_10;
	t_sample m_history_13;
	t_sample m_fc_12;
	t_sample m_history_14;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_s_1 = ((int)0);
		m_s_2 = ((int)0);
		m_s_3 = ((int)0);
		m_s_4 = ((int)0);
		m_s_5 = ((int)0);
		m_s_6 = ((int)0);
		m_s_7 = ((int)0);
		m_slim_8 = ((int)0);
		m_s_9 = ((int)0);
		m_previn_10 = ((int)0);
		m_rc_11 = ((int)0);
		m_fc_12 = ((int)1);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_sw_20 = ((int)0);
		m_sw_21 = ((int)0);
		m_knob4_depth_22 = 1;
		m_knob5_rate_23 = 0.1;
		m_knob3_manual_24 = 0;
		m_knob6_res_25 = 0.5;
		__m_sah_26.reset(0);
		__m_slide_28 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_31.reset(0);
		__m_cycle_32.reset(samplerate, 0);
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
		t_sample add_133 = (m_sw_20 + ((int)1));
		t_sample mstosamps_131 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_130 = (((int)100) * (samplerate * 0.001));
		t_sample iup_29 = (1 / maximum(1, abs(mstosamps_131)));
		t_sample idown_30 = (1 / maximum(1, abs(mstosamps_130)));
		samples_to_seconds = (1 / samplerate);
		t_sample choice_33 = int(add_133);
		t_sample minb_34 = ((((t_sample)1e-05) < m_knob6_res_25) ? m_knob6_res_25 : ((t_sample)1e-05));
		t_sample maxb_35 = safediv(((t_sample)12.5), samplerate);
		t_sample minb_36 = ((((t_sample)0.0001) < maxb_35) ? maxb_35 : ((t_sample)0.0001));
		t_sample expr_285 = sqrt(((minb_36 < ((int)1)) ? minb_36 : ((int)1)));
		t_sample expr_284 = (((int)-1) * log(expr_285));
		int min_39 = (-1);
		int min_42 = (-1);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out4 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample sah_142 = __m_sah_26(m_history_19, m_sw_21, ((int)0));
			t_sample gen_144 = sah_142;
			t_sample rsub_140 = (((int)1) - sah_142);
			t_sample history_141_next_143 = fixdenorm(rsub_140);
			t_sample out3 = gen_144;
			t_sample add_145 = (gen_144 + ((int)1));
			t_sample choice_27 = int(add_145);
			t_sample gate_137 = (((choice_27 >= 1) && (choice_27 < 2)) ? in1 : 0);
			t_sample gate_138 = ((choice_27 >= 2) ? in1 : 0);
			t_sample mix_1522 = (m_history_18 + (((t_sample)0.0042742627044161) * (m_knob3_manual_24 - m_history_18)));
			t_sample mix_7 = mix_1522;
			t_sample mix_1523 = (m_history_17 + (((t_sample)0.0042742627044161) * (mix_7 - m_history_17)));
			t_sample mix_5 = mix_1523;
			t_sample mix_1524 = (m_history_16 + (((t_sample)0.0042742627044161) * (mix_5 - m_history_16)));
			t_sample mix_3 = mix_1524;
			t_sample gen_15 = mix_3;
			t_sample history_9_next_12 = fixdenorm(mix_7);
			t_sample history_6_next_13 = fixdenorm(mix_5);
			t_sample history_4_next_14 = fixdenorm(mix_3);
			t_sample abs_136 = fabs(gate_138);
			__m_slide_28 = fixdenorm((__m_slide_28 + (((abs_136 > __m_slide_28) ? iup_29 : idown_30) * (abs_136 - __m_slide_28))));
			t_sample slide_135 = __m_slide_28;
			t_sample mul_132 = (slide_135 * ((int)10));
			t_sample clamp_2 = ((mul_132 <= ((int)0)) ? ((int)0) : ((mul_132 >= ((int)1)) ? ((int)1) : mul_132));
			t_sample mix_1525 = (m_history_15 + (((t_sample)0.0042742627044161) * (m_knob5_rate_23 - m_history_15)));
			t_sample mix_1496 = mix_1525;
			t_sample mix_1526 = (m_history_14 + (((t_sample)0.0042742627044161) * (mix_1496 - m_history_14)));
			t_sample mix_1503 = mix_1526;
			t_sample mix_1527 = (m_history_13 + (((t_sample)0.0042742627044161) * (mix_1503 - m_history_13)));
			t_sample mix_1502 = mix_1527;
			t_sample gen_127 = mix_1502;
			t_sample history_9_next_1501 = fixdenorm(mix_1496);
			t_sample history_6_next_1495 = fixdenorm(mix_1503);
			t_sample history_4_next_1497 = fixdenorm(mix_1502);
			t_sample rsub_148 = (((int)1) - gen_127);
			t_sample sqrt_147 = sqrt(rsub_148);
			t_sample rsub_146 = (((int)1) - sqrt_147);
			t_sample mul_152 = (rsub_146 * ((int)10));
			t_sample phasor_151 = __m_phasor_31(mul_152, samples_to_seconds);
			__m_cycle_32.phase(phasor_151);
			t_sample cycle_125 = __m_cycle_32(__sinedata);
			t_sample cycleindex_126 = __m_cycle_32.phase();
			t_sample sub_1531 = (cycle_125 - (-1));
			t_sample scale_1528 = ((safepow((sub_1531 * ((t_sample)0.5)), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_1 = scale_1528;
			t_sample selector_134 = ((choice_33 >= 2) ? clamp_2 : ((choice_33 >= 1) ? scale_1 : 0));
			t_sample mul_124 = (selector_134 * m_knob4_depth_22);
			t_sample add_17 = (mul_124 + gen_15);
			t_sample clamp_16 = ((add_17 <= ((int)0)) ? ((int)0) : ((add_17 >= ((int)1)) ? ((int)1) : add_17));
			t_sample sub_1535 = (clamp_16 - ((int)0));
			t_sample scale_1532 = ((safepow((sub_1535 * ((t_sample)1)), ((int)1)) * ((int)120)) + ((int)15));
			t_sample scale_18 = scale_1532;
			t_sample expr_1480 = (((((t_sample)1.05) * ((minb_34 < ((int)1)) ? minb_34 : ((int)1))) - m_rc_11) * ((t_sample)0.25));
			t_sample add_75 = (m_rc_11 + expr_1480);
			t_sample fixdenorm_36 = fixdenorm(m_previn_10);
			t_sample noise_19 = noise();
			t_sample expr_1465 = (gate_138 + (((t_sample)1e-11) * noise_19));
			t_sample mul_69 = (m_s_7 * ((t_sample)0.3));
			t_sample gen_412 = m_fc_12;
			t_sample mul_230 = (scale_18 * ((t_sample)0.90193));
			t_sample add_227 = (mul_230 + ((t_sample)7.29));
			t_sample div_226 = (add_227 * ((t_sample)0.0078740157480315));
			t_sample clamp_232 = ((div_226 <= ((int)0)) ? ((int)0) : ((div_226 >= ((t_sample)0.99)) ? ((t_sample)0.99) : div_226));
			t_sample mul_231 = (clamp_232 * expr_284);
			t_sample expr_286 = (((t_sample)0.99999636) + ((((t_sample)0.031261316) + ((((t_sample)0.00048274797) + (((t_sample)5.949053e-06) * mul_231)) * mul_231)) * mul_231));
			t_sample mul_239 = (expr_286 * expr_286);
			t_sample mul_238 = (mul_239 * mul_239);
			t_sample mul_237 = (mul_238 * mul_238);
			t_sample mul_236 = (mul_237 * mul_237);
			t_sample mul_235 = (mul_236 * mul_236);
			t_sample mul_229 = (mul_235 * expr_285);
			t_sample sub_228 = (mul_229 - m_fc_12);
			t_sample div_225 = (sub_228 * ((t_sample)0.5));
			t_sample add_241 = (m_fc_12 + div_225);
			t_sample fc_next_287 = fixdenorm(add_241);
			t_sample expr_1479 = (gen_412 * gen_412);
			t_sample expr_1478 = (expr_1479 * (((int)1) - m_rc_11));
			t_sample expr_1477 = (expr_1479 + (expr_1478 * expr_1478));
			t_sample expr_1476 = ((((t_sample)1.25) + ((((t_sample)-0.74375) + (((t_sample)0.3) * expr_1477)) * expr_1477)) * expr_1477);
			t_sample expr_1475 = (m_rc_11 * (((t_sample)1.4) + ((((t_sample)0.108) + ((((t_sample)-0.164) - (((t_sample)0.069) * expr_1476)) * expr_1476)) * expr_1476)));
			t_sample expr_1474 = (((t_sample)0.18) + (((t_sample)0.25) * (expr_1475 * expr_1475)));
			t_sample expr_1473 = ((fixdenorm_36 * expr_1474) - (expr_1475 * m_s_1));
			t_sample maxb_37 = (((((t_sample)0.062) * expr_1473) * expr_1473) + (((t_sample)0.993) * m_slim_8));
			t_sample minb_38 = ((((int)-1) < maxb_37) ? maxb_37 : ((int)-1));
			t_sample expr_1472 = ((minb_38 < ((int)1)) ? minb_38 : ((int)1));
			t_sample expr_1471 = (expr_1473 * ((((int)1) - expr_1472) + ((((t_sample)0.5) * expr_1472) * expr_1472)));
			t_sample rsub_76 = (((int)1) - expr_1476);
			t_sample expr_1470 = ((expr_1471 * expr_1476) + (rsub_76 * m_s_7));
			t_sample add_67 = (expr_1470 + mul_69);
			t_sample expr_1469 = ((add_67 * expr_1476) + (rsub_76 * m_s_6));
			t_sample mul_51 = (expr_1470 * ((t_sample)0.3));
			t_sample mul_58 = (m_s_4 * ((t_sample)0.3));
			t_sample mul_61 = (m_s_5 * ((t_sample)0.3));
			t_sample mul_48 = (expr_1469 * ((t_sample)0.3));
			t_sample mul_66 = (m_s_6 * ((t_sample)0.3));
			t_sample add_64 = (expr_1469 + mul_66);
			t_sample clamp_63 = ((add_64 <= min_39) ? min_39 : ((add_64 >= ((int)1)) ? ((int)1) : add_64));
			t_sample expr_1468 = (clamp_63 * (((int)1) - ((((t_sample)0.3333333) * clamp_63) * clamp_63)));
			t_sample expr_1467 = ((expr_1468 * expr_1476) + (rsub_76 * m_s_5));
			t_sample add_59 = (expr_1467 + mul_61);
			t_sample expr_1466 = ((add_59 * expr_1476) + (rsub_76 * m_s_4));
			t_sample add_56 = (expr_1466 + mul_58);
			t_sample expr_1464 = ((expr_1465 * expr_1474) - (expr_1475 * add_56));
			t_sample maxb_40 = (((((t_sample)0.062) * expr_1464) * expr_1464) + (((t_sample)0.993) * expr_1472));
			t_sample minb_41 = ((((int)-1) < maxb_40) ? maxb_40 : ((int)-1));
			t_sample expr_1463 = ((minb_41 < ((int)1)) ? minb_41 : ((int)1));
			t_sample expr_1462 = (expr_1464 * ((((int)1) - expr_1463) + ((((t_sample)0.5) * expr_1463) * expr_1463)));
			t_sample expr_1461 = ((expr_1462 * expr_1476) + (rsub_76 * expr_1470));
			t_sample add_49 = (expr_1461 + mul_51);
			t_sample expr_1460 = ((add_49 * expr_1476) + (rsub_76 * expr_1469));
			t_sample add_46 = (expr_1460 + mul_48);
			t_sample clamp_45 = ((add_46 <= min_42) ? min_42 : ((add_46 >= ((int)1)) ? ((int)1) : add_46));
			t_sample expr_1459 = (clamp_45 * (((int)1) - ((((t_sample)0.3333333) * clamp_45) * clamp_45)));
			t_sample expr_1458 = ((expr_1459 * expr_1476) + (rsub_76 * expr_1467));
			t_sample mul_40 = (expr_1466 * ((t_sample)0.3));
			t_sample mul_43 = (expr_1467 * ((t_sample)0.3));
			t_sample add_41 = (expr_1458 + mul_43);
			t_sample expr_1457 = ((add_41 * expr_1476) + (rsub_76 * expr_1466));
			t_sample add_38 = (expr_1457 + mul_40);
			t_sample expr_1456 = (((((t_sample)0.19) * (add_38 + m_s_9)) + (((t_sample)0.57) * (add_56 + m_s_3))) - (((t_sample)0.52) * m_s_2));
			t_sample gen_1492 = expr_1456;
			t_sample rc_next_1481 = fixdenorm(add_75);
			t_sample previn_next_1482 = fixdenorm(expr_1465);
			t_sample s8_next_1483 = fixdenorm(add_56);
			t_sample slim_next_1484 = fixdenorm(expr_1463);
			t_sample s1_next_1485 = fixdenorm(expr_1461);
			t_sample s2_next_1486 = fixdenorm(expr_1460);
			t_sample s3_next_1487 = fixdenorm(expr_1458);
			t_sample s4_next_1488 = fixdenorm(expr_1457);
			t_sample s7_next_1489 = fixdenorm(add_38);
			t_sample s6_next_1490 = fixdenorm(expr_1456);
			t_sample s5_next_1491 = fixdenorm(add_38);
			t_sample add_149 = (gen_1492 + gate_137);
			t_sample out2 = add_149;
			t_sample add_150 = (gen_1492 + gate_137);
			t_sample out1 = add_150;
			m_history_19 = history_141_next_143;
			m_history_18 = history_9_next_12;
			m_history_16 = history_4_next_14;
			m_history_17 = history_6_next_13;
			m_history_15 = history_9_next_1501;
			m_history_13 = history_4_next_1497;
			m_history_14 = history_6_next_1495;
			m_fc_12 = fc_next_287;
			m_s_1 = s5_next_1491;
			m_s_2 = s6_next_1490;
			m_s_3 = s7_next_1489;
			m_s_4 = s4_next_1488;
			m_s_5 = s3_next_1487;
			m_s_6 = s2_next_1486;
			m_s_7 = s1_next_1485;
			m_slim_8 = slim_next_1484;
			m_s_9 = s8_next_1483;
			m_previn_10 = previn_next_1482;
			m_rc_11 = rc_next_1481;
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
	inline void set_sw5(t_param _value) {
		m_sw_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_depth(t_param _value) {
		m_knob4_depth_22 = (_value < -1 ? -1 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_rate(t_param _value) {
		m_knob5_rate_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_manual(t_param _value) {
		m_knob3_manual_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob6_res(t_param _value) {
		m_knob6_res_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: self->set_knob3_manual(value); break;
		case 1: self->set_knob4_depth(value); break;
		case 2: self->set_knob5_rate(value); break;
		case 3: self->set_knob6_res(value); break;
		case 4: self->set_sw1(value); break;
		case 5: self->set_sw5(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob3_manual_24; break;
		case 1: *value = self->m_knob4_depth_22; break;
		case 2: *value = self->m_knob5_rate_23; break;
		case 3: *value = self->m_knob6_res_25; break;
		case 4: *value = self->m_sw_21; break;
		case 5: *value = self->m_sw_20; break;
		
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
	// initialize parameter 0 ("m_knob3_manual_24")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_manual";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_manual_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_depth_22")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_depth_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -1;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_rate_23")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_rate_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob6_res_25")
	pi = self->__commonstate.params + 3;
	pi->name = "knob6_res";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob6_res_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_21")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_sw_20")
	pi = self->__commonstate.params + 5;
	pi->name = "sw5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_20;
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
