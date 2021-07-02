#include "lukephaser_field.h"

namespace lukephaser_field {

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
	DCBlock __m_dcblock_115;
	DCBlock __m_dcblock_114;
	Phasor __m_phasor_41;
	Sah __m_sah_61;
	Sah __m_sah_70;
	Sah __m_sah_106;
	Sah __m_sah_43;
	Sah __m_sah_79;
	Sah __m_sah_52;
	Sah __m_sah_88;
	Sah __m_sah_97;
	SineCycle __m_cycle_42;
	SineCycle __m_cycle_51;
	SineCycle __m_cycle_69;
	SineCycle __m_cycle_78;
	SineCycle __m_cycle_60;
	SineCycle __m_cycle_96;
	SineCycle __m_cycle_105;
	SineCycle __m_cycle_87;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample __m_slide_72;
	t_sample m_history_7;
	t_sample m_history_8;
	t_sample m_history_19;
	t_sample m_history_6;
	t_sample __m_slide_75;
	t_sample m_history_5;
	t_sample __m_slide_66;
	t_sample m_history_9;
	t_sample __m_slide_54;
	t_sample __m_slide_63;
	t_sample __m_slide_57;
	t_sample m_history_10;
	t_sample m_history_11;
	t_sample __m_slide_81;
	t_sample m_history_4;
	t_sample samplerate;
	t_sample __m_slide_102;
	t_sample __m_slide_108;
	t_sample __m_slide_111;
	t_sample __m_slide_84;
	t_sample __m_slide_99;
	t_sample m_history_2;
	t_sample m_history_3;
	t_sample m_history_1;
	t_sample __m_slide_90;
	t_sample __m_slide_93;
	t_sample m_history_18;
	t_sample m_history_12;
	t_sample __m_slide_45;
	t_sample m_history_27;
	t_sample m_history_26;
	t_sample m_history_28;
	t_sample m_history_30;
	t_sample m_history_29;
	t_sample m_history_31;
	t_sample m_history_25;
	t_sample m_history_23;
	t_sample m_history_20;
	t_sample m_history_24;
	t_sample m_history_21;
	t_sample m_history_22;
	t_sample __m_slide_48;
	t_sample m_history_32;
	t_sample m_knob1_rate_34;
	t_sample m_history_16;
	t_sample samples_to_seconds;
	t_sample m_history_15;
	t_sample m_history_13;
	t_sample m_history_14;
	t_sample m_history_33;
	t_sample m_knob3_Q_40;
	t_sample m_knob4_diffusion_38;
	t_sample m_knob6_waveform_35;
	t_sample m_knob2_width_39;
	t_sample m_knob7_gain_36;
	t_sample m_history_17;
	t_sample m_knob5_fb_37;
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
		m_knob1_rate_34 = 0.1;
		m_knob6_waveform_35 = 1;
		m_knob7_gain_36 = 1;
		m_knob5_fb_37 = 0;
		m_knob4_diffusion_38 = 0;
		m_knob2_width_39 = 1;
		m_knob3_Q_40 = 0.5;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_41.reset(0);
		__m_cycle_42.reset(samplerate, 0);
		__m_sah_43.reset(0);
		__m_slide_45 = 0;
		__m_slide_48 = 0;
		__m_cycle_51.reset(samplerate, 0);
		__m_sah_52.reset(0);
		__m_slide_54 = 0;
		__m_slide_57 = 0;
		__m_cycle_60.reset(samplerate, 0);
		__m_sah_61.reset(0);
		__m_slide_63 = 0;
		__m_slide_66 = 0;
		__m_cycle_69.reset(samplerate, 0);
		__m_sah_70.reset(0);
		__m_slide_72 = 0;
		__m_slide_75 = 0;
		__m_cycle_78.reset(samplerate, 0);
		__m_sah_79.reset(0);
		__m_slide_81 = 0;
		__m_slide_84 = 0;
		__m_cycle_87.reset(samplerate, 0);
		__m_sah_88.reset(0);
		__m_slide_90 = 0;
		__m_slide_93 = 0;
		__m_cycle_96.reset(samplerate, 0);
		__m_sah_97.reset(0);
		__m_slide_99 = 0;
		__m_slide_102 = 0;
		__m_cycle_105.reset(samplerate, 0);
		__m_sah_106.reset(0);
		__m_slide_108 = 0;
		__m_slide_111 = 0;
		__m_dcblock_114.reset();
		__m_dcblock_115.reset();
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
		samples_to_seconds = (1 / samplerate);
		t_sample floor_1890 = floor(m_knob6_waveform_35);
		t_sample mul_1724 = (m_knob4_diffusion_38 * ((int)7));
		t_sample div_1723 = (mul_1724 * ((t_sample)0.125));
		t_sample mul_1728 = (m_knob4_diffusion_38 * ((int)6));
		t_sample div_1725 = (mul_1728 * ((t_sample)0.125));
		t_sample mul_1729 = (m_knob4_diffusion_38 * ((int)5));
		t_sample div_1726 = (mul_1729 * ((t_sample)0.125));
		t_sample mul_1730 = (m_knob4_diffusion_38 * ((int)4));
		t_sample div_1727 = (mul_1730 * ((t_sample)0.125));
		t_sample mul_1882 = (m_knob4_diffusion_38 * ((int)3));
		t_sample div_1881 = (mul_1882 * ((t_sample)0.125));
		t_sample mul_1886 = (m_knob4_diffusion_38 * ((int)2));
		t_sample div_1883 = (mul_1886 * ((t_sample)0.125));
		t_sample mul_1887 = (m_knob4_diffusion_38 * ((int)1));
		t_sample div_1884 = (mul_1887 * ((t_sample)0.125));
		t_sample mul_1888 = (m_knob4_diffusion_38 * ((int)0));
		t_sample div_1885 = (mul_1888 * ((t_sample)0.125));
		t_sample choice_44 = int(floor_1890);
		t_sample div_1910 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_46 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_47 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_49 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_50 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_53 = int(floor_1890);
		t_sample div_2055 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_55 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_56 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_58 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_59 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_62 = int(floor_1890);
		t_sample div_2154 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_64 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_65 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_67 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_68 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_71 = int(floor_1890);
		t_sample div_2105 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_73 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_74 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_76 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_77 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_80 = int(floor_1890);
		t_sample div_2465 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_82 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_83 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_85 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_86 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_89 = int(floor_1890);
		t_sample div_2416 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_91 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_92 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_94 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_95 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_98 = int(floor_1890);
		t_sample div_2367 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_100 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_101 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_103 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_104 = (1 / maximum(1, abs(((int)5))));
		t_sample choice_107 = int(floor_1890);
		t_sample div_2318 = safediv(((t_sample)6.2831853071796), samplerate);
		t_sample iup_109 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_110 = (1 / maximum(1, abs(((int)5))));
		t_sample iup_112 = (1 / maximum(1, abs(((int)5))));
		t_sample idown_113 = (1 / maximum(1, abs(((int)5))));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample phasor_1891 = __m_phasor_41(m_knob1_rate_34, samples_to_seconds);
			t_sample mul_1721 = (in2 * ((int)0));
			t_sample mul_1941 = (in1 * m_knob7_gain_36);
			t_sample mul_1733 = (m_history_1 * m_knob5_fb_37);
			t_sample add_1732 = (mul_1941 + mul_1733);
			t_sample add_1922 = (phasor_1891 + div_1885);
			t_sample mod_1923 = safemod(add_1922, ((int)1));
			t_sample triangle_1919 = triangle(mod_1923, ((t_sample)0.5));
			int gt_1918 = (mod_1923 > ((t_sample)0.5));
			__m_cycle_42.phase(mod_1923);
			t_sample cycle_1920 = __m_cycle_42(__sinedata);
			t_sample cycleindex_1921 = __m_cycle_42.phase();
			t_sample add_1916 = (cycle_1920 + ((int)1));
			t_sample div_1915 = (add_1916 * ((t_sample)0.5));
			t_sample noise_1894 = noise();
			t_sample sah_1895 = __m_sah_43(noise_1894, mod_1923, ((t_sample)0.5));
			t_sample add_1893 = (sah_1895 + ((int)1));
			t_sample div_1892 = (add_1893 * ((t_sample)0.5));
			t_sample selector_1914 = ((choice_44 >= 5) ? div_1892 : ((choice_44 >= 4) ? gt_1918 : ((choice_44 >= 3) ? mod_1923 : ((choice_44 >= 2) ? triangle_1919 : ((choice_44 >= 1) ? div_1915 : 0)))));
			t_sample mul_1917 = (selector_1914 * m_knob2_width_39);
			t_sample sub_4375 = (mul_1917 - ((int)0));
			t_sample scale_4372 = ((safepow((sub_4375 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_1924 = scale_4372;
			t_sample mtof_1925 = mtof(scale_1924, ((int)440));
			t_sample mul_1909 = (mtof_1925 * div_1910);
			t_sample cos_1907 = cos(mul_1909);
			t_sample mul_1902 = (cos_1907 * (-2));
			t_sample sin_1908 = sin(mul_1909);
			t_sample mul_1906 = (sin_1908 * ((t_sample)0.5));
			t_sample div_1905 = safediv(mul_1906, m_knob3_Q_40);
			t_sample rsub_1900 = (((int)1) - div_1905);
			t_sample add_1904 = (div_1905 + ((int)1));
			t_sample rdiv_1903 = safediv(((int)1), add_1904);
			t_sample mul_1899 = (rdiv_1903 * rsub_1900);
			__m_slide_45 = fixdenorm((__m_slide_45 + (((mul_1899 > __m_slide_45) ? iup_46 : idown_47) * (mul_1899 - __m_slide_45))));
			t_sample slide_1896 = __m_slide_45;
			t_sample gen_1912 = slide_1896;
			t_sample mul_1901 = (rdiv_1903 * mul_1902);
			__m_slide_48 = fixdenorm((__m_slide_48 + (((mul_1901 > __m_slide_48) ? iup_49 : idown_50) * (mul_1901 - __m_slide_48))));
			t_sample slide_1897 = __m_slide_48;
			t_sample gen_1911 = slide_1897;
			t_sample mul_1935 = (add_1732 * gen_1912);
			t_sample mul_1932 = (m_history_31 * gen_1911);
			t_sample mul_1930 = (m_history_32 * ((int)1));
			t_sample mul_1926 = (m_history_33 * gen_1912);
			t_sample mul_1928 = (m_history_30 * gen_1911);
			t_sample sub_1934 = (((mul_1930 + mul_1932) + mul_1935) - (mul_1928 + mul_1926));
			t_sample gen_1940 = sub_1934;
			t_sample history_1927_next_1936 = fixdenorm(m_history_30);
			t_sample history_1931_next_1937 = fixdenorm(m_history_31);
			t_sample history_1933_next_1938 = fixdenorm(add_1732);
			t_sample history_1929_next_1939 = fixdenorm(sub_1934);
			t_sample add_2067 = (phasor_1891 + div_1884);
			t_sample mod_2068 = safemod(add_2067, ((int)1));
			t_sample triangle_2064 = triangle(mod_2068, ((t_sample)0.5));
			int gt_2063 = (mod_2068 > ((t_sample)0.5));
			__m_cycle_51.phase(mod_2068);
			t_sample cycle_2065 = __m_cycle_51(__sinedata);
			t_sample cycleindex_2066 = __m_cycle_51.phase();
			t_sample add_2061 = (cycle_2065 + ((int)1));
			t_sample div_2060 = (add_2061 * ((t_sample)0.5));
			t_sample noise_2039 = noise();
			t_sample sah_2040 = __m_sah_52(noise_2039, mod_2068, ((t_sample)0.5));
			t_sample add_2038 = (sah_2040 + ((int)1));
			t_sample div_2037 = (add_2038 * ((t_sample)0.5));
			t_sample selector_2059 = ((choice_53 >= 5) ? div_2037 : ((choice_53 >= 4) ? gt_2063 : ((choice_53 >= 3) ? mod_2068 : ((choice_53 >= 2) ? triangle_2064 : ((choice_53 >= 1) ? div_2060 : 0)))));
			t_sample mul_2062 = (selector_2059 * m_knob2_width_39);
			t_sample sub_4379 = (mul_2062 - ((int)0));
			t_sample scale_4376 = ((safepow((sub_4379 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_2069 = scale_4376;
			t_sample mtof_2070 = mtof(scale_2069, ((int)440));
			t_sample mul_2054 = (mtof_2070 * div_2055);
			t_sample cos_2052 = cos(mul_2054);
			t_sample mul_2047 = (cos_2052 * (-2));
			t_sample sin_2053 = sin(mul_2054);
			t_sample mul_2051 = (sin_2053 * ((t_sample)0.5));
			t_sample div_2050 = safediv(mul_2051, m_knob3_Q_40);
			t_sample rsub_2045 = (((int)1) - div_2050);
			t_sample add_2049 = (div_2050 + ((int)1));
			t_sample rdiv_2048 = safediv(((int)1), add_2049);
			t_sample mul_2044 = (rdiv_2048 * rsub_2045);
			__m_slide_54 = fixdenorm((__m_slide_54 + (((mul_2044 > __m_slide_54) ? iup_55 : idown_56) * (mul_2044 - __m_slide_54))));
			t_sample slide_2041 = __m_slide_54;
			t_sample gen_2057 = slide_2041;
			t_sample mul_2046 = (rdiv_2048 * mul_2047);
			__m_slide_57 = fixdenorm((__m_slide_57 + (((mul_2046 > __m_slide_57) ? iup_58 : idown_59) * (mul_2046 - __m_slide_57))));
			t_sample slide_2042 = __m_slide_57;
			t_sample gen_2056 = slide_2042;
			t_sample mul_2075 = (m_history_29 * ((int)1));
			t_sample mul_2077 = (m_history_27 * gen_2056);
			t_sample mul_2080 = (gen_1940 * gen_2057);
			t_sample mul_2073 = (m_history_26 * gen_2056);
			t_sample mul_2071 = (m_history_28 * gen_2057);
			t_sample sub_2079 = (((mul_2080 + mul_2077) + mul_2075) - (mul_2071 + mul_2073));
			t_sample gen_2085 = sub_2079;
			t_sample history_2076_next_2081 = fixdenorm(m_history_27);
			t_sample history_2072_next_2082 = fixdenorm(m_history_26);
			t_sample history_2078_next_2083 = fixdenorm(gen_1940);
			t_sample history_2074_next_2084 = fixdenorm(sub_2079);
			t_sample add_2166 = (phasor_1891 + div_1883);
			t_sample mod_2167 = safemod(add_2166, ((int)1));
			t_sample triangle_2163 = triangle(mod_2167, ((t_sample)0.5));
			int gt_2162 = (mod_2167 > ((t_sample)0.5));
			__m_cycle_60.phase(mod_2167);
			t_sample cycle_2164 = __m_cycle_60(__sinedata);
			t_sample cycleindex_2165 = __m_cycle_60.phase();
			t_sample add_2160 = (cycle_2164 + ((int)1));
			t_sample div_2159 = (add_2160 * ((t_sample)0.5));
			t_sample noise_2138 = noise();
			t_sample sah_2139 = __m_sah_61(noise_2138, mod_2167, ((t_sample)0.5));
			t_sample add_2137 = (sah_2139 + ((int)1));
			t_sample div_2136 = (add_2137 * ((t_sample)0.5));
			t_sample selector_2158 = ((choice_62 >= 5) ? div_2136 : ((choice_62 >= 4) ? gt_2162 : ((choice_62 >= 3) ? mod_2167 : ((choice_62 >= 2) ? triangle_2163 : ((choice_62 >= 1) ? div_2159 : 0)))));
			t_sample mul_2161 = (selector_2158 * m_knob2_width_39);
			t_sample sub_4383 = (mul_2161 - ((int)0));
			t_sample scale_4380 = ((safepow((sub_4383 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_2168 = scale_4380;
			t_sample mtof_2169 = mtof(scale_2168, ((int)440));
			t_sample mul_2153 = (mtof_2169 * div_2154);
			t_sample cos_2151 = cos(mul_2153);
			t_sample mul_2146 = (cos_2151 * (-2));
			t_sample sin_2152 = sin(mul_2153);
			t_sample mul_2150 = (sin_2152 * ((t_sample)0.5));
			t_sample div_2149 = safediv(mul_2150, m_knob3_Q_40);
			t_sample rsub_2144 = (((int)1) - div_2149);
			t_sample add_2148 = (div_2149 + ((int)1));
			t_sample rdiv_2147 = safediv(((int)1), add_2148);
			t_sample mul_2145 = (rdiv_2147 * mul_2146);
			__m_slide_63 = fixdenorm((__m_slide_63 + (((mul_2145 > __m_slide_63) ? iup_64 : idown_65) * (mul_2145 - __m_slide_63))));
			t_sample slide_2141 = __m_slide_63;
			t_sample gen_2155 = slide_2141;
			t_sample mul_2143 = (rdiv_2147 * rsub_2144);
			__m_slide_66 = fixdenorm((__m_slide_66 + (((mul_2143 > __m_slide_66) ? iup_67 : idown_68) * (mul_2143 - __m_slide_66))));
			t_sample slide_2140 = __m_slide_66;
			t_sample gen_2156 = slide_2140;
			t_sample mul_2174 = (m_history_24 * ((int)1));
			t_sample mul_2176 = (m_history_23 * gen_2155);
			t_sample mul_2179 = (gen_2085 * gen_2156);
			t_sample mul_2172 = (m_history_22 * gen_2155);
			t_sample mul_2170 = (m_history_25 * gen_2156);
			t_sample sub_2178 = (((mul_2179 + mul_2176) + mul_2174) - (mul_2170 + mul_2172));
			t_sample gen_2184 = sub_2178;
			t_sample history_2171_next_2180 = fixdenorm(m_history_22);
			t_sample history_2175_next_2181 = fixdenorm(m_history_23);
			t_sample history_2177_next_2182 = fixdenorm(gen_2085);
			t_sample history_2173_next_2183 = fixdenorm(sub_2178);
			t_sample add_2117 = (phasor_1891 + div_1881);
			t_sample mod_2118 = safemod(add_2117, ((int)1));
			t_sample triangle_2114 = triangle(mod_2118, ((t_sample)0.5));
			int gt_2113 = (mod_2118 > ((t_sample)0.5));
			__m_cycle_69.phase(mod_2118);
			t_sample cycle_2115 = __m_cycle_69(__sinedata);
			t_sample cycleindex_2116 = __m_cycle_69.phase();
			t_sample add_2111 = (cycle_2115 + ((int)1));
			t_sample div_2110 = (add_2111 * ((t_sample)0.5));
			t_sample noise_2089 = noise();
			t_sample sah_2090 = __m_sah_70(noise_2089, mod_2118, ((t_sample)0.5));
			t_sample add_2088 = (sah_2090 + ((int)1));
			t_sample div_2087 = (add_2088 * ((t_sample)0.5));
			t_sample selector_2109 = ((choice_71 >= 5) ? div_2087 : ((choice_71 >= 4) ? gt_2113 : ((choice_71 >= 3) ? mod_2118 : ((choice_71 >= 2) ? triangle_2114 : ((choice_71 >= 1) ? div_2110 : 0)))));
			t_sample mul_2112 = (selector_2109 * m_knob2_width_39);
			t_sample sub_4387 = (mul_2112 - ((int)0));
			t_sample scale_4384 = ((safepow((sub_4387 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_2119 = scale_4384;
			t_sample mtof_2120 = mtof(scale_2119, ((int)440));
			t_sample mul_2104 = (mtof_2120 * div_2105);
			t_sample cos_2102 = cos(mul_2104);
			t_sample mul_2097 = (cos_2102 * (-2));
			t_sample sin_2103 = sin(mul_2104);
			t_sample mul_2101 = (sin_2103 * ((t_sample)0.5));
			t_sample div_2100 = safediv(mul_2101, m_knob3_Q_40);
			t_sample rsub_2095 = (((int)1) - div_2100);
			t_sample add_2099 = (div_2100 + ((int)1));
			t_sample rdiv_2098 = safediv(((int)1), add_2099);
			t_sample mul_2096 = (rdiv_2098 * mul_2097);
			__m_slide_72 = fixdenorm((__m_slide_72 + (((mul_2096 > __m_slide_72) ? iup_73 : idown_74) * (mul_2096 - __m_slide_72))));
			t_sample slide_2092 = __m_slide_72;
			t_sample gen_2106 = slide_2092;
			t_sample mul_2094 = (rdiv_2098 * rsub_2095);
			__m_slide_75 = fixdenorm((__m_slide_75 + (((mul_2094 > __m_slide_75) ? iup_76 : idown_77) * (mul_2094 - __m_slide_75))));
			t_sample slide_2091 = __m_slide_75;
			t_sample gen_2107 = slide_2091;
			t_sample mul_2125 = (m_history_21 * ((int)1));
			t_sample mul_2127 = (m_history_19 * gen_2106);
			t_sample mul_2130 = (gen_2184 * gen_2107);
			t_sample mul_2123 = (m_history_18 * gen_2106);
			t_sample mul_2121 = (m_history_20 * gen_2107);
			t_sample sub_2129 = (((mul_2130 + mul_2127) + mul_2125) - (mul_2121 + mul_2123));
			t_sample gen_2135 = sub_2129;
			t_sample history_2126_next_2131 = fixdenorm(m_history_19);
			t_sample history_2122_next_2132 = fixdenorm(m_history_18);
			t_sample history_2128_next_2133 = fixdenorm(gen_2184);
			t_sample history_2124_next_2134 = fixdenorm(sub_2129);
			t_sample add_2477 = (phasor_1891 + div_1727);
			t_sample mod_2478 = safemod(add_2477, ((int)1));
			t_sample triangle_2474 = triangle(mod_2478, ((t_sample)0.5));
			int gt_2473 = (mod_2478 > ((t_sample)0.5));
			__m_cycle_78.phase(mod_2478);
			t_sample cycle_2475 = __m_cycle_78(__sinedata);
			t_sample cycleindex_2476 = __m_cycle_78.phase();
			t_sample add_2471 = (cycle_2475 + ((int)1));
			t_sample div_2470 = (add_2471 * ((t_sample)0.5));
			t_sample noise_2449 = noise();
			t_sample sah_2450 = __m_sah_79(noise_2449, mod_2478, ((t_sample)0.5));
			t_sample add_2448 = (sah_2450 + ((int)1));
			t_sample div_2447 = (add_2448 * ((t_sample)0.5));
			t_sample selector_2469 = ((choice_80 >= 5) ? div_2447 : ((choice_80 >= 4) ? gt_2473 : ((choice_80 >= 3) ? mod_2478 : ((choice_80 >= 2) ? triangle_2474 : ((choice_80 >= 1) ? div_2470 : 0)))));
			t_sample mul_2472 = (selector_2469 * m_knob2_width_39);
			t_sample sub_4391 = (mul_2472 - ((int)0));
			t_sample scale_4388 = ((safepow((sub_4391 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_2479 = scale_4388;
			t_sample mtof_2480 = mtof(scale_2479, ((int)440));
			t_sample mul_2464 = (mtof_2480 * div_2465);
			t_sample cos_2462 = cos(mul_2464);
			t_sample mul_2457 = (cos_2462 * (-2));
			t_sample sin_2463 = sin(mul_2464);
			t_sample mul_2461 = (sin_2463 * ((t_sample)0.5));
			t_sample div_2460 = safediv(mul_2461, m_knob3_Q_40);
			t_sample rsub_2455 = (((int)1) - div_2460);
			t_sample add_2459 = (div_2460 + ((int)1));
			t_sample rdiv_2458 = safediv(((int)1), add_2459);
			t_sample mul_2456 = (rdiv_2458 * mul_2457);
			__m_slide_81 = fixdenorm((__m_slide_81 + (((mul_2456 > __m_slide_81) ? iup_82 : idown_83) * (mul_2456 - __m_slide_81))));
			t_sample slide_2452 = __m_slide_81;
			t_sample gen_2466 = slide_2452;
			t_sample mul_2454 = (rdiv_2458 * rsub_2455);
			__m_slide_84 = fixdenorm((__m_slide_84 + (((mul_2454 > __m_slide_84) ? iup_85 : idown_86) * (mul_2454 - __m_slide_84))));
			t_sample slide_2451 = __m_slide_84;
			t_sample gen_2467 = slide_2451;
			t_sample mul_2485 = (m_history_16 * ((int)1));
			t_sample mul_2487 = (m_history_15 * gen_2466);
			t_sample mul_2490 = (gen_2135 * gen_2467);
			t_sample mul_2483 = (m_history_14 * gen_2466);
			t_sample mul_2481 = (m_history_17 * gen_2467);
			t_sample sub_2489 = (((mul_2490 + mul_2487) + mul_2485) - (mul_2481 + mul_2483));
			t_sample gen_2495 = sub_2489;
			t_sample history_2482_next_2491 = fixdenorm(m_history_14);
			t_sample history_2486_next_2492 = fixdenorm(m_history_15);
			t_sample history_2488_next_2493 = fixdenorm(gen_2135);
			t_sample history_2484_next_2494 = fixdenorm(sub_2489);
			t_sample add_2428 = (phasor_1891 + div_1726);
			t_sample mod_2429 = safemod(add_2428, ((int)1));
			t_sample triangle_2425 = triangle(mod_2429, ((t_sample)0.5));
			int gt_2424 = (mod_2429 > ((t_sample)0.5));
			__m_cycle_87.phase(mod_2429);
			t_sample cycle_2426 = __m_cycle_87(__sinedata);
			t_sample cycleindex_2427 = __m_cycle_87.phase();
			t_sample add_2422 = (cycle_2426 + ((int)1));
			t_sample div_2421 = (add_2422 * ((t_sample)0.5));
			t_sample noise_2400 = noise();
			t_sample sah_2401 = __m_sah_88(noise_2400, mod_2429, ((t_sample)0.5));
			t_sample add_2399 = (sah_2401 + ((int)1));
			t_sample div_2398 = (add_2399 * ((t_sample)0.5));
			t_sample selector_2420 = ((choice_89 >= 5) ? div_2398 : ((choice_89 >= 4) ? gt_2424 : ((choice_89 >= 3) ? mod_2429 : ((choice_89 >= 2) ? triangle_2425 : ((choice_89 >= 1) ? div_2421 : 0)))));
			t_sample mul_2423 = (selector_2420 * m_knob2_width_39);
			t_sample sub_4395 = (mul_2423 - ((int)0));
			t_sample scale_4392 = ((safepow((sub_4395 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_2430 = scale_4392;
			t_sample mtof_2431 = mtof(scale_2430, ((int)440));
			t_sample mul_2415 = (mtof_2431 * div_2416);
			t_sample cos_2413 = cos(mul_2415);
			t_sample mul_2408 = (cos_2413 * (-2));
			t_sample sin_2414 = sin(mul_2415);
			t_sample mul_2412 = (sin_2414 * ((t_sample)0.5));
			t_sample div_2411 = safediv(mul_2412, m_knob3_Q_40);
			t_sample rsub_2406 = (((int)1) - div_2411);
			t_sample add_2410 = (div_2411 + ((int)1));
			t_sample rdiv_2409 = safediv(((int)1), add_2410);
			t_sample mul_2407 = (rdiv_2409 * mul_2408);
			__m_slide_90 = fixdenorm((__m_slide_90 + (((mul_2407 > __m_slide_90) ? iup_91 : idown_92) * (mul_2407 - __m_slide_90))));
			t_sample slide_2403 = __m_slide_90;
			t_sample gen_2417 = slide_2403;
			t_sample mul_2405 = (rdiv_2409 * rsub_2406);
			__m_slide_93 = fixdenorm((__m_slide_93 + (((mul_2405 > __m_slide_93) ? iup_94 : idown_95) * (mul_2405 - __m_slide_93))));
			t_sample slide_2402 = __m_slide_93;
			t_sample gen_2418 = slide_2402;
			t_sample mul_2441 = (gen_2495 * gen_2418);
			t_sample mul_2438 = (m_history_11 * gen_2417);
			t_sample mul_2436 = (m_history_12 * ((int)1));
			t_sample mul_2432 = (m_history_13 * gen_2418);
			t_sample mul_2434 = (m_history_10 * gen_2417);
			t_sample sub_2440 = (((mul_2436 + mul_2438) + mul_2441) - (mul_2434 + mul_2432));
			t_sample gen_2446 = sub_2440;
			t_sample history_2433_next_2442 = fixdenorm(m_history_10);
			t_sample history_2437_next_2443 = fixdenorm(m_history_11);
			t_sample history_2439_next_2444 = fixdenorm(gen_2495);
			t_sample history_2435_next_2445 = fixdenorm(sub_2440);
			t_sample add_2379 = (phasor_1891 + div_1725);
			t_sample mod_2380 = safemod(add_2379, ((int)1));
			t_sample triangle_2376 = triangle(mod_2380, ((t_sample)0.5));
			int gt_2375 = (mod_2380 > ((t_sample)0.5));
			__m_cycle_96.phase(mod_2380);
			t_sample cycle_2377 = __m_cycle_96(__sinedata);
			t_sample cycleindex_2378 = __m_cycle_96.phase();
			t_sample add_2373 = (cycle_2377 + ((int)1));
			t_sample div_2372 = (add_2373 * ((t_sample)0.5));
			t_sample noise_2351 = noise();
			t_sample sah_2352 = __m_sah_97(noise_2351, mod_2380, ((t_sample)0.5));
			t_sample add_2350 = (sah_2352 + ((int)1));
			t_sample div_2349 = (add_2350 * ((t_sample)0.5));
			t_sample selector_2371 = ((choice_98 >= 5) ? div_2349 : ((choice_98 >= 4) ? gt_2375 : ((choice_98 >= 3) ? mod_2380 : ((choice_98 >= 2) ? triangle_2376 : ((choice_98 >= 1) ? div_2372 : 0)))));
			t_sample mul_2374 = (selector_2371 * m_knob2_width_39);
			t_sample sub_4399 = (mul_2374 - ((int)0));
			t_sample scale_4396 = ((safepow((sub_4399 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_2381 = scale_4396;
			t_sample mtof_2382 = mtof(scale_2381, ((int)440));
			t_sample mul_2366 = (mtof_2382 * div_2367);
			t_sample cos_2364 = cos(mul_2366);
			t_sample mul_2359 = (cos_2364 * (-2));
			t_sample sin_2365 = sin(mul_2366);
			t_sample mul_2363 = (sin_2365 * ((t_sample)0.5));
			t_sample div_2362 = safediv(mul_2363, m_knob3_Q_40);
			t_sample rsub_2357 = (((int)1) - div_2362);
			t_sample add_2361 = (div_2362 + ((int)1));
			t_sample rdiv_2360 = safediv(((int)1), add_2361);
			t_sample mul_2358 = (rdiv_2360 * mul_2359);
			__m_slide_99 = fixdenorm((__m_slide_99 + (((mul_2358 > __m_slide_99) ? iup_100 : idown_101) * (mul_2358 - __m_slide_99))));
			t_sample slide_2354 = __m_slide_99;
			t_sample gen_2368 = slide_2354;
			t_sample mul_2356 = (rdiv_2360 * rsub_2357);
			__m_slide_102 = fixdenorm((__m_slide_102 + (((mul_2356 > __m_slide_102) ? iup_103 : idown_104) * (mul_2356 - __m_slide_102))));
			t_sample slide_2353 = __m_slide_102;
			t_sample gen_2369 = slide_2353;
			t_sample mul_2392 = (gen_2446 * gen_2369);
			t_sample mul_2389 = (m_history_7 * gen_2368);
			t_sample mul_2387 = (m_history_8 * ((int)1));
			t_sample mul_2383 = (m_history_9 * gen_2369);
			t_sample mul_2385 = (m_history_6 * gen_2368);
			t_sample sub_2391 = (((mul_2387 + mul_2389) + mul_2392) - (mul_2385 + mul_2383));
			t_sample gen_2397 = sub_2391;
			t_sample history_2384_next_2393 = fixdenorm(m_history_6);
			t_sample history_2388_next_2394 = fixdenorm(m_history_7);
			t_sample history_2390_next_2395 = fixdenorm(gen_2446);
			t_sample history_2386_next_2396 = fixdenorm(sub_2391);
			t_sample add_2330 = (phasor_1891 + div_1723);
			t_sample mod_2331 = safemod(add_2330, ((int)1));
			t_sample triangle_2327 = triangle(mod_2331, ((t_sample)0.5));
			int gt_2326 = (mod_2331 > ((t_sample)0.5));
			__m_cycle_105.phase(mod_2331);
			t_sample cycle_2328 = __m_cycle_105(__sinedata);
			t_sample cycleindex_2329 = __m_cycle_105.phase();
			t_sample add_2324 = (cycle_2328 + ((int)1));
			t_sample div_2323 = (add_2324 * ((t_sample)0.5));
			t_sample noise_2302 = noise();
			t_sample sah_2303 = __m_sah_106(noise_2302, mod_2331, ((t_sample)0.5));
			t_sample add_2301 = (sah_2303 + ((int)1));
			t_sample div_2300 = (add_2301 * ((t_sample)0.5));
			t_sample selector_2322 = ((choice_107 >= 5) ? div_2300 : ((choice_107 >= 4) ? gt_2326 : ((choice_107 >= 3) ? mod_2331 : ((choice_107 >= 2) ? triangle_2327 : ((choice_107 >= 1) ? div_2323 : 0)))));
			t_sample mul_2325 = (selector_2322 * m_knob2_width_39);
			t_sample sub_4403 = (mul_2325 - ((int)0));
			t_sample scale_4400 = ((safepow((sub_4403 * ((t_sample)1)), ((int)1)) * ((int)115)) + ((int)20));
			t_sample scale_2332 = scale_4400;
			t_sample mtof_2333 = mtof(scale_2332, ((int)440));
			t_sample mul_2317 = (mtof_2333 * div_2318);
			t_sample cos_2315 = cos(mul_2317);
			t_sample mul_2310 = (cos_2315 * (-2));
			t_sample sin_2316 = sin(mul_2317);
			t_sample mul_2314 = (sin_2316 * ((t_sample)0.5));
			t_sample div_2313 = safediv(mul_2314, m_knob3_Q_40);
			t_sample rsub_2308 = (((int)1) - div_2313);
			t_sample add_2312 = (div_2313 + ((int)1));
			t_sample rdiv_2311 = safediv(((int)1), add_2312);
			t_sample mul_2307 = (rdiv_2311 * rsub_2308);
			__m_slide_108 = fixdenorm((__m_slide_108 + (((mul_2307 > __m_slide_108) ? iup_109 : idown_110) * (mul_2307 - __m_slide_108))));
			t_sample slide_2304 = __m_slide_108;
			t_sample gen_2320 = slide_2304;
			t_sample mul_2309 = (rdiv_2311 * mul_2310);
			__m_slide_111 = fixdenorm((__m_slide_111 + (((mul_2309 > __m_slide_111) ? iup_112 : idown_113) * (mul_2309 - __m_slide_111))));
			t_sample slide_2305 = __m_slide_111;
			t_sample gen_2319 = slide_2305;
			t_sample mul_2343 = (gen_2397 * gen_2320);
			t_sample mul_2340 = (m_history_3 * gen_2319);
			t_sample mul_2338 = (m_history_5 * ((int)1));
			t_sample mul_2334 = (m_history_4 * gen_2320);
			t_sample mul_2336 = (m_history_2 * gen_2319);
			t_sample sub_2342 = (((mul_2338 + mul_2340) + mul_2343) - (mul_2336 + mul_2334));
			t_sample gen_2348 = sub_2342;
			t_sample history_2339_next_2344 = fixdenorm(m_history_3);
			t_sample history_2335_next_2345 = fixdenorm(m_history_2);
			t_sample history_2341_next_2346 = fixdenorm(gen_2397);
			t_sample history_2337_next_2347 = fixdenorm(sub_2342);
			t_sample dcblock_1719 = __m_dcblock_114(gen_2348);
			t_sample add_1889 = (mul_1941 + gen_2348);
			t_sample dcblock_1722 = __m_dcblock_115(add_1889);
			t_sample add_1720 = (dcblock_1722 + mul_1721);
			t_sample out1 = add_1720;
			t_sample out2 = add_1720;
			t_sample history_1731_next_4123 = fixdenorm(dcblock_1719);
			m_history_33 = history_1927_next_1936;
			m_history_30 = history_1929_next_1939;
			m_history_31 = history_1933_next_1938;
			m_history_32 = history_1931_next_1937;
			m_history_29 = history_2076_next_2081;
			m_history_26 = history_2074_next_2084;
			m_history_27 = history_2078_next_2083;
			m_history_28 = history_2072_next_2082;
			m_history_25 = history_2171_next_2180;
			m_history_22 = history_2173_next_2183;
			m_history_23 = history_2177_next_2182;
			m_history_24 = history_2175_next_2181;
			m_history_21 = history_2126_next_2131;
			m_history_18 = history_2124_next_2134;
			m_history_19 = history_2128_next_2133;
			m_history_20 = history_2122_next_2132;
			m_history_17 = history_2482_next_2491;
			m_history_14 = history_2484_next_2494;
			m_history_15 = history_2488_next_2493;
			m_history_16 = history_2486_next_2492;
			m_history_13 = history_2433_next_2442;
			m_history_10 = history_2435_next_2445;
			m_history_11 = history_2439_next_2444;
			m_history_12 = history_2437_next_2443;
			m_history_9 = history_2384_next_2393;
			m_history_6 = history_2386_next_2396;
			m_history_7 = history_2390_next_2395;
			m_history_8 = history_2388_next_2394;
			m_history_5 = history_2339_next_2344;
			m_history_2 = history_2337_next_2347;
			m_history_3 = history_2341_next_2346;
			m_history_4 = history_2335_next_2345;
			m_history_1 = history_1731_next_4123;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_knob1_rate(t_param _value) {
		m_knob1_rate_34 = (_value < 0 ? 0 : (_value > 7.5 ? 7.5 : _value));
	};
	inline void set_knob6_waveform(t_param _value) {
		m_knob6_waveform_35 = (_value < 1 ? 1 : (_value > 4 ? 4 : _value));
	};
	inline void set_knob7_gain(t_param _value) {
		m_knob7_gain_36 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_fb(t_param _value) {
		m_knob5_fb_37 = (_value < 0 ? 0 : (_value > 0.95 ? 0.95 : _value));
	};
	inline void set_knob4_diffusion(t_param _value) {
		m_knob4_diffusion_38 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2_width(t_param _value) {
		m_knob2_width_39 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_Q(t_param _value) {
		m_knob3_Q_40 = (_value < 1e-06 ? 1e-06 : (_value > 20 ? 20 : _value));
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
		case 0: *value = self->m_knob1_rate_34; break;
		case 1: *value = self->m_knob2_width_39; break;
		case 2: *value = self->m_knob3_Q_40; break;
		case 3: *value = self->m_knob4_diffusion_38; break;
		case 4: *value = self->m_knob5_fb_37; break;
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
	// initialize parameter 0 ("m_knob1_rate_34")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_rate_34;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 7.5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_width_39")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_width";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_width_39;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_Q_40")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_Q";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_Q_40;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1e-06;
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_diffusion_38")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_diffusion";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_diffusion_38;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob5_fb_37")
	pi = self->__commonstate.params + 4;
	pi->name = "knob5_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_fb_37;
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


} // lukephaser_field::
