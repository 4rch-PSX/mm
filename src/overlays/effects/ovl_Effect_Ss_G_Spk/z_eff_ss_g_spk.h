#ifndef _Z64_EFFECT_SS_G_SPK_H_
#define _Z64_EFFECT_SS_G_SPK_H_

#include "global.h"

typedef struct {
    /* 0x00 */ Actor* actor;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f accel;
    /* 0x28 */ Color_RGBA8 primColor;
    /* 0x2C */ Color_RGBA8 envColor;
    /* 0x30 */ s16 scale;
    /* 0x32 */ s16 scaleStep;
    /* 0x34 */ u8 updateMode;
} EffectSsGSpkInitParams; // size = 0x38

extern const EffectSsInit Effect_Ss_G_Spk_InitVars;

#endif
