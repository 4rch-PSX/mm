/*
 * File: z_en_prz.c
 * Overlay: ovl_En_Prz
 * Description: Skullfish - Defeated
 */

#include "z_en_prz.h"
#include "objects/object_pr/object_pr.h"
#include "overlays/actors/ovl_En_Pr/z_en_pr.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10)

#define THIS ((EnPrz*)thisx)

void EnPrz_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPrz_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPrz_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPrz_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A76388(EnPrz* this);
void func_80A763E8(EnPrz* this, GlobalContext* globalCtx);
void func_80A76604(EnPrz* this, GlobalContext* globalCtx);
void func_80A76634(EnPrz* this, GlobalContext* globalCtx);
void func_80A76748(EnPrz* this);
void func_80A767A8(EnPrz* this, GlobalContext* globalCtx);
void func_80A76B14(EnPrz* this, GlobalContext* globalCtx);

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0xF),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(2, 0xF),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

f32 D_80A771E0[] = { 40.0f, 40.0f, 40.0f, 30.0f, 30.0f };

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK4,
        { 0x20000000, 0x00, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 10, 10, 0, { 0, 0, 0 } },
};

const ActorInit En_Prz_InitVars = {
    ACTOR_EN_PRZ,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_PR,
    sizeof(EnPrz),
    (ActorFunc)EnPrz_Init,
    (ActorFunc)EnPrz_Destroy,
    (ActorFunc)EnPrz_Update,
    (ActorFunc)EnPrz_Draw,
};

AnimationHeader* D_80A77240[] = { &object_pr_Anim_004340, &object_pr_Anim_004274 };

u8 D_80A77248[] = { 0, 0 };

Vec3f D_80A7724C = { 0.0f, 0.0f, 0.0f };

void EnPrz_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPrz* this = THIS;

    this->unk_20C = 0.01f;
    this->unk_1E4 = this->actor.world.rot.y;

    Actor_SetScale(&this->actor, 0.01f);

    this->actor.targetMode = 3;
    this->unk_1E8 = 255;
    this->actor.hintId = 0x5B;
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.colChkInfo.health = 1;

    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_pr_Skel_004188, &object_pr_Anim_004340, this->jointTable,
                       this->morphTable, 5);

    this->unk_1E6 = ENPRZ_GET(&this->actor);
    this->actor.shape.yOffset = 500.0f;
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->actor.flags &= ~ACTOR_FLAG_1;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    Math_Vec3f_Copy(&this->unk_1D8, &this->actor.world.pos);

    this->unk_220 = &this->actor;
    this->unk_1EC = 255;
    this->unk_202 = randPlusMinusPoint5Scaled((this->unk_1E6 * 100.0f) + 1000.0f);

    func_80A76388(this);
}

void EnPrz_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80A75F18(EnPrz* this, s32 arg1) {
    this->unk_204 = arg1;
    Animation_Change(&this->skelAnime, D_80A77240[arg1], 1.0f, 0.0f, Animation_GetLastFrame(D_80A77240[arg1]),
                     D_80A77248[arg1], -2.0f);
}

s32 func_80A75FA4(EnPrz* this, GlobalContext* globalCtx) {
    WaterBox* sp2C;
    f32 temp_f0;

    if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                             &this->unk_210, &sp2C)) {
        temp_f0 = BREG(10) + (this->unk_210 - 10.0f);
        if (temp_f0 < this->actor.world.pos.y) {
            this->unk_1D8.y = temp_f0;
            return 1;
        }
    } else {
        temp_f0 = this->actor.floorHeight + 35.0f;
        if (this->actor.world.pos.y < temp_f0) {
            this->unk_1D8.y = temp_f0;
            return 2;
        }
    }

    return 0;
}

