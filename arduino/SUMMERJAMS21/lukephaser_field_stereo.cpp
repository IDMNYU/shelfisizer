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
	t_sample m_knob3_manual_21;
	t_sample m_s_3;
	t_sample m_knob6_res_22;
	t_sample m_knob4_depth_20;
	t_sample m_knob5_rate_19;
	t_sample m_sw_23;
	t_sample m_sw_24;
	t_sample m_history_25;
	t_sample samples_to_seconds;
	t_sample m_history_18;
	t_sample __m_slide_28;
	t_sample samplerate;
	t_sample m_s_2;
	t_sample m_history_17;
	t_sample m_history_15;
	t_sample m_slim_7;
	t_sample m_s_8;
	t_sample m_s_6;
	t_sample m_s_4;
	t_sample m_s_5;
	t_sample m_history_16;
	t_sample m_s_9;
	t_sample m_rc_11;
	t_sample m_fc_1;
	t_sample m_s_10;
	t_sample m_history_13;
	t_sample m_previn_12;
	t_sample m_history_14;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_fc_1 = ((int)1);
		m_s_2 = ((int)0);
		m_s_3 = ((int)0);
		m_s_4 = ((int)0);
		m_s_5 = ((int)0);
		m_s_6 = ((int)0);
		m_slim_7 = ((int)0);
		m_s_8 = ((int)0);
		m_s_9 = ((int)0);
		m_s_10 = ((int)0);
		m_rc_11 = ((int)0);
		m_previn_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		m_knob5_rate_19 = 0.1;
		m_knob4_depth_20 = 1;
		m_knob3_manual_21 = 0;
		m_knob6_res_22 = 0.5;
		m_sw_23 = ((int)0);
		m_sw_24 = ((int)0);
		m_history_25 = ((int)0);
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
		t_sample add_1675 = (m_sw_23 + ((int)1));
		t_sample mstosamps_1671 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_1670 = (((int)100) * (samplerate * 0.001));
		t_sample iup_29 = (1 / maximum(1, abs(mstosamps_1671)));
		t_sample idown_30 = (1 / maximum(1, abs(mstosamps_1670)));
		samples_to_seconds = (1 / samplerate);
		t_sample choice_33 = int(add_1675);
		t_sample maxb_34 = safediv(((t_sample)12.5), samplerate);
		t_sample minb_35 = ((((t_sample)0.0001) < maxb_34) ? maxb_34 : ((t_sample)0.0001));
		t_sample expr_1608 = sqrt(((minb_35 < ((int)1)) ? minb_35 : ((int)1)));
		t_sample expr_1607 = (((int)-1) * log(expr_1608));
		t_sample minb_36 = ((((t_sample)1e-05) < m_knob6_res_22) ? m_knob6_res_22 : ((t_sample)1e-05));
		int min_39 = (-1);
		int min_42 = (-1);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_1685 = __m_sah_26(m_history_25, m_sw_24, ((int)0));
			t_sample gen_1687 = sah_1685;
			t_sample rsub_1683 = (((int)1) - sah_1685);
			t_sample history_1684_next_1686 = fixdenorm(rsub_1683);
			t_sample out3 = gen_1687;
			t_sample out6 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample add_1688 = (gen_1687 + ((int)1));
			t_sample choice_27 = int(add_1688);
			t_sample gate_1680 = (((choice_27 >= 1) && (choice_27 < 2)) ? in1 : 0);
			t_sample gate_1681 = ((choice_27 >= 2) ? in1 : 0);
			t_sample mix_3395 = (m_history_18 + (((t_sample)0.003926980723806) * (m_knob3_manual_21 - m_history_18)));
			t_sample mix_1659 = mix_3395;
			t_sample mix_3396 = (m_history_17 + (((t_sample)0.003926980723806) * (mix_1659 - m_history_17)));
			t_sample mix_1657 = mix_3396;
			t_sample mix_3397 = (m_history_16 + (((t_sample)0.003926980723806) * (mix_1657 - m_history_16)));
			t_sample mix_1655 = mix_3397;
			t_sample gen_2172 = mix_1655;
			t_sample history_1661_next_1664 = fixdenorm(mix_1659);
			t_sample history_1658_next_1665 = fixdenorm(mix_1657);
			t_sample history_1656_next_1666 = fixdenorm(mix_1655);
			t_sample abs_1679 = fabs(gate_1681);
			__m_slide_28 = fixdenorm((__m_slide_28 + (((abs_1679 > __m_slide_28) ? iup_29 : idown_30) * (abs_1679 - __m_slide_28))));
			t_sample slide_1678 = __m_slide_28;
			t_sample mul_2990 = (slide_1678 * ((int)10));
			t_sample clamp_2627 = ((mul_2990 <= ((int)0)) ? ((int)0) : ((mul_2990 >= ((int)1)) ? ((int)1) : mul_2990));
			t_sample mix_3398 = (m_history_15 + (((t_sample)0.003926980723806) * (m_knob5_rate_19 - m_history_15)));
			t_sample mix_3355 = mix_3398;
			t_sample mix_3399 = (m_history_14 + (((t_sample)0.003926980723806) * (mix_3355 - m_history_14)));
			t_sample mix_3359 = mix_3399;
			t_sample mix_3400 = (m_history_13 + (((t_sample)0.003926980723806) * (mix_3359 - m_history_13)));
			t_sample mix_3360 = mix_3400;
			t_sample gen_1667 = mix_3360;
			t_sample history_1661_next_3357 = fixdenorm(mix_3355);
			t_sample history_1658_next_3362 = fixdenorm(mix_3359);
			t_sample history_1656_next_3353 = fixdenorm(mix_3360);
			t_sample rsub_1691 = (((int)1) - gen_1667);
			t_sample sqrt_1690 = sqrt(rsub_1691);
			t_sample rsub_1689 = (((int)1) - sqrt_1690);
			t_sample mul_2954 = (rsub_1689 * ((int)10));
			t_sample phasor_1694 = __m_phasor_31(mul_2954, samples_to_seconds);
			__m_cycle_32.phase(phasor_1694);
			t_sample cycle_1653 = __m_cycle_32(__sinedata);
			t_sample cycleindex_1654 = __m_cycle_32.phase();
			t_sample sub_3404 = (cycle_1653 - (-1));
			t_sample scale_3401 = ((safepow((sub_3404 * ((t_sample)0.5)), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_3061 = scale_3401;
			t_sample selector_1677 = ((choice_33 >= 2) ? clamp_2627 : ((choice_33 >= 1) ? scale_3061 : 0));
			t_sample mul_1651 = (selector_1677 * m_knob4_depth_20);
			t_sample add_1984 = (mul_1651 + gen_2172);
			t_sample clamp_2089 = ((add_1984 <= ((int)0)) ? ((int)0) : ((add_1984 >= ((int)1)) ? ((int)1) : add_1984));
			t_sample sub_3408 = (clamp_2089 - ((int)0));
			t_sample scale_3405 = ((safepow((sub_3408 * ((t_sample)1)), ((int)1)) * ((int)120)) + ((int)15));
			t_sample scale_1542 = scale_3405;
			t_sample expr_1633 = (m_fc_1 * m_fc_1);
			t_sample expr_1632 = (expr_1633 * (((int)1) - m_rc_11));
			t_sample expr_1631 = (expr_1633 + (expr_1632 * expr_1632));
			t_sample expr_1630 = ((((t_sample)1.25) + ((((t_sample)-0.74375) + (((t_sample)0.3) * expr_1631)) * expr_1631)) * expr_1631);
			t_sample expr_1629 = (m_rc_11 * (((t_sample)1.4) + ((((t_sample)0.108) + ((((t_sample)-0.164) - (((t_sample)0.069) * expr_1630)) * expr_1630)) * expr_1630)));
			t_sample expr_1628 = (((t_sample)0.18) + (((t_sample)0.25) * (expr_1629 * expr_1629)));
			t_sample rsub_1600 = (((int)1) - expr_1630);
			t_sample noise_1543 = noise();
			t_sample expr_1619 = (gate_1681 + (((t_sample)1e-11) * noise_1543));
			t_sample expr_1634 = (((((t_sample)1.05) * ((minb_36 < ((int)1)) ? minb_36 : ((int)1))) - m_rc_11) * ((t_sample)0.25));
			t_sample add_1599 = (m_rc_11 + expr_1634);
			t_sample fixdenorm_1560 = fixdenorm(m_previn_12);
			t_sample expr_1627 = ((fixdenorm_1560 * expr_1628) - (expr_1629 * m_s_2));
			t_sample maxb_37 = (((((t_sample)0.062) * expr_1627) * expr_1627) + (((t_sample)0.993) * m_slim_7));
			t_sample minb_38 = ((((int)-1) < maxb_37) ? maxb_37 : ((int)-1));
			t_sample expr_1626 = ((minb_38 < ((int)1)) ? minb_38 : ((int)1));
			t_sample expr_1625 = (expr_1627 * ((((int)1) - expr_1626) + ((((t_sample)0.5) * expr_1626) * expr_1626)));
			t_sample expr_1624 = ((expr_1625 * expr_1630) + (rsub_1600 * m_s_10));
			t_sample mul_1582 = (m_s_5 * ((t_sample)0.3));
			t_sample mul_1575 = (expr_1624 * ((t_sample)0.3));
			t_sample mul_1593 = (m_s_10 * ((t_sample)0.3));
			t_sample add_1591 = (expr_1624 + mul_1593);
			t_sample expr_1623 = ((add_1591 * expr_1630) + (rsub_1600 * m_s_9));
			t_sample mul_1585 = (m_s_8 * ((t_sample)0.3));
			t_sample mul_1572 = (expr_1623 * ((t_sample)0.3));
			t_sample mul_1590 = (m_s_9 * ((t_sample)0.3));
			t_sample add_1588 = (expr_1623 + mul_1590);
			t_sample clamp_1587 = ((add_1588 <= min_39) ? min_39 : ((add_1588 >= ((int)1)) ? ((int)1) : add_1588));
			t_sample expr_1622 = (clamp_1587 * (((int)1) - ((((t_sample)0.3333333) * clamp_1587) * clamp_1587)));
			t_sample expr_1621 = ((expr_1622 * expr_1630) + (rsub_1600 * m_s_8));
			t_sample add_1583 = (expr_1621 + mul_1585);
			t_sample expr_1620 = ((add_1583 * expr_1630) + (rsub_1600 * m_s_5));
			t_sample add_1580 = (expr_1620 + mul_1582);
			t_sample expr_1618 = ((expr_1619 * expr_1628) - (expr_1629 * add_1580));
			t_sample maxb_40 = (((((t_sample)0.062) * expr_1618) * expr_1618) + (((t_sample)0.993) * expr_1626));
			t_sample minb_41 = ((((int)-1) < maxb_40) ? maxb_40 : ((int)-1));
			t_sample expr_1617 = ((minb_41 < ((int)1)) ? minb_41 : ((int)1));
			t_sample expr_1616 = (expr_1618 * ((((int)1) - expr_1617) + ((((t_sample)0.5) * expr_1617) * expr_1617)));
			t_sample expr_1615 = ((expr_1616 * expr_1630) + (rsub_1600 * expr_1624));
			t_sample add_1573 = (expr_1615 + mul_1575);
			t_sample expr_1614 = ((add_1573 * expr_1630) + (rsub_1600 * expr_1623));
			t_sample add_1570 = (expr_1614 + mul_1572);
			t_sample clamp_1569 = ((add_1570 <= min_42) ? min_42 : ((add_1570 >= ((int)1)) ? ((int)1) : add_1570));
			t_sample expr_1613 = (clamp_1569 * (((int)1) - ((((t_sample)0.3333333) * clamp_1569) * clamp_1569)));
			t_sample expr_1612 = ((expr_1613 * expr_1630) + (rsub_1600 * expr_1621));
			t_sample mul_1564 = (expr_1620 * ((t_sample)0.3));
			t_sample mul_1567 = (expr_1621 * ((t_sample)0.3));
			t_sample add_1565 = (expr_1612 + mul_1567);
			t_sample expr_1611 = ((add_1565 * expr_1630) + (rsub_1600 * expr_1620));
			t_sample add_1562 = (expr_1611 + mul_1564);
			t_sample expr_1610 = (((((t_sample)0.19) * (add_1562 + m_s_6)) + (((t_sample)0.57) * (add_1580 + m_s_3))) - (((t_sample)0.52) * m_s_4));
			t_sample gen_1647 = expr_1610;
			t_sample mul_1549 = (scale_1542 * ((t_sample)0.90193));
			t_sample add_1546 = (mul_1549 + ((t_sample)7.29));
			t_sample div_1545 = (add_1546 * ((t_sample)0.0078740157480315));
			t_sample clamp_1551 = ((div_1545 <= ((int)0)) ? ((int)0) : ((div_1545 >= ((t_sample)0.99)) ? ((t_sample)0.99) : div_1545));
			t_sample mul_1550 = (clamp_1551 * expr_1607);
			t_sample expr_1609 = (((t_sample)0.99999636) + ((((t_sample)0.031261316) + ((((t_sample)0.00048274797) + (((t_sample)5.949053e-06) * mul_1550)) * mul_1550)) * mul_1550));
			t_sample mul_1558 = (expr_1609 * expr_1609);
			t_sample mul_1557 = (mul_1558 * mul_1558);
			t_sample mul_1556 = (mul_1557 * mul_1557);
			t_sample mul_1555 = (mul_1556 * mul_1556);
			t_sample mul_1554 = (mul_1555 * mul_1555);
			t_sample mul_1548 = (mul_1554 * expr_1608);
			t_sample sub_1547 = (mul_1548 - m_fc_1);
			t_sample div_1544 = (sub_1547 * ((t_sample)0.5));
			t_sample add_1603 = (m_fc_1 + div_1544);
			t_sample previn_next_1635 = fixdenorm(expr_1619);
			t_sample rc_next_1636 = fixdenorm(add_1599);
			t_sample s1_next_1637 = fixdenorm(expr_1615);
			t_sample s2_next_1638 = fixdenorm(expr_1614);
			t_sample s3_next_1639 = fixdenorm(expr_1612);
			t_sample slim_next_1640 = fixdenorm(expr_1617);
			t_sample s8_next_1641 = fixdenorm(add_1580);
			t_sample s4_next_1642 = fixdenorm(expr_1611);
			t_sample s6_next_1643 = fixdenorm(expr_1610);
			t_sample s7_next_1644 = fixdenorm(add_1562);
			t_sample s5_next_1645 = fixdenorm(add_1562);
			t_sample fc_next_1646 = fixdenorm(add_1603);
			t_sample add_1693 = (gen_1647 + gate_1680);
			t_sample out1 = add_1693;
			t_sample add_1692 = (gen_1647 + gate_1680);
			t_sample out2 = add_1692;
			m_history_25 = history_1684_next_1686;
			m_history_18 = history_1661_next_1664;
			m_history_16 = history_1656_next_1666;
			m_history_17 = history_1658_next_1665;
			m_history_15 = history_1661_next_3357;
			m_history_13 = history_1656_next_3353;
			m_history_14 = history_1658_next_3362;
			m_previn_12 = previn_next_1635;
			m_fc_1 = fc_next_1646;
			m_s_2 = s5_next_1645;
			m_s_3 = s7_next_1644;
			m_s_4 = s6_next_1643;
			m_s_5 = s4_next_1642;
			m_s_6 = s8_next_1641;
			m_slim_7 = slim_next_1640;
			m_s_8 = s3_next_1639;
			m_s_9 = s2_next_1638;
			m_s_10 = s1_next_1637;
			m_rc_11 = rc_next_1636;
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
	inline void set_knob5_rate(t_param _value) {
		m_knob5_rate_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_depth(t_param _value) {
		m_knob4_depth_20 = (_value < -1 ? -1 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_manual(t_param _value) {
		m_knob3_manual_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob6_res(t_param _value) {
		m_knob6_res_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: *value = self->m_knob3_manual_21; break;
		case 1: *value = self->m_knob4_depth_20; break;
		case 2: *value = self->m_knob5_rate_19; break;
		case 3: *value = self->m_knob6_res_22; break;
		case 4: *value = self->m_sw_24; break;
		case 5: *value = self->m_sw_23; break;
		
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
	// initialize parameter 0 ("m_knob3_manual_21")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_manual";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_manual_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_depth_20")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_depth_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -1;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_rate_19")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_rate_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob6_res_22")
	pi = self->__commonstate.params + 3;
	pi->name = "knob6_res";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob6_res_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_24")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_sw_23")
	pi = self->__commonstate.params + 5;
	pi->name = "sw5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_23;
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
