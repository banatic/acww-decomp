/* The room object of /roomObj/obj_tarot1 to obj_tarot4 (tarot_object.h). */
#include "tarot_object.h"

#include <stdint.h>

#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/frame_ctrl.h"
#include "main/model_object.h"
#include "member_pointer.h"
#include "ov004/rmo_model.h"
#include "ov004/rmo_object_slots.h"
#include "rmo_object_base.h"

static_assert(sizeof(RmoAnimatedModel) == 0xb8, "RmoAnimatedModel size");
static_assert(sizeof(RmoModel) == 0xa4, "RmoModel size");
static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(offsetof(TarotObject, parts) == 0x290, "parts");
static_assert(offsetof(TarotObject, part_models) == 0x4b8, "part models");
static_assert(offsetof(TarotObject, part_textures) == 0x6a4, "part textures");
static_assert(offsetof(TarotObject, part_shown) == 0x6b0, "part shown");
static_assert(offsetof(TarotObject, part1_anim) == 0x6b4, "part 1 animation");
static_assert(offsetof(TarotObject, body_shown) == 0x6d4, "body shown");
static_assert(offsetof(TarotObject, state) == 0x6d8, "state");
static_assert(sizeof(TarotObject) == 0x6dc, "the size TarotObject_Create allocates");
static_assert(offsetof(TarotObject, parts[1].object.model) == 0x3a4, "part 1 model resource");
static_assert(offsetof(TarotObject, parts[2].frames) == 0x49c, "part 2 frames");

#define TAROT_OBJECT_ONE 0x1000           /* normal speed, 20.12 fixed point */
#define TAROT_OBJECT_ONCE FRAME_CTRL_ONCE /* the animations stop at their end */
#define TAROT_OBJECT_FRAME_SHIFT 12

/* The frames of overlay 45's object's animation at which the updates show and hide. */
#define TAROT_OBJECT_STATE1_SWAP_FRAME 0xb
#define TAROT_OBJECT_STATE2_SHOW_FRAME 0x9
#define TAROT_OBJECT_STATE3_HIDE_PART0_FRAME 0x7
#define TAROT_OBJECT_STATE3_HIDE_PART2_FRAME 0x12
#define TAROT_OBJECT_STATE3_SHOW_BODY_FRAME 0x13
#define TAROT_OBJECT_STATE3_HIDE_BODY_FRAME 0x25

/* The one that exists, NULL for none. */
extern TarotObject *data_ov004_02258870;

/* The class's vtable. */
extern const u8 data_ov004_02255674[];

/* The archives: "/roomObj/obj_tarot1.arc" and ".nsbtx" to "/roomObj/obj_tarot4.arc" and
 * ".nsbtx". */
extern const char data_ov004_022556dc[], data_ov004_022556f4[];
extern const char data_ov004_02255710[], data_ov004_02255728[];
extern const char data_ov004_02255744[], data_ov004_0225575c[];
extern const char data_ov004_02255778[], data_ov004_02255790[];

/* The scratch matrix the game builds model matrices in. */
extern Mtx43 data_021fbe48;
extern Heap *data_021c9b24;

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02258878;
extern MemberPointer data_ov004_0225887c[TAROT_OBJECT_STATE_COUNT];
extern const MemberPointer data_ov004_02255634, data_ov004_0225561c, data_ov004_02255624, data_ov004_0225562c;
extern u32 data_ov004_02258874;
extern MemberPointer data_ov004_0225889c[TAROT_OBJECT_STATE_COUNT];
extern const MemberPointer data_ov004_02255614, data_ov004_0225564c, data_ov004_02255644, data_ov004_0225563c;

/* The RMO family's base class and holders (rmo_object.h). */

