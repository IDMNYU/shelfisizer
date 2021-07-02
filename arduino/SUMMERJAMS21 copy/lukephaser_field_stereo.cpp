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
	DCBlock __m_dcblock_118;
	DCBlock __m_dcblock_80;
	DCBlock __m_dcblock_79;
	DCBlock __m_dcblock_117;
	Phasor __m_phasor_42;
	Sah __m_sah_71;
	Sah __m_sah_62;
	Sah __m_sah_44;
	Sah __m_sah_53;
	Sah __m_sah_109;
	Sah __m_sah_100;
	Sah __m_sah_82;
	Sah __m_sah_91;
	SineCycle __m_cycle_81;
	SineCycle __m_cycle_43;
	SineCycle __m_cycle_99;
	SineCycle __m_cycle_52;
	SineCycle __m_cycle_90;
	SineCycle __m_cycle_61;
	SineCycle __m_cycle_70;
	SineCycle __m_cycle_108;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample __m_slide_76;
	t_sample __m_slide_73;
	t_sample m_history_9;
	t_sample m_history_21;
	t_sample m_history_7;
	t_sample m_history_8;
	t_sample m_history_6;
	t_sample m_history_10;
	t_sample __m_slide_64;
	t_sample __m_slide_58;
	t_sample __m_slide_67;
	t_sample m_history_12;
	t_sample m_history_11;
	t_sample m_history_5;
	t_sample __m_slide_84;
	t_sample __m_slide_87;
	t_sample __m_slide_105;
	t_sample __m_slide_102;
	t_sample samplerate;
	t_sample __m_slide_114;
	t_sample __m_slide_111;
	t_sample __m_slide_55;
	t_sample m_history_1;
	t_sample __m_slide_96;
	t_sample m_history_4;
	t_sample m_history_2;
	t_sample m_history_3;
	t_sample __m_slide_93;
	t_sample m_history_20;
	t_sample m_history_13;
	t_sample __m_slide_49;
	t_sample m_history_29;
	t_sample m_history_28;
	t_sample m_history_30;
	t_sample m_history_32;
	t_sample m_history_31;
	t_sample m_history_33;
	t_sample m_history_27;
	t_sample m_history_25;
	t_sample m_history_22;
	t_sample m_history_26;
	t_sample m_history_23;
	t_sample m_history_24;
	t_sample m_history_14;
	t_sample m_history_34;
	t_sample m_knob7_gain_36;
	t_sample m_history_17;
	t_sample m_history_18;
	t_sample m_history_16;
	t_sample __m_slide_46;
	t_sample m_history_15;
	t_sample m_knob6_waveform_35;
	t_sample samples_to_seconds;
	t_sample m_knob5_fb_40;
	t_sample m_knob1_rate_37;
	t_sample m_knob4_diffusion_41;
	t_sample m_knob2_width_38;
	t_sample m_history_19;
	t_sample m_knob3_Q_39;
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
		m_history_21 = ((int)0);
		m_history_22 = ((int)0);
		m_history_23 = ((int)0);
		m_history_24 = ((int)0);
		m_history_25 = ((int)0);
		m_history_26 = ((int)0);
		m_history_27 = ((int)0);
		m_history_28 = ((int)0);
		m_history_29 = ((int)0);
		m_history_30 = ((int)0);
		m_history_31 = ((int)0);
		m_history_32 = ((int)0);
		m_history_33 = ((int)0);
		m_history_34 = ((int)0);
		m_knob6_waveform_35 = 1;
		m_knob7_gain_36 = 1;
		m_knob1_rate_37 = 0.1;
		m_knob2_width_38 = 1;
		m_knob3_Q_39 = 0.5;
		m_knob5_fb_40 = 0;
		m_knob4_diffusion_41 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_42.reset(0);
		__m_cycle_43.reset(samplerate, 0);
		__m_sah_44.reset(0);
		__m_slide_46 = 0;
		__m_slide_49 = 0;
		__m_cycle_52.reset(samplerate, 0);
		__m_sah_53.reset(0);
		__m_slide_55 = 0;
		__m_slide_58 = 0;
		__m_cycle_61.reset(samplerate, 0);
		__m_sah_62.reset(0);
		__m_slide_64 = 0;
		__m_slide_67 = 0;
		__m_cycle_70.reset(samplerate, 0);
		__m_sah_71.reset(0);
		__m_slide_73 = 0;
		__m_slide_76 = 0;
		__m_dcblock_79.reset();
		__m_dcblock_80.reset();
		__m_cycle_81.reset(samplerate, 0);
		__m_sah_82.reset(0);
		__m_slide_84 = 0;
		__m_slide_87 = 0;
		__m_cycle_90.reset(samplerate, 0);
		__m_sah_91.reset(0);
		__m_slide_93 = 0;
		__m_slide_96 = 0;
		__m_cycle_99.reset(samplerate, 0);
		__m_sah_100.reset(0);
		__m_slide_102 = 0;
		__m_slide_105 = 0;
		__m_cycle_108.reset(samplerate, 0);
		__m_sah_109.reset(0);
		__m_slide_111 = 0;
		__m_slide_114 = 0;
		__m_dcblock_117.reset();
		__m_dcblock_118.reset();
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample floor_4771 = floor(m_knob6_waveform_35);
		t_sample mul_4605 = (m_knob4_diffusion_41 * ((int)7));
		t_sample div_4604 = (mul_4605 * ((t_sample)0.125));
		t_sample mul_5977 = (m_knob4_diffusion_41 * ((int)6));
		t_sample div_4762 = (mul_5977 * ((t_sample)0.125));
		t_sample mul_6178 = (m_knob4_diffusion_41 * ((int)5));
		t_sample div_4606 = (mul_6178 * ((t_sample)0.125));
		t_sample mul_5910 = (m_knob4_diffusion_41 * ((int)4));
		t_sample div_4764 = (mul_5910 * ((t_sample)0.125));
		t_sample mul_6111 = (m_knob4_diffusion_41 * ((int)3));
		t_sample div_4607 = (mul_6111 * ((t_sample)0.125));
		t_sample mul_5843 = (m_knob4_diffusion_41 * ((int)2));
		t_sample div_4765 = (mul_5843 * ((t_sample)0.125));
		t_sample mul_6044 = (m_knob4_diffusion_41 * ((int)1));
		t_sample div_4608 = (mul_6044 * ((t_sample)0.125));
		t_sample mul_4769 = (m_knob4_diffusion_41 * ((int)0));
		t_sample div_4766 = (mul_4769 * ((t_sample)0.125));
		t_sample rsub_6676 = (((int)1) - m_knob1_rate_37);
		t_sample sqrt_6743 = sqrt(rsub_6676);
		t_sample sqrt_6942 = sqrt(sqrt_6743);
		t_sample rsub_7075 = (((int)1) - sqrt_6942);
		t_sample mul_6609 = (rsub_7075 * ((t_sample)7.5));
		samples_to_seconds = (1 / samplerate);
		t_sample choice_45 = int(floor_4771);
		t_sample div_4569 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_47 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_48 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_50 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_51 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_54 = int(floor_4771);
		t_sample div_4520 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_56 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_57 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_59 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_60 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_63 = int(floor_4771);
		t_sample div_4471 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_65 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_66 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_68 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_69 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_72 = int(floor_4771);
		t_sample div_4422 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_74 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_75 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_77 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_78 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_83 = int(floor_4771);
		t_sample div_4791 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_85 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_86 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_88 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_89 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_92 = int(floor_4771);
		t_sample div_4731 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_94 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_95 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_97 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_98 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_101 = int(floor_4771);
		t_sample div_4682 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_103 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_104 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_106 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_107 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_110 = int(floor_4771);
		t_sample div_4633 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_112 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_113 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_115 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_116 = (1 / maximum(1, abs(((int)5))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample mul_4602 = (in2 * ((int)0));
			t_sample mul_4822 = (in1 * m_knob7_gain_36);
			t_sample mul_5512 = (m_history_1 * m_knob5_fb_40);
			t_sample add_5511 = (((int)0) + mul_5512);
			t_sample mul_4614 = (m_history_2 * m_knob5_fb_40);
			t_sample add_4613 = (mul_4822 + mul_4614);
			t_sample phasor_4772 = __m_phasor_42(mul_6609, samples_to_seconds);
			t_sample add_8251 = (phasor_4772 + ((t_sample)0.25));
			t_sample mod_8250 = safemod(add_8251, ((int)1));
			t_sample add_4581 = (mod_8250 + div_4608);
			t_sample mod_4582 = safemod(add_4581, ((int)1));
			t_sample triangle_4578 = triangle(mod_4582, ((t_sample)0.5));
			int gt_4577 = (mod_4582 > ((t_sample)0.5));
			__m_cycle_43.phase(mod_4582);
			t_sample cycle_4579 = __m_cycle_43(__sinedata);
			t_sample cycleindex_4580 = __m_cycle_43.phase();
			t_sample add_4575 = (cycle_4579 + ((int)1));
			t_sample div_4574 = (add_4575 * ((t_sample)0.5));
			t_sample noise_4553 = noise();
			t_sample sah_4554 = __m_sah_44(noise_4553, mod_4582, ((t_sample)0.5));
			t_sample add_4552 = (sah_4554 + ((int)1));
			t_sample div_4551 = (add_4552 * ((t_sample)0.5));
			t_sample selector_4573 = ((choice_45 >= 5) ? div_4551 : ((choice_45 >= 4) ? gt_4577 : ((choice_45 >= 3) ? mod_4582 : ((choice_45 >= 2) ? triangle_4578 : ((choice_45 >= 1) ? div_4574 : 0)))));
			t_sample mul_4576 = (selector_4573 * m_knob2_width_38);
			t_sample sub_8915 = (mul_4576 - ((int)0));
			t_sample scale_8912 = ((safepow((sub_8915 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_4583 = scale_8912;
			t_sample mtof_4584 = mtof(scale_4583, ((int)440));
			t_sample mul_4568 = (mtof_4584 * div_4569);
			t_sample cos_4566 = cos(mul_4568);
			t_sample mul_4561 = (cos_4566 * (-2));
			t_sample sin_4567 = sin(mul_4568);
			t_sample mul_4565 = (sin_4567 * ((t_sample)0.5));
			t_sample div_4564 = safediv(mul_4565, m_knob3_Q_39);
			t_sample rsub_4559 = (((int)1) - div_4564);
			t_sample add_4563 = (div_4564 + ((int)1));
			t_sample rdiv_4562 = safediv(((int)1), add_4563);
			t_sample mul_4558 = (rdiv_4562 * rsub_4559);
			__m_slide_46 = fixdenorm((__m_slide_46 + (((mul_4558 > __m_slide_46) ? iup_47 : idown_48) * (mul_4558 - __m_slide_46))));
			t_sample slide_4555 = __m_slide_46;
			t_sample gen_4571 = slide_4555;
			t_sample mul_4560 = (rdiv_4562 * mul_4561);
			__m_slide_49 = fixdenorm((__m_slide_49 + (((mul_4560 > __m_slide_49) ? iup_50 : idown_51) * (mul_4560 - __m_slide_49))));
			t_sample slide_4556 = __m_slide_49;
			t_sample gen_4570 = slide_4556;
			t_sample mul_4594 = (add_5511 * gen_4571);
			t_sample mul_4591 = (m_history_32 * gen_4570);
			t_sample mul_4589 = (m_history_33 * ((int)1));
			t_sample mul_4585 = (m_history_34 * gen_4571);
			t_sample mul_4587 = (m_history_31 * gen_4570);
			t_sample sub_4593 = (((mul_4589 + mul_4591) + mul_4594) - (mul_4587 + mul_4585));
			t_sample gen_4599 = sub_4593;
			t_sample history_4586_next_4595 = fixdenorm(m_history_31);
			t_sample history_4590_next_4596 = fixdenorm(m_history_32);
			t_sample history_4592_next_4597 = fixdenorm(add_5511);
			t_sample history_4588_next_4598 = fixdenorm(sub_4593);
			t_sample add_4532 = (mod_8250 + div_4607);
			t_sample mod_4533 = safemod(add_4532, ((int)1));
			t_sample triangle_4529 = triangle(mod_4533, ((t_sample)0.5));
			int gt_4528 = (mod_4533 > ((t_sample)0.5));
			__m_cycle_52.phase(mod_4533);
			t_sample cycle_4530 = __m_cycle_52(__sinedata);
			t_sample cycleindex_4531 = __m_cycle_52.phase();
			t_sample add_4526 = (cycle_4530 + ((int)1));
			t_sample div_4525 = (add_4526 * ((t_sample)0.5));
			t_sample noise_4504 = noise();
			t_sample sah_4505 = __m_sah_53(noise_4504, mod_4533, ((t_sample)0.5));
			t_sample add_4503 = (sah_4505 + ((int)1));
			t_sample div_4502 = (add_4503 * ((t_sample)0.5));
			t_sample selector_4524 = ((choice_54 >= 5) ? div_4502 : ((choice_54 >= 4) ? gt_4528 : ((choice_54 >= 3) ? mod_4533 : ((choice_54 >= 2) ? triangle_4529 : ((choice_54 >= 1) ? div_4525 : 0)))));
			t_sample mul_4527 = (selector_4524 * m_knob2_width_38);
			t_sample sub_8919 = (mul_4527 - ((int)0));
			t_sample scale_8916 = ((safepow((sub_8919 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_4534 = scale_8916;
			t_sample mtof_4535 = mtof(scale_4534, ((int)440));
			t_sample mul_4519 = (mtof_4535 * div_4520);
			t_sample cos_4517 = cos(mul_4519);
			t_sample mul_4512 = (cos_4517 * (-2));
			t_sample sin_4518 = sin(mul_4519);
			t_sample mul_4516 = (sin_4518 * ((t_sample)0.5));
			t_sample div_4515 = safediv(mul_4516, m_knob3_Q_39);
			t_sample rsub_4510 = (((int)1) - div_4515);
			t_sample add_4514 = (div_4515 + ((int)1));
			t_sample rdiv_4513 = safediv(((int)1), add_4514);
			t_sample mul_4511 = (rdiv_4513 * mul_4512);
			__m_slide_55 = fixdenorm((__m_slide_55 + (((mul_4511 > __m_slide_55) ? iup_56 : idown_57) * (mul_4511 - __m_slide_55))));
			t_sample slide_4507 = __m_slide_55;
			t_sample gen_4521 = slide_4507;
			t_sample mul_4509 = (rdiv_4513 * rsub_4510);
			__m_slide_58 = fixdenorm((__m_slide_58 + (((mul_4509 > __m_slide_58) ? iup_59 : idown_60) * (mul_4509 - __m_slide_58))));
			t_sample slide_4506 = __m_slide_58;
			t_sample gen_4522 = slide_4506;
			t_sample mul_4545 = (gen_4599 * gen_4522);
			t_sample mul_4542 = (m_history_28 * gen_4521);
			t_sample mul_4540 = (m_history_29 * ((int)1));
			t_sample mul_4536 = (m_history_30 * gen_4522);
			t_sample mul_4538 = (m_history_27 * gen_4521);
			t_sample sub_4544 = (((mul_4540 + mul_4542) + mul_4545) - (mul_4538 + mul_4536));
			t_sample gen_4550 = sub_4544;
			t_sample history_4537_next_4546 = fixdenorm(m_history_27);
			t_sample history_4541_next_4547 = fixdenorm(m_history_28);
			t_sample history_4543_next_4548 = fixdenorm(gen_4599);
			t_sample history_4539_next_4549 = fixdenorm(sub_4544);
			t_sample add_4483 = (mod_8250 + div_4606);
			t_sample mod_4484 = safemod(add_4483, ((int)1));
			t_sample triangle_4480 = triangle(mod_4484, ((t_sample)0.5));
			int gt_4479 = (mod_4484 > ((t_sample)0.5));
			__m_cycle_61.phase(mod_4484);
			t_sample cycle_4481 = __m_cycle_61(__sinedata);
			t_sample cycleindex_4482 = __m_cycle_61.phase();
			t_sample add_4477 = (cycle_4481 + ((int)1));
			t_sample div_4476 = (add_4477 * ((t_sample)0.5));
			t_sample noise_4455 = noise();
			t_sample sah_4456 = __m_sah_62(noise_4455, mod_4484, ((t_sample)0.5));
			t_sample add_4454 = (sah_4456 + ((int)1));
			t_sample div_4453 = (add_4454 * ((t_sample)0.5));
			t_sample selector_4475 = ((choice_63 >= 5) ? div_4453 : ((choice_63 >= 4) ? gt_4479 : ((choice_63 >= 3) ? mod_4484 : ((choice_63 >= 2) ? triangle_4480 : ((choice_63 >= 1) ? div_4476 : 0)))));
			t_sample mul_4478 = (selector_4475 * m_knob2_width_38);
			t_sample sub_8923 = (mul_4478 - ((int)0));
			t_sample scale_8920 = ((safepow((sub_8923 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_4485 = scale_8920;
			t_sample mtof_4486 = mtof(scale_4485, ((int)440));
			t_sample mul_4470 = (mtof_4486 * div_4471);
			t_sample cos_4468 = cos(mul_4470);
			t_sample mul_4463 = (cos_4468 * (-2));
			t_sample sin_4469 = sin(mul_4470);
			t_sample mul_4467 = (sin_4469 * ((t_sample)0.5));
			t_sample div_4466 = safediv(mul_4467, m_knob3_Q_39);
			t_sample rsub_4461 = (((int)1) - div_4466);
			t_sample add_4465 = (div_4466 + ((int)1));
			t_sample rdiv_4464 = safediv(((int)1), add_4465);
			t_sample mul_4462 = (rdiv_4464 * mul_4463);
			__m_slide_64 = fixdenorm((__m_slide_64 + (((mul_4462 > __m_slide_64) ? iup_65 : idown_66) * (mul_4462 - __m_slide_64))));
			t_sample slide_4458 = __m_slide_64;
			t_sample gen_4472 = slide_4458;
			t_sample mul_4460 = (rdiv_4464 * rsub_4461);
			__m_slide_67 = fixdenorm((__m_slide_67 + (((mul_4460 > __m_slide_67) ? iup_68 : idown_69) * (mul_4460 - __m_slide_67))));
			t_sample slide_4457 = __m_slide_67;
			t_sample gen_4473 = slide_4457;
			t_sample mul_4496 = (gen_4550 * gen_4473);
			t_sample mul_4493 = (m_history_24 * gen_4472);
			t_sample mul_4491 = (m_history_25 * ((int)1));
			t_sample mul_4487 = (m_history_26 * gen_4473);
			t_sample mul_4489 = (m_history_23 * gen_4472);
			t_sample sub_4495 = (((mul_4491 + mul_4493) + mul_4496) - (mul_4489 + mul_4487));
			t_sample gen_4501 = sub_4495;
			t_sample history_4488_next_4497 = fixdenorm(m_history_23);
			t_sample history_4492_next_4498 = fixdenorm(m_history_24);
			t_sample history_4494_next_4499 = fixdenorm(gen_4550);
			t_sample history_4490_next_4500 = fixdenorm(sub_4495);
			t_sample add_4434 = (mod_8250 + div_4604);
			t_sample mod_4435 = safemod(add_4434, ((int)1));
			t_sample triangle_4431 = triangle(mod_4435, ((t_sample)0.5));
			int gt_4430 = (mod_4435 > ((t_sample)0.5));
			__m_cycle_70.phase(mod_4435);
			t_sample cycle_4432 = __m_cycle_70(__sinedata);
			t_sample cycleindex_4433 = __m_cycle_70.phase();
			t_sample add_4428 = (cycle_4432 + ((int)1));
			t_sample div_4427 = (add_4428 * ((t_sample)0.5));
			t_sample noise_4406 = noise();
			t_sample sah_4407 = __m_sah_71(noise_4406, mod_4435, ((t_sample)0.5));
			t_sample add_4405 = (sah_4407 + ((int)1));
			t_sample div_4404 = (add_4405 * ((t_sample)0.5));
			t_sample selector_4426 = ((choice_72 >= 5) ? div_4404 : ((choice_72 >= 4) ? gt_4430 : ((choice_72 >= 3) ? mod_4435 : ((choice_72 >= 2) ? triangle_4431 : ((choice_72 >= 1) ? div_4427 : 0)))));
			t_sample mul_4429 = (selector_4426 * m_knob2_width_38);
			t_sample sub_8927 = (mul_4429 - ((int)0));
			t_sample scale_8924 = ((safepow((sub_8927 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_4436 = scale_8924;
			t_sample mtof_4437 = mtof(scale_4436, ((int)440));
			t_sample mul_4421 = (mtof_4437 * div_4422);
			t_sample cos_4419 = cos(mul_4421);
			t_sample mul_4414 = (cos_4419 * (-2));
			t_sample sin_4420 = sin(mul_4421);
			t_sample mul_4418 = (sin_4420 * ((t_sample)0.5));
			t_sample div_4417 = safediv(mul_4418, m_knob3_Q_39);
			t_sample rsub_4412 = (((int)1) - div_4417);
			t_sample add_4416 = (div_4417 + ((int)1));
			t_sample rdiv_4415 = safediv(((int)1), add_4416);
			t_sample mul_4411 = (rdiv_4415 * rsub_4412);
			__m_slide_73 = fixdenorm((__m_slide_73 + (((mul_4411 > __m_slide_73) ? iup_74 : idown_75) * (mul_4411 - __m_slide_73))));
			t_sample slide_4408 = __m_slide_73;
			t_sample gen_4424 = slide_4408;
			t_sample mul_4413 = (rdiv_4415 * mul_4414);
			__m_slide_76 = fixdenorm((__m_slide_76 + (((mul_4413 > __m_slide_76) ? iup_77 : idown_78) * (mul_4413 - __m_slide_76))));
			t_sample slide_4409 = __m_slide_76;
			t_sample gen_4423 = slide_4409;
			t_sample mul_4447 = (gen_4501 * gen_4424);
			t_sample mul_4444 = (m_history_20 * gen_4423);
			t_sample mul_4442 = (m_history_22 * ((int)1));
			t_sample mul_4438 = (m_history_21 * gen_4424);
			t_sample mul_4440 = (m_history_19 * gen_4423);
			t_sample sub_4446 = (((mul_4442 + mul_4444) + mul_4447) - (mul_4440 + mul_4438));
			t_sample gen_4452 = sub_4446;
			t_sample history_4443_next_4448 = fixdenorm(m_history_20);
			t_sample history_4439_next_4449 = fixdenorm(m_history_19);
			t_sample history_4445_next_4450 = fixdenorm(gen_4501);
			t_sample history_4441_next_4451 = fixdenorm(sub_4446);
			t_sample dcblock_4600 = __m_dcblock_79(gen_4452);
			t_sample add_4955 = (mul_4822 + gen_4452);
			t_sample dcblock_4954 = __m_dcblock_80(add_4955);
			t_sample add_4953 = (dcblock_4954 + mul_4602);
			t_sample out2 = add_4953;
			t_sample add_4803 = (phasor_4772 + div_4766);
			t_sample mod_4804 = safemod(add_4803, ((int)1));
			t_sample triangle_4800 = triangle(mod_4804, ((t_sample)0.5));
			int gt_4799 = (mod_4804 > ((t_sample)0.5));
			__m_cycle_81.phase(mod_4804);
			t_sample cycle_4801 = __m_cycle_81(__sinedata);
			t_sample cycleindex_4802 = __m_cycle_81.phase();
			t_sample add_4797 = (cycle_4801 + ((int)1));
			t_sample div_4796 = (add_4797 * ((t_sample)0.5));
			t_sample noise_4775 = noise();
			t_sample sah_4776 = __m_sah_82(noise_4775, mod_4804, ((t_sample)0.5));
			t_sample add_4774 = (sah_4776 + ((int)1));
			t_sample div_4773 = (add_4774 * ((t_sample)0.5));
			t_sample selector_4795 = ((choice_83 >= 5) ? div_4773 : ((choice_83 >= 4) ? gt_4799 : ((choice_83 >= 3) ? mod_4804 : ((choice_83 >= 2) ? triangle_4800 : ((choice_83 >= 1) ? div_4796 : 0)))));
			t_sample mul_4798 = (selector_4795 * m_knob2_width_38);
			t_sample sub_8931 = (mul_4798 - ((int)0));
			t_sample scale_8928 = ((safepow((sub_8931 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_4805 = scale_8928;
			t_sample mtof_4806 = mtof(scale_4805, ((int)440));
			t_sample mul_4790 = (mtof_4806 * div_4791);
			t_sample cos_4788 = cos(mul_4790);
			t_sample mul_4783 = (cos_4788 * (-2));
			t_sample sin_4789 = sin(mul_4790);
			t_sample mul_4787 = (sin_4789 * ((t_sample)0.5));
			t_sample div_4786 = safediv(mul_4787, m_knob3_Q_39);
			t_sample rsub_4781 = (((int)1) - div_4786);
			t_sample add_4785 = (div_4786 + ((int)1));
			t_sample rdiv_4784 = safediv(((int)1), add_4785);
			t_sample mul_4780 = (rdiv_4784 * rsub_4781);
			__m_slide_84 = fixdenorm((__m_slide_84 + (((mul_4780 > __m_slide_84) ? iup_85 : idown_86) * (mul_4780 - __m_slide_84))));
			t_sample slide_4777 = __m_slide_84;
			t_sample gen_4793 = slide_4777;
			t_sample mul_4782 = (rdiv_4784 * mul_4783);
			__m_slide_87 = fixdenorm((__m_slide_87 + (((mul_4782 > __m_slide_87) ? iup_88 : idown_89) * (mul_4782 - __m_slide_87))));
			t_sample slide_4778 = __m_slide_87;
			t_sample gen_4792 = slide_4778;
			t_sample mul_4816 = (add_4613 * gen_4793);
			t_sample mul_4813 = (m_history_16 * gen_4792);
			t_sample mul_4811 = (m_history_17 * ((int)1));
			t_sample mul_4807 = (m_history_18 * gen_4793);
			t_sample mul_4809 = (m_history_15 * gen_4792);
			t_sample sub_4815 = (((mul_4811 + mul_4813) + mul_4816) - (mul_4809 + mul_4807));
			t_sample gen_4821 = sub_4815;
			t_sample history_4808_next_4817 = fixdenorm(m_history_15);
			t_sample history_4812_next_4818 = fixdenorm(m_history_16);
			t_sample history_4814_next_4819 = fixdenorm(add_4613);
			t_sample history_4810_next_4820 = fixdenorm(sub_4815);
			t_sample add_4743 = (phasor_4772 + div_4765);
			t_sample mod_4744 = safemod(add_4743, ((int)1));
			t_sample triangle_4740 = triangle(mod_4744, ((t_sample)0.5));
			int gt_4739 = (mod_4744 > ((t_sample)0.5));
			__m_cycle_90.phase(mod_4744);
			t_sample cycle_4741 = __m_cycle_90(__sinedata);
			t_sample cycleindex_4742 = __m_cycle_90.phase();
			t_sample add_4737 = (cycle_4741 + ((int)1));
			t_sample div_4736 = (add_4737 * ((t_sample)0.5));
			t_sample noise_4715 = noise();
			t_sample sah_4716 = __m_sah_91(noise_4715, mod_4744, ((t_sample)0.5));
			t_sample add_4714 = (sah_4716 + ((int)1));
			t_sample div_4713 = (add_4714 * ((t_sample)0.5));
			t_sample selector_4735 = ((choice_92 >= 5) ? div_4713 : ((choice_92 >= 4) ? gt_4739 : ((choice_92 >= 3) ? mod_4744 : ((choice_92 >= 2) ? triangle_4740 : ((choice_92 >= 1) ? div_4736 : 0)))));
			t_sample mul_4738 = (selector_4735 * m_knob2_width_38);
			t_sample sub_8935 = (mul_4738 - ((int)0));
			t_sample scale_8932 = ((safepow((sub_8935 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_4745 = scale_8932;
			t_sample mtof_4746 = mtof(scale_4745, ((int)440));
			t_sample mul_4730 = (mtof_4746 * div_4731);
			t_sample cos_4728 = cos(mul_4730);
			t_sample mul_4723 = (cos_4728 * (-2));
			t_sample sin_4729 = sin(mul_4730);
			t_sample mul_4727 = (sin_4729 * ((t_sample)0.5));
			t_sample div_4726 = safediv(mul_4727, m_knob3_Q_39);
			t_sample rsub_4721 = (((int)1) - div_4726);
			t_sample add_4725 = (div_4726 + ((int)1));
			t_sample rdiv_4724 = safediv(((int)1), add_4725);
			t_sample mul_4722 = (rdiv_4724 * mul_4723);
			__m_slide_93 = fixdenorm((__m_slide_93 + (((mul_4722 > __m_slide_93) ? iup_94 : idown_95) * (mul_4722 - __m_slide_93))));
			t_sample slide_4718 = __m_slide_93;
			t_sample gen_4732 = slide_4718;
			t_sample mul_4720 = (rdiv_4724 * rsub_4721);
			__m_slide_96 = fixdenorm((__m_slide_96 + (((mul_4720 > __m_slide_96) ? iup_97 : idown_98) * (mul_4720 - __m_slide_96))));
			t_sample slide_4717 = __m_slide_96;
			t_sample gen_4733 = slide_4717;
			t_sample mul_4756 = (gen_4821 * gen_4733);
			t_sample mul_4753 = (m_history_12 * gen_4732);
			t_sample mul_4751 = (m_history_13 * ((int)1));
			t_sample mul_4747 = (m_history_14 * gen_4733);
			t_sample mul_4749 = (m_history_11 * gen_4732);
			t_sample sub_4755 = (((mul_4751 + mul_4753) + mul_4756) - (mul_4749 + mul_4747));
			t_sample gen_4761 = sub_4755;
			t_sample history_4748_next_4757 = fixdenorm(m_history_11);
			t_sample history_4752_next_4758 = fixdenorm(m_history_12);
			t_sample history_4754_next_4759 = fixdenorm(gen_4821);
			t_sample history_4750_next_4760 = fixdenorm(sub_4755);
			t_sample add_4694 = (phasor_4772 + div_4764);
			t_sample mod_4695 = safemod(add_4694, ((int)1));
			t_sample triangle_4691 = triangle(mod_4695, ((t_sample)0.5));
			int gt_4690 = (mod_4695 > ((t_sample)0.5));
			__m_cycle_99.phase(mod_4695);
			t_sample cycle_4692 = __m_cycle_99(__sinedata);
			t_sample cycleindex_4693 = __m_cycle_99.phase();
			t_sample add_4688 = (cycle_4692 + ((int)1));
			t_sample div_4687 = (add_4688 * ((t_sample)0.5));
			t_sample noise_4666 = noise();
			t_sample sah_4667 = __m_sah_100(noise_4666, mod_4695, ((t_sample)0.5));
			t_sample add_4665 = (sah_4667 + ((int)1));
			t_sample div_4664 = (add_4665 * ((t_sample)0.5));
			t_sample selector_4686 = ((choice_101 >= 5) ? div_4664 : ((choice_101 >= 4) ? gt_4690 : ((choice_101 >= 3) ? mod_4695 : ((choice_101 >= 2) ? triangle_4691 : ((choice_101 >= 1) ? div_4687 : 0)))));
			t_sample mul_4689 = (selector_4686 * m_knob2_width_38);
			t_sample sub_8939 = (mul_4689 - ((int)0));
			t_sample scale_8936 = ((safepow((sub_8939 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_4696 = scale_8936;
			t_sample mtof_4697 = mtof(scale_4696, ((int)440));
			t_sample mul_4681 = (mtof_4697 * div_4682);
			t_sample cos_4679 = cos(mul_4681);
			t_sample mul_4674 = (cos_4679 * (-2));
			t_sample sin_4680 = sin(mul_4681);
			t_sample mul_4678 = (sin_4680 * ((t_sample)0.5));
			t_sample div_4677 = safediv(mul_4678, m_knob3_Q_39);
			t_sample rsub_4672 = (((int)1) - div_4677);
			t_sample add_4676 = (div_4677 + ((int)1));
			t_sample rdiv_4675 = safediv(((int)1), add_4676);
			t_sample mul_4671 = (rdiv_4675 * rsub_4672);
			__m_slide_102 = fixdenorm((__m_slide_102 + (((mul_4671 > __m_slide_102) ? iup_103 : idown_104) * (mul_4671 - __m_slide_102))));
			t_sample slide_4668 = __m_slide_102;
			t_sample gen_4684 = slide_4668;
			t_sample mul_4673 = (rdiv_4675 * mul_4674);
			__m_slide_105 = fixdenorm((__m_slide_105 + (((mul_4673 > __m_slide_105) ? iup_106 : idown_107) * (mul_4673 - __m_slide_105))));
			t_sample slide_4669 = __m_slide_105;
			t_sample gen_4683 = slide_4669;
			t_sample mul_4707 = (gen_4761 * gen_4684);
			t_sample mul_4704 = (m_history_8 * gen_4683);
			t_sample mul_4702 = (m_history_10 * ((int)1));
			t_sample mul_4698 = (m_history_9 * gen_4684);
			t_sample mul_4700 = (m_history_7 * gen_4683);
			t_sample sub_4706 = (((mul_4702 + mul_4704) + mul_4707) - (mul_4700 + mul_4698));
			t_sample gen_4712 = sub_4706;
			t_sample history_4703_next_4708 = fixdenorm(m_history_8);
			t_sample history_4699_next_4709 = fixdenorm(m_history_7);
			t_sample history_4705_next_4710 = fixdenorm(gen_4761);
			t_sample history_4701_next_4711 = fixdenorm(sub_4706);
			t_sample add_4645 = (phasor_4772 + div_4762);
			t_sample mod_4646 = safemod(add_4645, ((int)1));
			t_sample triangle_4642 = triangle(mod_4646, ((t_sample)0.5));
			int gt_4641 = (mod_4646 > ((t_sample)0.5));
			__m_cycle_108.phase(mod_4646);
			t_sample cycle_4643 = __m_cycle_108(__sinedata);
			t_sample cycleindex_4644 = __m_cycle_108.phase();
			t_sample add_4639 = (cycle_4643 + ((int)1));
			t_sample div_4638 = (add_4639 * ((t_sample)0.5));
			t_sample noise_4617 = noise();
			t_sample sah_4618 = __m_sah_109(noise_4617, mod_4646, ((t_sample)0.5));
			t_sample add_4616 = (sah_4618 + ((int)1));
			t_sample div_4615 = (add_4616 * ((t_sample)0.5));
			t_sample selector_4637 = ((choice_110 >= 5) ? div_4615 : ((choice_110 >= 4) ? gt_4641 : ((choice_110 >= 3) ? mod_4646 : ((choice_110 >= 2) ? triangle_4642 : ((choice_110 >= 1) ? div_4638 : 0)))));
			t_sample mul_4640 = (selector_4637 * m_knob2_width_38);
			t_sample sub_8943 = (mul_4640 - ((int)0));
			t_sample scale_8940 = ((safepow((sub_8943 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_4647 = scale_8940;
			t_sample mtof_4648 = mtof(scale_4647, ((int)440));
			t_sample mul_4632 = (mtof_4648 * div_4633);
			t_sample cos_4630 = cos(mul_4632);
			t_sample mul_4625 = (cos_4630 * (-2));
			t_sample sin_4631 = sin(mul_4632);
			t_sample mul_4629 = (sin_4631 * ((t_sample)0.5));
			t_sample div_4628 = safediv(mul_4629, m_knob3_Q_39);
			t_sample rsub_4623 = (((int)1) - div_4628);
			t_sample add_4627 = (div_4628 + ((int)1));
			t_sample rdiv_4626 = safediv(((int)1), add_4627);
			t_sample mul_4622 = (rdiv_4626 * rsub_4623);
			__m_slide_111 = fixdenorm((__m_slide_111 + (((mul_4622 > __m_slide_111) ? iup_112 : idown_113) * (mul_4622 - __m_slide_111))));
			t_sample slide_4619 = __m_slide_111;
			t_sample gen_4635 = slide_4619;
			t_sample mul_4624 = (rdiv_4626 * mul_4625);
			__m_slide_114 = fixdenorm((__m_slide_114 + (((mul_4624 > __m_slide_114) ? iup_115 : idown_116) * (mul_4624 - __m_slide_114))));
			t_sample slide_4620 = __m_slide_114;
			t_sample gen_4634 = slide_4620;
			t_sample mul_4658 = (gen_4712 * gen_4635);
			t_sample mul_4655 = (m_history_4 * gen_4634);
			t_sample mul_4653 = (m_history_5 * ((int)1));
			t_sample mul_4649 = (m_history_6 * gen_4635);
			t_sample mul_4651 = (m_history_3 * gen_4634);
			t_sample sub_4657 = (((mul_4653 + mul_4655) + mul_4658) - (mul_4651 + mul_4649));
			t_sample gen_4663 = sub_4657;
			t_sample history_4650_next_4659 = fixdenorm(m_history_3);
			t_sample history_4654_next_4660 = fixdenorm(m_history_4);
			t_sample history_4656_next_4661 = fixdenorm(gen_4712);
			t_sample history_4652_next_4662 = fixdenorm(sub_4657);
			t_sample dcblock_5509 = __m_dcblock_117(gen_4663);
			t_sample add_4770 = (mul_4822 + gen_4663);
			t_sample dcblock_4603 = __m_dcblock_118(add_4770);
			t_sample add_4601 = (dcblock_4603 + mul_4602);
			t_sample out1 = add_4601;
			t_sample history_4612_next_8846 = fixdenorm(dcblock_4600);
			t_sample history_5510_next_8847 = fixdenorm(dcblock_5509);
			m_history_34 = history_4586_next_4595;
			m_history_31 = history_4588_next_4598;
			m_history_32 = history_4592_next_4597;
			m_history_33 = history_4590_next_4596;
			m_history_30 = history_4537_next_4546;
			m_history_27 = history_4539_next_4549;
			m_history_28 = history_4543_next_4548;
			m_history_29 = history_4541_next_4547;
			m_history_26 = history_4488_next_4497;
			m_history_23 = history_4490_next_4500;
			m_history_24 = history_4494_next_4499;
			m_history_25 = history_4492_next_4498;
			m_history_22 = history_4443_next_4448;
			m_history_19 = history_4441_next_4451;
			m_history_20 = history_4445_next_4450;
			m_history_21 = history_4439_next_4449;
			m_history_18 = history_4808_next_4817;
			m_history_15 = history_4810_next_4820;
			m_history_16 = history_4814_next_4819;
			m_history_17 = history_4812_next_4818;
			m_history_14 = history_4748_next_4757;
			m_history_11 = history_4750_next_4760;
			m_history_12 = history_4754_next_4759;
			m_history_13 = history_4752_next_4758;
			m_history_10 = history_4703_next_4708;
			m_history_7 = history_4701_next_4711;
			m_history_8 = history_4705_next_4710;
			m_history_9 = history_4699_next_4709;
			m_history_6 = history_4650_next_4659;
			m_history_3 = history_4652_next_4662;
			m_history_4 = history_4656_next_4661;
			m_history_5 = history_4654_next_4660;
			m_history_2 = history_4612_next_8846;
			m_history_1 = history_5510_next_8847;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_knob6_waveform(t_param _value) {
		m_knob6_waveform_35 = (_value < 1 ? 1 : (_value > 4 ? 4 : _value));
	};
	inline void set_knob7_gain(t_param _value) {
		m_knob7_gain_36 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1_rate(t_param _value) {
		m_knob1_rate_37 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2_width(t_param _value) {
		m_knob2_width_38 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_Q(t_param _value) {
		m_knob3_Q_39 = (_value < 1e-06 ? 1e-06 : (_value > 20 ? 20 : _value));
	};
	inline void set_knob5_fb(t_param _value) {
		m_knob5_fb_40 = (_value < 0 ? 0 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_knob4_diffusion(t_param _value) {
		m_knob4_diffusion_41 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 7; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

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
		case 0: self->set_knob1_rate(value); break;
		case 1: self->set_knob2_width(value); break;
		case 2: self->set_knob3_Q(value); break;
		case 3: self->set_knob4_diffusion(value); break;
		case 4: self->set_knob5_fb(value); break;
		case 5: self->set_knob6_waveform(value); break;
		case 6: self->set_knob7_gain(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_rate_37; break;
		case 1: *value = self->m_knob2_width_38; break;
		case 2: *value = self->m_knob3_Q_39; break;
		case 3: *value = self->m_knob4_diffusion_41; break;
		case 4: *value = self->m_knob5_fb_40; break;
		case 5: *value = self->m_knob6_waveform_35; break;
		case 6: *value = self->m_knob7_gain_36; break;
		
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
	// initialize parameter 0 ("m_knob1_rate_37")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_rate_37;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_width_38")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_width";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_width_38;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_Q_39")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_Q";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_Q_39;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1e-06;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_diffusion_41")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_diffusion";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_diffusion_41;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob5_fb_40")
	pi = self->__commonstate.params + 4;
	pi->name = "knob5_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_fb_40;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.95;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_knob6_waveform_35")
	pi = self->__commonstate.params + 5;
	pi->name = "knob6_waveform";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob6_waveform_35;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_knob7_gain_36")
	pi = self->__commonstate.params + 6;
	pi->name = "knob7_gain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob7_gain_36;
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
