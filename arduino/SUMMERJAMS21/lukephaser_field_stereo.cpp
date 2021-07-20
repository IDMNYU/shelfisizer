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
	t_sample m_knob5_fb_25;
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
	t_sample m_knob3_depth_23;
	t_sample m_knob4_rate_24;
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
		m_knob3_depth_23 = 1;
		m_knob4_rate_24 = 0.1;
		m_knob5_fb_25 = ((int)0);
		m_sw_26 = ((int)0);
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
		t_sample sub_10256 = (m_knob5_fb_25 - ((t_sample)0.5));
		t_sample scale_10253 = ((safepow((sub_10256 * ((t_sample)2.0408163265306)), ((int)1)) * ((t_sample)-0.15)) + ((t_sample)0.25));
		t_sample mstosamps_8359 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_8463 = (((int)100) * (samplerate * 0.001));
		t_sample add_7032 = (m_sw_26 + ((int)1));
		t_sample choice_30 = int(add_7032);
		t_sample iup_32 = (1 / maximum(1, abs(mstosamps_8359)));
		t_sample idown_33 = (1 / maximum(1, abs(mstosamps_8463)));
		samples_to_seconds = (1 / samplerate);
		t_sample div_134 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_37 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_38 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_40 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_41 = (1 / maximum(1, abs(((int)5))));
		t_sample div_46 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_44 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_45 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_47 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_48 = (1 / maximum(1, abs(((int)5))));
		t_sample div_1062 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_52 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_53 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_55 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_56 = (1 / maximum(1, abs(((int)5))));
		t_sample div_1104 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_59 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_60 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_62 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_63 = (1 / maximum(1, abs(((int)5))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out5 = ((int)0);
			t_sample out4 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample sah_6112 = __m_sah_28(m_history_22, m_sw_27, ((int)0));
			t_sample gen_6114 = sah_6112;
			t_sample rsub_6110 = (((int)1) - sah_6112);
			t_sample history_6111_next_6113 = fixdenorm(rsub_6110);
			t_sample out3 = gen_6114;
			t_sample add_6115 = (gen_6114 + ((int)1));
			t_sample choice_29 = int(add_6115);
			t_sample gate_6107 = (((choice_29 >= 1) && (choice_29 < 2)) ? in1 : 0);
			t_sample gate_6108 = ((choice_29 >= 2) ? in1 : 0);
			t_sample mul_21 = (m_history_1 * m_knob5_fb_25);
			t_sample add_20 = (gate_6108 + mul_21);
			t_sample mul_2713 = (m_history_2 * m_knob5_fb_25);
			t_sample add_2712 = (gate_6108 + mul_2713);
			t_sample selector_6963 = ((choice_30 >= 2) ? gate_6108 : ((choice_30 >= 1) ? ((int)1) : 0));
			t_sample abs_6687 = fabs(selector_6963);
			__m_slide_31 = fixdenorm((__m_slide_31 + (((abs_6687 > __m_slide_31) ? iup_32 : idown_33) * (abs_6687 - __m_slide_31))));
			t_sample slide_8394 = __m_slide_31;
			t_sample mul_7594 = (slide_8394 * ((int)10));
			t_sample clamp_7629 = ((mul_7594 <= ((int)0)) ? ((int)0) : ((mul_7594 >= ((int)1)) ? ((int)1) : mul_7594));
			t_sample mul_6859 = (m_knob3_depth_23 * clamp_7629);
			t_sample mix_10257 = (m_history_21 + (((t_sample)0.003926980723806) * (m_knob4_rate_24 - m_history_21)));
			t_sample mix_9623 = mix_10257;
			t_sample mix_10258 = (m_history_20 + (((t_sample)0.003926980723806) * (mix_9623 - m_history_20)));
			t_sample mix_9621 = mix_10258;
			t_sample mix_10259 = (m_history_19 + (((t_sample)0.003926980723806) * (mix_9621 - m_history_19)));
			t_sample mix_9619 = mix_10259;
			t_sample gen_9631 = mix_9619;
			t_sample history_9625_next_9628 = fixdenorm(mix_9623);
			t_sample history_9622_next_9629 = fixdenorm(mix_9621);
			t_sample history_9620_next_9630 = fixdenorm(mix_9619);
			t_sample rsub_8945 = (((int)1) - gen_9631);
			t_sample sqrt_8944 = sqrt(rsub_8945);
			t_sample sqrt_8943 = sqrt(sqrt_8944);
			t_sample sqrt_9375 = sqrt(sqrt_8943);
			t_sample rsub_8942 = (((int)1) - sqrt_9375);
			t_sample mul_8907 = (rsub_8942 * ((t_sample)7.5));
			t_sample phasor_31 = __m_phasor_34(mul_8907, samples_to_seconds);
			t_sample add_143 = (phasor_31 + ((t_sample)0.25));
			t_sample mod_144 = safemod(add_143, ((int)1));
			__m_cycle_35.phase(mod_144);
			t_sample cycle_141 = __m_cycle_35(__sinedata);
			t_sample cycleindex_142 = __m_cycle_35.phase();
			t_sample add_139 = (cycle_141 + ((int)1));
			t_sample div_138 = (add_139 * ((t_sample)0.5));
			t_sample mul_140 = (div_138 * mul_6859);
			t_sample sub_10263 = (mul_140 - ((int)0));
			t_sample scale_10260 = ((safepow((sub_10263 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_145 = scale_10260;
			t_sample mtof_146 = mtof(scale_145, ((int)440));
			t_sample mul_133 = (mtof_146 * div_134);
			t_sample cos_131 = cos(mul_133);
			t_sample mul_126 = (cos_131 * (-2));
			t_sample sin_132 = sin(mul_133);
			t_sample mul_130 = (sin_132 * ((t_sample)0.5));
			t_sample div_129 = (mul_130 * ((t_sample)0.33333333333333));
			t_sample rsub_124 = (((int)1) - div_129);
			t_sample add_128 = (div_129 + ((int)1));
			t_sample rdiv_127 = safediv(((int)1), add_128);
			t_sample mul_123 = (rdiv_127 * rsub_124);
			__m_slide_36 = fixdenorm((__m_slide_36 + (((mul_123 > __m_slide_36) ? iup_37 : idown_38) * (mul_123 - __m_slide_36))));
			t_sample slide_120 = __m_slide_36;
			t_sample gen_136 = slide_120;
			t_sample mul_125 = (rdiv_127 * mul_126);
			__m_slide_39 = fixdenorm((__m_slide_39 + (((mul_125 > __m_slide_39) ? iup_40 : idown_41) * (mul_125 - __m_slide_39))));
			t_sample slide_121 = __m_slide_39;
			t_sample gen_135 = slide_121;
			t_sample mul_151 = (m_history_18 * ((int)1));
			t_sample mul_153 = (m_history_16 * gen_135);
			t_sample mul_156 = (add_20 * gen_136);
			t_sample mul_149 = (m_history_15 * gen_135);
			t_sample mul_147 = (m_history_17 * gen_136);
			t_sample sub_155 = (((mul_156 + mul_153) + mul_151) - (mul_147 + mul_149));
			t_sample gen_161 = sub_155;
			t_sample history_152_next_157 = fixdenorm(m_history_16);
			t_sample history_148_next_158 = fixdenorm(m_history_15);
			t_sample history_154_next_159 = fixdenorm(add_20);
			t_sample history_150_next_160 = fixdenorm(sub_155);
			t_sample add_55 = (phasor_31 + ((int)0));
			t_sample mod_56 = safemod(add_55, ((int)1));
			__m_cycle_42.phase(mod_56);
			t_sample cycle_53 = __m_cycle_42(__sinedata);
			t_sample cycleindex_54 = __m_cycle_42.phase();
			t_sample add_51 = (cycle_53 + ((int)1));
			t_sample div_50 = (add_51 * ((t_sample)0.5));
			t_sample mul_52 = (div_50 * mul_6859);
			t_sample sub_10267 = (mul_52 - ((int)0));
			t_sample scale_10264 = ((safepow((sub_10267 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_57 = scale_10264;
			t_sample mtof_58 = mtof(scale_57, ((int)440));
			t_sample mul_45 = (mtof_58 * div_46);
			t_sample cos_43 = cos(mul_45);
			t_sample mul_38 = (cos_43 * (-2));
			t_sample sin_44 = sin(mul_45);
			t_sample mul_42 = (sin_44 * ((t_sample)0.5));
			t_sample div_41 = (mul_42 * ((t_sample)0.33333333333333));
			t_sample rsub_36 = (((int)1) - div_41);
			t_sample add_40 = (div_41 + ((int)1));
			t_sample rdiv_39 = safediv(((int)1), add_40);
			t_sample mul_37 = (rdiv_39 * mul_38);
			__m_slide_43 = fixdenorm((__m_slide_43 + (((mul_37 > __m_slide_43) ? iup_44 : idown_45) * (mul_37 - __m_slide_43))));
			t_sample slide_33 = __m_slide_43;
			t_sample gen_47 = slide_33;
			t_sample mul_35 = (rdiv_39 * rsub_36);
			__m_slide_46 = fixdenorm((__m_slide_46 + (((mul_35 > __m_slide_46) ? iup_47 : idown_48) * (mul_35 - __m_slide_46))));
			t_sample slide_32 = __m_slide_46;
			t_sample gen_48 = slide_32;
			t_sample mul_68 = (add_20 * gen_48);
			t_sample mul_65 = (m_history_12 * gen_47);
			t_sample mul_63 = (m_history_14 * ((int)1));
			t_sample mul_59 = (m_history_13 * gen_48);
			t_sample mul_61 = (m_history_11 * gen_47);
			t_sample sub_67 = (((mul_63 + mul_65) + mul_68) - (mul_61 + mul_59));
			t_sample gen_73 = sub_67;
			t_sample history_64_next_69 = fixdenorm(m_history_12);
			t_sample history_60_next_70 = fixdenorm(m_history_11);
			t_sample history_66_next_71 = fixdenorm(add_20);
			t_sample history_62_next_72 = fixdenorm(sub_67);
			t_sample mul_5653 = ((gen_73 + gen_161) * ((t_sample)0.5));
			t_sample dcblock_9 = __m_dcblock_49(mul_5653);
			t_sample mul_9996 = (((gate_6108 + gen_73) + gen_161) * scale_10253);
			t_sample add_10 = (mul_9996 + gate_6107);
			t_sample out1 = add_10;
			t_sample add_1071 = (phasor_31 + ((t_sample)0.375));
			t_sample mod_1072 = safemod(add_1071, ((int)1));
			__m_cycle_50.phase(mod_1072);
			t_sample cycle_1069 = __m_cycle_50(__sinedata);
			t_sample cycleindex_1070 = __m_cycle_50.phase();
			t_sample add_1067 = (cycle_1069 + ((int)1));
			t_sample div_1066 = (add_1067 * ((t_sample)0.5));
			t_sample mul_1068 = (div_1066 * mul_6859);
			t_sample sub_10271 = (mul_1068 - ((int)0));
			t_sample scale_10268 = ((safepow((sub_10271 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_1073 = scale_10268;
			t_sample mtof_1074 = mtof(scale_1073, ((int)440));
			t_sample mul_1061 = (mtof_1074 * div_1062);
			t_sample cos_1059 = cos(mul_1061);
			t_sample mul_1054 = (cos_1059 * (-2));
			t_sample sin_1060 = sin(mul_1061);
			t_sample mul_1058 = (sin_1060 * ((t_sample)0.5));
			t_sample div_1057 = (mul_1058 * ((t_sample)0.33333333333333));
			t_sample rsub_1052 = (((int)1) - div_1057);
			t_sample add_1056 = (div_1057 + ((int)1));
			t_sample rdiv_1055 = safediv(((int)1), add_1056);
			t_sample mul_1051 = (rdiv_1055 * rsub_1052);
			__m_slide_51 = fixdenorm((__m_slide_51 + (((mul_1051 > __m_slide_51) ? iup_52 : idown_53) * (mul_1051 - __m_slide_51))));
			t_sample slide_1048 = __m_slide_51;
			t_sample gen_1064 = slide_1048;
			t_sample mul_1053 = (rdiv_1055 * mul_1054);
			__m_slide_54 = fixdenorm((__m_slide_54 + (((mul_1053 > __m_slide_54) ? iup_55 : idown_56) * (mul_1053 - __m_slide_54))));
			t_sample slide_1049 = __m_slide_54;
			t_sample gen_1063 = slide_1049;
			t_sample mul_1084 = (add_2712 * gen_1064);
			t_sample mul_1081 = (m_history_8 * gen_1063);
			t_sample mul_1079 = (m_history_9 * ((int)1));
			t_sample mul_1075 = (m_history_10 * gen_1064);
			t_sample mul_1077 = (m_history_7 * gen_1063);
			t_sample sub_1083 = (((mul_1079 + mul_1081) + mul_1084) - (mul_1077 + mul_1075));
			t_sample gen_1089 = sub_1083;
			t_sample history_1076_next_1085 = fixdenorm(m_history_7);
			t_sample history_1080_next_1086 = fixdenorm(m_history_8);
			t_sample history_1082_next_1087 = fixdenorm(add_2712);
			t_sample history_1078_next_1088 = fixdenorm(sub_1083);
			t_sample add_1113 = (phasor_31 + ((t_sample)0.125));
			t_sample mod_1114 = safemod(add_1113, ((int)1));
			__m_cycle_57.phase(mod_1114);
			t_sample cycle_1111 = __m_cycle_57(__sinedata);
			t_sample cycleindex_1112 = __m_cycle_57.phase();
			t_sample add_1109 = (cycle_1111 + ((int)1));
			t_sample div_1108 = (add_1109 * ((t_sample)0.5));
			t_sample mul_1110 = (div_1108 * mul_6859);
			t_sample sub_10275 = (mul_1110 - ((int)0));
			t_sample scale_10272 = ((safepow((sub_10275 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_1115 = scale_10272;
			t_sample mtof_1116 = mtof(scale_1115, ((int)440));
			t_sample mul_1103 = (mtof_1116 * div_1104);
			t_sample cos_1101 = cos(mul_1103);
			t_sample mul_1096 = (cos_1101 * (-2));
			t_sample sin_1102 = sin(mul_1103);
			t_sample mul_1100 = (sin_1102 * ((t_sample)0.5));
			t_sample div_1099 = (mul_1100 * ((t_sample)0.33333333333333));
			t_sample rsub_1094 = (((int)1) - div_1099);
			t_sample add_1098 = (div_1099 + ((int)1));
			t_sample rdiv_1097 = safediv(((int)1), add_1098);
			t_sample mul_1095 = (rdiv_1097 * mul_1096);
			__m_slide_58 = fixdenorm((__m_slide_58 + (((mul_1095 > __m_slide_58) ? iup_59 : idown_60) * (mul_1095 - __m_slide_58))));
			t_sample slide_1091 = __m_slide_58;
			t_sample gen_1105 = slide_1091;
			t_sample mul_1093 = (rdiv_1097 * rsub_1094);
			__m_slide_61 = fixdenorm((__m_slide_61 + (((mul_1093 > __m_slide_61) ? iup_62 : idown_63) * (mul_1093 - __m_slide_61))));
			t_sample slide_1090 = __m_slide_61;
			t_sample gen_1106 = slide_1090;
			t_sample mul_1121 = (m_history_6 * ((int)1));
			t_sample mul_1123 = (m_history_4 * gen_1105);
			t_sample mul_1126 = (add_2712 * gen_1106);
			t_sample mul_1119 = (m_history_3 * gen_1105);
			t_sample mul_1117 = (m_history_5 * gen_1106);
			t_sample sub_1125 = (((mul_1126 + mul_1123) + mul_1121) - (mul_1117 + mul_1119));
			t_sample gen_1131 = sub_1125;
			t_sample history_1122_next_1127 = fixdenorm(m_history_4);
			t_sample history_1118_next_1128 = fixdenorm(m_history_3);
			t_sample history_1124_next_1129 = fixdenorm(add_2712);
			t_sample history_1120_next_1130 = fixdenorm(sub_1125);
			t_sample mul_5688 = ((gen_1131 + gen_1089) * ((t_sample)0.5));
			t_sample dcblock_2453 = __m_dcblock_64(mul_5688);
			t_sample mul_9955 = (((gate_6108 + gen_1131) + gen_1089) * scale_10253);
			t_sample add_8 = (mul_9955 + gate_6107);
			t_sample out2 = add_8;
			t_sample history_2711_next_10205 = fixdenorm(dcblock_9);
			t_sample history_19_next_10206 = fixdenorm(dcblock_2453);
			m_history_22 = history_6111_next_6113;
			m_history_21 = history_9625_next_9628;
			m_history_19 = history_9620_next_9630;
			m_history_20 = history_9622_next_9629;
			m_history_18 = history_152_next_157;
			m_history_15 = history_150_next_160;
			m_history_16 = history_154_next_159;
			m_history_17 = history_148_next_158;
			m_history_14 = history_64_next_69;
			m_history_11 = history_62_next_72;
			m_history_12 = history_66_next_71;
			m_history_13 = history_60_next_70;
			m_history_10 = history_1076_next_1085;
			m_history_7 = history_1078_next_1088;
			m_history_8 = history_1082_next_1087;
			m_history_9 = history_1080_next_1086;
			m_history_6 = history_1122_next_1127;
			m_history_3 = history_1120_next_1130;
			m_history_4 = history_1124_next_1129;
			m_history_5 = history_1118_next_1128;
			m_history_2 = history_2711_next_10205;
			m_history_1 = history_19_next_10206;
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
		m_knob3_depth_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_rate(t_param _value) {
		m_knob4_rate_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_fb(t_param _value) {
		m_knob5_fb_25 = (_value < 0.5 ? 0.5 : (_value > 0.99 ? 0.99 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
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
		case 0: *value = self->m_knob3_depth_23; break;
		case 1: *value = self->m_knob4_rate_24; break;
		case 2: *value = self->m_knob5_fb_25; break;
		case 3: *value = self->m_sw_27; break;
		case 4: *value = self->m_sw_26; break;
		
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
	// initialize parameter 0 ("m_knob3_depth_23")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_depth_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_rate_24")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_rate_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_fb_25")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_fb_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_sw_27")
	pi = self->__commonstate.params + 3;
	pi->name = "sw1";
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
	// initialize parameter 4 ("m_sw_26")
	pi = self->__commonstate.params + 4;
	pi->name = "sw5";
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // lukephaser_field_stereo::