/* The constructors and destructors the array helpers are handed: the game's own. */
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void func_02055210(void *model);         /* the animated model's constructor */
extern void func_020551e0(void *model);         /* and destructor */
extern void func_ov004_0222c548(void *model);   /* RmoModel's constructor */
extern void func_ov004_0222c538(void *model);   /* and destructor */
extern void func_ov004_0222c398(void *texture); /* RmoTexture's constructor */
extern void func_ov004_0222c394(void *texture); /* and destructor */

/* Overlay 45's object: the whole frame of its animation (its word at 0x190, cut to 16 bits) and
 * the matrix the body and part 0 are drawn at (at its 0x65c). */
extern unsigned int func_ov045_02260618(void);
extern const Mtx43 *func_ov045_02260630(void);

extern int NNS_G3dBindMdlTex(u8 *model, void *texture);
extern int NNS_G3dBindMdlPltt(u8 *model, void *texture);

static AnimatedModel *TarotObject_animated(RmoAnimatedModel *model)
{
    return (AnimatedModel *) (void *) model;
}

static Mtx43 *TarotObject_matrix(RmoAnimatedModel *model)
{
    return (Mtx43 *) (void *) model->object.unk_64;
}

/* A frame position cut to its whole frames, as the game keeps them: 16 bits. */
static fx32 TarotObject_whole(fx32 value)
{
    return (fx32) ((u32) (u16) ((u32) value >> TAROT_OBJECT_FRAME_SHIFT) << TAROT_OBJECT_FRAME_SHIFT);
}

/* func_ov004_02230404: the part's archive and textures released. */
void TarotObject_ReleasePart(TarotObject *self, int part)
{
    RmoModel_Release(&self->part_models[part]);
    RmoTexture_Release(&self->part_textures[part]);
}
CLEAN_AS(func_ov004_02230404, TarotObject_ReleasePart)

/* func_ov004_02230438: the part's archive and textures loaded, its model set up and the
 * textures and palettes bound to the model. */
void TarotObject_LoadPart(TarotObject *self, int part, const char *archive, const char *texture)
{
    RmoModel *source = &self->part_models[part];
    RmoTexture *textures = &self->part_textures[part];

    RmoModel_Load(source, archive);
    RmoTexture_Load(textures, texture);
    ModelObject_SetModel(&self->parts[part].object, RmoModel_Model(source), NULL);
    u8 *model = RmoModel_Model(source);
    NNS_G3dBindMdlTex(model, RmoTexture_Texture(textures));
    model = RmoModel_Model(source);
    NNS_G3dBindMdlPltt(model, RmoTexture_Texture(textures));
}
CLEAN_AS(func_ov004_02230438, TarotObject_LoadPart)

/* func_ov004_022304bc: the one that exists drawn (overlay 45's draw calls it). */
void TarotObject_DrawCurrent(void)
{
    if (data_ov004_02258870 != NULL) {
        TarotObject_Draw(data_ov004_02258870);
    }
}
CLEAN_AS(func_ov004_022304bc, TarotObject_DrawCurrent)

/* func_ov004_022304d8: the one that exists enters state 3; whether it did, 0 when none
 * exists. */
int TarotObject_EnterState3Current(void)
{
    if (data_ov004_02258870 != NULL) {
        return TarotObject_SetState(data_ov004_02258870, TAROT_OBJECT_STATE_3);
    }
    return 0;
}
CLEAN_AS(func_ov004_022304d8, TarotObject_EnterState3Current)

/* func_ov004_022304f8: the one that exists enters state 2; whether it did, 0 when none
 * exists. */
int TarotObject_EnterState2Current(void)
{
    if (data_ov004_02258870 != NULL) {
        return TarotObject_SetState(data_ov004_02258870, TAROT_OBJECT_STATE_2);
    }
    return 0;
}
CLEAN_AS(func_ov004_022304f8, TarotObject_EnterState2Current)

/* func_ov004_02230518: the one that exists enters state 1; whether it did, 0 when none
 * exists. */
