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
	DCBlock __m_dcblock_201;
	DCBlock __m_dcblock_157;
	DCBlock __m_dcblock_161;
	DCBlock __m_dcblock_165;
	DCBlock __m_dcblock_153;
	DCBlock __m_dcblock_145;
	DCBlock __m_dcblock_149;
	DCBlock __m_dcblock_141;
	DCBlock __m_dcblock_169;
	DCBlock __m_dcblock_177;
	DCBlock __m_dcblock_193;
	DCBlock __m_dcblock_197;
	DCBlock __m_dcblock_173;
	DCBlock __m_dcblock_189;
	DCBlock __m_dcblock_181;
	DCBlock __m_dcblock_185;
	Sah __m_sah_136;
	int __exception;
	int vectorsize;
	t_sample m_x_16;
	t_sample m_y_117;
	t_sample m_y_118;
	t_sample m_x_116;
	t_sample m_x_115;
	t_sample m_y_114;
	t_sample m_x_119;
	t_sample m_y_113;
	t_sample m_x_112;
	t_sample m_x_120;
	t_sample m_y_122;
	t_sample m_y_126;
	t_sample m_x_127;
	t_sample m_y_121;
	t_sample m_y_125;
	t_sample m_x_123;
	t_sample m_x_124;
	t_sample m_x_111;
	t_sample m_y_110;
	t_sample m_y_109;
	t_sample m_y_98;
	t_sample m_x_99;
	t_sample m_x_100;
	t_sample m_y_97;
	t_sample m_x_95;
	t_sample m_x_96;
	t_sample m_y_94;
	t_sample m_x_128;
	t_sample m_y_101;
	t_sample m_x_103;
	t_sample m_x_107;
	t_sample m_x_108;
	t_sample m_y_102;
	t_sample m_y_106;
	t_sample m_x_104;
	t_sample m_y_105;
	t_sample m_history_129;
	t_sample m_history_130;
	t_sample m_history_131;
	t_sample __m_slide_174;
	t_sample m_x_4;
	t_sample __m_slide_178;
	t_sample m_y_5;
	t_sample m_y_6;
	t_sample __m_slide_170;
	t_sample __m_slide_166;
	t_sample m_x_7;
	t_sample m_x_3;
	t_sample m_y_2;
	t_sample samplerate;
	t_sample __m_slide_194;
	t_sample __m_slide_182;
	t_sample __m_slide_190;
	t_sample __m_slide_186;
	t_sample m_y_1;
	t_sample m_y_93;
	t_sample __m_slide_162;
	t_sample __m_slide_158;
	t_sample m_y_14;
	t_sample __m_slide_138;
	t_sample m_y_13;
	t_sample m_sw_135;
	t_sample m_knob4_gain_133;
	t_sample m_knob3_res_134;
	t_sample m_history_132;
	t_sample m_x_8;
	t_sample __m_slide_142;
	t_sample __m_slide_146;
	t_sample __m_slide_154;
	t_sample m_y_9;
	t_sample m_x_12;
	t_sample m_y_10;
	t_sample m_x_11;
	t_sample __m_slide_150;
	t_sample m_x_15;
	t_sample m_x_92;
	t_sample m_y_90;
	t_sample m_x_40;
	t_sample m_y_41;
	t_sample m_y_42;
	t_sample m_x_39;
	t_sample m_y_37;
	t_sample m_y_38;
	t_sample m_x_36;
	t_sample m_x_35;
	t_sample m_x_43;
	t_sample m_y_45;
	t_sample m_y_50;
	t_sample m_x_51;
	t_sample m_x_44;
	t_sample m_y_49;
	t_sample m_x_47;
	t_sample m_x_48;
	t_sample m_y_46;
	t_sample m_x_52;
	t_sample m_y_34;
	t_sample m_x_32;
	t_sample m_y_21;
	t_sample m_y_22;
	t_sample m_x_23;
	t_sample m_x_20;
	t_sample m_y_18;
	t_sample m_x_19;
	t_sample m_y_17;
	t_sample m_y_33;
	t_sample m_x_24;
	t_sample m_y_26;
	t_sample m_y_30;
	t_sample m_x_31;
	t_sample m_y_25;
	t_sample m_y_29;
	t_sample m_x_27;
	t_sample m_x_28;
	t_sample m_x_91;
	t_sample m_y_53;
	t_sample m_x_55;
	t_sample m_x_79;
	t_sample m_x_80;
	t_sample m_y_81;
	t_sample m_y_78;
	t_sample m_x_76;
	t_sample m_y_77;
	t_sample m_x_75;
	t_sample m_y_74;
	t_sample m_y_82;
	t_sample m_x_84;
	t_sample m_x_88;
	t_sample m_y_89;
	t_sample __m_slide_198;
	t_sample m_x_87;
	t_sample m_y_85;
	t_sample m_y_86;
	t_sample m_y_54;
	t_sample m_y_73;
	t_sample m_x_71;
	t_sample m_x_60;
	t_sample m_y_61;
	t_sample m_y_62;
	t_sample m_x_59;
	t_sample m_y_57;
	t_sample m_y_58;
	t_sample m_x_56;
	t_sample m_x_72;
	t_sample m_x_63;
	t_sample m_y_65;
	t_sample m_y_69;
	t_sample m_y_70;
	t_sample m_x_64;
	t_sample m_x_68;
	t_sample m_y_66;
	t_sample m_x_67;
	t_sample m_x_83;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_y_1 = ((int)0);
		m_y_2 = ((int)0);
		m_x_3 = ((int)0);
		m_x_4 = ((int)0);
		m_y_5 = ((int)0);
		m_y_6 = ((int)0);
		m_x_7 = ((int)0);
		m_x_8 = ((int)0);
		m_y_9 = ((int)0);
		m_y_10 = ((int)0);
		m_x_11 = ((int)0);
		m_x_12 = ((int)0);
		m_y_13 = ((int)0);
		m_y_14 = ((int)0);
		m_x_15 = ((int)0);
		m_x_16 = ((int)0);
		m_y_17 = ((int)0);
		m_y_18 = ((int)0);
		m_x_19 = ((int)0);
		m_x_20 = ((int)0);
		m_y_21 = ((int)0);
		m_y_22 = ((int)0);
		m_x_23 = ((int)0);
		m_x_24 = ((int)0);
		m_y_25 = ((int)0);
		m_y_26 = ((int)0);
		m_x_27 = ((int)0);
		m_x_28 = ((int)0);
		m_y_29 = ((int)0);
		m_y_30 = ((int)0);
		m_x_31 = ((int)0);
		m_x_32 = ((int)0);
		m_y_33 = ((int)0);
		m_y_34 = ((int)0);
		m_x_35 = ((int)0);
		m_x_36 = ((int)0);
		m_y_37 = ((int)0);
		m_y_38 = ((int)0);
		m_x_39 = ((int)0);
		m_x_40 = ((int)0);
		m_y_41 = ((int)0);
		m_y_42 = ((int)0);
		m_x_43 = ((int)0);
		m_x_44 = ((int)0);
		m_y_45 = ((int)0);
		m_y_46 = ((int)0);
		m_x_47 = ((int)0);
		m_x_48 = ((int)0);
		m_y_49 = ((int)0);
		m_y_50 = ((int)0);
		m_x_51 = ((int)0);
		m_x_52 = ((int)0);
		m_y_53 = ((int)0);
		m_y_54 = ((int)0);
		m_x_55 = ((int)0);
		m_x_56 = ((int)0);
		m_y_57 = ((int)0);
		m_y_58 = ((int)0);
		m_x_59 = ((int)0);
		m_x_60 = ((int)0);
		m_y_61 = ((int)0);
		m_y_62 = ((int)0);
		m_x_63 = ((int)0);
		m_x_64 = ((int)0);
		m_y_65 = ((int)0);
		m_y_66 = ((int)0);
		m_x_67 = ((int)0);
		m_x_68 = ((int)0);
		m_y_69 = ((int)0);
		m_y_70 = ((int)0);
		m_x_71 = ((int)0);
		m_x_72 = ((int)0);
		m_y_73 = ((int)0);
		m_y_74 = ((int)0);
		m_x_75 = ((int)0);
		m_x_76 = ((int)0);
		m_y_77 = ((int)0);
		m_y_78 = ((int)0);
		m_x_79 = ((int)0);
		m_x_80 = ((int)0);
		m_y_81 = ((int)0);
		m_y_82 = ((int)0);
		m_x_83 = ((int)0);
		m_x_84 = ((int)0);
		m_y_85 = ((int)0);
		m_y_86 = ((int)0);
		m_x_87 = ((int)0);
		m_x_88 = ((int)0);
		m_y_89 = ((int)0);
		m_y_90 = ((int)0);
		m_x_91 = ((int)0);
		m_x_92 = ((int)0);
		m_y_93 = ((int)0);
		m_y_94 = ((int)0);
		m_x_95 = ((int)0);
		m_x_96 = ((int)0);
		m_y_97 = ((int)0);
		m_y_98 = ((int)0);
		m_x_99 = ((int)0);
		m_x_100 = ((int)0);
		m_y_101 = ((int)0);
		m_y_102 = ((int)0);
		m_x_103 = ((int)0);
		m_x_104 = ((int)0);
		m_y_105 = ((int)0);
		m_y_106 = ((int)0);
		m_x_107 = ((int)0);
		m_x_108 = ((int)0);
		m_y_109 = ((int)0);
		m_y_110 = ((int)0);
		m_x_111 = ((int)0);
		m_x_112 = ((int)0);
		m_y_113 = ((int)0);
		m_y_114 = ((int)0);
		m_x_115 = ((int)0);
		m_x_116 = ((int)0);
		m_y_117 = ((int)0);
		m_y_118 = ((int)0);
		m_x_119 = ((int)0);
		m_x_120 = ((int)0);
		m_y_121 = ((int)0);
		m_y_122 = ((int)0);
		m_x_123 = ((int)0);
		m_x_124 = ((int)0);
		m_y_125 = ((int)0);
		m_y_126 = ((int)0);
		m_x_127 = ((int)0);
		m_x_128 = ((int)0);
		m_history_129 = ((int)0);
		m_history_130 = ((int)0);
		m_history_131 = ((int)0);
		m_history_132 = ((int)0);
		m_knob4_gain_133 = 5;
		m_knob3_res_134 = 15;
		m_sw_135 = ((int)0);
		__m_sah_136.reset(0);
		__m_slide_138 = 0;
		__m_dcblock_141.reset();
		__m_slide_142 = 0;
		__m_dcblock_145.reset();
		__m_slide_146 = 0;
		__m_dcblock_149.reset();
		__m_slide_150 = 0;
		__m_dcblock_153.reset();
		__m_slide_154 = 0;
		__m_dcblock_157.reset();
		__m_slide_158 = 0;
		__m_dcblock_161.reset();
		__m_slide_162 = 0;
		__m_dcblock_165.reset();
		__m_slide_166 = 0;
		__m_dcblock_169.reset();
		__m_slide_170 = 0;
		__m_dcblock_173.reset();
		__m_slide_174 = 0;
		__m_dcblock_177.reset();
		__m_slide_178 = 0;
		__m_dcblock_181.reset();
		__m_slide_182 = 0;
		__m_dcblock_185.reset();
		__m_slide_186 = 0;
		__m_dcblock_189.reset();
		__m_slide_190 = 0;
		__m_dcblock_193.reset();
		__m_slide_194 = 0;
		__m_dcblock_197.reset();
		__m_slide_198 = 0;
		__m_dcblock_201.reset();
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		t_sample * __out5 = __outs[4];
		t_sample * __out6 = __outs[5];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample mstosamps_378 = (((int)2) * (samplerate * 0.001));
		t_sample mstosamps_470 = (((int)20) * (samplerate * 0.001));
		t_sample twopi_over_sr = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_320 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_139 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_140 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_1891 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_296 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_143 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_144 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_1908 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_270 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_147 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_148 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_1923 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_245 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_151 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_152 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_1945 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_220 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_155 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_156 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_1961 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_196 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_159 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_160 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_1970 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_170 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_163 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_164 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_1988 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_145 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_167 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_168 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_2006 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_120 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_171 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_172 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_2024 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_95 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_175 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_176 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_2041 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_70 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_179 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_180 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_2060 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_45 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_183 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_184 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_2078 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_20 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_187 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_188 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_2094 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_441 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_191 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_192 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_2112 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_370 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_195 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_196 = (1 / maximum(1, abs(mstosamps_470)));
		t_sample twopi_over_sr_2130 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample twopi_over_sr_345 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_199 = (1 / maximum(1, abs(mstosamps_378)));
		t_sample idown_200 = (1 / maximum(1, abs(mstosamps_470)));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out4 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample sah_477 = __m_sah_136(m_history_132, m_sw_135, ((int)0));
			t_sample gen_479 = sah_477;
			t_sample rsub_475 = (((int)1) - sah_477);
			t_sample history_476_next_478 = fixdenorm(rsub_475);
			t_sample out3 = gen_479;
			t_sample add_480 = (gen_479 + ((int)1));
			t_sample choice_137 = int(add_480);
			t_sample gate_472 = (((choice_137 >= 1) && (choice_137 < 2)) ? in1 : 0);
			t_sample gate_473 = ((choice_137 >= 2) ? in1 : 0);
			t_sample mix_2154 = (m_history_131 + (((t_sample)0.0042742627044161) * (m_knob3_res_134 - m_history_131)));
			t_sample mix_460 = mix_2154;
			t_sample mix_2155 = (m_history_130 + (((t_sample)0.0042742627044161) * (mix_460 - m_history_130)));
			t_sample mix_458 = mix_2155;
			t_sample mix_2156 = (m_history_129 + (((t_sample)0.0042742627044161) * (mix_458 - m_history_129)));
			t_sample mix_456 = mix_2156;
			t_sample gen_468 = mix_456;
			t_sample history_462_next_465 = fixdenorm(mix_460);
			t_sample history_459_next_466 = fixdenorm(mix_458);
			t_sample history_457_next_467 = fixdenorm(mix_456);
			t_sample x = gate_473;
			t_sample q = gen_468;
			t_sample bw = safediv(((t_sample)284.5), q);
			t_sample r = exp(((-bw) * twopi_over_sr));
			t_sample c1 = ((((int)2) * r) * cos((((t_sample)284.5) * twopi_over_sr)));
			t_sample c2 = ((-r) * r);
			t_sample y = ((((((int)1) - r) * (x - (r * m_x_127))) + (c1 * m_y_126)) + (c2 * m_y_125));
			m_y_125 = m_y_126;
			m_y_126 = y;
			m_x_127 = m_x_128;
			m_x_128 = x;
			t_sample x_316 = in2;
			t_sample q_309 = gen_468;
			t_sample bw_317 = safediv(((t_sample)284.5), q_309);
			t_sample r_310 = exp(((-bw_317) * twopi_over_sr_320));
			t_sample c_319 = ((((int)2) * r_310) * cos((((t_sample)284.5) * twopi_over_sr_320)));
			t_sample c_322 = ((-r_310) * r_310);
			t_sample y_321 = ((((((int)1) - r_310) * (x_316 - (r_310 * m_x_123))) + (c_319 * m_y_122)) + (c_322 * m_y_121));
			m_y_121 = m_y_122;
			m_y_122 = y_321;
			m_x_123 = m_x_124;
			m_x_124 = x_316;
			t_sample abs_308 = fabs(y_321);
			__m_slide_138 = fixdenorm((__m_slide_138 + (((abs_308 > __m_slide_138) ? iup_139 : idown_140) * (abs_308 - __m_slide_138))));
			t_sample slide_307 = __m_slide_138;
			t_sample mul_304 = (y * slide_307);
			t_sample dcblock_303 = __m_dcblock_141(mul_304);
			t_sample x_1883 = gate_473;
			t_sample q_1880 = gen_468;
			t_sample bw_1884 = safediv(((t_sample)358.5), q_1880);
			t_sample r_1881 = exp(((-bw_1884) * twopi_over_sr_1891));
			t_sample c_1886 = ((((int)2) * r_1881) * cos((((t_sample)358.5) * twopi_over_sr_1891)));
			t_sample c_1879 = ((-r_1881) * r_1881);
			t_sample y_1882 = ((((((int)1) - r_1881) * (x_1883 - (r_1881 * m_x_119))) + (c_1886 * m_y_118)) + (c_1879 * m_y_117));
			m_y_117 = m_y_118;
			m_y_118 = y_1882;
			m_x_119 = m_x_120;
			m_x_120 = x_1883;
			t_sample x_292 = in2;
			t_sample q_284 = gen_468;
			t_sample bw_293 = safediv(((t_sample)358.5), q_284);
			t_sample r_286 = exp(((-bw_293) * twopi_over_sr_296));
			t_sample c_295 = ((((int)2) * r_286) * cos((((t_sample)358.5) * twopi_over_sr_296)));
			t_sample c_297 = ((-r_286) * r_286);
			t_sample y_285 = ((((((int)1) - r_286) * (x_292 - (r_286 * m_x_115))) + (c_295 * m_y_114)) + (c_297 * m_y_113));
			m_y_113 = m_y_114;
			m_y_114 = y_285;
			m_x_115 = m_x_116;
			m_x_116 = x_292;
			t_sample abs_283 = fabs(y_285);
			__m_slide_142 = fixdenorm((__m_slide_142 + (((abs_283 > __m_slide_142) ? iup_143 : idown_144) * (abs_283 - __m_slide_142))));
			t_sample slide_282 = __m_slide_142;
			t_sample mul_279 = (y_1882 * slide_282);
			t_sample dcblock_278 = __m_dcblock_145(mul_279);
			t_sample x_1900 = gate_473;
			t_sample q_1897 = gen_468;
			t_sample bw_1901 = safediv(((int)452), q_1897);
			t_sample r_1898 = exp(((-bw_1901) * twopi_over_sr_1908));
			t_sample c_1903 = ((((int)2) * r_1898) * cos((((int)452) * twopi_over_sr_1908)));
			t_sample c_1904 = ((-r_1898) * r_1898);
			t_sample y_1899 = ((((((int)1) - r_1898) * (x_1900 - (r_1898 * m_x_111))) + (c_1903 * m_y_110)) + (c_1904 * m_y_109));
			m_y_109 = m_y_110;
			m_y_110 = y_1899;
			m_x_111 = m_x_112;
			m_x_112 = x_1900;
			t_sample x_266 = in2;
			t_sample q_259 = gen_468;
			t_sample bw_267 = safediv(((int)452), q_259);
			t_sample r_260 = exp(((-bw_267) * twopi_over_sr_270));
			t_sample c_269 = ((((int)2) * r_260) * cos((((int)452) * twopi_over_sr_270)));
			t_sample c_272 = ((-r_260) * r_260);
			t_sample y_271 = ((((((int)1) - r_260) * (x_266 - (r_260 * m_x_107))) + (c_269 * m_y_106)) + (c_272 * m_y_105));
			m_y_105 = m_y_106;
			m_y_106 = y_271;
			m_x_107 = m_x_108;
			m_x_108 = x_266;
			t_sample abs_258 = fabs(y_271);
			__m_slide_146 = fixdenorm((__m_slide_146 + (((abs_258 > __m_slide_146) ? iup_147 : idown_148) * (abs_258 - __m_slide_146))));
			t_sample slide_257 = __m_slide_146;
			t_sample mul_254 = (y_1899 * slide_257);
			t_sample dcblock_253 = __m_dcblock_149(mul_254);
			t_sample x_1920 = gate_473;
			t_sample q_1924 = gen_468;
			t_sample bw_1921 = safediv(((t_sample)569.5), q_1924);
			t_sample r_1918 = exp(((-bw_1921) * twopi_over_sr_1923));
			t_sample c_1922 = ((((int)2) * r_1918) * cos((((t_sample)569.5) * twopi_over_sr_1923)));
			t_sample c_1914 = ((-r_1918) * r_1918);
			t_sample y_1919 = ((((((int)1) - r_1918) * (x_1920 - (r_1918 * m_x_103))) + (c_1922 * m_y_102)) + (c_1914 * m_y_101));
			m_y_101 = m_y_102;
			m_y_102 = y_1919;
			m_x_103 = m_x_104;
			m_x_104 = x_1920;
			t_sample x_241 = in2;
			t_sample q_234 = gen_468;
			t_sample bw_242 = safediv(((t_sample)569.5), q_234);
			t_sample r_235 = exp(((-bw_242) * twopi_over_sr_245));
			t_sample c_244 = ((((int)2) * r_235) * cos((((t_sample)569.5) * twopi_over_sr_245)));
			t_sample c_247 = ((-r_235) * r_235);
			t_sample y_246 = ((((((int)1) - r_235) * (x_241 - (r_235 * m_x_99))) + (c_244 * m_y_98)) + (c_247 * m_y_97));
			m_y_97 = m_y_98;
			m_y_98 = y_246;
			m_x_99 = m_x_100;
			m_x_100 = x_241;
			t_sample abs_233 = fabs(y_246);
			__m_slide_150 = fixdenorm((__m_slide_150 + (((abs_233 > __m_slide_150) ? iup_151 : idown_152) * (abs_233 - __m_slide_150))));
			t_sample slide_232 = __m_slide_150;
			t_sample mul_229 = (y_1919 * slide_232);
			t_sample dcblock_228 = __m_dcblock_153(mul_229);
			t_sample x_1936 = gate_473;
			t_sample q_1942 = gen_468;
			t_sample bw_1937 = safediv(((t_sample)717.5), q_1942);
			t_sample r_1934 = exp(((-bw_1937) * twopi_over_sr_1945));
			t_sample c_1939 = ((((int)2) * r_1934) * cos((((t_sample)717.5) * twopi_over_sr_1945)));
			t_sample c_1932 = ((-r_1934) * r_1934);
			t_sample y_1935 = ((((((int)1) - r_1934) * (x_1936 - (r_1934 * m_x_95))) + (c_1939 * m_y_94)) + (c_1932 * m_y_93));
			m_y_93 = m_y_94;
			m_y_94 = y_1935;
			m_x_95 = m_x_96;
			m_x_96 = x_1936;
			t_sample x_216 = in2;
			t_sample q_209 = gen_468;
			t_sample bw_217 = safediv(((t_sample)717.5), q_209);
			t_sample r_210 = exp(((-bw_217) * twopi_over_sr_220));
			t_sample c_219 = ((((int)2) * r_210) * cos((((t_sample)717.5) * twopi_over_sr_220)));
			t_sample c_222 = ((-r_210) * r_210);
			t_sample y_221 = ((((((int)1) - r_210) * (x_216 - (r_210 * m_x_91))) + (c_219 * m_y_90)) + (c_222 * m_y_89));
			m_y_89 = m_y_90;
			m_y_90 = y_221;
			m_x_91 = m_x_92;
			m_x_92 = x_216;
			t_sample abs_208 = fabs(y_221);
			__m_slide_154 = fixdenorm((__m_slide_154 + (((abs_208 > __m_slide_154) ? iup_155 : idown_156) * (abs_208 - __m_slide_154))));
			t_sample slide_207 = __m_slide_154;
			t_sample mul_204 = (y_1935 * slide_207);
			t_sample dcblock_203 = __m_dcblock_157(mul_204);
			t_sample x_1954 = gate_473;
			t_sample q_1959 = gen_468;
			t_sample bw_1955 = safediv(((int)904), q_1959);
			t_sample r_1952 = exp(((-bw_1955) * twopi_over_sr_1961));
			t_sample c_1957 = ((((int)2) * r_1952) * cos((((int)904) * twopi_over_sr_1961)));
			t_sample c_1950 = ((-r_1952) * r_1952);
			t_sample y_1953 = ((((((int)1) - r_1952) * (x_1954 - (r_1952 * m_x_87))) + (c_1957 * m_y_86)) + (c_1950 * m_y_85));
			m_y_85 = m_y_86;
			m_y_86 = y_1953;
			m_x_87 = m_x_88;
			m_x_88 = x_1954;
			t_sample x_192 = in2;
			t_sample q_184 = gen_468;
			t_sample bw_193 = safediv(((int)904), q_184);
			t_sample r_186 = exp(((-bw_193) * twopi_over_sr_196));
			t_sample c_195 = ((((int)2) * r_186) * cos((((int)904) * twopi_over_sr_196)));
			t_sample c_197 = ((-r_186) * r_186);
			t_sample y_185 = ((((((int)1) - r_186) * (x_192 - (r_186 * m_x_83))) + (c_195 * m_y_82)) + (c_197 * m_y_81));
			m_y_81 = m_y_82;
			m_y_82 = y_185;
			m_x_83 = m_x_84;
			m_x_84 = x_192;
			t_sample abs_183 = fabs(y_185);
			__m_slide_158 = fixdenorm((__m_slide_158 + (((abs_183 > __m_slide_158) ? iup_159 : idown_160) * (abs_183 - __m_slide_158))));
			t_sample slide_182 = __m_slide_158;
			t_sample mul_179 = (y_1953 * slide_182);
			t_sample dcblock_178 = __m_dcblock_161(mul_179);
			t_sample x_1980 = gate_473;
			t_sample q_1973 = gen_468;
			t_sample bw_1978 = safediv(((int)1139), q_1973);
			t_sample r_1979 = exp(((-bw_1978) * twopi_over_sr_1970));
			t_sample c_1975 = ((((int)2) * r_1979) * cos((((int)1139) * twopi_over_sr_1970)));
			t_sample c_1968 = ((-r_1979) * r_1979);
			t_sample y_1974 = ((((((int)1) - r_1979) * (x_1980 - (r_1979 * m_x_79))) + (c_1975 * m_y_78)) + (c_1968 * m_y_77));
			m_y_77 = m_y_78;
			m_y_78 = y_1974;
			m_x_79 = m_x_80;
			m_x_80 = x_1980;
			t_sample x_166 = in2;
			t_sample q_159 = gen_468;
			t_sample bw_167 = safediv(((int)1139), q_159);
			t_sample r_160 = exp(((-bw_167) * twopi_over_sr_170));
			t_sample c_169 = ((((int)2) * r_160) * cos((((int)1139) * twopi_over_sr_170)));
			t_sample c_172 = ((-r_160) * r_160);
			t_sample y_171 = ((((((int)1) - r_160) * (x_166 - (r_160 * m_x_75))) + (c_169 * m_y_74)) + (c_172 * m_y_73));
			m_y_73 = m_y_74;
			m_y_74 = y_171;
			m_x_75 = m_x_76;
			m_x_76 = x_166;
			t_sample abs_158 = fabs(y_171);
			__m_slide_162 = fixdenorm((__m_slide_162 + (((abs_158 > __m_slide_162) ? iup_163 : idown_164) * (abs_158 - __m_slide_162))));
			t_sample slide_157 = __m_slide_162;
			t_sample mul_154 = (y_1974 * slide_157);
			t_sample dcblock_153 = __m_dcblock_165(mul_154);
			t_sample x_1999 = gate_473;
			t_sample q_1991 = gen_468;
			t_sample bw_1997 = safediv(((int)1435), q_1991);
			t_sample r_1996 = exp(((-bw_1997) * twopi_over_sr_1988));
			t_sample c_1993 = ((((int)2) * r_1996) * cos((((int)1435) * twopi_over_sr_1988)));
			t_sample c_1986 = ((-r_1996) * r_1996);
			t_sample y_1992 = ((((((int)1) - r_1996) * (x_1999 - (r_1996 * m_x_71))) + (c_1993 * m_y_70)) + (c_1986 * m_y_69));
			m_y_69 = m_y_70;
			m_y_70 = y_1992;
			m_x_71 = m_x_72;
			m_x_72 = x_1999;
			t_sample x_141 = in2;
			t_sample q_134 = gen_468;
			t_sample bw_142 = safediv(((int)1435), q_134);
			t_sample r_135 = exp(((-bw_142) * twopi_over_sr_145));
			t_sample c_144 = ((((int)2) * r_135) * cos((((int)1435) * twopi_over_sr_145)));
			t_sample c_147 = ((-r_135) * r_135);
			t_sample y_146 = ((((((int)1) - r_135) * (x_141 - (r_135 * m_x_67))) + (c_144 * m_y_66)) + (c_147 * m_y_65));
			m_y_65 = m_y_66;
			m_y_66 = y_146;
			m_x_67 = m_x_68;
			m_x_68 = x_141;
			t_sample abs_133 = fabs(y_146);
			__m_slide_166 = fixdenorm((__m_slide_166 + (((abs_133 > __m_slide_166) ? iup_167 : idown_168) * (abs_133 - __m_slide_166))));
			t_sample slide_132 = __m_slide_166;
			t_sample mul_129 = (y_1992 * slide_132);
			t_sample dcblock_128 = __m_dcblock_169(mul_129);
			t_sample x_2017 = gate_473;
			t_sample q_2009 = gen_468;
			t_sample bw_2015 = safediv(((int)1808), q_2009);
			t_sample r_2010 = exp(((-bw_2015) * twopi_over_sr_2006));
			t_sample c_2012 = ((((int)2) * r_2010) * cos((((int)1808) * twopi_over_sr_2006)));
			t_sample c_2004 = ((-r_2010) * r_2010);
			t_sample y_2011 = ((((((int)1) - r_2010) * (x_2017 - (r_2010 * m_x_63))) + (c_2012 * m_y_62)) + (c_2004 * m_y_61));
			m_y_61 = m_y_62;
			m_y_62 = y_2011;
			m_x_63 = m_x_64;
			m_x_64 = x_2017;
			t_sample x_116 = in2;
			t_sample q_109 = gen_468;
			t_sample bw_117 = safediv(((int)1808), q_109);
			t_sample r_110 = exp(((-bw_117) * twopi_over_sr_120));
			t_sample c_119 = ((((int)2) * r_110) * cos((((int)1808) * twopi_over_sr_120)));
			t_sample c_122 = ((-r_110) * r_110);
			t_sample y_121 = ((((((int)1) - r_110) * (x_116 - (r_110 * m_x_59))) + (c_119 * m_y_58)) + (c_122 * m_y_57));
			m_y_57 = m_y_58;
			m_y_58 = y_121;
			m_x_59 = m_x_60;
			m_x_60 = x_116;
			t_sample abs_108 = fabs(y_121);
			__m_slide_170 = fixdenorm((__m_slide_170 + (((abs_108 > __m_slide_170) ? iup_171 : idown_172) * (abs_108 - __m_slide_170))));
			t_sample slide_107 = __m_slide_170;
			t_sample mul_104 = (y_2011 * slide_107);
			t_sample dcblock_103 = __m_dcblock_173(mul_104);
			t_sample x_2032 = gate_473;
			t_sample q_2027 = gen_468;
			t_sample bw_2034 = safediv(((int)2260), q_2027);
			t_sample r_2028 = exp(((-bw_2034) * twopi_over_sr_2024));
			t_sample c_2029 = ((((int)2) * r_2028) * cos((((int)2260) * twopi_over_sr_2024)));
			t_sample c_2022 = ((-r_2028) * r_2028);
			t_sample y_2033 = ((((((int)1) - r_2028) * (x_2032 - (r_2028 * m_x_55))) + (c_2029 * m_y_54)) + (c_2022 * m_y_53));
			m_y_53 = m_y_54;
			m_y_54 = y_2033;
			m_x_55 = m_x_56;
			m_x_56 = x_2032;
			t_sample x_91 = in2;
			t_sample q_84 = gen_468;
			t_sample bw_92 = safediv(((int)2260), q_84);
			t_sample r_85 = exp(((-bw_92) * twopi_over_sr_95));
			t_sample c_94 = ((((int)2) * r_85) * cos((((int)2260) * twopi_over_sr_95)));
			t_sample c_97 = ((-r_85) * r_85);
			t_sample y_96 = ((((((int)1) - r_85) * (x_91 - (r_85 * m_x_51))) + (c_94 * m_y_50)) + (c_97 * m_y_49));
			m_y_49 = m_y_50;
			m_y_50 = y_96;
			m_x_51 = m_x_52;
			m_x_52 = x_91;
			t_sample abs_83 = fabs(y_96);
			__m_slide_174 = fixdenorm((__m_slide_174 + (((abs_83 > __m_slide_174) ? iup_175 : idown_176) * (abs_83 - __m_slide_174))));
			t_sample slide_82 = __m_slide_174;
			t_sample mul_79 = (y_2033 * slide_82);
			t_sample dcblock_78 = __m_dcblock_177(mul_79);
			t_sample x_2049 = gate_473;
			t_sample q_2043 = gen_468;
			t_sample bw_2050 = safediv(((int)2852), q_2043);
			t_sample r_2044 = exp(((-bw_2050) * twopi_over_sr_2041));
			t_sample c_2046 = ((((int)2) * r_2044) * cos((((int)2852) * twopi_over_sr_2041)));
			t_sample c_2053 = ((-r_2044) * r_2044);
			t_sample y_2045 = ((((((int)1) - r_2044) * (x_2049 - (r_2044 * m_x_47))) + (c_2046 * m_y_46)) + (c_2053 * m_y_45));
			m_y_45 = m_y_46;
			m_y_46 = y_2045;
			m_x_47 = m_x_48;
			m_x_48 = x_2049;
			t_sample x_66 = in2;
			t_sample q_59 = gen_468;
			t_sample bw_67 = safediv(((int)2852), q_59);
			t_sample r_60 = exp(((-bw_67) * twopi_over_sr_70));
			t_sample c_69 = ((((int)2) * r_60) * cos((((int)2852) * twopi_over_sr_70)));
			t_sample c_72 = ((-r_60) * r_60);
			t_sample y_71 = ((((((int)1) - r_60) * (x_66 - (r_60 * m_x_43))) + (c_69 * m_y_42)) + (c_72 * m_y_41));
			m_y_41 = m_y_42;
			m_y_42 = y_71;
			m_x_43 = m_x_44;
			m_x_44 = x_66;
			t_sample abs_58 = fabs(y_71);
			__m_slide_178 = fixdenorm((__m_slide_178 + (((abs_58 > __m_slide_178) ? iup_179 : idown_180) * (abs_58 - __m_slide_178))));
			t_sample slide_57 = __m_slide_178;
			t_sample mul_54 = (y_2045 * slide_57);
			t_sample dcblock_53 = __m_dcblock_181(mul_54);
			t_sample x_2065 = gate_473;
			t_sample q_2063 = gen_468;
			t_sample bw_2070 = safediv(((int)3616), q_2063);
			t_sample r_2064 = exp(((-bw_2070) * twopi_over_sr_2060));
			t_sample c_2067 = ((((int)2) * r_2064) * cos((((int)3616) * twopi_over_sr_2060)));
			t_sample c_2058 = ((-r_2064) * r_2064);
			t_sample y_2066 = ((((((int)1) - r_2064) * (x_2065 - (r_2064 * m_x_39))) + (c_2067 * m_y_38)) + (c_2058 * m_y_37));
			m_y_37 = m_y_38;
			m_y_38 = y_2066;
			m_x_39 = m_x_40;
			m_x_40 = x_2065;
			t_sample x_41 = in2;
			t_sample q_34 = gen_468;
			t_sample bw_42 = safediv(((int)3616), q_34);
			t_sample r_35 = exp(((-bw_42) * twopi_over_sr_45));
			t_sample c_44 = ((((int)2) * r_35) * cos((((int)3616) * twopi_over_sr_45)));
			t_sample c_47 = ((-r_35) * r_35);
			t_sample y_46 = ((((((int)1) - r_35) * (x_41 - (r_35 * m_x_35))) + (c_44 * m_y_34)) + (c_47 * m_y_33));
			m_y_33 = m_y_34;
			m_y_34 = y_46;
			m_x_35 = m_x_36;
			m_x_36 = x_41;
			t_sample abs_33 = fabs(y_46);
			__m_slide_182 = fixdenorm((__m_slide_182 + (((abs_33 > __m_slide_182) ? iup_183 : idown_184) * (abs_33 - __m_slide_182))));
			t_sample slide_32 = __m_slide_182;
			t_sample mul_29 = (y_2066 * slide_32);
			t_sample dcblock_28 = __m_dcblock_185(mul_29);
			t_sample x_2084 = gate_473;
			t_sample q_2081 = gen_468;
			t_sample bw_2087 = safediv(((int)4556), q_2081);
			t_sample r_2082 = exp(((-bw_2087) * twopi_over_sr_2078));
			t_sample c_2085 = ((((int)2) * r_2082) * cos((((int)4556) * twopi_over_sr_2078)));
			t_sample c_2076 = ((-r_2082) * r_2082);
			t_sample y_2083 = ((((((int)1) - r_2082) * (x_2084 - (r_2082 * m_x_31))) + (c_2085 * m_y_30)) + (c_2076 * m_y_29));
			m_y_29 = m_y_30;
			m_y_30 = y_2083;
			m_x_31 = m_x_32;
			m_x_32 = x_2084;
			t_sample x_16 = in2;
			t_sample q_9 = gen_468;
			t_sample bw_17 = safediv(((int)4556), q_9);
			t_sample r_10 = exp(((-bw_17) * twopi_over_sr_20));
			t_sample c_19 = ((((int)2) * r_10) * cos((((int)4556) * twopi_over_sr_20)));
			t_sample c_22 = ((-r_10) * r_10);
			t_sample y_21 = ((((((int)1) - r_10) * (x_16 - (r_10 * m_x_27))) + (c_19 * m_y_26)) + (c_22 * m_y_25));
			m_y_25 = m_y_26;
			m_y_26 = y_21;
			m_x_27 = m_x_28;
			m_x_28 = x_16;
			t_sample abs_8 = fabs(y_21);
			__m_slide_186 = fixdenorm((__m_slide_186 + (((abs_8 > __m_slide_186) ? iup_187 : idown_188) * (abs_8 - __m_slide_186))));
			t_sample slide_7 = __m_slide_186;
			t_sample mul_2 = (y_2083 * slide_7);
			t_sample dcblock_1 = __m_dcblock_189(mul_2);
			t_sample x_2106 = gate_473;
			t_sample q_2095 = gen_468;
			t_sample bw_2103 = safediv(((t_sample)104.5), q_2095);
			t_sample r_2096 = exp(((-bw_2103) * twopi_over_sr_2094));
			t_sample c_2107 = ((((int)2) * r_2096) * cos((((t_sample)104.5) * twopi_over_sr_2094)));
			t_sample c_2102 = ((-r_2096) * r_2096);
			t_sample y_2105 = ((((((int)1) - r_2096) * (x_2106 - (r_2096 * m_x_23))) + (c_2107 * m_y_22)) + (c_2102 * m_y_21));
			m_y_21 = m_y_22;
			m_y_22 = y_2105;
			m_x_23 = m_x_24;
			m_x_24 = x_2106;
			t_sample x_437 = in2;
			t_sample q_430 = gen_468;
			t_sample bw_438 = safediv(((t_sample)104.5), q_430);
			t_sample r_431 = exp(((-bw_438) * twopi_over_sr_441));
			t_sample c_440 = ((((int)2) * r_431) * cos((((t_sample)104.5) * twopi_over_sr_441)));
			t_sample c_443 = ((-r_431) * r_431);
			t_sample y_442 = ((((((int)1) - r_431) * (x_437 - (r_431 * m_x_19))) + (c_440 * m_y_18)) + (c_443 * m_y_17));
			m_y_17 = m_y_18;
			m_y_18 = y_442;
			m_x_19 = m_x_20;
			m_x_20 = x_437;
			t_sample abs_429 = fabs(y_442);
			__m_slide_190 = fixdenorm((__m_slide_190 + (((abs_429 > __m_slide_190) ? iup_191 : idown_192) * (abs_429 - __m_slide_190))));
			t_sample slide_428 = __m_slide_190;
			t_sample mul_425 = (y_2105 * slide_428);
			t_sample dcblock_424 = __m_dcblock_193(mul_425);
			t_sample x_2123 = gate_473;
			t_sample q_2113 = gen_468;
			t_sample bw_2122 = safediv(((t_sample)179.5), q_2113);
			t_sample r_2114 = exp(((-bw_2122) * twopi_over_sr_2112));
			t_sample c_2124 = ((((int)2) * r_2114) * cos((((t_sample)179.5) * twopi_over_sr_2112)));
			t_sample c_2121 = ((-r_2114) * r_2114);
			t_sample y_2115 = ((((((int)1) - r_2114) * (x_2123 - (r_2114 * m_x_15))) + (c_2124 * m_y_14)) + (c_2121 * m_y_13));
			m_y_13 = m_y_14;
			m_y_14 = y_2115;
			m_x_15 = m_x_16;
			m_x_16 = x_2123;
			t_sample x_366 = in2;
			t_sample q_359 = gen_468;
			t_sample bw_367 = safediv(((t_sample)179.5), q_359);
			t_sample r_360 = exp(((-bw_367) * twopi_over_sr_370));
			t_sample c_369 = ((((int)2) * r_360) * cos((((t_sample)179.5) * twopi_over_sr_370)));
			t_sample c_372 = ((-r_360) * r_360);
			t_sample y_371 = ((((((int)1) - r_360) * (x_366 - (r_360 * m_x_11))) + (c_369 * m_y_10)) + (c_372 * m_y_9));
			m_y_9 = m_y_10;
			m_y_10 = y_371;
			m_x_11 = m_x_12;
			m_x_12 = x_366;
			t_sample abs_358 = fabs(y_371);
			__m_slide_194 = fixdenorm((__m_slide_194 + (((abs_358 > __m_slide_194) ? iup_195 : idown_196) * (abs_358 - __m_slide_194))));
			t_sample slide_357 = __m_slide_194;
			t_sample mul_354 = (y_2115 * slide_357);
			t_sample dcblock_353 = __m_dcblock_197(mul_354);
			t_sample x_2141 = gate_473;
			t_sample q_2131 = gen_468;
			t_sample bw_2138 = safediv(((int)226), q_2131);
			t_sample r_2132 = exp(((-bw_2138) * twopi_over_sr_2130));
			t_sample c_2142 = ((((int)2) * r_2132) * cos((((int)226) * twopi_over_sr_2130)));
			t_sample c_2137 = ((-r_2132) * r_2132);
			t_sample y_2140 = ((((((int)1) - r_2132) * (x_2141 - (r_2132 * m_x_7))) + (c_2142 * m_y_6)) + (c_2137 * m_y_5));
			m_y_5 = m_y_6;
			m_y_6 = y_2140;
			m_x_7 = m_x_8;
			m_x_8 = x_2141;
			t_sample x_341 = in2;
			t_sample q_334 = gen_468;
			t_sample bw_342 = safediv(((int)226), q_334);
			t_sample r_335 = exp(((-bw_342) * twopi_over_sr_345));
			t_sample c_344 = ((((int)2) * r_335) * cos((((int)226) * twopi_over_sr_345)));
			t_sample c_347 = ((-r_335) * r_335);
			t_sample y_346 = ((((((int)1) - r_335) * (x_341 - (r_335 * m_x_3))) + (c_344 * m_y_2)) + (c_347 * m_y_1));
			m_y_1 = m_y_2;
			m_y_2 = y_346;
			m_x_3 = m_x_4;
			m_x_4 = x_341;
			t_sample abs_333 = fabs(y_346);
			__m_slide_198 = fixdenorm((__m_slide_198 + (((abs_333 > __m_slide_198) ? iup_199 : idown_200) * (abs_333 - __m_slide_198))));
			t_sample slide_332 = __m_slide_198;
			t_sample mul_329 = (y_2140 * slide_332);
			t_sample dcblock_328 = __m_dcblock_201(mul_329);
			t_sample mul_469 = ((((((((((((((((dcblock_328 + dcblock_353) + dcblock_424) + dcblock_1) + dcblock_28) + dcblock_53) + dcblock_78) + dcblock_103) + dcblock_128) + dcblock_153) + dcblock_178) + dcblock_203) + dcblock_228) + dcblock_253) + dcblock_278) + dcblock_303) * m_knob4_gain_133);
			t_sample add_482 = (mul_469 + gate_472);
			t_sample out1 = add_482;
			t_sample add_481 = (mul_469 + gate_472);
			t_sample out2 = add_481;
			m_history_132 = history_476_next_478;
			m_history_131 = history_462_next_465;
			m_history_129 = history_457_next_467;
			m_history_130 = history_459_next_466;
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
	inline void set_knob4_gain(t_param _value) {
		m_knob4_gain_133 = (_value < 1 ? 1 : (_value > 20 ? 20 : _value));
	};
	inline void set_knob3_res(t_param _value) {
		m_knob3_res_134 = (_value < 15 ? 15 : (_value > 50 ? 50 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_135 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 6;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 3; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
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
		case 0: self->set_knob3_res(value); break;
		case 1: self->set_knob4_gain(value); break;
		case 2: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob3_res_134; break;
		case 1: *value = self->m_knob4_gain_133; break;
		case 2: *value = self->m_sw_135; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(3 * sizeof(ParamInfo));
	self->__commonstate.numparams = 3;
	// initialize parameter 0 ("m_knob3_res_134")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_res";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_res_134;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 15;
	pi->outputmax = 50;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_gain_133")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_gain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_gain_133;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_sw_135")
	pi = self->__commonstate.params + 2;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_135;
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
