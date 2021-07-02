#include "lukephaser.h"

namespace lukephaser {

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
	DCBlock __m_dcblock_220;
	DCBlock __m_dcblock_147;
	Phasor __m_phasor_74;
	Sah __m_sah_121;
	Sah __m_sah_130;
	Sah __m_sah_212;
	Sah __m_sah_149;
	Sah __m_sah_112;
	Sah __m_sah_94;
	Sah __m_sah_103;
	Sah __m_sah_76;
	Sah __m_sah_85;
	Sah __m_sah_158;
	Sah __m_sah_139;
	Sah __m_sah_185;
	Sah __m_sah_194;
	Sah __m_sah_203;
	Sah __m_sah_176;
	Sah __m_sah_167;
	SineCycle __m_cycle_102;
	SineCycle __m_cycle_93;
	SineCycle __m_cycle_202;
	SineCycle __m_cycle_84;
	SineCycle __m_cycle_193;
	SineCycle __m_cycle_75;
	SineCycle __m_cycle_111;
	SineCycle __m_cycle_157;
	SineCycle __m_cycle_120;
	SineCycle __m_cycle_166;
	SineCycle __m_cycle_148;
	SineCycle __m_cycle_138;
	SineCycle __m_cycle_175;
	SineCycle __m_cycle_211;
	SineCycle __m_cycle_129;
	SineCycle __m_cycle_184;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_35;
	t_sample m_history_17;
	t_sample m_history_16;
	t_sample __m_slide_135;
	t_sample __m_slide_132;
	t_sample __m_slide_141;
	t_sample __m_slide_144;
	t_sample m_history_15;
	t_sample __m_slide_151;
	t_sample m_history_18;
	t_sample m_history_13;
	t_sample m_history_14;
	t_sample __m_slide_154;
	t_sample m_history_19;
	t_sample __m_slide_123;
	t_sample __m_slide_108;
	t_sample m_history_23;
	t_sample __m_slide_105;
	t_sample m_history_24;
	t_sample __m_slide_126;
	t_sample m_history_22;
	t_sample __m_slide_117;
	t_sample __m_slide_114;
	t_sample m_history_20;
	t_sample m_history_21;
	t_sample m_history_12;
	t_sample m_history_11;
	t_sample __m_slide_160;
	t_sample __m_slide_196;
	t_sample __m_slide_199;
	t_sample m_history_3;
	t_sample m_history_4;
	t_sample __m_slide_190;
	t_sample m_history_2;
	t_sample __m_slide_205;
	t_sample __m_slide_214;
	t_sample m_history_1;
	t_sample samplerate;
	t_sample __m_slide_208;
	t_sample m_history_25;
	t_sample __m_slide_187;
	t_sample m_history_6;
	t_sample m_history_9;
	t_sample __m_slide_169;
	t_sample m_history_10;
	t_sample __m_slide_163;
	t_sample m_history_5;
	t_sample __m_slide_172;
	t_sample m_history_7;
	t_sample m_history_8;
	t_sample __m_slide_181;
	t_sample __m_slide_178;
	t_sample m_history_34;
	t_sample __m_slide_99;
	t_sample m_history_26;
	t_sample m_history_51;
	t_sample m_history_52;
	t_sample m_history_50;
	t_sample m_history_49;
	t_sample m_history_48;
	t_sample m_history_53;
	t_sample m_history_55;
	t_sample m_history_58;
	t_sample m_history_54;
	t_sample m_history_57;
	t_sample m_history_56;
	t_sample m_history_59;
	t_sample m_history_47;
	t_sample m_history_45;
	t_sample m_history_38;
	t_sample m_history_39;
	t_sample m_history_37;
	t_sample m_history_36;
	t_sample m_history_46;
	t_sample m_history_40;
	t_sample m_history_42;
	t_sample m_history_41;
	t_sample m_history_44;
	t_sample m_history_43;
	t_sample __m_slide_96;
	t_sample m_history_60;
	t_sample m_history_62;
	t_sample m_history_30;
	t_sample __m_slide_78;
	t_sample m_history_31;
	t_sample m_history_32;
	t_sample m_history_33;
	t_sample __m_slide_81;
	t_sample m_history_28;
	t_sample m_history_27;
	t_sample m_history_29;
	t_sample __m_slide_90;
	t_sample __m_slide_87;
	t_sample m_history_61;
	t_sample samples_to_seconds;
	t_sample m_gain_72;
	t_sample m_history_65;
	t_sample m_history_66;
	t_sample m_history_64;
	t_sample m_history_63;
	t_sample m_Q_73;
	t_sample m_rate_67;
	t_sample m_waveform_69;
	t_sample m_fb_68;
	t_sample m_diffusion_71;
	t_sample __m_slide_217;
	t_sample m_width_70;
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
		m_history_35 = ((int)0);
		m_history_36 = ((int)0);
		m_history_37 = ((int)0);
		m_history_38 = ((int)0);
		m_history_39 = ((int)0);
		m_history_40 = ((int)0);
		m_history_41 = ((int)0);
		m_history_42 = ((int)0);
		m_history_43 = ((int)0);
		m_history_44 = ((int)0);
		m_history_45 = ((int)0);
		m_history_46 = ((int)0);
		m_history_47 = ((int)0);
		m_history_48 = ((int)0);
		m_history_49 = ((int)0);
		m_history_50 = ((int)0);
		m_history_51 = ((int)0);
		m_history_52 = ((int)0);
		m_history_53 = ((int)0);
		m_history_54 = ((int)0);
		m_history_55 = ((int)0);
		m_history_56 = ((int)0);
		m_history_57 = ((int)0);
		m_history_58 = ((int)0);
		m_history_59 = ((int)0);
		m_history_60 = ((int)0);
		m_history_61 = ((int)0);
		m_history_62 = ((int)0);
		m_history_63 = ((int)0);
		m_history_64 = ((int)0);
		m_history_65 = ((int)0);
		m_history_66 = ((int)0);
		m_rate_67 = 0.1;
		m_fb_68 = 0;
		m_waveform_69 = 1;
		m_width_70 = 1;
		m_diffusion_71 = 0;
		m_gain_72 = 1;
		m_Q_73 = 0.5;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_74.reset(0);
		__m_cycle_75.reset(samplerate, 0);
		__m_sah_76.reset(0);
		__m_slide_78 = 0;
		__m_slide_81 = 0;
		__m_cycle_84.reset(samplerate, 0);
		__m_sah_85.reset(0);
		__m_slide_87 = 0;
		__m_slide_90 = 0;
		__m_cycle_93.reset(samplerate, 0);
		__m_sah_94.reset(0);
		__m_slide_96 = 0;
		__m_slide_99 = 0;
		__m_cycle_102.reset(samplerate, 0);
		__m_sah_103.reset(0);
		__m_slide_105 = 0;
		__m_slide_108 = 0;
		__m_cycle_111.reset(samplerate, 0);
		__m_sah_112.reset(0);
		__m_slide_114 = 0;
		__m_slide_117 = 0;
		__m_cycle_120.reset(samplerate, 0);
		__m_sah_121.reset(0);
		__m_slide_123 = 0;
		__m_slide_126 = 0;
		__m_cycle_129.reset(samplerate, 0);
		__m_sah_130.reset(0);
		__m_slide_132 = 0;
		__m_slide_135 = 0;
		__m_cycle_138.reset(samplerate, 0);
		__m_sah_139.reset(0);
		__m_slide_141 = 0;
		__m_slide_144 = 0;
		__m_dcblock_147.reset();
		__m_cycle_148.reset(samplerate, 0);
		__m_sah_149.reset(0);
		__m_slide_151 = 0;
		__m_slide_154 = 0;
		__m_cycle_157.reset(samplerate, 0);
		__m_sah_158.reset(0);
		__m_slide_160 = 0;
		__m_slide_163 = 0;
		__m_cycle_166.reset(samplerate, 0);
		__m_sah_167.reset(0);
		__m_slide_169 = 0;
		__m_slide_172 = 0;
		__m_cycle_175.reset(samplerate, 0);
		__m_sah_176.reset(0);
		__m_slide_178 = 0;
		__m_slide_181 = 0;
		__m_cycle_184.reset(samplerate, 0);
		__m_sah_185.reset(0);
		__m_slide_187 = 0;
		__m_slide_190 = 0;
		__m_cycle_193.reset(samplerate, 0);
		__m_sah_194.reset(0);
		__m_slide_196 = 0;
		__m_slide_199 = 0;
		__m_cycle_202.reset(samplerate, 0);
		__m_sah_203.reset(0);
		__m_slide_205 = 0;
		__m_slide_208 = 0;
		__m_cycle_211.reset(samplerate, 0);
		__m_sah_212.reset(0);
		__m_slide_214 = 0;
		__m_slide_217 = 0;
		__m_dcblock_220.reset();
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		samples_to_seconds = (1 / samplerate);
		t_sample mul_6 = (m_diffusion_71 * ((int)7));
		t_sample div_5 = (mul_6 * ((t_sample)0.125));
		t_sample mul_10 = (m_diffusion_71 * ((int)6));
		t_sample div_7 = (mul_10 * ((t_sample)0.125));
		t_sample mul_11 = (m_diffusion_71 * ((int)5));
		t_sample div_8 = (mul_11 * ((t_sample)0.125));
		t_sample mul_12 = (m_diffusion_71 * ((int)4));
		t_sample div_9 = (mul_12 * ((t_sample)0.125));
		t_sample mul_755 = (m_diffusion_71 * ((int)3));
		t_sample div_754 = (mul_755 * ((t_sample)0.125));
		t_sample mul_759 = (m_diffusion_71 * ((int)2));
		t_sample div_756 = (mul_759 * ((t_sample)0.125));
		t_sample mul_760 = (m_diffusion_71 * ((int)1));
		t_sample div_757 = (mul_760 * ((t_sample)0.125));
		t_sample mul_761 = (m_diffusion_71 * ((int)0));
		t_sample div_758 = (mul_761 * ((t_sample)0.125));
		t_sample choice_77 = int(m_waveform_69);
		t_sample div_377 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_79 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_80 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_82 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_83 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_86 = int(m_waveform_69);
		t_sample div_328 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_88 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_89 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_91 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_92 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_95 = int(m_waveform_69);
		t_sample div_279 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_97 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_98 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_100 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_101 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_104 = int(m_waveform_69);
		t_sample div_230 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_106 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_107 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_109 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_110 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_113 = int(m_waveform_69);
		t_sample div_181 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_115 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_116 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_118 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_119 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_122 = int(m_waveform_69);
		t_sample div_132 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_124 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_125 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_127 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_128 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_131 = int(m_waveform_69);
		t_sample div_83 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_133 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_134 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_136 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_137 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_140 = int(m_waveform_69);
		t_sample div_34 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_142 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_143 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_145 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_146 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_150 = int(m_waveform_69);
		t_sample div_783 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_152 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_153 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_155 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_156 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_159 = int(m_waveform_69);
		t_sample div_723 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_161 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_162 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_164 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_165 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_168 = int(m_waveform_69);
		t_sample div_674 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_170 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_171 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_173 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_174 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_177 = int(m_waveform_69);
		t_sample div_625 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_179 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_180 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_182 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_183 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_186 = int(m_waveform_69);
		t_sample div_573 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_188 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_189 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_191 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_192 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_195 = int(m_waveform_69);
		t_sample div_524 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_197 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_198 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_200 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_201 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_204 = int(m_waveform_69);
		t_sample div_475 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_206 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_207 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_209 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_210 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_213 = int(m_waveform_69);
		t_sample div_426 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_215 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_216 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_218 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_219 = (1 / maximum(1, abs(((int)5))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample phasor_764 = __m_phasor_74(m_rate_67, samples_to_seconds);
			t_sample add_4 = (phasor_764 + ((t_sample)0.25));
			t_sample mod_3 = safemod(add_4, ((int)1));
			t_sample mul_814 = (in1 * m_gain_72);
			t_sample mul_14 = (m_history_2 * m_fb_68);
			t_sample add_15 = (mul_814 + mul_14);
			t_sample add_389 = (mod_3 + div_758);
			t_sample mod_390 = safemod(add_389, ((int)1));
			t_sample triangle_386 = triangle(mod_390, ((t_sample)0.5));
			int gt_385 = (mod_390 > ((t_sample)0.5));
			__m_cycle_75.phase(mod_390);
			t_sample cycle_387 = __m_cycle_75(__sinedata);
			t_sample cycleindex_388 = __m_cycle_75.phase();
			t_sample add_383 = (cycle_387 + ((int)1));
			t_sample div_382 = (add_383 * ((t_sample)0.5));
			t_sample noise_361 = noise();
			t_sample sah_362 = __m_sah_76(noise_361, mod_390, ((t_sample)0.5));
			t_sample add_360 = (sah_362 + ((int)1));
			t_sample div_359 = (add_360 * ((t_sample)0.5));
			t_sample selector_381 = ((choice_77 >= 5) ? div_359 : ((choice_77 >= 4) ? gt_385 : ((choice_77 >= 3) ? mod_390 : ((choice_77 >= 2) ? triangle_386 : ((choice_77 >= 1) ? div_382 : 0)))));
			t_sample mul_384 = (selector_381 * m_width_70);
			t_sample sub_1983 = (mul_384 - ((int)0));
			t_sample scale_1980 = ((safepow((sub_1983 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_391 = scale_1980;
			t_sample mtof_392 = mtof(scale_391, ((int)440));
			t_sample mul_376 = (mtof_392 * div_377);
			t_sample cos_374 = cos(mul_376);
			t_sample mul_369 = (cos_374 * (-2));
			t_sample sin_375 = sin(mul_376);
			t_sample mul_373 = (sin_375 * ((t_sample)0.5));
			t_sample div_372 = safediv(mul_373, m_Q_73);
			t_sample rsub_367 = (((int)1) - div_372);
			t_sample add_371 = (div_372 + ((int)1));
			t_sample rdiv_370 = safediv(((int)1), add_371);
			t_sample mul_368 = (rdiv_370 * mul_369);
			__m_slide_78 = fixdenorm((__m_slide_78 + (((mul_368 > __m_slide_78) ? iup_79 : idown_80) * (mul_368 - __m_slide_78))));
			t_sample slide_364 = __m_slide_78;
			t_sample gen_378 = slide_364;
			t_sample mul_366 = (rdiv_370 * rsub_367);
			__m_slide_81 = fixdenorm((__m_slide_81 + (((mul_366 > __m_slide_81) ? iup_82 : idown_83) * (mul_366 - __m_slide_81))));
			t_sample slide_363 = __m_slide_81;
			t_sample gen_379 = slide_363;
			t_sample mul_402 = (add_15 * gen_379);
			t_sample mul_399 = (m_history_64 * gen_378);
			t_sample mul_397 = (m_history_65 * ((int)1));
			t_sample mul_393 = (m_history_66 * gen_379);
			t_sample mul_395 = (m_history_63 * gen_378);
			t_sample sub_401 = (((mul_397 + mul_399) + mul_402) - (mul_395 + mul_393));
			t_sample gen_407 = sub_401;
			t_sample history_394_next_403 = fixdenorm(m_history_63);
			t_sample history_398_next_404 = fixdenorm(m_history_64);
			t_sample history_400_next_405 = fixdenorm(add_15);
			t_sample history_396_next_406 = fixdenorm(sub_401);
			t_sample add_340 = (mod_3 + div_757);
			t_sample mod_341 = safemod(add_340, ((int)1));
			t_sample triangle_337 = triangle(mod_341, ((t_sample)0.5));
			int gt_336 = (mod_341 > ((t_sample)0.5));
			__m_cycle_84.phase(mod_341);
			t_sample cycle_338 = __m_cycle_84(__sinedata);
			t_sample cycleindex_339 = __m_cycle_84.phase();
			t_sample add_334 = (cycle_338 + ((int)1));
			t_sample div_333 = (add_334 * ((t_sample)0.5));
			t_sample noise_312 = noise();
			t_sample sah_313 = __m_sah_85(noise_312, mod_341, ((t_sample)0.5));
			t_sample add_311 = (sah_313 + ((int)1));
			t_sample div_310 = (add_311 * ((t_sample)0.5));
			t_sample selector_332 = ((choice_86 >= 5) ? div_310 : ((choice_86 >= 4) ? gt_336 : ((choice_86 >= 3) ? mod_341 : ((choice_86 >= 2) ? triangle_337 : ((choice_86 >= 1) ? div_333 : 0)))));
			t_sample mul_335 = (selector_332 * m_width_70);
			t_sample sub_1987 = (mul_335 - ((int)0));
			t_sample scale_1984 = ((safepow((sub_1987 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_342 = scale_1984;
			t_sample mtof_343 = mtof(scale_342, ((int)440));
			t_sample mul_327 = (mtof_343 * div_328);
			t_sample cos_325 = cos(mul_327);
			t_sample mul_320 = (cos_325 * (-2));
			t_sample sin_326 = sin(mul_327);
			t_sample mul_324 = (sin_326 * ((t_sample)0.5));
			t_sample div_323 = safediv(mul_324, m_Q_73);
			t_sample rsub_318 = (((int)1) - div_323);
			t_sample add_322 = (div_323 + ((int)1));
			t_sample rdiv_321 = safediv(((int)1), add_322);
			t_sample mul_317 = (rdiv_321 * rsub_318);
			__m_slide_87 = fixdenorm((__m_slide_87 + (((mul_317 > __m_slide_87) ? iup_88 : idown_89) * (mul_317 - __m_slide_87))));
			t_sample slide_314 = __m_slide_87;
			t_sample gen_330 = slide_314;
			t_sample mul_319 = (rdiv_321 * mul_320);
			__m_slide_90 = fixdenorm((__m_slide_90 + (((mul_319 > __m_slide_90) ? iup_91 : idown_92) * (mul_319 - __m_slide_90))));
			t_sample slide_315 = __m_slide_90;
			t_sample gen_329 = slide_315;
			t_sample mul_353 = (gen_407 * gen_330);
			t_sample mul_350 = (m_history_60 * gen_329);
			t_sample mul_348 = (m_history_62 * ((int)1));
			t_sample mul_344 = (m_history_61 * gen_330);
			t_sample mul_346 = (m_history_59 * gen_329);
			t_sample sub_352 = (((mul_348 + mul_350) + mul_353) - (mul_346 + mul_344));
			t_sample gen_358 = sub_352;
			t_sample history_349_next_354 = fixdenorm(m_history_60);
			t_sample history_345_next_355 = fixdenorm(m_history_59);
			t_sample history_351_next_356 = fixdenorm(gen_407);
			t_sample history_347_next_357 = fixdenorm(sub_352);
			t_sample add_291 = (mod_3 + div_756);
			t_sample mod_292 = safemod(add_291, ((int)1));
			t_sample triangle_288 = triangle(mod_292, ((t_sample)0.5));
			int gt_287 = (mod_292 > ((t_sample)0.5));
			__m_cycle_93.phase(mod_292);
			t_sample cycle_289 = __m_cycle_93(__sinedata);
			t_sample cycleindex_290 = __m_cycle_93.phase();
			t_sample add_285 = (cycle_289 + ((int)1));
			t_sample div_284 = (add_285 * ((t_sample)0.5));
			t_sample noise_263 = noise();
			t_sample sah_264 = __m_sah_94(noise_263, mod_292, ((t_sample)0.5));
			t_sample add_262 = (sah_264 + ((int)1));
			t_sample div_261 = (add_262 * ((t_sample)0.5));
			t_sample selector_283 = ((choice_95 >= 5) ? div_261 : ((choice_95 >= 4) ? gt_287 : ((choice_95 >= 3) ? mod_292 : ((choice_95 >= 2) ? triangle_288 : ((choice_95 >= 1) ? div_284 : 0)))));
			t_sample mul_286 = (selector_283 * m_width_70);
			t_sample sub_1991 = (mul_286 - ((int)0));
			t_sample scale_1988 = ((safepow((sub_1991 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_293 = scale_1988;
			t_sample mtof_294 = mtof(scale_293, ((int)440));
			t_sample mul_278 = (mtof_294 * div_279);
			t_sample cos_276 = cos(mul_278);
			t_sample mul_271 = (cos_276 * (-2));
			t_sample sin_277 = sin(mul_278);
			t_sample mul_275 = (sin_277 * ((t_sample)0.5));
			t_sample div_274 = safediv(mul_275, m_Q_73);
			t_sample rsub_269 = (((int)1) - div_274);
			t_sample add_273 = (div_274 + ((int)1));
			t_sample rdiv_272 = safediv(((int)1), add_273);
			t_sample mul_268 = (rdiv_272 * rsub_269);
			__m_slide_96 = fixdenorm((__m_slide_96 + (((mul_268 > __m_slide_96) ? iup_97 : idown_98) * (mul_268 - __m_slide_96))));
			t_sample slide_265 = __m_slide_96;
			t_sample gen_281 = slide_265;
			t_sample mul_270 = (rdiv_272 * mul_271);
			__m_slide_99 = fixdenorm((__m_slide_99 + (((mul_270 > __m_slide_99) ? iup_100 : idown_101) * (mul_270 - __m_slide_99))));
			t_sample slide_266 = __m_slide_99;
			t_sample gen_280 = slide_266;
			t_sample mul_304 = (gen_358 * gen_281);
			t_sample mul_301 = (m_history_56 * gen_280);
			t_sample mul_299 = (m_history_58 * ((int)1));
			t_sample mul_295 = (m_history_57 * gen_281);
			t_sample mul_297 = (m_history_55 * gen_280);
			t_sample sub_303 = (((mul_299 + mul_301) + mul_304) - (mul_297 + mul_295));
			t_sample gen_309 = sub_303;
			t_sample history_300_next_305 = fixdenorm(m_history_56);
			t_sample history_296_next_306 = fixdenorm(m_history_55);
			t_sample history_302_next_307 = fixdenorm(gen_358);
			t_sample history_298_next_308 = fixdenorm(sub_303);
			t_sample add_242 = (mod_3 + div_754);
			t_sample mod_243 = safemod(add_242, ((int)1));
			t_sample triangle_239 = triangle(mod_243, ((t_sample)0.5));
			int gt_238 = (mod_243 > ((t_sample)0.5));
			__m_cycle_102.phase(mod_243);
			t_sample cycle_240 = __m_cycle_102(__sinedata);
			t_sample cycleindex_241 = __m_cycle_102.phase();
			t_sample add_236 = (cycle_240 + ((int)1));
			t_sample div_235 = (add_236 * ((t_sample)0.5));
			t_sample noise_214 = noise();
			t_sample sah_215 = __m_sah_103(noise_214, mod_243, ((t_sample)0.5));
			t_sample add_213 = (sah_215 + ((int)1));
			t_sample div_212 = (add_213 * ((t_sample)0.5));
			t_sample selector_234 = ((choice_104 >= 5) ? div_212 : ((choice_104 >= 4) ? gt_238 : ((choice_104 >= 3) ? mod_243 : ((choice_104 >= 2) ? triangle_239 : ((choice_104 >= 1) ? div_235 : 0)))));
			t_sample mul_237 = (selector_234 * m_width_70);
			t_sample sub_1995 = (mul_237 - ((int)0));
			t_sample scale_1992 = ((safepow((sub_1995 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_244 = scale_1992;
			t_sample mtof_245 = mtof(scale_244, ((int)440));
			t_sample mul_229 = (mtof_245 * div_230);
			t_sample cos_227 = cos(mul_229);
			t_sample mul_222 = (cos_227 * (-2));
			t_sample sin_228 = sin(mul_229);
			t_sample mul_226 = (sin_228 * ((t_sample)0.5));
			t_sample div_225 = safediv(mul_226, m_Q_73);
			t_sample rsub_220 = (((int)1) - div_225);
			t_sample add_224 = (div_225 + ((int)1));
			t_sample rdiv_223 = safediv(((int)1), add_224);
			t_sample mul_219 = (rdiv_223 * rsub_220);
			__m_slide_105 = fixdenorm((__m_slide_105 + (((mul_219 > __m_slide_105) ? iup_106 : idown_107) * (mul_219 - __m_slide_105))));
			t_sample slide_216 = __m_slide_105;
			t_sample gen_232 = slide_216;
			t_sample mul_221 = (rdiv_223 * mul_222);
			__m_slide_108 = fixdenorm((__m_slide_108 + (((mul_221 > __m_slide_108) ? iup_109 : idown_110) * (mul_221 - __m_slide_108))));
			t_sample slide_217 = __m_slide_108;
			t_sample gen_231 = slide_217;
			t_sample mul_255 = (gen_309 * gen_232);
			t_sample mul_252 = (m_history_52 * gen_231);
			t_sample mul_250 = (m_history_54 * ((int)1));
			t_sample mul_246 = (m_history_53 * gen_232);
			t_sample mul_248 = (m_history_51 * gen_231);
			t_sample sub_254 = (((mul_250 + mul_252) + mul_255) - (mul_248 + mul_246));
			t_sample gen_260 = sub_254;
			t_sample history_251_next_256 = fixdenorm(m_history_52);
			t_sample history_247_next_257 = fixdenorm(m_history_51);
			t_sample history_253_next_258 = fixdenorm(gen_309);
			t_sample history_249_next_259 = fixdenorm(sub_254);
			t_sample add_193 = (mod_3 + div_9);
			t_sample mod_194 = safemod(add_193, ((int)1));
			t_sample triangle_190 = triangle(mod_194, ((t_sample)0.5));
			int gt_189 = (mod_194 > ((t_sample)0.5));
			__m_cycle_111.phase(mod_194);
			t_sample cycle_191 = __m_cycle_111(__sinedata);
			t_sample cycleindex_192 = __m_cycle_111.phase();
			t_sample add_187 = (cycle_191 + ((int)1));
			t_sample div_186 = (add_187 * ((t_sample)0.5));
			t_sample noise_165 = noise();
			t_sample sah_166 = __m_sah_112(noise_165, mod_194, ((t_sample)0.5));
			t_sample add_164 = (sah_166 + ((int)1));
			t_sample div_163 = (add_164 * ((t_sample)0.5));
			t_sample selector_185 = ((choice_113 >= 5) ? div_163 : ((choice_113 >= 4) ? gt_189 : ((choice_113 >= 3) ? mod_194 : ((choice_113 >= 2) ? triangle_190 : ((choice_113 >= 1) ? div_186 : 0)))));
			t_sample mul_188 = (selector_185 * m_width_70);
			t_sample sub_1999 = (mul_188 - ((int)0));
			t_sample scale_1996 = ((safepow((sub_1999 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_195 = scale_1996;
			t_sample mtof_196 = mtof(scale_195, ((int)440));
			t_sample mul_180 = (mtof_196 * div_181);
			t_sample cos_178 = cos(mul_180);
			t_sample mul_173 = (cos_178 * (-2));
			t_sample sin_179 = sin(mul_180);
			t_sample mul_177 = (sin_179 * ((t_sample)0.5));
			t_sample div_176 = safediv(mul_177, m_Q_73);
			t_sample rsub_171 = (((int)1) - div_176);
			t_sample add_175 = (div_176 + ((int)1));
			t_sample rdiv_174 = safediv(((int)1), add_175);
			t_sample mul_172 = (rdiv_174 * mul_173);
			__m_slide_114 = fixdenorm((__m_slide_114 + (((mul_172 > __m_slide_114) ? iup_115 : idown_116) * (mul_172 - __m_slide_114))));
			t_sample slide_168 = __m_slide_114;
			t_sample gen_182 = slide_168;
			t_sample mul_170 = (rdiv_174 * rsub_171);
			__m_slide_117 = fixdenorm((__m_slide_117 + (((mul_170 > __m_slide_117) ? iup_118 : idown_119) * (mul_170 - __m_slide_117))));
			t_sample slide_167 = __m_slide_117;
			t_sample gen_183 = slide_167;
			t_sample mul_206 = (gen_260 * gen_183);
			t_sample mul_203 = (m_history_48 * gen_182);
			t_sample mul_201 = (m_history_50 * ((int)1));
			t_sample mul_197 = (m_history_49 * gen_183);
			t_sample mul_199 = (m_history_47 * gen_182);
			t_sample sub_205 = (((mul_201 + mul_203) + mul_206) - (mul_199 + mul_197));
			t_sample gen_211 = sub_205;
			t_sample history_202_next_207 = fixdenorm(m_history_48);
			t_sample history_198_next_208 = fixdenorm(m_history_47);
			t_sample history_204_next_209 = fixdenorm(gen_260);
			t_sample history_200_next_210 = fixdenorm(sub_205);
			t_sample add_144 = (mod_3 + div_8);
			t_sample mod_145 = safemod(add_144, ((int)1));
			t_sample triangle_141 = triangle(mod_145, ((t_sample)0.5));
			int gt_140 = (mod_145 > ((t_sample)0.5));
			__m_cycle_120.phase(mod_145);
			t_sample cycle_142 = __m_cycle_120(__sinedata);
			t_sample cycleindex_143 = __m_cycle_120.phase();
			t_sample add_138 = (cycle_142 + ((int)1));
			t_sample div_137 = (add_138 * ((t_sample)0.5));
			t_sample noise_116 = noise();
			t_sample sah_117 = __m_sah_121(noise_116, mod_145, ((t_sample)0.5));
			t_sample add_115 = (sah_117 + ((int)1));
			t_sample div_114 = (add_115 * ((t_sample)0.5));
			t_sample selector_136 = ((choice_122 >= 5) ? div_114 : ((choice_122 >= 4) ? gt_140 : ((choice_122 >= 3) ? mod_145 : ((choice_122 >= 2) ? triangle_141 : ((choice_122 >= 1) ? div_137 : 0)))));
			t_sample mul_139 = (selector_136 * m_width_70);
			t_sample sub_2003 = (mul_139 - ((int)0));
			t_sample scale_2000 = ((safepow((sub_2003 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_146 = scale_2000;
			t_sample mtof_147 = mtof(scale_146, ((int)440));
			t_sample mul_131 = (mtof_147 * div_132);
			t_sample cos_129 = cos(mul_131);
			t_sample mul_124 = (cos_129 * (-2));
			t_sample sin_130 = sin(mul_131);
			t_sample mul_128 = (sin_130 * ((t_sample)0.5));
			t_sample div_127 = safediv(mul_128, m_Q_73);
			t_sample rsub_122 = (((int)1) - div_127);
			t_sample add_126 = (div_127 + ((int)1));
			t_sample rdiv_125 = safediv(((int)1), add_126);
			t_sample mul_121 = (rdiv_125 * rsub_122);
			__m_slide_123 = fixdenorm((__m_slide_123 + (((mul_121 > __m_slide_123) ? iup_124 : idown_125) * (mul_121 - __m_slide_123))));
			t_sample slide_118 = __m_slide_123;
			t_sample gen_134 = slide_118;
			t_sample mul_123 = (rdiv_125 * mul_124);
			__m_slide_126 = fixdenorm((__m_slide_126 + (((mul_123 > __m_slide_126) ? iup_127 : idown_128) * (mul_123 - __m_slide_126))));
			t_sample slide_119 = __m_slide_126;
			t_sample gen_133 = slide_119;
			t_sample mul_157 = (gen_211 * gen_134);
			t_sample mul_154 = (m_history_44 * gen_133);
			t_sample mul_152 = (m_history_46 * ((int)1));
			t_sample mul_148 = (m_history_45 * gen_134);
			t_sample mul_150 = (m_history_43 * gen_133);
			t_sample sub_156 = (((mul_152 + mul_154) + mul_157) - (mul_150 + mul_148));
			t_sample gen_162 = sub_156;
			t_sample history_153_next_158 = fixdenorm(m_history_44);
			t_sample history_149_next_159 = fixdenorm(m_history_43);
			t_sample history_155_next_160 = fixdenorm(gen_211);
			t_sample history_151_next_161 = fixdenorm(sub_156);
			t_sample add_95 = (mod_3 + div_7);
			t_sample mod_96 = safemod(add_95, ((int)1));
			t_sample triangle_92 = triangle(mod_96, ((t_sample)0.5));
			int gt_91 = (mod_96 > ((t_sample)0.5));
			__m_cycle_129.phase(mod_96);
			t_sample cycle_93 = __m_cycle_129(__sinedata);
			t_sample cycleindex_94 = __m_cycle_129.phase();
			t_sample add_89 = (cycle_93 + ((int)1));
			t_sample div_88 = (add_89 * ((t_sample)0.5));
			t_sample noise_67 = noise();
			t_sample sah_68 = __m_sah_130(noise_67, mod_96, ((t_sample)0.5));
			t_sample add_66 = (sah_68 + ((int)1));
			t_sample div_65 = (add_66 * ((t_sample)0.5));
			t_sample selector_87 = ((choice_131 >= 5) ? div_65 : ((choice_131 >= 4) ? gt_91 : ((choice_131 >= 3) ? mod_96 : ((choice_131 >= 2) ? triangle_92 : ((choice_131 >= 1) ? div_88 : 0)))));
			t_sample mul_90 = (selector_87 * m_width_70);
			t_sample sub_2007 = (mul_90 - ((int)0));
			t_sample scale_2004 = ((safepow((sub_2007 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_97 = scale_2004;
			t_sample mtof_98 = mtof(scale_97, ((int)440));
			t_sample mul_82 = (mtof_98 * div_83);
			t_sample cos_80 = cos(mul_82);
			t_sample mul_75 = (cos_80 * (-2));
			t_sample sin_81 = sin(mul_82);
			t_sample mul_79 = (sin_81 * ((t_sample)0.5));
			t_sample div_78 = safediv(mul_79, m_Q_73);
			t_sample rsub_73 = (((int)1) - div_78);
			t_sample add_77 = (div_78 + ((int)1));
			t_sample rdiv_76 = safediv(((int)1), add_77);
			t_sample mul_74 = (rdiv_76 * mul_75);
			__m_slide_132 = fixdenorm((__m_slide_132 + (((mul_74 > __m_slide_132) ? iup_133 : idown_134) * (mul_74 - __m_slide_132))));
			t_sample slide_70 = __m_slide_132;
			t_sample gen_84 = slide_70;
			t_sample mul_72 = (rdiv_76 * rsub_73);
			__m_slide_135 = fixdenorm((__m_slide_135 + (((mul_72 > __m_slide_135) ? iup_136 : idown_137) * (mul_72 - __m_slide_135))));
			t_sample slide_69 = __m_slide_135;
			t_sample gen_85 = slide_69;
			t_sample mul_108 = (gen_162 * gen_85);
			t_sample mul_105 = (m_history_40 * gen_84);
			t_sample mul_103 = (m_history_41 * ((int)1));
			t_sample mul_99 = (m_history_42 * gen_85);
			t_sample mul_101 = (m_history_39 * gen_84);
			t_sample sub_107 = (((mul_103 + mul_105) + mul_108) - (mul_101 + mul_99));
			t_sample gen_113 = sub_107;
			t_sample history_100_next_109 = fixdenorm(m_history_39);
			t_sample history_104_next_110 = fixdenorm(m_history_40);
			t_sample history_106_next_111 = fixdenorm(gen_162);
			t_sample history_102_next_112 = fixdenorm(sub_107);
			t_sample add_46 = (mod_3 + div_5);
			t_sample mod_47 = safemod(add_46, ((int)1));
			t_sample triangle_43 = triangle(mod_47, ((t_sample)0.5));
			int gt_42 = (mod_47 > ((t_sample)0.5));
			__m_cycle_138.phase(mod_47);
			t_sample cycle_44 = __m_cycle_138(__sinedata);
			t_sample cycleindex_45 = __m_cycle_138.phase();
			t_sample add_40 = (cycle_44 + ((int)1));
			t_sample div_39 = (add_40 * ((t_sample)0.5));
			t_sample noise_18 = noise();
			t_sample sah_19 = __m_sah_139(noise_18, mod_47, ((t_sample)0.5));
			t_sample add_17 = (sah_19 + ((int)1));
			t_sample div_16 = (add_17 * ((t_sample)0.5));
			t_sample selector_38 = ((choice_140 >= 5) ? div_16 : ((choice_140 >= 4) ? gt_42 : ((choice_140 >= 3) ? mod_47 : ((choice_140 >= 2) ? triangle_43 : ((choice_140 >= 1) ? div_39 : 0)))));
			t_sample mul_41 = (selector_38 * m_width_70);
			t_sample sub_2011 = (mul_41 - ((int)0));
			t_sample scale_2008 = ((safepow((sub_2011 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_48 = scale_2008;
			t_sample mtof_49 = mtof(scale_48, ((int)440));
			t_sample mul_33 = (mtof_49 * div_34);
			t_sample cos_31 = cos(mul_33);
			t_sample mul_26 = (cos_31 * (-2));
			t_sample sin_32 = sin(mul_33);
			t_sample mul_30 = (sin_32 * ((t_sample)0.5));
			t_sample div_29 = safediv(mul_30, m_Q_73);
			t_sample rsub_24 = (((int)1) - div_29);
			t_sample add_28 = (div_29 + ((int)1));
			t_sample rdiv_27 = safediv(((int)1), add_28);
			t_sample mul_23 = (rdiv_27 * rsub_24);
			__m_slide_141 = fixdenorm((__m_slide_141 + (((mul_23 > __m_slide_141) ? iup_142 : idown_143) * (mul_23 - __m_slide_141))));
			t_sample slide_20 = __m_slide_141;
			t_sample gen_36 = slide_20;
			t_sample mul_25 = (rdiv_27 * mul_26);
			__m_slide_144 = fixdenorm((__m_slide_144 + (((mul_25 > __m_slide_144) ? iup_145 : idown_146) * (mul_25 - __m_slide_144))));
			t_sample slide_21 = __m_slide_144;
			t_sample gen_35 = slide_21;
			t_sample mul_59 = (gen_113 * gen_36);
			t_sample mul_56 = (m_history_36 * gen_35);
			t_sample mul_54 = (m_history_37 * ((int)1));
			t_sample mul_50 = (m_history_38 * gen_36);
			t_sample mul_52 = (m_history_35 * gen_35);
			t_sample sub_58 = (((mul_54 + mul_56) + mul_59) - (mul_52 + mul_50));
			t_sample gen_64 = sub_58;
			t_sample history_51_next_60 = fixdenorm(m_history_35);
			t_sample history_55_next_61 = fixdenorm(m_history_36);
			t_sample history_57_next_62 = fixdenorm(gen_113);
			t_sample history_53_next_63 = fixdenorm(sub_58);
			t_sample add_762 = (mul_814 + gen_64);
			t_sample dcblock_1 = __m_dcblock_147(add_762);
			t_sample out2 = dcblock_1;
			t_sample mul_606 = (m_history_1 * m_fb_68);
			t_sample add_605 = (mul_814 + mul_606);
			t_sample add_795 = (phasor_764 + div_758);
			t_sample mod_796 = safemod(add_795, ((int)1));
			t_sample triangle_792 = triangle(mod_796, ((t_sample)0.5));
			int gt_791 = (mod_796 > ((t_sample)0.5));
			__m_cycle_148.phase(mod_796);
			t_sample cycle_793 = __m_cycle_148(__sinedata);
			t_sample cycleindex_794 = __m_cycle_148.phase();
			t_sample add_789 = (cycle_793 + ((int)1));
			t_sample div_788 = (add_789 * ((t_sample)0.5));
			t_sample noise_767 = noise();
			t_sample sah_768 = __m_sah_149(noise_767, mod_796, ((t_sample)0.5));
			t_sample add_766 = (sah_768 + ((int)1));
			t_sample div_765 = (add_766 * ((t_sample)0.5));
			t_sample selector_787 = ((choice_150 >= 5) ? div_765 : ((choice_150 >= 4) ? gt_791 : ((choice_150 >= 3) ? mod_796 : ((choice_150 >= 2) ? triangle_792 : ((choice_150 >= 1) ? div_788 : 0)))));
			t_sample mul_790 = (selector_787 * m_width_70);
			t_sample sub_2015 = (mul_790 - ((int)0));
			t_sample scale_2012 = ((safepow((sub_2015 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_797 = scale_2012;
			t_sample mtof_798 = mtof(scale_797, ((int)440));
			t_sample mul_782 = (mtof_798 * div_783);
			t_sample cos_780 = cos(mul_782);
			t_sample mul_775 = (cos_780 * (-2));
			t_sample sin_781 = sin(mul_782);
			t_sample mul_779 = (sin_781 * ((t_sample)0.5));
			t_sample div_778 = safediv(mul_779, m_Q_73);
			t_sample rsub_773 = (((int)1) - div_778);
			t_sample add_777 = (div_778 + ((int)1));
			t_sample rdiv_776 = safediv(((int)1), add_777);
			t_sample mul_772 = (rdiv_776 * rsub_773);
			__m_slide_151 = fixdenorm((__m_slide_151 + (((mul_772 > __m_slide_151) ? iup_152 : idown_153) * (mul_772 - __m_slide_151))));
			t_sample slide_769 = __m_slide_151;
			t_sample gen_785 = slide_769;
			t_sample mul_774 = (rdiv_776 * mul_775);
			__m_slide_154 = fixdenorm((__m_slide_154 + (((mul_774 > __m_slide_154) ? iup_155 : idown_156) * (mul_774 - __m_slide_154))));
			t_sample slide_770 = __m_slide_154;
			t_sample gen_784 = slide_770;
			t_sample mul_808 = (add_605 * gen_785);
			t_sample mul_805 = (m_history_32 * gen_784);
			t_sample mul_803 = (m_history_34 * ((int)1));
			t_sample mul_799 = (m_history_33 * gen_785);
			t_sample mul_801 = (m_history_31 * gen_784);
			t_sample sub_807 = (((mul_803 + mul_805) + mul_808) - (mul_801 + mul_799));
			t_sample gen_813 = sub_807;
			t_sample history_804_next_809 = fixdenorm(m_history_32);
			t_sample history_800_next_810 = fixdenorm(m_history_31);
			t_sample history_806_next_811 = fixdenorm(add_605);
			t_sample history_802_next_812 = fixdenorm(sub_807);
			t_sample add_735 = (phasor_764 + div_757);
			t_sample mod_736 = safemod(add_735, ((int)1));
			t_sample triangle_732 = triangle(mod_736, ((t_sample)0.5));
			int gt_731 = (mod_736 > ((t_sample)0.5));
			__m_cycle_157.phase(mod_736);
			t_sample cycle_733 = __m_cycle_157(__sinedata);
			t_sample cycleindex_734 = __m_cycle_157.phase();
			t_sample add_729 = (cycle_733 + ((int)1));
			t_sample div_728 = (add_729 * ((t_sample)0.5));
			t_sample noise_707 = noise();
			t_sample sah_708 = __m_sah_158(noise_707, mod_736, ((t_sample)0.5));
			t_sample add_706 = (sah_708 + ((int)1));
			t_sample div_705 = (add_706 * ((t_sample)0.5));
			t_sample selector_727 = ((choice_159 >= 5) ? div_705 : ((choice_159 >= 4) ? gt_731 : ((choice_159 >= 3) ? mod_736 : ((choice_159 >= 2) ? triangle_732 : ((choice_159 >= 1) ? div_728 : 0)))));
			t_sample mul_730 = (selector_727 * m_width_70);
			t_sample sub_2019 = (mul_730 - ((int)0));
			t_sample scale_2016 = ((safepow((sub_2019 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_737 = scale_2016;
			t_sample mtof_738 = mtof(scale_737, ((int)440));
			t_sample mul_722 = (mtof_738 * div_723);
			t_sample cos_720 = cos(mul_722);
			t_sample mul_715 = (cos_720 * (-2));
			t_sample sin_721 = sin(mul_722);
			t_sample mul_719 = (sin_721 * ((t_sample)0.5));
			t_sample div_718 = safediv(mul_719, m_Q_73);
			t_sample rsub_713 = (((int)1) - div_718);
			t_sample add_717 = (div_718 + ((int)1));
			t_sample rdiv_716 = safediv(((int)1), add_717);
			t_sample mul_714 = (rdiv_716 * mul_715);
			__m_slide_160 = fixdenorm((__m_slide_160 + (((mul_714 > __m_slide_160) ? iup_161 : idown_162) * (mul_714 - __m_slide_160))));
			t_sample slide_710 = __m_slide_160;
			t_sample gen_724 = slide_710;
			t_sample mul_712 = (rdiv_716 * rsub_713);
			__m_slide_163 = fixdenorm((__m_slide_163 + (((mul_712 > __m_slide_163) ? iup_164 : idown_165) * (mul_712 - __m_slide_163))));
			t_sample slide_709 = __m_slide_163;
			t_sample gen_725 = slide_709;
			t_sample mul_748 = (gen_813 * gen_725);
			t_sample mul_745 = (m_history_28 * gen_724);
			t_sample mul_743 = (m_history_29 * ((int)1));
			t_sample mul_739 = (m_history_30 * gen_725);
			t_sample mul_741 = (m_history_27 * gen_724);
			t_sample sub_747 = (((mul_743 + mul_745) + mul_748) - (mul_741 + mul_739));
			t_sample gen_753 = sub_747;
			t_sample history_740_next_749 = fixdenorm(m_history_27);
			t_sample history_744_next_750 = fixdenorm(m_history_28);
			t_sample history_746_next_751 = fixdenorm(gen_813);
			t_sample history_742_next_752 = fixdenorm(sub_747);
			t_sample add_686 = (phasor_764 + div_756);
			t_sample mod_687 = safemod(add_686, ((int)1));
			t_sample triangle_683 = triangle(mod_687, ((t_sample)0.5));
			int gt_682 = (mod_687 > ((t_sample)0.5));
			__m_cycle_166.phase(mod_687);
			t_sample cycle_684 = __m_cycle_166(__sinedata);
			t_sample cycleindex_685 = __m_cycle_166.phase();
			t_sample add_680 = (cycle_684 + ((int)1));
			t_sample div_679 = (add_680 * ((t_sample)0.5));
			t_sample noise_658 = noise();
			t_sample sah_659 = __m_sah_167(noise_658, mod_687, ((t_sample)0.5));
			t_sample add_657 = (sah_659 + ((int)1));
			t_sample div_656 = (add_657 * ((t_sample)0.5));
			t_sample selector_678 = ((choice_168 >= 5) ? div_656 : ((choice_168 >= 4) ? gt_682 : ((choice_168 >= 3) ? mod_687 : ((choice_168 >= 2) ? triangle_683 : ((choice_168 >= 1) ? div_679 : 0)))));
			t_sample mul_681 = (selector_678 * m_width_70);
			t_sample sub_2023 = (mul_681 - ((int)0));
			t_sample scale_2020 = ((safepow((sub_2023 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_688 = scale_2020;
			t_sample mtof_689 = mtof(scale_688, ((int)440));
			t_sample mul_673 = (mtof_689 * div_674);
			t_sample cos_671 = cos(mul_673);
			t_sample mul_666 = (cos_671 * (-2));
			t_sample sin_672 = sin(mul_673);
			t_sample mul_670 = (sin_672 * ((t_sample)0.5));
			t_sample div_669 = safediv(mul_670, m_Q_73);
			t_sample rsub_664 = (((int)1) - div_669);
			t_sample add_668 = (div_669 + ((int)1));
			t_sample rdiv_667 = safediv(((int)1), add_668);
			t_sample mul_663 = (rdiv_667 * rsub_664);
			__m_slide_169 = fixdenorm((__m_slide_169 + (((mul_663 > __m_slide_169) ? iup_170 : idown_171) * (mul_663 - __m_slide_169))));
			t_sample slide_660 = __m_slide_169;
			t_sample gen_676 = slide_660;
			t_sample mul_665 = (rdiv_667 * mul_666);
			__m_slide_172 = fixdenorm((__m_slide_172 + (((mul_665 > __m_slide_172) ? iup_173 : idown_174) * (mul_665 - __m_slide_172))));
			t_sample slide_661 = __m_slide_172;
			t_sample gen_675 = slide_661;
			t_sample mul_699 = (gen_753 * gen_676);
			t_sample mul_696 = (m_history_24 * gen_675);
			t_sample mul_694 = (m_history_25 * ((int)1));
			t_sample mul_690 = (m_history_26 * gen_676);
			t_sample mul_692 = (m_history_23 * gen_675);
			t_sample sub_698 = (((mul_694 + mul_696) + mul_699) - (mul_692 + mul_690));
			t_sample gen_704 = sub_698;
			t_sample history_691_next_700 = fixdenorm(m_history_23);
			t_sample history_695_next_701 = fixdenorm(m_history_24);
			t_sample history_697_next_702 = fixdenorm(gen_753);
			t_sample history_693_next_703 = fixdenorm(sub_698);
			t_sample add_637 = (phasor_764 + div_754);
			t_sample mod_638 = safemod(add_637, ((int)1));
			t_sample triangle_634 = triangle(mod_638, ((t_sample)0.5));
			int gt_633 = (mod_638 > ((t_sample)0.5));
			__m_cycle_175.phase(mod_638);
			t_sample cycle_635 = __m_cycle_175(__sinedata);
			t_sample cycleindex_636 = __m_cycle_175.phase();
			t_sample add_631 = (cycle_635 + ((int)1));
			t_sample div_630 = (add_631 * ((t_sample)0.5));
			t_sample noise_609 = noise();
			t_sample sah_610 = __m_sah_176(noise_609, mod_638, ((t_sample)0.5));
			t_sample add_608 = (sah_610 + ((int)1));
			t_sample div_607 = (add_608 * ((t_sample)0.5));
			t_sample selector_629 = ((choice_177 >= 5) ? div_607 : ((choice_177 >= 4) ? gt_633 : ((choice_177 >= 3) ? mod_638 : ((choice_177 >= 2) ? triangle_634 : ((choice_177 >= 1) ? div_630 : 0)))));
			t_sample mul_632 = (selector_629 * m_width_70);
			t_sample sub_2027 = (mul_632 - ((int)0));
			t_sample scale_2024 = ((safepow((sub_2027 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_639 = scale_2024;
			t_sample mtof_640 = mtof(scale_639, ((int)440));
			t_sample mul_624 = (mtof_640 * div_625);
			t_sample cos_622 = cos(mul_624);
			t_sample mul_617 = (cos_622 * (-2));
			t_sample sin_623 = sin(mul_624);
			t_sample mul_621 = (sin_623 * ((t_sample)0.5));
			t_sample div_620 = safediv(mul_621, m_Q_73);
			t_sample rsub_615 = (((int)1) - div_620);
			t_sample add_619 = (div_620 + ((int)1));
			t_sample rdiv_618 = safediv(((int)1), add_619);
			t_sample mul_616 = (rdiv_618 * mul_617);
			__m_slide_178 = fixdenorm((__m_slide_178 + (((mul_616 > __m_slide_178) ? iup_179 : idown_180) * (mul_616 - __m_slide_178))));
			t_sample slide_612 = __m_slide_178;
			t_sample gen_626 = slide_612;
			t_sample mul_614 = (rdiv_618 * rsub_615);
			__m_slide_181 = fixdenorm((__m_slide_181 + (((mul_614 > __m_slide_181) ? iup_182 : idown_183) * (mul_614 - __m_slide_181))));
			t_sample slide_611 = __m_slide_181;
			t_sample gen_627 = slide_611;
			t_sample mul_650 = (gen_704 * gen_627);
			t_sample mul_647 = (m_history_20 * gen_626);
			t_sample mul_645 = (m_history_22 * ((int)1));
			t_sample mul_641 = (m_history_21 * gen_627);
			t_sample mul_643 = (m_history_19 * gen_626);
			t_sample sub_649 = (((mul_645 + mul_647) + mul_650) - (mul_643 + mul_641));
			t_sample gen_655 = sub_649;
			t_sample history_646_next_651 = fixdenorm(m_history_20);
			t_sample history_642_next_652 = fixdenorm(m_history_19);
			t_sample history_648_next_653 = fixdenorm(gen_704);
			t_sample history_644_next_654 = fixdenorm(sub_649);
			t_sample add_585 = (phasor_764 + div_9);
			t_sample mod_586 = safemod(add_585, ((int)1));
			t_sample triangle_582 = triangle(mod_586, ((t_sample)0.5));
			int gt_581 = (mod_586 > ((t_sample)0.5));
			__m_cycle_184.phase(mod_586);
			t_sample cycle_583 = __m_cycle_184(__sinedata);
			t_sample cycleindex_584 = __m_cycle_184.phase();
			t_sample add_579 = (cycle_583 + ((int)1));
			t_sample div_578 = (add_579 * ((t_sample)0.5));
			t_sample noise_557 = noise();
			t_sample sah_558 = __m_sah_185(noise_557, mod_586, ((t_sample)0.5));
			t_sample add_556 = (sah_558 + ((int)1));
			t_sample div_555 = (add_556 * ((t_sample)0.5));
			t_sample selector_577 = ((choice_186 >= 5) ? div_555 : ((choice_186 >= 4) ? gt_581 : ((choice_186 >= 3) ? mod_586 : ((choice_186 >= 2) ? triangle_582 : ((choice_186 >= 1) ? div_578 : 0)))));
			t_sample mul_580 = (selector_577 * m_width_70);
			t_sample sub_2031 = (mul_580 - ((int)0));
			t_sample scale_2028 = ((safepow((sub_2031 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_587 = scale_2028;
			t_sample mtof_588 = mtof(scale_587, ((int)440));
			t_sample mul_572 = (mtof_588 * div_573);
			t_sample cos_570 = cos(mul_572);
			t_sample mul_565 = (cos_570 * (-2));
			t_sample sin_571 = sin(mul_572);
			t_sample mul_569 = (sin_571 * ((t_sample)0.5));
			t_sample div_568 = safediv(mul_569, m_Q_73);
			t_sample rsub_563 = (((int)1) - div_568);
			t_sample add_567 = (div_568 + ((int)1));
			t_sample rdiv_566 = safediv(((int)1), add_567);
			t_sample mul_564 = (rdiv_566 * mul_565);
			__m_slide_187 = fixdenorm((__m_slide_187 + (((mul_564 > __m_slide_187) ? iup_188 : idown_189) * (mul_564 - __m_slide_187))));
			t_sample slide_560 = __m_slide_187;
			t_sample gen_574 = slide_560;
			t_sample mul_562 = (rdiv_566 * rsub_563);
			__m_slide_190 = fixdenorm((__m_slide_190 + (((mul_562 > __m_slide_190) ? iup_191 : idown_192) * (mul_562 - __m_slide_190))));
			t_sample slide_559 = __m_slide_190;
			t_sample gen_575 = slide_559;
			t_sample mul_598 = (gen_655 * gen_575);
			t_sample mul_595 = (m_history_16 * gen_574);
			t_sample mul_593 = (m_history_18 * ((int)1));
			t_sample mul_589 = (m_history_17 * gen_575);
			t_sample mul_591 = (m_history_15 * gen_574);
			t_sample sub_597 = (((mul_593 + mul_595) + mul_598) - (mul_591 + mul_589));
			t_sample gen_603 = sub_597;
			t_sample history_594_next_599 = fixdenorm(m_history_16);
			t_sample history_590_next_600 = fixdenorm(m_history_15);
			t_sample history_596_next_601 = fixdenorm(gen_655);
			t_sample history_592_next_602 = fixdenorm(sub_597);
			t_sample add_536 = (phasor_764 + div_8);
			t_sample mod_537 = safemod(add_536, ((int)1));
			t_sample triangle_533 = triangle(mod_537, ((t_sample)0.5));
			int gt_532 = (mod_537 > ((t_sample)0.5));
			__m_cycle_193.phase(mod_537);
			t_sample cycle_534 = __m_cycle_193(__sinedata);
			t_sample cycleindex_535 = __m_cycle_193.phase();
			t_sample add_530 = (cycle_534 + ((int)1));
			t_sample div_529 = (add_530 * ((t_sample)0.5));
			t_sample noise_508 = noise();
			t_sample sah_509 = __m_sah_194(noise_508, mod_537, ((t_sample)0.5));
			t_sample add_507 = (sah_509 + ((int)1));
			t_sample div_506 = (add_507 * ((t_sample)0.5));
			t_sample selector_528 = ((choice_195 >= 5) ? div_506 : ((choice_195 >= 4) ? gt_532 : ((choice_195 >= 3) ? mod_537 : ((choice_195 >= 2) ? triangle_533 : ((choice_195 >= 1) ? div_529 : 0)))));
			t_sample mul_531 = (selector_528 * m_width_70);
			t_sample sub_2035 = (mul_531 - ((int)0));
			t_sample scale_2032 = ((safepow((sub_2035 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_538 = scale_2032;
			t_sample mtof_539 = mtof(scale_538, ((int)440));
			t_sample mul_523 = (mtof_539 * div_524);
			t_sample cos_521 = cos(mul_523);
			t_sample mul_516 = (cos_521 * (-2));
			t_sample sin_522 = sin(mul_523);
			t_sample mul_520 = (sin_522 * ((t_sample)0.5));
			t_sample div_519 = safediv(mul_520, m_Q_73);
			t_sample rsub_514 = (((int)1) - div_519);
			t_sample add_518 = (div_519 + ((int)1));
			t_sample rdiv_517 = safediv(((int)1), add_518);
			t_sample mul_515 = (rdiv_517 * mul_516);
			__m_slide_196 = fixdenorm((__m_slide_196 + (((mul_515 > __m_slide_196) ? iup_197 : idown_198) * (mul_515 - __m_slide_196))));
			t_sample slide_511 = __m_slide_196;
			t_sample gen_525 = slide_511;
			t_sample mul_513 = (rdiv_517 * rsub_514);
			__m_slide_199 = fixdenorm((__m_slide_199 + (((mul_513 > __m_slide_199) ? iup_200 : idown_201) * (mul_513 - __m_slide_199))));
			t_sample slide_510 = __m_slide_199;
			t_sample gen_526 = slide_510;
			t_sample mul_549 = (gen_603 * gen_526);
			t_sample mul_546 = (m_history_12 * gen_525);
			t_sample mul_544 = (m_history_13 * ((int)1));
			t_sample mul_540 = (m_history_14 * gen_526);
			t_sample mul_542 = (m_history_11 * gen_525);
			t_sample sub_548 = (((mul_544 + mul_546) + mul_549) - (mul_542 + mul_540));
			t_sample gen_554 = sub_548;
			t_sample history_541_next_550 = fixdenorm(m_history_11);
			t_sample history_545_next_551 = fixdenorm(m_history_12);
			t_sample history_547_next_552 = fixdenorm(gen_603);
			t_sample history_543_next_553 = fixdenorm(sub_548);
			t_sample add_487 = (phasor_764 + div_7);
			t_sample mod_488 = safemod(add_487, ((int)1));
			t_sample triangle_484 = triangle(mod_488, ((t_sample)0.5));
			int gt_483 = (mod_488 > ((t_sample)0.5));
			__m_cycle_202.phase(mod_488);
			t_sample cycle_485 = __m_cycle_202(__sinedata);
			t_sample cycleindex_486 = __m_cycle_202.phase();
			t_sample add_481 = (cycle_485 + ((int)1));
			t_sample div_480 = (add_481 * ((t_sample)0.5));
			t_sample noise_459 = noise();
			t_sample sah_460 = __m_sah_203(noise_459, mod_488, ((t_sample)0.5));
			t_sample add_458 = (sah_460 + ((int)1));
			t_sample div_457 = (add_458 * ((t_sample)0.5));
			t_sample selector_479 = ((choice_204 >= 5) ? div_457 : ((choice_204 >= 4) ? gt_483 : ((choice_204 >= 3) ? mod_488 : ((choice_204 >= 2) ? triangle_484 : ((choice_204 >= 1) ? div_480 : 0)))));
			t_sample mul_482 = (selector_479 * m_width_70);
			t_sample sub_2039 = (mul_482 - ((int)0));
			t_sample scale_2036 = ((safepow((sub_2039 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_489 = scale_2036;
			t_sample mtof_490 = mtof(scale_489, ((int)440));
			t_sample mul_474 = (mtof_490 * div_475);
			t_sample cos_472 = cos(mul_474);
			t_sample mul_467 = (cos_472 * (-2));
			t_sample sin_473 = sin(mul_474);
			t_sample mul_471 = (sin_473 * ((t_sample)0.5));
			t_sample div_470 = safediv(mul_471, m_Q_73);
			t_sample rsub_465 = (((int)1) - div_470);
			t_sample add_469 = (div_470 + ((int)1));
			t_sample rdiv_468 = safediv(((int)1), add_469);
			t_sample mul_464 = (rdiv_468 * rsub_465);
			__m_slide_205 = fixdenorm((__m_slide_205 + (((mul_464 > __m_slide_205) ? iup_206 : idown_207) * (mul_464 - __m_slide_205))));
			t_sample slide_461 = __m_slide_205;
			t_sample gen_477 = slide_461;
			t_sample mul_466 = (rdiv_468 * mul_467);
			__m_slide_208 = fixdenorm((__m_slide_208 + (((mul_466 > __m_slide_208) ? iup_209 : idown_210) * (mul_466 - __m_slide_208))));
			t_sample slide_462 = __m_slide_208;
			t_sample gen_476 = slide_462;
			t_sample mul_500 = (gen_554 * gen_477);
			t_sample mul_497 = (m_history_8 * gen_476);
			t_sample mul_495 = (m_history_10 * ((int)1));
			t_sample mul_491 = (m_history_9 * gen_477);
			t_sample mul_493 = (m_history_7 * gen_476);
			t_sample sub_499 = (((mul_495 + mul_497) + mul_500) - (mul_493 + mul_491));
			t_sample gen_505 = sub_499;
			t_sample history_496_next_501 = fixdenorm(m_history_8);
			t_sample history_492_next_502 = fixdenorm(m_history_7);
			t_sample history_498_next_503 = fixdenorm(gen_554);
			t_sample history_494_next_504 = fixdenorm(sub_499);
			t_sample add_438 = (phasor_764 + div_5);
			t_sample mod_439 = safemod(add_438, ((int)1));
			t_sample triangle_435 = triangle(mod_439, ((t_sample)0.5));
			int gt_434 = (mod_439 > ((t_sample)0.5));
			__m_cycle_211.phase(mod_439);
			t_sample cycle_436 = __m_cycle_211(__sinedata);
			t_sample cycleindex_437 = __m_cycle_211.phase();
			t_sample add_432 = (cycle_436 + ((int)1));
			t_sample div_431 = (add_432 * ((t_sample)0.5));
			t_sample noise_410 = noise();
			t_sample sah_411 = __m_sah_212(noise_410, mod_439, ((t_sample)0.5));
			t_sample add_409 = (sah_411 + ((int)1));
			t_sample div_408 = (add_409 * ((t_sample)0.5));
			t_sample selector_430 = ((choice_213 >= 5) ? div_408 : ((choice_213 >= 4) ? gt_434 : ((choice_213 >= 3) ? mod_439 : ((choice_213 >= 2) ? triangle_435 : ((choice_213 >= 1) ? div_431 : 0)))));
			t_sample mul_433 = (selector_430 * m_width_70);
			t_sample sub_2043 = (mul_433 - ((int)0));
			t_sample scale_2040 = ((safepow((sub_2043 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_440 = scale_2040;
			t_sample mtof_441 = mtof(scale_440, ((int)440));
			t_sample mul_425 = (mtof_441 * div_426);
			t_sample cos_423 = cos(mul_425);
			t_sample mul_418 = (cos_423 * (-2));
			t_sample sin_424 = sin(mul_425);
			t_sample mul_422 = (sin_424 * ((t_sample)0.5));
			t_sample div_421 = safediv(mul_422, m_Q_73);
			t_sample rsub_416 = (((int)1) - div_421);
			t_sample add_420 = (div_421 + ((int)1));
			t_sample rdiv_419 = safediv(((int)1), add_420);
			t_sample mul_417 = (rdiv_419 * mul_418);
			__m_slide_214 = fixdenorm((__m_slide_214 + (((mul_417 > __m_slide_214) ? iup_215 : idown_216) * (mul_417 - __m_slide_214))));
			t_sample slide_413 = __m_slide_214;
			t_sample gen_427 = slide_413;
			t_sample mul_415 = (rdiv_419 * rsub_416);
			__m_slide_217 = fixdenorm((__m_slide_217 + (((mul_415 > __m_slide_217) ? iup_218 : idown_219) * (mul_415 - __m_slide_217))));
			t_sample slide_412 = __m_slide_217;
			t_sample gen_428 = slide_412;
			t_sample mul_451 = (gen_505 * gen_428);
			t_sample mul_448 = (m_history_4 * gen_427);
			t_sample mul_446 = (m_history_5 * ((int)1));
			t_sample mul_442 = (m_history_6 * gen_428);
			t_sample mul_444 = (m_history_3 * gen_427);
			t_sample sub_450 = (((mul_446 + mul_448) + mul_451) - (mul_444 + mul_442));
			t_sample gen_456 = sub_450;
			t_sample history_443_next_452 = fixdenorm(m_history_3);
			t_sample history_447_next_453 = fixdenorm(m_history_4);
			t_sample history_449_next_454 = fixdenorm(gen_505);
			t_sample history_445_next_455 = fixdenorm(sub_450);
			t_sample add_763 = (mul_814 + gen_456);
			t_sample dcblock_2 = __m_dcblock_220(add_763);
			t_sample out1 = dcblock_2;
			t_sample history_13_next_815 = fixdenorm(gen_64);
			t_sample history_604_next_816 = fixdenorm(gen_456);
			m_history_66 = history_394_next_403;
			m_history_63 = history_396_next_406;
			m_history_64 = history_400_next_405;
			m_history_65 = history_398_next_404;
			m_history_62 = history_349_next_354;
			m_history_59 = history_347_next_357;
			m_history_60 = history_351_next_356;
			m_history_61 = history_345_next_355;
			m_history_58 = history_300_next_305;
			m_history_55 = history_298_next_308;
			m_history_56 = history_302_next_307;
			m_history_57 = history_296_next_306;
			m_history_54 = history_251_next_256;
			m_history_51 = history_249_next_259;
			m_history_52 = history_253_next_258;
			m_history_53 = history_247_next_257;
			m_history_50 = history_202_next_207;
			m_history_47 = history_200_next_210;
			m_history_48 = history_204_next_209;
			m_history_49 = history_198_next_208;
			m_history_46 = history_153_next_158;
			m_history_43 = history_151_next_161;
			m_history_44 = history_155_next_160;
			m_history_45 = history_149_next_159;
			m_history_42 = history_100_next_109;
			m_history_39 = history_102_next_112;
			m_history_40 = history_106_next_111;
			m_history_41 = history_104_next_110;
			m_history_38 = history_51_next_60;
			m_history_35 = history_53_next_63;
			m_history_36 = history_57_next_62;
			m_history_37 = history_55_next_61;
			m_history_34 = history_804_next_809;
			m_history_31 = history_802_next_812;
			m_history_32 = history_806_next_811;
			m_history_33 = history_800_next_810;
			m_history_30 = history_740_next_749;
			m_history_27 = history_742_next_752;
			m_history_28 = history_746_next_751;
			m_history_29 = history_744_next_750;
			m_history_26 = history_691_next_700;
			m_history_23 = history_693_next_703;
			m_history_24 = history_697_next_702;
			m_history_25 = history_695_next_701;
			m_history_22 = history_646_next_651;
			m_history_19 = history_644_next_654;
			m_history_20 = history_648_next_653;
			m_history_21 = history_642_next_652;
			m_history_18 = history_594_next_599;
			m_history_15 = history_592_next_602;
			m_history_16 = history_596_next_601;
			m_history_17 = history_590_next_600;
			m_history_14 = history_541_next_550;
			m_history_11 = history_543_next_553;
			m_history_12 = history_547_next_552;
			m_history_13 = history_545_next_551;
			m_history_10 = history_496_next_501;
			m_history_7 = history_494_next_504;
			m_history_8 = history_498_next_503;
			m_history_9 = history_492_next_502;
			m_history_6 = history_443_next_452;
			m_history_3 = history_445_next_455;
			m_history_4 = history_449_next_454;
			m_history_5 = history_447_next_453;
			m_history_2 = history_13_next_815;
			m_history_1 = history_604_next_816;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_rate(t_param _value) {
		m_rate_67 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_fb(t_param _value) {
		m_fb_68 = (_value < -0.99 ? -0.99 : (_value > 0.99 ? 0.99 : _value));
	};
	inline void set_waveform(t_param _value) {
		m_waveform_69 = (_value < 1 ? 1 : (_value > 4 ? 4 : _value));
	};
	inline void set_width(t_param _value) {
		m_width_70 = (_value < -1 ? -1 : (_value > 1 ? 1 : _value));
	};
	inline void set_diffusion(t_param _value) {
		m_diffusion_71 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_gain(t_param _value) {
		m_gain_72 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_Q(t_param _value) {
		m_Q_73 = (_value < 1e-06 ? 1e-06 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 7; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "input" };
const char *gen_kernel_outnames[] = { "left output", "right output" };

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
		case 0: self->set_Q(value); break;
		case 1: self->set_diffusion(value); break;
		case 2: self->set_fb(value); break;
		case 3: self->set_gain(value); break;
		case 4: self->set_rate(value); break;
		case 5: self->set_waveform(value); break;
		case 6: self->set_width(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_Q_73; break;
		case 1: *value = self->m_diffusion_71; break;
		case 2: *value = self->m_fb_68; break;
		case 3: *value = self->m_gain_72; break;
		case 4: *value = self->m_rate_67; break;
		case 5: *value = self->m_waveform_69; break;
		case 6: *value = self->m_width_70; break;
		
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
	// initialize parameter 0 ("m_Q_73")
	pi = self->__commonstate.params + 0;
	pi->name = "Q";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_Q_73;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1e-06;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_diffusion_71")
	pi = self->__commonstate.params + 1;
	pi->name = "diffusion";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_diffusion_71;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_fb_68")
	pi = self->__commonstate.params + 2;
	pi->name = "fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_fb_68;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -0.99;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_gain_72")
	pi = self->__commonstate.params + 3;
	pi->name = "gain";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gain_72;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_rate_67")
	pi = self->__commonstate.params + 4;
	pi->name = "rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_rate_67;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_waveform_69")
	pi = self->__commonstate.params + 5;
	pi->name = "waveform";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_waveform_69;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_width_70")
	pi = self->__commonstate.params + 6;
	pi->name = "width";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_width_70;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -1;
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


} // lukephaser::