int TarotObject_EnterState1Current(void)
{
    if (data_ov004_02258870 != NULL) {
        return TarotObject_SetState(data_ov004_02258870, TAROT_OBJECT_STATE_1);
    }
    return 0;
}
CLEAN_AS(func_ov004_02230518, TarotObject_EnterState1Current)

/* func_ov004_02230538 (update of state 3): by overlay 45's object's frame, part 0 hidden at
 * frame 7, part 2 at frame 18, the body shown at frame 19 and hidden at frame 37 (the frame is
 * asked for once for each); idle once part 2's animation has run out. */
void TarotObject_UpdateState3(TarotObject *self)
{
    if (func_ov045_02260618() == TAROT_OBJECT_STATE3_HIDE_PART0_FRAME) {
        self->part_shown[0] = 0;
    }
    if (func_ov045_02260618() == TAROT_OBJECT_STATE3_HIDE_PART2_FRAME) {
        self->part_shown[2] = 0;
    }
    if (func_ov045_02260618() == TAROT_OBJECT_STATE3_SHOW_BODY_FRAME) {
        self->body_shown = 1;
    }
    if (func_ov045_02260618() == TAROT_OBJECT_STATE3_HIDE_BODY_FRAME) {
        self->body_shown = 0;
    }
    if (FrameCtrl_IsDone(&self->parts[2].frames)) {
        TarotObject_SetState(self, TAROT_OBJECT_IDLE);
    }
}
CLEAN_AS(func_ov004_02230538, TarotObject_UpdateState3)

/* func_ov004_022305a0 (entry of state 3): the parts shown, the body hidden; part 2 plays its
 * joint animation 1 once and part 1 its texture animation 1. */