void func_80A76070(EnPrz* this, s16 arg1, GlobalContext* globalCtx) {
    s16 temp_s0 = arg1 - this->actor.world.rot.y;

    temp_s0 *= 0.01f;

    if (temp_s0 > 100) {
        temp_s0 = 100;
    }

    if (temp_s0 < -100) {
        temp_s0 = -100;
    }

    if (fabsf(this->actor.world.rot.y - (f32)arg1) < (randPlusMinusPoint5Scaled(20.0f) + 100.0f)) {
        Math_ApproachZeroF(&this->unk_218, 0.5f, 20.0f);
    } else {
        Math_ApproachF(&this->unk_218, temp_s0, 0.5f, 5.0f);
    }

    temp_s0 = fabsf(this->unk_218) * 0.1f;
    if (temp_s0 < 2) {
        temp_s0 = 2;
    }

    Math_SmoothStepToS(&this->actor.world.rot.y, arg1, temp_s0, this->unk_202 + 0x1388, 0);
    func_80A75FA4(this, globalCtx);
    Math_ApproachF(&this->actor.world.pos.y, this->unk_1D8.y, 0.5f, 1.0f);
    temp_s0 = Math_Vec3f_Pitch(&this->actor.world.pos, &this->unk_1D8) * 0.5f;

    if (fabsf(this->actor.world.pos.y - this->unk_208) > 4.0f) {
        Math_SmoothStepToS(&this->actor.world.rot.x, temp_s0, 1, BREG(48) + 0x1F4, 0);
    } else {
        Math_SmoothStepToS(&this->actor.world.rot.x, 0, 1, BREG(52) + 0xBB8, 0);
    }
}

s32 func_80A762C0(EnPrz* this, GlobalContext* globalCtx) {
    CollisionPoly* sp54;
    Vec3f sp48;
    s32 sp44;
    Vec3f sp38;

    Math_Vec3f_Copy(&sp38, &this->actor.world.pos);

    sp38.x += Math_SinS(this->actor.world.rot.y) * 40.0f;
    sp38.z += Math_CosS(this->actor.world.rot.y) * 40.0f;

    if (BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &sp38, &sp48, &sp54, true, false, false,
                                true, &sp44)) {
        return true;
    }
    return false;
}

void func_80A76388(EnPrz* this) {
    this->actor.speedXZ = randPlusMinusPoint5Scaled(1.0f) + 4.0f;
    func_80A75F18(this, 0);
    this->unk_1EA = 1;
    this->actionFunc = func_80A763E8;
}

void func_80A763E8(EnPrz* this, GlobalContext* globalCtx) {
    Actor* sp3C = this->actor.parent;
    Player* player = GET_PLAYER(globalCtx);
    s16 yaw;
    s32 pad;

    if (&this->actor == this->unk_220) {
        return;
    }

    if ((player->stateFlags1 & 0x8000000) && (this->unk_1F2 == 0)) {
        func_80A76748(this);
        return;
    }

    if (func_80A762C0(this, globalCtx)) {
        func_80A76604(this, globalCtx);
        return;
    }

    if ((this->unk_220 != NULL) && (this->unk_220->update == NULL)) {
        this->unk_220 = this->actor.parent;
    }

    if ((this->unk_1EE == 0) && (this->unk_1F2 == 0)) {
        s16 rot;

        this->unk_214 = randPlusMinusPoint5Scaled(40.0f);

        rot = BINANG_ROT180(this->unk_220->world.rot.y);
        this->unk_1D8.x += Math_SinS(rot) * this->unk_214;
        this->unk_1D8.y = randPlusMinusPoint5Scaled(40.0f) + (this->unk_220->world.pos.y + 40.0f);
        rot = BINANG_ROT180(this->unk_220->world.rot.y);
        this->unk_1D8.z += Math_CosS(rot) * this->unk_214;

        this->unk_1EE = Rand_S16Offset(20, 30);
    } else if (sqrtf(SQ(this->actor.world.pos.x - sp3C->world.pos.x) +
                     SQ(this->actor.world.pos.z - sp3C->world.pos.z)) > 100.0f) {
        Math_Vec3f_Copy(&this->unk_1D8, &sp3C->world.pos);
    }

    if (1) {}

    if ((Rand_ZeroOne() < 0.1f) && (this->unk_1C8 == 0)) {
        this->unk_1C8 = 1;
    }

    yaw = Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_1D8);
    func_80A76070(this, yaw, globalCtx);
}

void func_80A76604(EnPrz* this, GlobalContext* globalCtx) {
    this->unk_1EE = 0;
    this->unk_1E4 = BINANG_ADD(this->actor.world.rot.y, 0x4000);
    this->unk_1EA = 2;
    this->actionFunc = func_80A76634;
}

