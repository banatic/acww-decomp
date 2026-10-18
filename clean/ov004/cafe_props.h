/* The props of the cafe's counter (a room object of the RMO family, rmo_object.h; vtable
 * 0x02254fc8, 0xf44 bytes): the counter itself (/roomObj/obj_cafe1) and nine animated parts
 * (obj_cafe2 to obj_cafe6, some loaded twice), which the cafe's master handles while he makes
 * coffee. Only one exists at a time; data_ov004_02258310 points to it while it runs.
 *
 * The master's coffee sequences (CafeMasterTalk_ClearUp, CafeMasterTalk_Drink and
 * CafeMasterTalk_Brew) move it through ten states (CafeProps.state) and wait on the parts'
 * animations. Each state has an entry function and an update, both called through tables of
 * member pointers (member_pointer.h); most updates start animations of the parts when the
 * master's own animation (CafeMaster_AnimNumber, numbers 0xf2 to 0xf8) reaches theirs, often
 * from his animation's frame (CafeMaster_AnimFrame):
 *
 * - 0: shows the counter and part 0; master's 0xf2 or 0xf4 play animation 0 or 1 on both;
 * - 1: master's 0xf3 or 0xf5 play animation 0 or 1 on parts 1 and 2;
 * - 2: master's 0xf3 plays 3 and 0 on parts 1 and 2, his 0xf5 plays 4 and 1;
 * - 3 and 7: as 0 and 1 together; master's 0xf6 shows or hides the counter and parts 0 to 2 by
 *   his frame and plays animation 2 on the counter and parts 0 to 2;
 * - 4: part 3 plays its first animation from the start; master's 0xf7 plays 5 and 3 on parts 1
 *   and 2;
 * - 5: master's 0xf8 plays 6 and 4 on parts 1 and 2, and at his frame 0x3b starts effect 0x6b
 *   at CafeProps.effect_point;
 * - 6: master's 0xf8 plays 7 and 5 on parts 1 and 2 backwards from his frame;
 * - 8: ends that effect; then each time part 1's animation (6, then 9, then 10) has run out,
 *   the next pair plays (9 and 7, 10 and 8, 11 and 9), the last after the camera mutes its
 *   sounds and switches to mode 4;
 * - 9: the camera goes back to its previous mode; once part 1's animation 11 has run out, 12
 *   and 10 play on parts 1 and 2.
 *
 * Each frame the counter and part 0 follow the beat of a music between 99 and 171, the
 * animations step, the state's update runs, the effect follows its point, and parts 4 and 6,
 * once shown, start an effect 0x6b each. The master's draw places and draws them
 * (CafeProps_DrawCurrent): the counter and part 0 at two of his matrices, parts 1 and 2 at his
 * first matrix or at a fixed point by state, part 3 at his second matrix during frames 15 to
 * 72 of its animation, the others at fixed points. */
#ifndef CLEAN_OV004_CAFE_PROPS_H
#define CLEAN_OV004_CAFE_PROPS_H

#include "autoload_2/vector.h"
#include "rmo_object.h"
#include "types.h"

#define CAFE_PROPS_PARTS 9
#define CAFE_PROPS_STATES 10
#define CAFE_PROPS_EFFECT_PARTS 2 /* parts 4 and 6 */

typedef struct CafeProps {
    RmoObject base;                                   /* 0x000: the counter */
    RmoAnimatedModel parts[CAFE_PROPS_PARTS];         /* 0x290 */
    RmoModel part_models[CAFE_PROPS_PARTS];           /* 0x908 */
    RmoTexture part_textures[CAFE_PROPS_PARTS];       /* 0xecc */
    u8 part_shown[CAFE_PROPS_PARTS];                  /* 0xef0: drawn when nonzero */
    u8 body_shown;                                    /* 0xef9: the counter is drawn */
    u8 unk_efa[2];                                    /* 0xefa */
    s32 state;                                        /* 0xefc: 0 to 9 */
    u8 unk_f00[0x10];                                 /* 0xf00 */
    Vec3 effect_point;                                /* 0xf10: of the effect of state 5 */
    Vec3 part_effect_points[CAFE_PROPS_EFFECT_PARTS]; /* 0xf1c: of parts 4 and 6's effects */
    s16 part_effect_angles[CAFE_PROPS_EFFECT_PARTS];  /* 0xf34 */
    s32 effect;                                       /* 0xf38: its handle, -1 for none */
    s32 part_effects[CAFE_PROPS_EFFECT_PARTS];        /* 0xf3c: their handles, -1 for none */
} CafeProps;

void CafeProps_ShowPart8(void);
void CafeProps_ShowParts6And7(void);
void CafeProps_PlayAnim(CafeProps *unused, int anim, RmoAnimatedModel *model, RmoModel *source, u8 flags, fx32 speed,
                        u16 start, u16 frames);
int CafeProps_Part1Anim12Done(void);
int CafeProps_Part1Anim11AtFrame9(void);
int CafeProps_State(void);
int CafeProps_EnterState9(void);
int CafeProps_EnterState8(void);
int CafeProps_EnterState7(void);
int CafeProps_EnterState6(void);
int CafeProps_EnterState5(void);
int CafeProps_EnterState4(void);
int CafeProps_EnterState3(void);
int CafeProps_EnterState2(void);
int CafeProps_EnterState1(void);
int CafeProps_EnterState0(void);
void CafeProps_StartPartAnim(CafeProps *self, int part);
void CafeProps_ReleasePart(CafeProps *self, int part);
void CafeProps_LoadPart(CafeProps *self, int part, const char *archive, const char *texture);
void CafeProps_DrawCurrent(void);
void CafeProps_UpdateState9(CafeProps *self);
int CafeProps_OnEnterState9(CafeProps *self);
void CafeProps_UpdateState8(CafeProps *self);
int CafeProps_OnEnterState8(CafeProps *self);
void CafeProps_UpdateState6(CafeProps *self);
int CafeProps_OnEnterState6(CafeProps *self);
void CafeProps_UpdateState5(CafeProps *self);
int CafeProps_OnEnterState5(CafeProps *self);
void CafeProps_UpdateState4(CafeProps *self);
int CafeProps_OnEnterState4(CafeProps *self);
void CafeProps_UpdateState3(CafeProps *self);
int CafeProps_OnEnterState3(CafeProps *self);
void CafeProps_UpdateState2(CafeProps *self);
int CafeProps_OnEnterState2(CafeProps *self);
void CafeProps_UpdateState1(CafeProps *self);
int CafeProps_OnEnterState1(CafeProps *self);
void CafeProps_UpdateState0(CafeProps *self);
int CafeProps_OnEnterState0(CafeProps *self);
void CafeProps_UpdateState(CafeProps *self);
int CafeProps_SetState(CafeProps *self, int state);
int CafeProps_Release(CafeProps *self);
void CafeProps_Draw(CafeProps *self);
int CafeProps_Vfunc24(void);
int CafeProps_Update(CafeProps *self);
int CafeProps_Start(CafeProps *self);
CafeProps *CafeProps_Delete(CafeProps *self);
CafeProps *CafeProps_Destruct(CafeProps *self);
CafeProps *CafeProps_Construct(CafeProps *self);
void CafeProps_Create(void);

#endif
