#ifndef _Z64_EFFECT_SS_DUST_H_
#define _Z64_EFFECT_SS_DUST_H_

#include "global.h"

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f velocity;
    /* 0x18 */ Vec3f accel;
    /* 0x24 */ Color_RGBA8 primColor;
    /* 0x28 */ Color_RGBA8 envColor;
    /* 0x2C */ s16 scale;
    /* 0x2E */ s16 scaleStep;
    /* 0x30 */ s16 life;
    /* 0x32 */ u16 drawFlags;
    /* 0x34 */ u8 updateMode;
} EffectSsDustInitParams; // size = 0x38

extern const EffectSsInit Effect_Ss_Dust_InitVars;

#endif
