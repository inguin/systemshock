#include "precompiled.h"
/*

Copyright (C) 2015-2018 Night Dive Studios, LLC.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
*/
/*	This file created by RESTOOL */

#ifndef __CITBARK_H
#define __CITBARK_H

#define RES_alog_bark0 0xc1c		// (3100)
#define RES_alog_bark1 0xc1d		// (3101)
#define RES_alog_bark2 0xc1e		// (3102)
#define RES_alog_bark3 0xc1f		// (3103)
#define RES_alog_bark4 0xc20		// (3104)
#define RES_alog_bark5 0xc21		// (3105)
#define RES_alog_bark6 0xc22		// (3106)
#define RES_alog_bark7 0xc23		// (3107)
#define RES_alog_bark8 0xc24		// (3108)
#define RES_alog_bark9 0xc25		// (3109)
#define RES_alog_bark10 0xc26		// (3110)
#define RES_alog_bark11 0xc27		// (3111)
#define RES_alog_bark12 0xc28		// (3112)
#define RES_alog_bark13 0xc29		// (3113)
#define RES_alog_bark14 0xc2a		// (3114)
#define RES_alog_bark15 0xc2b		// (3115)
#define RES_alog_bark16 0xc2c		// (3116)
#define RES_alog_bark17 0xc2d		// (3117)
#define RES_alog_bark18 0xc2e		// (3118)
#define RES_alog_bark19 0xc2f		// (3119)
#define RES_alog_bark20 0xc30		// (3120)
#define RES_alog_bark21 0xc31		// (3121)
#define RES_alog_bark22 0xc32		// (3122)
#define RES_alog_bark23 0xc33		// (3123)
#define RES_alog_bark24 0xc34		// (3124)
#define RES_alog_bark25 0xc35		// (3125)
#define RES_alog_bark26 0xc36		// (3126)
#define RES_alog_bark27 0xc37		// (3127)
#define RES_alog_bark28 0xc38		// (3128)
#define RES_alog_bark29 0xc39		// (3129)
#define RES_alog_bark30 0xc3a		// (3130)
#define RES_alog_bark31 0xc3b		// (3131)
#define RES_alog_bark32 0xc3c		// (3132)
#define RES_alog_bark33 0xc3d		// (3133)
#define RES_alog_bark34 0xc3e		// (3134)
#define RES_alog_bark35 0xc3f		// (3135)
#define RES_alog_bark36 0xc40		// (3136)
#define RES_alog_bark37 0xc41		// (3137)
#define RES_alog_bark38 0xc42		// (3138)
#define RES_alog_bark39 0xc43		// (3139)
#define RES_alog_bark40 0xc44		// (3140)
#define RES_alog_bark41 0xc45		// (3141)
#define RES_alog_bark42 0xc46		// (3142)
#define RES_alog_bark43 0xc47		// (3143)
#define RES_alog_bark44 0xc48		// (3144)
#define RES_alog_bark45 0xc49		// (3145)
#define RES_alog_bark46 0xc4a		// (3146)
#define RES_alog_bark47 0xc4b		// (3147)
#define RES_alog_bark48 0xc4c		// (3148)
#define RES_alog_bark49 0xc4d		// (3149)
#define RES_alog_bark50 0xc4e		// (3150)
#define RES_alog_bark51 0xc4f		// (3151)
#define RES_alog_bark52 0xc50		// (3152)
#define RES_alog_bark53 0xc51		// (3153)
#define RES_alog_bark54 0xc52		// (3154)
#define RES_alog_bark55 0xc53		// (3155)
#define RES_alog_bark56 0xc54		// (3156)
#define RES_alog_bark57 0xc55		// (3157)
#define RES_alog_bark58 0xc56		// (3158)
#define RES_alog_bark59 0xc57		// (3159)
#define RES_alog_bark60 0xc58		// (3160)
#define RES_alog_bark61 0xc59		// (3161)
#define RES_alog_bark62 0xc5a		// (3162)
#define RES_alog_bark63 0xc5b		// (3163)
#define RES_alog_bark64 0xc5c		// (3164)
#define RES_alog_bark65 0xc5d		// (3165)
#define RES_alog_bark66 0xc5e		// (3166)
#define RES_alog_bark67 0xc5f		// (3167)
#define RES_alog_bark68 0xc60		// (3168)
#define RES_alog_bark69 0xc61		// (3169)
#define RES_alog_bark70 0xc62		// (3170)
#define RES_alog_bark71 0xc63		// (3171)
#define RES_alog_bark72 0xc64		// (3172)
#define RES_alog_bark73 0xc65		// (3173)
#define RES_alog_bark74 0xc66		// (3174)
#define RES_alog_bark75 0xc67		// (3175)
#define RES_alog_bark76 0xc68		// (3176)
#define RES_alog_bark77 0xc69		// (3177)
#define RES_alog_bark78 0xc6a		// (3178)
#define RES_alog_bark79 0xc6b		// (3179)
#define RES_alog_bark80 0xc6c		// (3180)
#define RES_alog_bark81 0xc6d		// (3181)
#define RES_alog_bark82 0xc6e		// (3182)
#define RES_alog_bark83 0xc6f		// (3183)
#define RES_alog_bark84 0xc70		// (3184)
#define RES_alog_bark85 0xc71		// (3185)
#define RES_alog_bark86 0xc72		// (3186)
#define RES_alog_bark87 0xc73		// (3187)
#define RES_alog_bark88 0xc74		// (3188)
#define RES_alog_bark89 0xc75		// (3189)
#define RES_alog_bark90 0xc76		// (3190)
#define RES_alog_bark91 0xc77		// (3191)
#define RES_alog_bark92 0xc78		// (3192)
#define RES_alog_bark93 0xc79		// (3193)
#define RES_alog_bark94 0xc7a		// (3194)
#define RES_alog_bark95 0xc7b		// (3195)
#define RES_alog_bark96 0xc7c		// (3196)
#define RES_alog_bark97 0xc7d		// (3197)
#define RES_alog_bark98 0xc7e		// (3198)
#define RES_alog_bark99 0xc7f		// (3199)
#define RES_alog_bark100 0xc80		// (3200)
#define RES_alog_bark101 0xc81		// (3201)
#define RES_alog_bark102 0xc82		// (3202)
#define RES_alog_bark103 0xc83		// (3203)
#define RES_alog_bark104 0xc84		// (3204)
#define RES_alog_bark105 0xc85		// (3205)
#define RES_alog_bark106 0xc86		// (3206)

#endif