void func_80A76634(EnPrz* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80A76070(this, this->unk_1E4, globalCtx);

    if (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, this->unk_1E4)) < 0x100) {
        if (func_80A762C0(this, globalCtx) != 0) {
            this->unk_1E4 += 0x1500;
            this->unk_1E4 += (s16)Rand_ZeroFloat(5000.0f);
        } else if ((player->stateFlags1 & 0x8000000) && (player->actor.floorHeight < 30.0f)) {
            this->actionFunc = func_80A763E8;
        } else {
            this->unk_1EE = 10;
            this->unk_1EA = 1;
            this->actionFunc = func_80A763E8;
        }
    }
}

void func_80A76748(EnPrz* this) {
    this->actor.speedXZ = randPlusMinusPoint5Scaled(1.0f) + 3.0f;
    this->unk_1EE = 0;
    this->unk_1EA = 3;
    this->skelAnime.playSpeed = 2.0f;
    this->actionFunc = func_80A767A8;
}

void func_80A767A8(EnPrz* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    EnPr* pr = (EnPr*)this->actor.parent;
    f32 sqrt;
    s32 pad[2];
    u8 playerForm;

    if (func_80A762C0(this, globalCtx)) {
        func_80A75F18(this, 0);
        this->actor.speedXZ = randPlusMinusPoint5Scaled(1.0f) + 4.0f;
        func_80A76604(this, globalCtx);
        return;
    }

    sqrt = sqrtf(SQ(player->actor.world.pos.x - this->actor.parent->home.pos.x) +
                 SQ(player->actor.world.pos.z - this->actor.parent->home.pos.z));

    if (!(player->stateFlags1 & 0x8000000) || (pr->unk_2C8 < sqrt)) {
        this->unk_1F2 = 100;
        this->skelAnime.playSpeed = 1.0f;
        func_80A76388(this);
        return;
    }

    if ((this->actor.xzDistToPlayer < 200.0f) && (fabsf(player->actor.world.pos.y - this->actor.world.pos.y) < 80.0f)) {
        if (this->unk_204 != 1) {
            func_80A75F18(this, 1);
        }
        this->skelAnime.playSpeed = 1.0f;
    } else {
        if (this->unk_204 != 0) {
            func_80A75F18(this, 0);
        }
        this->skelAnime.playSpeed = 2.0f;
    }

    if (this->unk_1EE == 0) {
        this->unk_1EE = Rand_S16Offset(2, 3);
        Math_Vec3f_Copy(&this->unk_1D8, &player->actor.world.pos);
    }

    if ((Rand_ZeroOne() < 0.1f) && (this->unk_1C8 == 0)) {
        this->unk_1C8 = 1;
    }

    playerForm = gSaveContext.playerForm;
    this->unk_1D8.y =
        (player->actor.world.pos.y + D_80A771E0[playerForm]) + randPlusMinusPoint5Scaled((2.0f * this->unk_1E6) + 1.0f);
    func_80A76070(this, Math_Vec3f_Yaw(&this->actor.world.pos, &this->unk_1D8), globalCtx);
}

void func_80A76A1C(EnPrz* this) {
    this->unk_1E8 = 0;
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->actor.flags &= ~ACTOR_FLAG_1;

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLEWALK_DEAD);

    this->unk_1EE = Rand_S16Offset(100, 30);
    this->unk_1FC = 0x4000;

    if (Rand_ZeroOne() < 0.5f) {
        this->unk_1FC = -0x4000;
    }

    this->unk_1FE = this->actor.world.rot.y;
    this->actor.speedXZ = Rand_ZeroFloat(0.5f);
    this->actor.world.rot.y = randPlusMinusPoint5Scaled(0x8000);

    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 30);
    this->unk_1EE = 50;
    func_80A75F18(this, 0);
    this->unk_1EA = 7;
    this->actionFunc = func_80A76B14;
}

