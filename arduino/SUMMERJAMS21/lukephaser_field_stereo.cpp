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
	t_sample m_sw_27;
	t_sample m_sw_25;
	t_sample m_history_13;
	t_sample m_history_14;
	t_sample m_history_15;
	t_sample m_history_12;
	t_sample m_history_10;
	t_sample m_history_11;
	t_sample m_history_9;
	t_sample m_knob3_depth_26;
	t_sample m_history_16;
	t_sample m_history_18;
	t_sample m_knob4_rate_23;
	t_sample m_knob5_fb_24;
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
		m_knob4_rate_23 = 0.1;
		m_knob5_fb_24 = ((int)0);
		m_sw_25 = ((int)0);
		m_knob3_depth_26 = 1;
		m_sw_27 = ((int)0);
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
		t_sample sub_410 = (m_knob5_fb_24 - ((t_sample)0.5));
		t_sample scale_407 = ((safepow((sub_410 * ((t_sample)2.0408163265306)), ((int)1)) * ((t_sample)-0.15)) + ((t_sample)0.25));
		t_sample mstosamps_97 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_96 = (((int)100) * (samplerate * 0.001));
		t_sample add_101 = (m_sw_27 + ((int)1));
		t_sample choice_30 = int(add_101);
		t_sample iup_32 = (1 / maximum(1, abs(mstosamps_97)));
		t_sample idown_33 = (1 / maximum(1, abs(mstosamps_96)));
		samples_to_seconds = (1 / samplerate);
		t_sample div_220 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_37 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_38 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_40 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_41 = (1 / maximum(1, abs(((int)5))));
		t_sample div_283 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_44 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_45 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_47 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_48 = (1 / maximum(1, abs(((int)5))));
		t_sample div_135 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_52 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_53 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_55 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_56 = (1 / maximum(1, abs(((int)5))));
		t_sample div_177 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_59 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_60 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_62 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_63 = (1 / maximum(1, abs(((int)5))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out6 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample sah_111 = __m_sah_28(m_history_22, m_sw_25, ((int)0));
			t_sample gen_113 = sah_111;
			t_sample rsub_109 = (((int)1) - sah_111);
			t_sample history_110_next_112 = fixdenorm(rsub_109);
			t_sample out3 = gen_113;
			t_sample add_114 = (gen_113 + ((int)1));
			t_sample choice_29 = int(add_114);
			t_sample gate_106 = (((choice_29 >= 1) && (choice_29 < 2)) ? in1 : 0);
			t_sample gate_107 = ((choice_29 >= 2) ? in1 : 0);
			t_sample mul_262 = (m_history_1 * m_knob5_fb_24);
			t_sample add_261 = (gate_107 + mul_262);
			t_sample mul_117 = (m_history_2 * m_knob5_fb_24);
			t_sample add_116 = (gate_107 + mul_117);
			t_sample selector_103 = ((choice_30 >= 2) ? gate_107 : ((choice_30 >= 1) ? ((int)1) : 0));
			t_sample abs_105 = fabs(selector_103);
			__m_slide_31 = fixdenorm((__m_slide_31 + (((abs_105 > __m_slide_31) ? iup_32 : idown_33) * (abs_105 - __m_slide_31))));
			t_sample slide_104 = __m_slide_31;
			t_sample mul_99 = (slide_104 * ((int)10));
			t_sample clamp_98 = ((mul_99 <= ((int)0)) ? ((int)0) : ((mul_99 >= ((int)1)) ? ((int)1) : mul_99));
			t_sample mul_102 = (m_knob3_depth_26 * clamp_98);
			t_sample mix_411 = (m_history_21 + (((t_sample)0.003926980723806) * (m_knob4_rate_23 - m_history_21)));
			t_sample mix_84 = mix_411;
			t_sample mix_412 = (m_history_20 + (((t_sample)0.003926980723806) * (mix_84 - m_history_20)));
			t_sample mix_82 = mix_412;
			t_sample mix_413 = (m_history_19 + (((t_sample)0.003926980723806) * (mix_82 - m_history_19)));
			t_sample mix_80 = mix_413;
			t_sample gen_92 = mix_80;
			t_sample history_86_next_89 = fixdenorm(mix_84);
			t_sample history_83_next_90 = fixdenorm(mix_82);
			t_sample history_81_next_91 = fixdenorm(mix_80);
			t_sample rsub_252 = (((int)1) - gen_92);
			t_sample sqrt_251 = sqrt(rsub_252);
			t_sample sqrt_250 = sqrt(sqrt_251);
			t_sample sqrt_93 = sqrt(sqrt_250);
			t_sample rsub_249 = (((int)1) - sqrt_93);
			t_sample mul_312 = (rsub_249 * ((t_sample)7.5));
			t_sample phasor_268 = __m_phasor_34(mul_312, samples_to_seconds);
			t_sample add_229 = (phasor_268 + ((t_sample)0.25));
			t_sample mod_230 = safemod(add_229, ((int)1));
			__m_cycle_35.phase(mod_230);
			t_sample cycle_227 = __m_cycle_35(__sinedata);
			t_sample cycleindex_228 = __m_cycle_35.phase();
			t_sample add_225 = (cycle_227 + ((int)1));
			t_sample div_224 = (add_225 * ((t_sample)0.5));
			t_sample mul_226 = (div_224 * mul_102);
			t_sample sub_417 = (mul_226 - ((int)0));
			t_sample scale_414 = ((safepow((sub_417 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_231 = scale_414;
			t_sample mtof_232 = mtof(scale_231, ((int)440));
			t_sample mul_219 = (mtof_232 * div_220);
			t_sample cos_217 = cos(mul_219);
			t_sample mul_212 = (cos_217 * (-2));
			t_sample sin_218 = sin(mul_219);
			t_sample mul_216 = (sin_218 * ((t_sample)0.5));
			t_sample div_215 = (mul_216 * ((t_sample)0.33333333333333));
			t_sample rsub_210 = (((int)1) - div_215);
			t_sample add_214 = (div_215 + ((int)1));
			t_sample rdiv_213 = safediv(((int)1), add_214);
			t_sample mul_209 = (rdiv_213 * rsub_210);
			__m_slide_36 = fixdenorm((__m_slide_36 + (((mul_209 > __m_slide_36) ? iup_37 : idown_38) * (mul_209 - __m_slide_36))));
			t_sample slide_206 = __m_slide_36;
			t_sample gen_222 = slide_206;
			t_sample mul_211 = (rdiv_213 * mul_212);
			__m_slide_39 = fixdenorm((__m_slide_39 + (((mul_211 > __m_slide_39) ? iup_40 : idown_41) * (mul_211 - __m_slide_39))));
			t_sample slide_207 = __m_slide_39;
			t_sample gen_221 = slide_207;
			t_sample mul_242 = (add_261 * gen_222);
			t_sample mul_239 = (m_history_16 * gen_221);
			t_sample mul_237 = (m_history_18 * ((int)1));
			t_sample mul_233 = (m_history_17 * gen_222);
			t_sample mul_235 = (m_history_15 * gen_221);
			t_sample sub_241 = (((mul_237 + mul_239) + mul_242) - (mul_235 + mul_233));
			t_sample gen_247 = sub_241;
			t_sample history_238_next_243 = fixdenorm(m_history_16);
			t_sample history_234_next_244 = fixdenorm(m_history_15);
			t_sample history_240_next_245 = fixdenorm(add_261);
			t_sample history_236_next_246 = fixdenorm(sub_241);
			t_sample add_292 = (phasor_268 + ((int)0));
			t_sample mod_293 = safemod(add_292, ((int)1));
			__m_cycle_42.phase(mod_293);
			t_sample cycle_290 = __m_cycle_42(__sinedata);
			t_sample cycleindex_291 = __m_cycle_42.phase();
			t_sample add_288 = (cycle_290 + ((int)1));
			t_sample div_287 = (add_288 * ((t_sample)0.5));
			t_sample mul_289 = (div_287 * mul_102);
			t_sample sub_421 = (mul_289 - ((int)0));
			t_sample scale_418 = ((safepow((sub_421 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_294 = scale_418;
			t_sample mtof_295 = mtof(scale_294, ((int)440));
			t_sample mul_282 = (mtof_295 * div_283);
			t_sample cos_280 = cos(mul_282);
			t_sample mul_275 = (cos_280 * (-2));
			t_sample sin_281 = sin(mul_282);
			t_sample mul_279 = (sin_281 * ((t_sample)0.5));
			t_sample div_278 = (mul_279 * ((t_sample)0.33333333333333));
			t_sample rsub_273 = (((int)1) - div_278);
			t_sample add_277 = (div_278 + ((int)1));
			t_sample rdiv_276 = safediv(((int)1), add_277);
			t_sample mul_272 = (rdiv_276 * rsub_273);
			__m_slide_43 = fixdenorm((__m_slide_43 + (((mul_272 > __m_slide_43) ? iup_44 : idown_45) * (mul_272 - __m_slide_43))));
			t_sample slide_269 = __m_slide_43;
			t_sample gen_285 = slide_269;
			t_sample mul_274 = (rdiv_276 * mul_275);
			__m_slide_46 = fixdenorm((__m_slide_46 + (((mul_274 > __m_slide_46) ? iup_47 : idown_48) * (mul_274 - __m_slide_46))));
			t_sample slide_270 = __m_slide_46;
			t_sample gen_284 = slide_270;
			t_sample mul_305 = (add_261 * gen_285);
			t_sample mul_302 = (m_history_12 * gen_284);
			t_sample mul_300 = (m_history_13 * ((int)1));
			t_sample mul_296 = (m_history_14 * gen_285);
			t_sample mul_298 = (m_history_11 * gen_284);
			t_sample sub_304 = (((mul_300 + mul_302) + mul_305) - (mul_298 + mul_296));
			t_sample gen_310 = sub_304;
			t_sample history_297_next_306 = fixdenorm(m_history_11);
			t_sample history_301_next_307 = fixdenorm(m_history_12);
			t_sample history_303_next_308 = fixdenorm(add_261);
			t_sample history_299_next_309 = fixdenorm(sub_304);
			t_sample mul_248 = (((gate_107 + gen_310) + gen_247) * scale_407);
			t_sample add_255 = (mul_248 + gate_106);
			t_sample out1 = add_255;
			t_sample mul_205 = ((gen_310 + gen_247) * ((t_sample)0.5));
			t_sample dcblock_254 = __m_dcblock_49(mul_205);
			t_sample add_144 = (phasor_268 + ((t_sample)0.375));
			t_sample mod_145 = safemod(add_144, ((int)1));
			__m_cycle_50.phase(mod_145);
			t_sample cycle_142 = __m_cycle_50(__sinedata);
			t_sample cycleindex_143 = __m_cycle_50.phase();
			t_sample add_140 = (cycle_142 + ((int)1));
			t_sample div_139 = (add_140 * ((t_sample)0.5));
			t_sample mul_141 = (div_139 * mul_102);
			t_sample sub_425 = (mul_141 - ((int)0));
			t_sample scale_422 = ((safepow((sub_425 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_146 = scale_422;
			t_sample mtof_147 = mtof(scale_146, ((int)440));
			t_sample mul_134 = (mtof_147 * div_135);
			t_sample cos_132 = cos(mul_134);
			t_sample mul_127 = (cos_132 * (-2));
			t_sample sin_133 = sin(mul_134);
			t_sample mul_131 = (sin_133 * ((t_sample)0.5));
			t_sample div_130 = (mul_131 * ((t_sample)0.33333333333333));
			t_sample rsub_125 = (((int)1) - div_130);
			t_sample add_129 = (div_130 + ((int)1));
			t_sample rdiv_128 = safediv(((int)1), add_129);
			t_sample mul_126 = (rdiv_128 * mul_127);
			__m_slide_51 = fixdenorm((__m_slide_51 + (((mul_126 > __m_slide_51) ? iup_52 : idown_53) * (mul_126 - __m_slide_51))));
			t_sample slide_122 = __m_slide_51;
			t_sample gen_136 = slide_122;
			t_sample mul_124 = (rdiv_128 * rsub_125);
			__m_slide_54 = fixdenorm((__m_slide_54 + (((mul_124 > __m_slide_54) ? iup_55 : idown_56) * (mul_124 - __m_slide_54))));
			t_sample slide_121 = __m_slide_54;
			t_sample gen_137 = slide_121;
			t_sample mul_157 = (add_116 * gen_137);
			t_sample mul_154 = (m_history_8 * gen_136);
			t_sample mul_152 = (m_history_9 * ((int)1));
			t_sample mul_148 = (m_history_10 * gen_137);
			t_sample mul_150 = (m_history_7 * gen_136);
			t_sample sub_156 = (((mul_152 + mul_154) + mul_157) - (mul_150 + mul_148));
			t_sample gen_162 = sub_156;
			t_sample history_149_next_158 = fixdenorm(m_history_7);
			t_sample history_153_next_159 = fixdenorm(m_history_8);
			t_sample history_155_next_160 = fixdenorm(add_116);
			t_sample history_151_next_161 = fixdenorm(sub_156);
			t_sample add_186 = (phasor_268 + ((t_sample)0.125));
			t_sample mod_187 = safemod(add_186, ((int)1));
			__m_cycle_57.phase(mod_187);
			t_sample cycle_184 = __m_cycle_57(__sinedata);
			t_sample cycleindex_185 = __m_cycle_57.phase();
			t_sample add_182 = (cycle_184 + ((int)1));
			t_sample div_181 = (add_182 * ((t_sample)0.5));
			t_sample mul_183 = (div_181 * mul_102);
			t_sample sub_429 = (mul_183 - ((int)0));
			t_sample scale_426 = ((safepow((sub_429 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_188 = scale_426;
			t_sample mtof_189 = mtof(scale_188, ((int)440));
			t_sample mul_176 = (mtof_189 * div_177);
			t_sample cos_174 = cos(mul_176);
			t_sample mul_169 = (cos_174 * (-2));
			t_sample sin_175 = sin(mul_176);
			t_sample mul_173 = (sin_175 * ((t_sample)0.5));
			t_sample div_172 = (mul_173 * ((t_sample)0.33333333333333));
			t_sample rsub_167 = (((int)1) - div_172);
			t_sample add_171 = (div_172 + ((int)1));
			t_sample rdiv_170 = safediv(((int)1), add_171);
			t_sample mul_166 = (rdiv_170 * rsub_167);
			__m_slide_58 = fixdenorm((__m_slide_58 + (((mul_166 > __m_slide_58) ? iup_59 : idown_60) * (mul_166 - __m_slide_58))));
			t_sample slide_163 = __m_slide_58;
			t_sample gen_179 = slide_163;
			t_sample mul_168 = (rdiv_170 * mul_169);
			__m_slide_61 = fixdenorm((__m_slide_61 + (((mul_168 > __m_slide_61) ? iup_62 : idown_63) * (mul_168 - __m_slide_61))));
			t_sample slide_164 = __m_slide_61;
			t_sample gen_178 = slide_164;
			t_sample mul_199 = (add_116 * gen_179);
			t_sample mul_196 = (m_history_4 * gen_178);
			t_sample mul_194 = (m_history_5 * ((int)1));
			t_sample mul_190 = (m_history_6 * gen_179);
			t_sample mul_192 = (m_history_3 * gen_178);
			t_sample sub_198 = (((mul_194 + mul_196) + mul_199) - (mul_192 + mul_190));
			t_sample gen_204 = sub_198;
			t_sample history_191_next_200 = fixdenorm(m_history_3);
			t_sample history_195_next_201 = fixdenorm(m_history_4);
			t_sample history_197_next_202 = fixdenorm(add_116);
			t_sample history_193_next_203 = fixdenorm(sub_198);
			t_sample mul_118 = ((gen_204 + gen_162) * ((t_sample)0.5));
			t_sample dcblock_119 = __m_dcblock_64(mul_118);
			t_sample mul_120 = (((gate_107 + gen_204) + gen_162) * scale_407);
			t_sample add_253 = (mul_120 + gate_106);
			t_sample out2 = add_253;
			t_sample history_115_next_313 = fixdenorm(dcblock_254);
			t_sample history_260_next_314 = fixdenorm(dcblock_119);
			m_history_22 = history_110_next_112;
			m_history_21 = history_86_next_89;
			m_history_19 = history_81_next_91;
			m_history_20 = history_83_next_90;
			m_history_18 = history_238_next_243;
			m_history_15 = history_236_next_246;
			m_history_16 = history_240_next_245;
			m_history_17 = history_234_next_244;
			m_history_14 = history_297_next_306;
			m_history_11 = history_299_next_309;
			m_history_12 = history_303_next_308;
			m_history_13 = history_301_next_307;
			m_history_10 = history_149_next_158;
			m_history_7 = history_151_next_161;
			m_history_8 = history_155_next_160;
			m_history_9 = history_153_next_159;
			m_history_6 = history_191_next_200;
			m_history_3 = history_193_next_203;
			m_history_4 = history_197_next_202;
			m_history_5 = history_195_next_201;
			m_history_2 = history_115_next_313;
			m_history_1 = history_260_next_314;
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
		m_knob4_rate_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_fb(t_param _value) {
		m_knob5_fb_24 = (_value < 0.5 ? 0.5 : (_value > 0.99 ? 0.99 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_depth(t_param _value) {
		m_knob3_depth_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: *value = self->m_knob3_depth_26; break;
		case 1: *value = self->m_knob4_rate_23; break;
		case 2: *value = self->m_knob5_fb_24; break;
		case 3: *value = self->m_sw_25; break;
		case 4: *value = self->m_sw_27; break;
		
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
	// initialize parameter 0 ("m_knob3_depth_26")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_depth_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_rate_23")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_rate_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_fb_24")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_fb_24;
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
	// initialize parameter 4 ("m_sw_27")
	pi = self->__commonstate.params + 4;
	pi->name = "sw5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_27;
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