int TarotObject_EnterState3(TarotObject *self)
{
    self->body_shown = 0;
    self->part_shown[0] = 1;
    self->part_shown[1] = 1;
    self->part_shown[2] = 1;
    AnimatedModel_Start(TarotObject_animated(&self->parts[2]), RmoModel_JointAnim(&self->part_models[2], 1), TAROT_OBJECT_ONCE,
                        TAROT_OBJECT_ONE, 0, 0);
    ModelAnim_Start(&self->part1_anim, RmoModel_TextureAnim(&self->part_models[1], 1), TAROT_OBJECT_ONCE, TAROT_OBJECT_ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_022305a0, TarotObject_EnterState3)

/* func_ov004_02230620 (update of state 2): part 0 shown at overlay 45's object's frame 9.
 * QUIRK: the table calls it as a function without a result, but it answers the frame, or at
 * frame 9 the offset of the flag it set (0x6b0). */
int TarotObject_UpdateState2(TarotObject *self)
{
    unsigned int frame = func_ov045_02260618();
    if (frame == TAROT_OBJECT_STATE2_SHOW_FRAME) {
        self->part_shown[0] = 1;
        return (int) offsetof(TarotObject, part_shown[0]);
    }
    return (int) frame;
}
CLEAN_AS(func_ov004_02230620, TarotObject_UpdateState2)

/* func_ov004_0223063c (entry of state 2): parts 1 and 2 shown, the body and part 0 hidden;
 * part 2's joint animation and part 1's texture animation put at their last whole frame (their
 * frame counts' whole frames, 16 bits) and standing still. */
int TarotObject_EnterState2(TarotObject *self)
{
    self->body_shown = 0;
    self->part_shown[0] = 0;
    self->part_shown[1] = 1;
    self->part_shown[2] = 1;
    self->parts[2].frames.frame = TarotObject_whole(self->parts[2].frames.end);
    self->parts[2].frames.speed = 0;
    self->part1_anim.ctrl.frame = TarotObject_whole(self->part1_anim.ctrl.end);
    self->part1_anim.ctrl.speed = 0;
    return 1;
}
CLEAN_AS(func_ov004_0223063c, TarotObject_EnterState2)

/* func_ov004_022306a8 (update of state 1): at overlay 45's object's frame 11 the body hidden
 * and part 2 shown.
 * QUIRK: the table calls it as a function without a result, but it answers the frame, or at
 * frame 11 the offset of the last flag it set (0x6b2). */
int TarotObject_UpdateState1(TarotObject *self)
{
    unsigned int frame = func_ov045_02260618();
    if (frame == TAROT_OBJECT_STATE1_SWAP_FRAME) {
        self->body_shown = 0;
        self->part_shown[2] = 1;
        return (int) offsetof(TarotObject, part_shown[2]);
    }
    return (int) frame;
}
CLEAN_AS(func_ov004_022306a8, TarotObject_UpdateState1)

/* func_ov004_022306d0 (entry of state 1): the body and part 1 shown, parts 0 and 2 hidden; part
 * 2 plays its joint animation 0 once and part 1 its texture animation 0. */
int TarotObject_EnterState1(TarotObject *self)
{
    self->body_shown = 1;
    self->part_shown[0] = 0;
    self->part_shown[1] = 1;
    self->part_shown[2] = 0;
    AnimatedModel_Start(TarotObject_animated(&self->parts[2]), RmoModel_JointAnim(&self->part_models[2], 0), TAROT_OBJECT_ONCE,
                        TAROT_OBJECT_ONE, 0, 0);
    ModelAnim_Start(&self->part1_anim, RmoModel_TextureAnim(&self->part_models[1], 0), TAROT_OBJECT_ONCE, TAROT_OBJECT_ONE, 0);
    return 1;
}
CLEAN_AS(func_ov004_022306d0, TarotObject_EnterState1)

/* func_ov004_02230750 (update of the idle state): nothing. */
void TarotObject_UpdateIdle(TarotObject *self)
{
    (void) self;
}
CLEAN_AS(func_ov004_02230750, TarotObject_UpdateIdle)

/* func_ov004_02230754 (entry of the idle state): the body and the parts hidden. */
int TarotObject_EnterIdle(TarotObject *self)
{
    self->body_shown = 0;
    for (int i = 0; i < TAROT_OBJECT_PARTS; i++) {
        self->part_shown[i] = 0;
    }
    return 1;
}
CLEAN_AS(func_ov004_02230754, TarotObject_EnterIdle)

/* _ZN18Obj_ov004_0225567419func_ov004_02230780Ev: the state's update, through its table. */
void TarotObject_UpdateState(TarotObject *self)
{
    static const MemberPointer *const updates[TAROT_OBJECT_STATE_COUNT] = {
        &data_ov004_02255634, /* TarotObject_UpdateIdle */
        &data_ov004_0225561c, /* TarotObject_UpdateState1 */
        &data_ov004_02255624, /* TarotObject_UpdateState2 */
        &data_ov004_0225562c, /* TarotObject_UpdateState3 */
    };
    MemberTable_InitOnce(&data_ov004_02258878, data_ov004_0225887c, updates, TAROT_OBJECT_STATE_COUNT);
    /* REQUIRES: state >= 0 (TarotObject_SetState sets 0 to 3); the ROM's signed test lets a
     * negative one index before the table */
    if (self->state >= 0 && self->state < TAROT_OBJECT_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_0225887c[self->state], self);
    }
}
CLEAN_AS(_ZN18Obj_ov004_0225567419func_ov004_02230780Ev, TarotObject_UpdateState)

/* func_ov004_0223080c: enters `state` if its entry (through a table) agrees; whether it did.
 * States 4 and above do not exist. */