void func_80A76B14(EnPrz* this, GlobalContext* globalCtx) {
    WaterBox* sp7C;
    s32 i;
    Vec3f sp6C;
    s32 phi_s0 = false;

    Math_SmoothStepToS(&this->actor.shape.rot.x, 0, 5, 0x2710, 0x3E8);
    Math_SmoothStepToS(&this->actor.shape.rot.z, this->unk_1FC, 5, 0x2710, 0x3E8);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_1FE, 5, 0x2710, 0x3E8);

    if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                             &this->unk_210, &sp7C)) {
        if ((this->unk_210 - 15.0f) <= this->actor.world.pos.y) {
            phi_s0 = true;
        } else {
            Math_ApproachF(&this->actor.world.pos.y, this->unk_210 - 14.0f, 0.3f, 1.0f);
        }
    }

    if ((this->unk_1EE == 0) || phi_s0) {
        Math_SmoothStepToS(&this->unk_1EC, 0, 1, 15, 50);

        if (this->unk_1EC < 2) {
            for (i = 0; i < 10; i++) {
                Math_Vec3f_Copy(&sp6C, &this->actor.world.pos);

                sp6C.x += randPlusMinusPoint5Scaled(20.0f);
                sp6C.y += randPlusMinusPoint5Scaled(5.0f);
                sp6C.z += randPlusMinusPoint5Scaled(20.0f);

                EffectSsBubble_Spawn(globalCtx, &sp6C, 0.0f, 5.0f, 5.0f, Rand_ZeroFloat(0.03f) + 0.07f);
            }
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void EnPrz_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnPrz* this = THIS;
    s32 sp44 = false;
    Vec3f sp38;

    if (this->unk_1EA != 7) {
        SkelAnime_Update(&this->skelAnime);
    }

    this->actionFunc(this, globalCtx);

    if (this->unk_1EE != 0) {
        this->unk_1EE--;
    }

    if (this->unk_1F2 != 0) {
        this->unk_1F2--;
    }

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 10.0f, 10.0f, 0x1D);

    if (this->unk_1EA != 7) {
        Math_Vec3s_Copy(&this->actor.shape.rot, &this->actor.world.rot);
    }

    if (this->unk_1EA != 7) {
        if (this->collider.base.acFlags & AC_HIT) {
            Actor_ApplyDamage(&this->actor);
            if (this->actor.colChkInfo.health <= 0) {
                sp44 = true;
            }
        }

        if (sp44 || (this->actor.parent == NULL) || (this->actor.parent->colChkInfo.health <= 0)) {
            this->collider.base.acFlags &= ~AC_HIT;
            if (this->unk_1EA != 7) {
                func_80A76A1C(this);
                return;
            }
        }

        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

        if (this->unk_1C8 != 0) {
            Math_Vec3f_Copy(&sp38, &this->unk_1CC);
            this->unk_1C8 = 0;

            sp38.x += randPlusMinusPoint5Scaled(20.0f);
            sp38.y += randPlusMinusPoint5Scaled(5.0f);
            sp38.z += randPlusMinusPoint5Scaled(20.0f);

            EffectSsBubble_Spawn(globalCtx, &sp38, 0.0f, 5.0f, 5.0f, Rand_ZeroFloat(0.03f) + 0.07f);
        }
    }
}

s32 func_80A76F70(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnPrz* this = THIS;

    if (limbIndex == 2) {
        rot->y += (s16)this->unk_218 * -100;
    }
    return false;
}

void func_80A76FCC(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    Vec3f sp1C = D_80A7724C;
    EnPrz* this = THIS;

    if (limbIndex == 2) {
        Matrix_InsertTranslation(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_MultiplyVector3fByState(&sp1C, &this->unk_1CC);
    }
}

void EnPrz_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnPrz* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    if (this->unk_1EC == 255) {
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->unk_1E8, this->unk_1E8, this->unk_1E8, this->unk_1EC);
        gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, this->unk_1EC);

        Scene_SetRenderModeXlu(globalCtx, 0, 1);
        SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                              this->skelAnime.dListCount, func_80A76F70, func_80A76FCC, &this->actor);
    } else {
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->unk_1EC);

        Scene_SetRenderModeXlu(globalCtx, 1, 2);
        POLY_XLU_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, NULL, NULL, &this->actor, POLY_XLU_DISP);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
