/* A room object of the RMO family (rmo_object.h; vtable 0x02255674, 0x6dc bytes) built from
 * /roomObj/obj_tarot1 (its body) with three more animated models (its parts) built from
 * obj_tarot2, obj_tarot3 and obj_tarot4, and a texture animation of obj_tarot3's on part 1.
 * Only one exists at a time: data_ov004_02258870 points to it from its start to its release.
 *
 * It draws nothing itself (vtable slot 0x24): overlay 45's code draws it (TarotObject_DrawCurrent)
 * at a matrix of its own object (FortuneTeller_CurrentMatrix), and asks for its states 1 to 3 (on its
 * values 0x1e, 0x1f and 0x20, FortuneTellerTalk_SetTalkStyle). Its updates follow the whole frame
 * of that object's animation (FortuneTeller_CurrentFrame) to show and hide the body and the parts:
 *
 * - 0 (idle): all hidden;
 * - 1: the body and part 1 shown; part 2's joint animation 0 and part 1's texture animation 0
 *   played once; at frame 11 the body is hidden and part 2 shown;
 * - 2: parts 1 and 2 shown at the last frames of their animations, standing still; at frame 9
 *   part 0 is shown too;
 * - 3: the parts shown; part 2's joint animation 1 and part 1's texture animation 1 played once;
 *   part 0 hidden at frame 7, part 2 at frame 18, the body shown at frame 19 and hidden at frame
 *   37; idle once part 2's animation has run out.
 *
 * Each state has an entry and an update called through tables of member pointers
 * (member_pointer.h). */
#ifndef CLEAN_OV004_TAROT_OBJECT_H
#define CLEAN_OV004_TAROT_OBJECT_H

#include "main/model_anim.h"
#include "rmo_object.h"
#include "types.h"

#define TAROT_OBJECT_PARTS 3

typedef struct TarotObject {
    RmoObject base;                               /* 0x000: obj_tarot1 */
    RmoAnimatedModel parts[TAROT_OBJECT_PARTS];   /* 0x290: obj_tarot2 to obj_tarot4 */
    RmoModel part_models[TAROT_OBJECT_PARTS];     /* 0x4b8 */
    RmoTexture part_textures[TAROT_OBJECT_PARTS]; /* 0x6a4 */
    u8 part_shown[TAROT_OBJECT_PARTS];            /* 0x6b0: drawn when nonzero */
    u8 unk_6b3;                                   /* 0x6b3 */
    ModelAnim part1_anim;                         /* 0x6b4: a texture animation of obj_tarot3's */
    u8 body_shown;                                /* 0x6d4: drawn when nonzero */
    u8 unk_6d5[3];                                /* 0x6d5 */
    s32 state;                                    /* 0x6d8: TarotObjectState */
} TarotObject;

enum TarotObjectState {
    TAROT_OBJECT_IDLE = 0,
    TAROT_OBJECT_STATE_1 = 1,
    TAROT_OBJECT_STATE_2 = 2,
    TAROT_OBJECT_STATE_3 = 3,
    TAROT_OBJECT_STATE_COUNT = 4
};

void TarotObject_ReleasePart(TarotObject *self, int part);
void TarotObject_LoadPart(TarotObject *self, int part, const char *archive, const char *texture);
void TarotObject_DrawCurrent(void);
int TarotObject_EnterState3Current(void);
int TarotObject_EnterState2Current(void);
int TarotObject_EnterState1Current(void);
void TarotObject_UpdateState3(TarotObject *self);
int TarotObject_EnterState3(TarotObject *self);
int TarotObject_UpdateState2(TarotObject *self);
int TarotObject_EnterState2(TarotObject *self);
int TarotObject_UpdateState1(TarotObject *self);
int TarotObject_EnterState1(TarotObject *self);
void TarotObject_UpdateIdle(TarotObject *self);
int TarotObject_EnterIdle(TarotObject *self);
void TarotObject_UpdateState(TarotObject *self);
int TarotObject_SetState(TarotObject *self, int state);
int TarotObject_Release(TarotObject *self);
void TarotObject_Draw(TarotObject *self);
int TarotObject_Vfunc24(void);
int TarotObject_Update(TarotObject *self);
int TarotObject_Start(TarotObject *self);
TarotObject *TarotObject_Delete(TarotObject *self);
TarotObject *TarotObject_Destruct(TarotObject *self);
TarotObject *TarotObject_Construct(TarotObject *self);
void TarotObject_Create(void);

#endif
