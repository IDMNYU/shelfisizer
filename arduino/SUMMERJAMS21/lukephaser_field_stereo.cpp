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
	DCBlock __m_dcblock_64;
	DCBlock __m_dcblock_49;
	Phasor __m_phasor_34;
	Sah __m_sah_28;
	SineCycle __m_cycle_57;
	SineCycle __m_cycle_50;
	SineCycle __m_cycle_42;
	SineCycle __m_cycle_35;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_3;
	t_sample m_history_8;
	t_sample __m_slide_36;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample samples_to_seconds;
	t_sample __m_slide_39;
	t_sample __m_slide_31;
	t_sample m_history_6;
	t_sample m_history_2;
	t_sample __m_slide_46;
	t_sample __m_slide_54;
	t_sample __m_slide_58;
	t_sample __m_slide_43;
	t_sample __m_slide_51;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample m_history_7;
	t_sample m_knob5_fb_27;
	t_sample m_knob4_rate_25;
	t_sample m_history_13;
	t_sample m_history_14;
	t_sample m_history_15;
	t_sample m_history_12;
	t_sample m_history_10;
	t_sample m_history_11;
	t_sample m_history_9;
	t_sample m_sw_26;
	t_sample m_history_16;
	t_sample m_history_18;
	t_sample m_sw_23;
	t_sample m_knob3_depth_24;
	t_sample m_history_17;
	t_sample __m_slide_61;
	t_sample m_history_20;
	t_sample m_history_21;
	t_sample m_history_19;
	t_sample m_history_22;
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
		m_sw_23 = ((int)0);
		m_knob3_depth_24 = 1;
		m_knob4_rate_25 = 0.1;
		m_sw_26 = ((int)0);
		m_knob5_fb_27 = ((int)0);
		__m_sah_28.reset(0);
		__m_slide_31 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_34.reset(0);
		__m_cycle_35.reset(samplerate, 0);
		__m_slide_36 = 0;
		__m_slide_39 = 0;
		__m_cycle_42.reset(samplerate, 0);
		__m_slide_43 = 0;
		__m_slide_46 = 0;
		__m_dcblock_49.reset();
		__m_cycle_50.reset(samplerate, 0);
		__m_slide_51 = 0;
		__m_slide_54 = 0;
		__m_cycle_57.reset(samplerate, 0);
		__m_slide_58 = 0;
		__m_slide_61 = 0;
		__m_dcblock_64.reset();
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
		t_sample sub_417 = (m_knob5_fb_27 - ((t_sample)0.5));
		t_sample scale_414 = ((safepow((sub_417 * ((t_sample)2.0408163265306)), ((int)1)) * ((t_sample)-0.15)) + ((t_sample)0.25));
		t_sample mstosamps_104 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_103 = (((int)100) * (samplerate * 0.001));
		t_sample add_108 = (m_sw_23 + ((int)1));
		t_sample choice_30 = int(add_108);
		t_sample iup_32 = (1 / maximum(1, abs(mstosamps_104)));
		t_sample idown_33 = (1 / maximum(1, abs(mstosamps_103)));
		samples_to_seconds = (1 / samplerate);
		t_sample div_227 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_37 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_38 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_40 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_41 = (1 / maximum(1, abs(((int)5))));
		t_sample div_290 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_44 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_45 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_47 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_48 = (1 / maximum(1, abs(((int)5))));
		t_sample div_142 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_52 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_53 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_55 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_56 = (1 / maximum(1, abs(((int)5))));
		t_sample div_184 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_59 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_60 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_62 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_63 = (1 / maximum(1, abs(((int)5))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out4 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample sah_118 = __m_sah_28(m_history_22, m_sw_26, ((int)0));
			t_sample gen_120 = sah_118;
			t_sample rsub_116 = (((int)1) - sah_118);
			t_sample history_117_next_119 = fixdenorm(rsub_116);
			t_sample out3 = gen_120;
			t_sample add_121 = (gen_120 + ((int)1));
			t_sample choice_29 = int(add_121);
			t_sample gate_113 = (((choice_29 >= 1) && (choice_29 < 2)) ? in1 : 0);
			t_sample gate_114 = ((choice_29 >= 2) ? in1 : 0);
			t_sample mul_269 = (m_history_1 * m_knob5_fb_27);
			t_sample add_268 = (gate_114 + mul_269);
			t_sample mul_124 = (m_history_2 * m_knob5_fb_27);
			t_sample add_123 = (gate_114 + mul_124);
			t_sample selector_110 = ((choice_30 >= 2) ? gate_114 : ((choice_30 >= 1) ? ((int)1) : 0));
			t_sample abs_112 = fabs(selector_110);
			__m_slide_31 = fixdenorm((__m_slide_31 + (((abs_112 > __m_slide_31) ? iup_32 : idown_33) * (abs_112 - __m_slide_31))));
			t_sample slide_111 = __m_slide_31;
			t_sample mul_106 = (slide_111 * ((int)10));
			t_sample clamp_105 = ((mul_106 <= ((int)0)) ? ((int)0) : ((mul_106 >= ((int)1)) ? ((int)1) : mul_106));
			t_sample mul_109 = (m_knob3_depth_24 * clamp_105);
			t_sample mix_418 = (m_history_21 + (((t_sample)0.003926980723806) * (m_knob4_rate_25 - m_history_21)));
			t_sample mix_91 = mix_418;
			t_sample mix_419 = (m_history_20 + (((t_sample)0.003926980723806) * (mix_91 - m_history_20)));
			t_sample mix_89 = mix_419;
			t_sample mix_420 = (m_history_19 + (((t_sample)0.003926980723806) * (mix_89 - m_history_19)));
			t_sample mix_87 = mix_420;
			t_sample gen_99 = mix_87;
			t_sample history_93_next_96 = fixdenorm(mix_91);
			t_sample history_90_next_97 = fixdenorm(mix_89);
			t_sample history_88_next_98 = fixdenorm(mix_87);
			t_sample rsub_259 = (((int)1) - gen_99);
			t_sample sqrt_258 = sqrt(rsub_259);
			t_sample sqrt_257 = sqrt(sqrt_258);
			t_sample sqrt_100 = sqrt(sqrt_257);
			t_sample rsub_256 = (((int)1) - sqrt_100);
			t_sample mul_319 = (rsub_256 * ((t_sample)7.5));
			t_sample phasor_275 = __m_phasor_34(mul_319, samples_to_seconds);
			t_sample add_236 = (phasor_275 + ((t_sample)0.25));
			t_sample mod_237 = safemod(add_236, ((int)1));
			__m_cycle_35.phase(mod_237);
			t_sample cycle_234 = __m_cycle_35(__sinedata);
			t_sample cycleindex_235 = __m_cycle_35.phase();
			t_sample add_232 = (cycle_234 + ((int)1));
			t_sample div_231 = (add_232 * ((t_sample)0.5));
			t_sample mul_233 = (div_231 * mul_109);
			t_sample sub_424 = (mul_233 - ((int)0));
			t_sample scale_421 = ((safepow((sub_424 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_238 = scale_421;
			t_sample mtof_239 = mtof(scale_238, ((int)440));
			t_sample mul_226 = (mtof_239 * div_227);
			t_sample cos_224 = cos(mul_226);
			t_sample mul_219 = (cos_224 * (-2));
			t_sample sin_225 = sin(mul_226);
			t_sample mul_223 = (sin_225 * ((t_sample)0.5));
			t_sample div_222 = (mul_223 * ((t_sample)0.33333333333333));
			t_sample rsub_217 = (((int)1) - div_222);
			t_sample add_221 = (div_222 + ((int)1));
			t_sample rdiv_220 = safediv(((int)1), add_221);
			t_sample mul_218 = (rdiv_220 * mul_219);
			__m_slide_36 = fixdenorm((__m_slide_36 + (((mul_218 > __m_slide_36) ? iup_37 : idown_38) * (mul_218 - __m_slide_36))));
			t_sample slide_214 = __m_slide_36;
			t_sample gen_228 = slide_214;
			t_sample mul_216 = (rdiv_220 * rsub_217);
			__m_slide_39 = fixdenorm((__m_slide_39 + (((mul_216 > __m_slide_39) ? iup_40 : idown_41) * (mul_216 - __m_slide_39))));
			t_sample slide_213 = __m_slide_39;
			t_sample gen_229 = slide_213;
			t_sample mul_249 = (add_268 * gen_229);
			t_sample mul_246 = (m_history_16 * gen_228);
			t_sample mul_244 = (m_history_17 * ((int)1));
			t_sample mul_240 = (m_history_18 * gen_229);
			t_sample mul_242 = (m_history_15 * gen_228);
			t_sample sub_248 = (((mul_244 + mul_246) + mul_249) - (mul_242 + mul_240));
			t_sample gen_254 = sub_248;
			t_sample history_241_next_250 = fixdenorm(m_history_15);
			t_sample history_245_next_251 = fixdenorm(m_history_16);
			t_sample history_247_next_252 = fixdenorm(add_268);
			t_sample history_243_next_253 = fixdenorm(sub_248);
			t_sample add_299 = (phasor_275 + ((int)0));
			t_sample mod_300 = safemod(add_299, ((int)1));
			__m_cycle_42.phase(mod_300);
			t_sample cycle_297 = __m_cycle_42(__sinedata);
			t_sample cycleindex_298 = __m_cycle_42.phase();
			t_sample add_295 = (cycle_297 + ((int)1));
			t_sample div_294 = (add_295 * ((t_sample)0.5));
			t_sample mul_296 = (div_294 * mul_109);
			t_sample sub_428 = (mul_296 - ((int)0));
			t_sample scale_425 = ((safepow((sub_428 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_301 = scale_425;
			t_sample mtof_302 = mtof(scale_301, ((int)440));
			t_sample mul_289 = (mtof_302 * div_290);
			t_sample cos_287 = cos(mul_289);
			t_sample mul_282 = (cos_287 * (-2));
			t_sample sin_288 = sin(mul_289);
			t_sample mul_286 = (sin_288 * ((t_sample)0.5));
			t_sample div_285 = (mul_286 * ((t_sample)0.33333333333333));
			t_sample rsub_280 = (((int)1) - div_285);
			t_sample add_284 = (div_285 + ((int)1));
			t_sample rdiv_283 = safediv(((int)1), add_284);
			t_sample mul_279 = (rdiv_283 * rsub_280);
			__m_slide_43 = fixdenorm((__m_slide_43 + (((mul_279 > __m_slide_43) ? iup_44 : idown_45) * (mul_279 - __m_slide_43))));
			t_sample slide_276 = __m_slide_43;
			t_sample gen_292 = slide_276;
			t_sample mul_281 = (rdiv_283 * mul_282);
			__m_slide_46 = fixdenorm((__m_slide_46 + (((mul_281 > __m_slide_46) ? iup_47 : idown_48) * (mul_281 - __m_slide_46))));
			t_sample slide_277 = __m_slide_46;
			t_sample gen_291 = slide_277;
			t_sample mul_312 = (add_268 * gen_292);
			t_sample mul_309 = (m_history_12 * gen_291);
			t_sample mul_307 = (m_history_14 * ((int)1));
			t_sample mul_303 = (m_history_13 * gen_292);
			t_sample mul_305 = (m_history_11 * gen_291);
			t_sample sub_311 = (((mul_307 + mul_309) + mul_312) - (mul_305 + mul_303));
			t_sample gen_317 = sub_311;
			t_sample history_308_next_313 = fixdenorm(m_history_12);
			t_sample history_304_next_314 = fixdenorm(m_history_11);
			t_sample history_310_next_315 = fixdenorm(add_268);
			t_sample history_306_next_316 = fixdenorm(sub_311);
			t_sample mul_212 = ((gen_317 + gen_254) * ((t_sample)0.5));
			t_sample dcblock_261 = __m_dcblock_49(mul_212);
			t_sample mul_255 = (((gate_114 + gen_317) + gen_254) * scale_414);
			t_sample add_262 = (mul_255 + gate_113);
			t_sample out1 = add_262;
			t_sample add_151 = (phasor_275 + ((t_sample)0.375));
			t_sample mod_152 = safemod(add_151, ((int)1));
			__m_cycle_50.phase(mod_152);
			t_sample cycle_149 = __m_cycle_50(__sinedata);
			t_sample cycleindex_150 = __m_cycle_50.phase();
			t_sample add_147 = (cycle_149 + ((int)1));
			t_sample div_146 = (add_147 * ((t_sample)0.5));
			t_sample mul_148 = (div_146 * mul_109);
			t_sample sub_432 = (mul_148 - ((int)0));
			t_sample scale_429 = ((safepow((sub_432 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_153 = scale_429;
			t_sample mtof_154 = mtof(scale_153, ((int)440));
			t_sample mul_141 = (mtof_154 * div_142);
			t_sample cos_139 = cos(mul_141);
			t_sample mul_134 = (cos_139 * (-2));
			t_sample sin_140 = sin(mul_141);
			t_sample mul_138 = (sin_140 * ((t_sample)0.5));
			t_sample div_137 = (mul_138 * ((t_sample)0.33333333333333));
			t_sample rsub_132 = (((int)1) - div_137);
			t_sample add_136 = (div_137 + ((int)1));
			t_sample rdiv_135 = safediv(((int)1), add_136);
			t_sample mul_133 = (rdiv_135 * mul_134);
			__m_slide_51 = fixdenorm((__m_slide_51 + (((mul_133 > __m_slide_51) ? iup_52 : idown_53) * (mul_133 - __m_slide_51))));
			t_sample slide_129 = __m_slide_51;
			t_sample gen_143 = slide_129;
			t_sample mul_131 = (rdiv_135 * rsub_132);
			__m_slide_54 = fixdenorm((__m_slide_54 + (((mul_131 > __m_slide_54) ? iup_55 : idown_56) * (mul_131 - __m_slide_54))));
			t_sample slide_128 = __m_slide_54;
			t_sample gen_144 = slide_128;
			t_sample mul_164 = (add_123 * gen_144);
			t_sample mul_161 = (m_history_8 * gen_143);
			t_sample mul_159 = (m_history_9 * ((int)1));
			t_sample mul_155 = (m_history_10 * gen_144);
			t_sample mul_157 = (m_history_7 * gen_143);
			t_sample sub_163 = (((mul_159 + mul_161) + mul_164) - (mul_157 + mul_155));
			t_sample gen_169 = sub_163;
			t_sample history_156_next_165 = fixdenorm(m_history_7);
			t_sample history_160_next_166 = fixdenorm(m_history_8);
			t_sample history_162_next_167 = fixdenorm(add_123);
			t_sample history_158_next_168 = fixdenorm(sub_163);
			t_sample add_193 = (phasor_275 + ((t_sample)0.125));
			t_sample mod_194 = safemod(add_193, ((int)1));
			__m_cycle_57.phase(mod_194);
			t_sample cycle_191 = __m_cycle_57(__sinedata);
			t_sample cycleindex_192 = __m_cycle_57.phase();
			t_sample add_189 = (cycle_191 + ((int)1));
			t_sample div_188 = (add_189 * ((t_sample)0.5));
			t_sample mul_190 = (div_188 * mul_109);
			t_sample sub_436 = (mul_190 - ((int)0));
			t_sample scale_433 = ((safepow((sub_436 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_195 = scale_433;
			t_sample mtof_196 = mtof(scale_195, ((int)440));
			t_sample mul_183 = (mtof_196 * div_184);
			t_sample cos_181 = cos(mul_183);
			t_sample mul_176 = (cos_181 * (-2));
			t_sample sin_182 = sin(mul_183);
			t_sample mul_180 = (sin_182 * ((t_sample)0.5));
			t_sample div_179 = (mul_180 * ((t_sample)0.33333333333333));
			t_sample rsub_174 = (((int)1) - div_179);
			t_sample add_178 = (div_179 + ((int)1));
			t_sample rdiv_177 = safediv(((int)1), add_178);
			t_sample mul_173 = (rdiv_177 * rsub_174);
			__m_slide_58 = fixdenorm((__m_slide_58 + (((mul_173 > __m_slide_58) ? iup_59 : idown_60) * (mul_173 - __m_slide_58))));
			t_sample slide_170 = __m_slide_58;
			t_sample gen_186 = slide_170;
			t_sample mul_175 = (rdiv_177 * mul_176);
			__m_slide_61 = fixdenorm((__m_slide_61 + (((mul_175 > __m_slide_61) ? iup_62 : idown_63) * (mul_175 - __m_slide_61))));
			t_sample slide_171 = __m_slide_61;
			t_sample gen_185 = slide_171;
			t_sample mul_206 = (add_123 * gen_186);
			t_sample mul_203 = (m_history_4 * gen_185);
			t_sample mul_201 = (m_history_6 * ((int)1));
			t_sample mul_197 = (m_history_5 * gen_186);
			t_sample mul_199 = (m_history_3 * gen_185);
			t_sample sub_205 = (((mul_201 + mul_203) + mul_206) - (mul_199 + mul_197));
			t_sample gen_211 = sub_205;
			t_sample history_202_next_207 = fixdenorm(m_history_4);
			t_sample history_198_next_208 = fixdenorm(m_history_3);
			t_sample history_204_next_209 = fixdenorm(add_123);
			t_sample history_200_next_210 = fixdenorm(sub_205);
			t_sample mul_125 = ((gen_211 + gen_169) * ((t_sample)0.5));
			t_sample dcblock_126 = __m_dcblock_64(mul_125);
			t_sample mul_127 = (((gate_114 + gen_211) + gen_169) * scale_414);
			t_sample add_260 = (mul_127 + gate_113);
			t_sample out2 = add_260;
			t_sample history_122_next_320 = fixdenorm(dcblock_261);
			t_sample history_267_next_321 = fixdenorm(dcblock_126);
			m_history_22 = history_117_next_119;
			m_history_21 = history_93_next_96;
			m_history_19 = history_88_next_98;
			m_history_20 = history_90_next_97;
			m_history_18 = history_241_next_250;
			m_history_15 = history_243_next_253;
			m_history_16 = history_247_next_252;
			m_history_17 = history_245_next_251;
			m_history_14 = history_308_next_313;
			m_history_11 = history_306_next_316;
			m_history_12 = history_310_next_315;
			m_history_13 = history_304_next_314;
			m_history_10 = history_156_next_165;
			m_history_7 = history_158_next_168;
			m_history_8 = history_162_next_167;
			m_history_9 = history_160_next_166;
			m_history_6 = history_202_next_207;
			m_history_3 = history_200_next_210;
			m_history_4 = history_204_next_209;
			m_history_5 = history_198_next_208;
			m_history_2 = history_122_next_320;
			m_history_1 = history_267_next_321;
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
		m_sw_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_depth(t_param _value) {
		m_knob3_depth_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_rate(t_param _value) {
		m_knob4_rate_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_fb(t_param _value) {
		m_knob5_fb_27 = (_value < 0.5 ? 0.5 : (_value > 0.99 ? 0.99 : _value));
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
		case 0: *value = self->m_knob3_depth_24; break;
		case 1: *value = self->m_knob4_rate_25; break;
		case 2: *value = self->m_knob5_fb_27; break;
		case 3: *value = self->m_sw_26; break;
		case 4: *value = self->m_sw_23; break;
		
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
	// initialize parameter 0 ("m_knob3_depth_24")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_depth_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_rate_25")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_rate_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_fb_27")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_fb_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_sw_26")
	pi = self->__commonstate.params + 3;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_23")
	pi = self->__commonstate.params + 4;
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