int TarotObject_SetState(TarotObject *self, int state)
{
    static const MemberPointer *const entries[TAROT_OBJECT_STATE_COUNT] = {
        &data_ov004_02255614, /* TarotObject_EnterIdle */
        &data_ov004_0225564c, /* TarotObject_EnterState1 */
        &data_ov004_02255644, /* TarotObject_EnterState2 */
        &data_ov004_0225563c, /* TarotObject_EnterState3 */
    };
    MemberTable_InitOnce(&data_ov004_02258874, data_ov004_0225889c, entries, TAROT_OBJECT_STATE_COUNT);
    /* REQUIRES: state >= 0 (the game passes 0 to 3); the ROM's signed test lets a negative one
     * index before the table */
    if (state >= 0 && state < TAROT_OBJECT_STATE_COUNT && MemberPointer_CallInt(&data_ov004_0225889c[state], self) != 0) {
        self->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0223080c, TarotObject_SetState)

/* func_ov004_022308a8 (vtable slot 0x0c): the body's and the parts' archives released; no longer
 * the one that exists. */
int TarotObject_Release(TarotObject *self)
{
    RmoObjectSlots_ReleaseBody(&self->base);
    for (int i = 0; i < TAROT_OBJECT_PARTS; i++) {
        TarotObject_ReleasePart(self, i);
    }
    data_ov004_02258870 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_022308a8, TarotObject_Release)

/* func_ov004_022308dc: the body and part 0 placed at overlay 45's object's matrix (copied
 * through the scratch matrix data_021fbe48), then the body and the parts drawn that are
 * shown. */
void TarotObject_Draw(TarotObject *self)
{
    data_021fbe48 = *func_ov045_02260630();
    *TarotObject_matrix(&self->base.body) = data_021fbe48;
    *TarotObject_matrix(&self->parts[0]) = data_021fbe48;
    if (self->body_shown) {
        AnimatedModel_Draw(TarotObject_animated(&self->base.body), NULL);
    }
    for (int i = 0; i < TAROT_OBJECT_PARTS; i++) {
        if (self->part_shown[i]) {
            AnimatedModel_Draw(TarotObject_animated(&self->parts[i]), NULL);
        }
    }
}
CLEAN_AS(func_ov004_022308dc, TarotObject_Draw)

/* func_ov004_02230978 (vtable slot 0x24): nothing; overlay 45's draw draws it. */
int TarotObject_Vfunc24(void)
{
    return 1;
}
CLEAN_AS(func_ov004_02230978, TarotObject_Vfunc24)

/* func_ov004_0223097c (vtable slot 0x18): part 2's animation and part 1's texture animation
 * step (the latter shows its frame control's frame), parts 1 and 2 placed at its position
 * (built in the scratch matrix data_021fbe48), then the state's update. */
int TarotObject_Update(TarotObject *self)
{
    AnimatedModel_StepFrames(TarotObject_animated(&self->parts[2]));
    FrameCtrl_Step(&self->part1_anim.ctrl);
    self->part1_anim.anim->frame = self->part1_anim.ctrl.frame;
    const Vec3 *position = &self->base.actor.position;
    Mtx43_Translation(&data_021fbe48, position->x, position->y, position->z);
    *TarotObject_matrix(&self->parts[1]) = data_021fbe48;
    *TarotObject_matrix(&self->parts[2]) = data_021fbe48;
    TarotObject_UpdateState(self);
    return 1;
}
CLEAN_AS(func_ov004_0223097c, TarotObject_Update)

/* func_ov004_022309f8 (vtable slot 0x00): becomes the one that exists and loads the body and
 * the parts. When obj_tarot4 has a first joint animation part 2 can take, part 2 plays it once,
 * standing still at its first frame; when part 1 takes a texture animation, it plays
 * obj_tarot3's first once, standing still too. Then idle.
 * QUIRK: the joint animation is asked for twice. */
int TarotObject_Start(TarotObject *self)
{
    data_ov004_02258870 = self;
    RmoObjectSlots_Load(&self->base, data_ov004_022556dc, data_ov004_022556f4);
    TarotObject_LoadPart(self, 0, data_ov004_02255710, data_ov004_02255728);
    TarotObject_LoadPart(self, 1, data_ov004_02255744, data_ov004_0225575c);
    TarotObject_LoadPart(self, 2, data_ov004_02255778, data_ov004_02255790);
    if (RmoModel_JointAnim(&self->part_models[2], 0) != NULL &&
        AnimatedModel_LoadAnim(TarotObject_animated(&self->parts[2]), data_021c9b24) != 0) {
        AnimatedModel_Start(TarotObject_animated(&self->parts[2]), RmoModel_JointAnim(&self->part_models[2], 0),
                            TAROT_OBJECT_ONCE, TAROT_OBJECT_ONE, 0, 0);
        AnimatedModel_Attach(TarotObject_animated(&self->parts[2]));
        self->parts[2].frames.speed = 0;
    }
    if (ModelAnim_AllocMaterialAnim(&self->part1_anim, self->parts[1].object.model, data_021c9b24) != 0) {
        ModelAnim_Start(&self->part1_anim, RmoModel_TextureAnim(&self->part_models[1], 0), TAROT_OBJECT_ONCE, TAROT_OBJECT_ONE,
                        0);
        ModelAnim_Attach(&self->part1_anim, ModelObject_RenderObject(&self->parts[1].object));
        self->part1_anim.ctrl.speed = 0;
    }
    TarotObject_SetState(self, TAROT_OBJECT_IDLE);
    return 1;
}
CLEAN_AS(func_ov004_022309f8, TarotObject_Start)

/* The parts' holders and part 1's texture animation taken down, then the base class. */
static void TarotObject_destruct(TarotObject *self)
{
    self->base.actor.vtable = data_ov004_02255674;
    ModelAnim_DestructComplete(&self->part1_anim);
    __cxa_vec_cleanup(self->part_textures, TAROT_OBJECT_PARTS, sizeof(RmoTexture), func_ov004_0222c394);
    __cxa_vec_cleanup(self->part_models, TAROT_OBJECT_PARTS, sizeof(RmoModel), func_ov004_0222c538);
    __cxa_vec_cleanup(self->parts, TAROT_OBJECT_PARTS, sizeof(RmoAnimatedModel), func_020551e0);
    RmoObjectSlots_Destruct(&self->base);
}

/* func_ov004_02230b20 (the deleting destructor, vtable slot 0x44) */
TarotObject *TarotObject_Delete(TarotObject *self)
{
    TarotObject_destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_02230b20, TarotObject_Delete)

/* func_ov004_02230b90 (the destructor, vtable slot 0x40) */
TarotObject *TarotObject_Destruct(TarotObject *self)
{
    TarotObject_destruct(self);
    return self;
}
CLEAN_AS(func_ov004_02230b90, TarotObject_Destruct)

/* func_ov004_02230bf8 (the constructor). Its state is left as the allocation zeroed it. */
TarotObject *TarotObject_Construct(TarotObject *self)
{
    RmoObjectBase_Construct(&self->base);
    self->base.actor.vtable = data_ov004_02255674;
    __cxa_vec_ctor(self->parts, TAROT_OBJECT_PARTS, sizeof(RmoAnimatedModel), func_02055210, func_020551e0);
    __cxa_vec_ctor(self->part_models, TAROT_OBJECT_PARTS, sizeof(RmoModel), func_ov004_0222c548, func_ov004_0222c538);
    __cxa_vec_ctor(self->part_textures, TAROT_OBJECT_PARTS, sizeof(RmoTexture), func_ov004_0222c398, func_ov004_0222c394);
    ModelAnim_Construct(&self->part1_anim);
    return self;
}
CLEAN_AS(func_ov004_02230bf8, TarotObject_Construct)

/* func_ov004_02230c7c: a new one from the room's heap; nothing when it has no room. */
void TarotObject_Create(void)
{
    TarotObject *self = Heap_AllocAuxZeroed(sizeof(TarotObject));
    if (self != NULL) {
        TarotObject_Construct(self);
    }
}
CLEAN_AS(func_ov004_02230c7c, TarotObject_Create)
