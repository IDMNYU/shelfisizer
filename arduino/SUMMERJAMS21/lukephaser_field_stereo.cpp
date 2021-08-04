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
	DCBlock __m_dcblock_63;
	DCBlock __m_dcblock_48;
	Phasor __m_phasor_33;
	Sah __m_sah_28;
	SineCycle __m_cycle_56;
	SineCycle __m_cycle_49;
	SineCycle __m_cycle_41;
	SineCycle __m_cycle_34;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_3;
	t_sample m_history_8;
	t_sample __m_slide_35;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample samples_to_seconds;
	t_sample __m_slide_38;
	t_sample __m_slide_30;
	t_sample m_history_6;
	t_sample m_history_2;
	t_sample __m_slide_45;
	t_sample __m_slide_53;
	t_sample __m_slide_57;
	t_sample __m_slide_42;
	t_sample __m_slide_50;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample m_history_7;
	t_sample m_history_27;
	t_sample m_sw_25;
	t_sample m_history_13;
	t_sample m_history_14;
	t_sample m_history_15;
	t_sample m_history_12;
	t_sample m_history_10;
	t_sample m_history_11;
	t_sample m_history_9;
	t_sample m_knob4_rate_26;
	t_sample m_history_16;
	t_sample m_history_18;
	t_sample m_knob5_fb_23;
	t_sample m_sw_24;
	t_sample m_history_17;
	t_sample __m_slide_60;
	t_sample m_history_20;
	t_sample m_history_21;
	t_sample m_history_19;
	t_sample m_knob3_depth_22;
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
		m_knob3_depth_22 = 1;
		m_knob5_fb_23 = ((int)0);
		m_sw_24 = ((int)0);
		m_sw_25 = ((int)0);
		m_knob4_rate_26 = 0.1;
		m_history_27 = ((int)0);
		__m_sah_28.reset(0);
		__m_slide_30 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_33.reset(0);
		__m_cycle_34.reset(samplerate, 0);
		__m_slide_35 = 0;
		__m_slide_38 = 0;
		__m_cycle_41.reset(samplerate, 0);
		__m_slide_42 = 0;
		__m_slide_45 = 0;
		__m_dcblock_48.reset();
		__m_cycle_49.reset(samplerate, 0);
		__m_slide_50 = 0;
		__m_slide_53 = 0;
		__m_cycle_56.reset(samplerate, 0);
		__m_slide_57 = 0;
		__m_slide_60 = 0;
		__m_dcblock_63.reset();
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
		t_sample sub_331 = (m_knob5_fb_23 - ((t_sample)0.5));
		t_sample scale_328 = ((safepow((sub_331 * ((t_sample)2.0408163265306)), ((int)1)) * ((t_sample)-0.15)) + ((t_sample)0.25));
		t_sample mstosamps_20 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_19 = (((int)100) * (samplerate * 0.001));
		t_sample iup_31 = (1 / maximum(1, abs(mstosamps_20)));
		t_sample idown_32 = (1 / maximum(1, abs(mstosamps_19)));
		samples_to_seconds = (1 / samplerate);
		t_sample div_141 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_36 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_37 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_39 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_40 = (1 / maximum(1, abs(((int)5))));
		t_sample div_204 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_43 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_44 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_46 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_47 = (1 / maximum(1, abs(((int)5))));
		t_sample div_56 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_51 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_52 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_54 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_55 = (1 / maximum(1, abs(((int)5))));
		t_sample div_98 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_58 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_59 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_61 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_62 = (1 / maximum(1, abs(((int)5))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_32 = __m_sah_28(m_history_27, m_sw_25, ((int)0));
			t_sample gen_34 = sah_32;
			t_sample rsub_30 = (((int)1) - sah_32);
			t_sample history_31_next_33 = fixdenorm(rsub_30);
			t_sample out3 = gen_34;
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample add_35 = (gen_34 + ((int)1));
			t_sample choice_29 = int(add_35);
			t_sample gate_27 = (((choice_29 >= 1) && (choice_29 < 2)) ? in1 : 0);
			t_sample gate_28 = ((choice_29 >= 2) ? in1 : 0);
			t_sample mul_183 = (m_history_1 * m_knob5_fb_23);
			t_sample add_182 = (gate_28 + mul_183);
			t_sample mul_38 = (m_history_2 * m_knob5_fb_23);
			t_sample add_37 = (gate_28 + mul_38);
			t_sample switch_24 = (m_sw_24 ? gate_28 : ((int)1));
			t_sample abs_26 = fabs(switch_24);
			t_sample mul_1 = (abs_26 * ((int)100));
			__m_slide_30 = fixdenorm((__m_slide_30 + (((mul_1 > __m_slide_30) ? iup_31 : idown_32) * (mul_1 - __m_slide_30))));
			t_sample slide_25 = __m_slide_30;
			t_sample clamp_21 = ((slide_25 <= ((int)0)) ? ((int)0) : ((slide_25 >= ((int)1)) ? ((int)1) : slide_25));
			t_sample mul_23 = (m_knob3_depth_22 * clamp_21);
			t_sample mix_332 = (m_history_21 + (((t_sample)0.0042742627044161) * (m_knob4_rate_26 - m_history_21)));
			t_sample mix_7 = mix_332;
			t_sample mix_333 = (m_history_20 + (((t_sample)0.0042742627044161) * (mix_7 - m_history_20)));
			t_sample mix_5 = mix_333;
			t_sample mix_334 = (m_history_19 + (((t_sample)0.0042742627044161) * (mix_5 - m_history_19)));
			t_sample mix_3 = mix_334;
			t_sample gen_15 = mix_3;
			t_sample history_9_next_12 = fixdenorm(mix_7);
			t_sample history_6_next_13 = fixdenorm(mix_5);
			t_sample history_4_next_14 = fixdenorm(mix_3);
			t_sample rsub_173 = (((int)1) - gen_15);
			t_sample sqrt_172 = sqrt(rsub_173);
			t_sample sqrt_171 = sqrt(sqrt_172);
			t_sample sqrt_16 = sqrt(sqrt_171);
			t_sample rsub_170 = (((int)1) - sqrt_16);
			t_sample mul_233 = (rsub_170 * ((t_sample)7.5));
			t_sample phasor_189 = __m_phasor_33(mul_233, samples_to_seconds);
			t_sample add_150 = (phasor_189 + ((t_sample)0.25));
			t_sample mod_151 = safemod(add_150, ((int)1));
			__m_cycle_34.phase(mod_151);
			t_sample cycle_148 = __m_cycle_34(__sinedata);
			t_sample cycleindex_149 = __m_cycle_34.phase();
			t_sample add_146 = (cycle_148 + ((int)1));
			t_sample div_145 = (add_146 * ((t_sample)0.5));
			t_sample mul_147 = (div_145 * mul_23);
			t_sample sub_338 = (mul_147 - ((int)0));
			t_sample scale_335 = ((safepow((sub_338 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_152 = scale_335;
			t_sample mtof_153 = mtof(scale_152, ((int)440));
			t_sample mul_140 = (mtof_153 * div_141);
			t_sample cos_138 = cos(mul_140);
			t_sample mul_133 = (cos_138 * (-2));
			t_sample sin_139 = sin(mul_140);
			t_sample mul_137 = (sin_139 * ((t_sample)0.5));
			t_sample div_136 = (mul_137 * ((t_sample)0.33333333333333));
			t_sample rsub_131 = (((int)1) - div_136);
			t_sample add_135 = (div_136 + ((int)1));
			t_sample rdiv_134 = safediv(((int)1), add_135);
			t_sample mul_130 = (rdiv_134 * rsub_131);
			__m_slide_35 = fixdenorm((__m_slide_35 + (((mul_130 > __m_slide_35) ? iup_36 : idown_37) * (mul_130 - __m_slide_35))));
			t_sample slide_127 = __m_slide_35;
			t_sample gen_143 = slide_127;
			t_sample mul_132 = (rdiv_134 * mul_133);
			__m_slide_38 = fixdenorm((__m_slide_38 + (((mul_132 > __m_slide_38) ? iup_39 : idown_40) * (mul_132 - __m_slide_38))));
			t_sample slide_128 = __m_slide_38;
			t_sample gen_142 = slide_128;
			t_sample mul_163 = (add_182 * gen_143);
			t_sample mul_160 = (m_history_16 * gen_142);
			t_sample mul_158 = (m_history_17 * ((int)1));
			t_sample mul_154 = (m_history_18 * gen_143);
			t_sample mul_156 = (m_history_15 * gen_142);
			t_sample sub_162 = (((mul_158 + mul_160) + mul_163) - (mul_156 + mul_154));
			t_sample gen_168 = sub_162;
			t_sample history_155_next_164 = fixdenorm(m_history_15);
			t_sample history_159_next_165 = fixdenorm(m_history_16);
			t_sample history_161_next_166 = fixdenorm(add_182);
			t_sample history_157_next_167 = fixdenorm(sub_162);
			t_sample add_213 = (phasor_189 + ((int)0));
			t_sample mod_214 = safemod(add_213, ((int)1));
			__m_cycle_41.phase(mod_214);
			t_sample cycle_211 = __m_cycle_41(__sinedata);
			t_sample cycleindex_212 = __m_cycle_41.phase();
			t_sample add_209 = (cycle_211 + ((int)1));
			t_sample div_208 = (add_209 * ((t_sample)0.5));
			t_sample mul_210 = (div_208 * mul_23);
			t_sample sub_342 = (mul_210 - ((int)0));
			t_sample scale_339 = ((safepow((sub_342 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_215 = scale_339;
			t_sample mtof_216 = mtof(scale_215, ((int)440));
			t_sample mul_203 = (mtof_216 * div_204);
			t_sample cos_201 = cos(mul_203);
			t_sample mul_196 = (cos_201 * (-2));
			t_sample sin_202 = sin(mul_203);
			t_sample mul_200 = (sin_202 * ((t_sample)0.5));
			t_sample div_199 = (mul_200 * ((t_sample)0.33333333333333));
			t_sample rsub_194 = (((int)1) - div_199);
			t_sample add_198 = (div_199 + ((int)1));
			t_sample rdiv_197 = safediv(((int)1), add_198);
			t_sample mul_195 = (rdiv_197 * mul_196);
			__m_slide_42 = fixdenorm((__m_slide_42 + (((mul_195 > __m_slide_42) ? iup_43 : idown_44) * (mul_195 - __m_slide_42))));
			t_sample slide_191 = __m_slide_42;
			t_sample gen_205 = slide_191;
			t_sample mul_193 = (rdiv_197 * rsub_194);
			__m_slide_45 = fixdenorm((__m_slide_45 + (((mul_193 > __m_slide_45) ? iup_46 : idown_47) * (mul_193 - __m_slide_45))));
			t_sample slide_190 = __m_slide_45;
			t_sample gen_206 = slide_190;
			t_sample mul_226 = (add_182 * gen_206);
			t_sample mul_223 = (m_history_12 * gen_205);
			t_sample mul_221 = (m_history_13 * ((int)1));
			t_sample mul_217 = (m_history_14 * gen_206);
			t_sample mul_219 = (m_history_11 * gen_205);
			t_sample sub_225 = (((mul_221 + mul_223) + mul_226) - (mul_219 + mul_217));
			t_sample gen_231 = sub_225;
			t_sample history_218_next_227 = fixdenorm(m_history_11);
			t_sample history_222_next_228 = fixdenorm(m_history_12);
			t_sample history_224_next_229 = fixdenorm(add_182);
			t_sample history_220_next_230 = fixdenorm(sub_225);
			t_sample mul_169 = (((gate_28 + gen_231) + gen_168) * scale_328);
			t_sample add_176 = (mul_169 + gate_27);
			t_sample out1 = add_176;
			t_sample mul_126 = ((gen_231 + gen_168) * ((t_sample)0.5));
			t_sample dcblock_175 = __m_dcblock_48(mul_126);
			t_sample add_65 = (phasor_189 + ((t_sample)0.375));
			t_sample mod_66 = safemod(add_65, ((int)1));
			__m_cycle_49.phase(mod_66);
			t_sample cycle_63 = __m_cycle_49(__sinedata);
			t_sample cycleindex_64 = __m_cycle_49.phase();
			t_sample add_61 = (cycle_63 + ((int)1));
			t_sample div_60 = (add_61 * ((t_sample)0.5));
			t_sample mul_62 = (div_60 * mul_23);
			t_sample sub_346 = (mul_62 - ((int)0));
			t_sample scale_343 = ((safepow((sub_346 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_67 = scale_343;
			t_sample mtof_68 = mtof(scale_67, ((int)440));
			t_sample mul_55 = (mtof_68 * div_56);
			t_sample cos_53 = cos(mul_55);
			t_sample mul_48 = (cos_53 * (-2));
			t_sample sin_54 = sin(mul_55);
			t_sample mul_52 = (sin_54 * ((t_sample)0.5));
			t_sample div_51 = (mul_52 * ((t_sample)0.33333333333333));
			t_sample rsub_46 = (((int)1) - div_51);
			t_sample add_50 = (div_51 + ((int)1));
			t_sample rdiv_49 = safediv(((int)1), add_50);
			t_sample mul_45 = (rdiv_49 * rsub_46);
			__m_slide_50 = fixdenorm((__m_slide_50 + (((mul_45 > __m_slide_50) ? iup_51 : idown_52) * (mul_45 - __m_slide_50))));
			t_sample slide_42 = __m_slide_50;
			t_sample gen_58 = slide_42;
			t_sample mul_47 = (rdiv_49 * mul_48);
			__m_slide_53 = fixdenorm((__m_slide_53 + (((mul_47 > __m_slide_53) ? iup_54 : idown_55) * (mul_47 - __m_slide_53))));
			t_sample slide_43 = __m_slide_53;
			t_sample gen_57 = slide_43;
			t_sample mul_78 = (add_37 * gen_58);
			t_sample mul_75 = (m_history_8 * gen_57);
			t_sample mul_73 = (m_history_9 * ((int)1));
			t_sample mul_69 = (m_history_10 * gen_58);
			t_sample mul_71 = (m_history_7 * gen_57);
			t_sample sub_77 = (((mul_73 + mul_75) + mul_78) - (mul_71 + mul_69));
			t_sample gen_83 = sub_77;
			t_sample history_70_next_79 = fixdenorm(m_history_7);
			t_sample history_74_next_80 = fixdenorm(m_history_8);
			t_sample history_76_next_81 = fixdenorm(add_37);
			t_sample history_72_next_82 = fixdenorm(sub_77);
			t_sample add_107 = (phasor_189 + ((t_sample)0.125));
			t_sample mod_108 = safemod(add_107, ((int)1));
			__m_cycle_56.phase(mod_108);
			t_sample cycle_105 = __m_cycle_56(__sinedata);
			t_sample cycleindex_106 = __m_cycle_56.phase();
			t_sample add_103 = (cycle_105 + ((int)1));
			t_sample div_102 = (add_103 * ((t_sample)0.5));
			t_sample mul_104 = (div_102 * mul_23);
			t_sample sub_350 = (mul_104 - ((int)0));
			t_sample scale_347 = ((safepow((sub_350 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_109 = scale_347;
			t_sample mtof_110 = mtof(scale_109, ((int)440));
			t_sample mul_97 = (mtof_110 * div_98);
			t_sample cos_95 = cos(mul_97);
			t_sample mul_90 = (cos_95 * (-2));
			t_sample sin_96 = sin(mul_97);
			t_sample mul_94 = (sin_96 * ((t_sample)0.5));
			t_sample div_93 = (mul_94 * ((t_sample)0.33333333333333));
			t_sample rsub_88 = (((int)1) - div_93);
			t_sample add_92 = (div_93 + ((int)1));
			t_sample rdiv_91 = safediv(((int)1), add_92);
			t_sample mul_87 = (rdiv_91 * rsub_88);
			__m_slide_57 = fixdenorm((__m_slide_57 + (((mul_87 > __m_slide_57) ? iup_58 : idown_59) * (mul_87 - __m_slide_57))));
			t_sample slide_84 = __m_slide_57;
			t_sample gen_100 = slide_84;
			t_sample mul_89 = (rdiv_91 * mul_90);
			__m_slide_60 = fixdenorm((__m_slide_60 + (((mul_89 > __m_slide_60) ? iup_61 : idown_62) * (mul_89 - __m_slide_60))));
			t_sample slide_85 = __m_slide_60;
			t_sample gen_99 = slide_85;
			t_sample mul_120 = (add_37 * gen_100);
			t_sample mul_117 = (m_history_4 * gen_99);
			t_sample mul_115 = (m_history_5 * ((int)1));
			t_sample mul_111 = (m_history_6 * gen_100);
			t_sample mul_113 = (m_history_3 * gen_99);
			t_sample sub_119 = (((mul_115 + mul_117) + mul_120) - (mul_113 + mul_111));
			t_sample gen_125 = sub_119;
			t_sample history_112_next_121 = fixdenorm(m_history_3);
			t_sample history_116_next_122 = fixdenorm(m_history_4);
			t_sample history_118_next_123 = fixdenorm(add_37);
			t_sample history_114_next_124 = fixdenorm(sub_119);
			t_sample mul_39 = ((gen_125 + gen_83) * ((t_sample)0.5));
			t_sample dcblock_40 = __m_dcblock_63(mul_39);
			t_sample mul_41 = (((gate_28 + gen_125) + gen_83) * scale_328);
			t_sample add_174 = (mul_41 + gate_27);
			t_sample out2 = add_174;
			t_sample history_36_next_234 = fixdenorm(dcblock_175);
			t_sample history_181_next_235 = fixdenorm(dcblock_40);
			m_history_27 = history_31_next_33;
			m_history_21 = history_9_next_12;
			m_history_19 = history_4_next_14;
			m_history_20 = history_6_next_13;
			m_history_18 = history_155_next_164;
			m_history_15 = history_157_next_167;
			m_history_16 = history_161_next_166;
			m_history_17 = history_159_next_165;
			m_history_14 = history_218_next_227;
			m_history_11 = history_220_next_230;
			m_history_12 = history_224_next_229;
			m_history_13 = history_222_next_228;
			m_history_10 = history_70_next_79;
			m_history_7 = history_72_next_82;
			m_history_8 = history_76_next_81;
			m_history_9 = history_74_next_80;
			m_history_6 = history_112_next_121;
			m_history_3 = history_114_next_124;
			m_history_4 = history_118_next_123;
			m_history_5 = history_116_next_122;
			m_history_2 = history_36_next_234;
			m_history_1 = history_181_next_235;
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
		m_knob3_depth_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_fb(t_param _value) {
		m_knob5_fb_23 = (_value < 0.5 ? 0.5 : (_value > 0.99 ? 0.99 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_rate(t_param _value) {
		m_knob4_rate_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 2: self->set_knob5_fb(value); break;
		case 3: self->set_sw1(value); break;
		case 4: self->set_sw5(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob3_depth_22; break;
		case 1: *value = self->m_knob4_rate_26; break;
		case 2: *value = self->m_knob5_fb_23; break;
		case 3: *value = self->m_sw_25; break;
		case 4: *value = self->m_sw_24; break;
		
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
	// initialize parameter 0 ("m_knob3_depth_22")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_depth_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_rate_26")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_rate_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_fb_23")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_fb_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_sw_25")
	pi = self->__commonstate.params + 3;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_25;
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
	pi->name = "sw5";
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // lukephaser_field_stereo::
