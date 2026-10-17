/* The props of the cafe's counter (cafe_props.h). */
#include "cafe_props.h"

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "autoload_2/matrix.h"
#include "cafe_master.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/camera_control.h"
#include "main/effect_system.h"
#include "main/frame_ctrl.h"
#include "main/model_object.h"
#include "main/music_queue.h"
#include "main/sound.h"
#include "member_pointer.h"
#include "ov004/rmo_model.h"
#include "ov004/rmo_object_slots.h"
#include "rmo_object_base.h"

static_assert(offsetof(Actor, angle) == 0x8c, "angle");
static_assert(sizeof(Actor) == 0xd4, "Actor size");
static_assert(sizeof(RmoAnimatedModel) == 0xb8, "RmoAnimatedModel size");
static_assert(sizeof(RmoModel) == 0xa4, "RmoModel size");
static_assert(offsetof(RmoObject, body) == 0xec, "body");
static_assert(offsetof(RmoObject, body_model) == 0x1a4, "body model");
static_assert(offsetof(RmoObject, body_texture) == 0x248, "body texture");
static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(offsetof(CafeProps, parts) == 0x290, "parts");
static_assert(offsetof(CafeProps, part_models) == 0x908, "part models");
static_assert(offsetof(CafeProps, part_textures) == 0xecc, "part textures");
static_assert(offsetof(CafeProps, part_shown) == 0xef0, "part shown");
static_assert(offsetof(CafeProps, body_shown) == 0xef9, "body shown");
static_assert(offsetof(CafeProps, state) == 0xefc, "state");
static_assert(offsetof(CafeProps, effect_point) == 0xf10, "effect point");
static_assert(offsetof(CafeProps, part_effect_points) == 0xf1c, "part effect points");
static_assert(offsetof(CafeProps, part_effect_angles) == 0xf34, "part effect angles");
static_assert(offsetof(CafeProps, effect) == 0xf38, "effect");
static_assert(offsetof(CafeProps, part_effects) == 0xf3c, "part effects");
static_assert(sizeof(CafeProps) == 0xf44, "the size CafeProps_Create allocates");

#define ONE 0x1000        /* normal speed, 20.12 fixed point */
#define NO_EFFECT (-1)    /* CafeProps.effect and part_effects when none runs */
#define EFFECT_SET 0x6b   /* the effect set of all three effects */
#define EFFECT_FRAME 0x3b /* the master's frame at which state 5 starts its effect */
#define MUSIC_FIRST 99    /* the musics whose beat the counter and part 0 follow */
#define MUSIC_LAST 171
#define RECORD_STOPPED 1 /* byte 3 of the sound's entry while it does not play */
#define PLAY_LOOP 0      /* FrameCtrlFlags */
#define PLAY_ONCE FRAME_CTRL_ONCE
#define PLAY_BACKWARDS (FRAME_CTRL_ONCE | FRAME_CTRL_REVERSE)

/* The master's animations (CafeMaster_AnimNumber). */
#define MASTER_ANIM_F2 0xf2
#define MASTER_ANIM_F3 0xf3
#define MASTER_ANIM_F4 0xf4
#define MASTER_ANIM_F5 0xf5
#define MASTER_ANIM_F6 0xf6
#define MASTER_ANIM_F7 0xf7
#define MASTER_ANIM_F8 0xf8

/* Frames of the master's animation 0xf6: the counter and part 0 show up to the first, parts 1
 * and 2 from the second. */
#define SHOW_BODY_LAST 6
#define SHOW_PARTS_FIRST 18

/* Part 1 and 2's place: at the master's first matrix, or (in states 5 and 6, from a frame of
 * their animation) at a fixed point. */
#define PLACED_FRAME_STATE_5 16
#define PLACED_FRAMES_BEFORE_END_STATE_6 45
#define FIXED_EFFECT_X 0x16a00
#define FIXED_EFFECT_Y 0x1900
#define FIXED_EFFECT_Z 0x15000

/* Part 3 is at the master's second matrix during these frames of its animation. */
#define PART3_HELD_FIRST 15
#define PART3_HELD_LAST 72

/* The one that exists, NULL for none. */
extern CafeProps *data_ov004_02258310;

/* The archives of the counter and of the parts (/roomObj/obj_cafe1 to obj_cafe6). */
extern const char data_ov004_02255030[], data_ov004_02255048[]; /* obj_cafe1.arc, .nsbtx */
extern const char data_ov004_02255064[], data_ov004_0225507c[]; /* obj_cafe2 */
extern const char data_ov004_02255098[], data_ov004_022550b0[]; /* obj_cafe3 */
extern const char data_ov004_022550cc[], data_ov004_022550e4[]; /* obj_cafe4 */
extern const char data_ov004_02255100[], data_ov004_02255118[]; /* obj_cafe5 */
extern const char data_ov004_02255134[], data_ov004_0225514c[]; /* obj_cafe6 */

/* The fixed points: of parts 1 and 2 when placed, of part 3 when not held, of parts 4 and 5,
 * of parts 6 and 7 (also those of the two effects), of part 8. */
extern const Vec3 data_ov004_0225836c, data_ov004_0225839c, data_ov004_02258318, data_ov004_02258330, data_ov004_02258348;

/* The class's vtable. */
extern const u8 data_ov004_02254fc8[];

/* The scratch matrix the game builds model matrices in. */
extern Mtx43 data_021fbe48;
extern Heap *data_021c9b24;

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_0225830c;
extern MemberPointer data_ov004_022583f8[CAFE_PROPS_STATES];
extern const MemberPointer data_ov004_02254f48, data_ov004_02254f40, data_ov004_02254f38, data_ov004_02254f30,
    data_ov004_02254f78, data_ov004_02254f28, data_ov004_02254f60, data_ov004_02254f18, data_ov004_02254f20,
    data_ov004_02254f58;
extern u32 data_ov004_02258314;
extern MemberPointer data_ov004_022583a8[CAFE_PROPS_STATES];
extern const MemberPointer data_ov004_02254f08, data_ov004_02254fa0, data_ov004_02254f98, data_ov004_02254f90,
    data_ov004_02254f88, data_ov004_02254f80, data_ov004_02254f10, data_ov004_02254f68, data_ov004_02254f70,
    data_ov004_02254f50;

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

extern int NNS_G3dBindMdlTex(u8 *model, void *texture);
extern int NNS_G3dBindMdlPltt(u8 *model, void *texture);

static AnimatedModel *animated(RmoAnimatedModel *model)
{
    return (AnimatedModel *) model;
}

static Mtx43 *model_matrix(RmoAnimatedModel *model)
{
    return (Mtx43 *) (void *) model->object.unk_64;
}

/* A frame position's whole frames, as the game keeps them: 16 bits. */
static int whole_frames(fx32 value)
{
    return (u16) ((u32) value >> 12);
}

/* func_ov004_0222dad8 */
void CafeProps_ShowPart8(void)
{
    if (data_ov004_02258310 != NULL) {
        data_ov004_02258310->part_shown[8] = 1;
    }
}
CLEAN_AS(func_ov004_0222dad8, CafeProps_ShowPart8)

/* func_ov004_0222daf0 */
void CafeProps_ShowParts6And7(void)
{
    if (data_ov004_02258310 != NULL) {
        data_ov004_02258310->part_shown[6] = 1;
        data_ov004_02258310->part_shown[7] = 1;
    }
}
CLEAN_AS(func_ov004_0222daf0, CafeProps_ShowParts6And7)

/* func_ov004_0222db14: `model` plays joint animation `anim` of `source` (AnimatedModel_Start),
 * unless it plays it already. QUIRK: the animation is asked for twice. */
void CafeProps_PlayAnim(CafeProps *unused, int anim, RmoAnimatedModel *model, RmoModel *source, u8 flags, fx32 speed,
                        u16 start, u16 frames)
{
    (void) unused;
    const u8 *playing = AnimatedModel_AnimFile(animated(model));
    if (playing != RmoModel_JointAnim(source, anim)) {
        AnimatedModel_Start(animated(model), RmoModel_JointAnim(source, anim), flags, speed, start, frames);
    }
}
CLEAN_AS(func_ov004_0222db14, CafeProps_PlayAnim)

/* Whether `model` plays joint animation `anim` of `source`. */
static int plays(RmoAnimatedModel *model, RmoModel *source, int anim)
{
    const u8 *playing = AnimatedModel_AnimFile(animated(model));
    return playing == RmoModel_JointAnim(source, anim);
}

/* Whether `model` plays joint animation `anim` of `source` and it has run out. */
static int played(RmoAnimatedModel *model, RmoModel *source, int anim)
{
    return plays(model, source, anim) && FrameCtrl_IsDone(&model->frames);
}

/* func_ov004_0222db58: whether part 1's animation 12 has run out. */
int CafeProps_Part1Anim12Done(void)
{
    CafeProps *self = data_ov004_02258310;
    if (self != NULL && played(&self->parts[1], &self->part_models[1], 12)) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222db58, CafeProps_Part1Anim12Done)

/* func_ov004_0222dbac: whether part 1 plays animation 11 at frame 9. */
int CafeProps_Part1Anim11AtFrame9(void)
{
    CafeProps *self = data_ov004_02258310;
    if (self != NULL && plays(&self->parts[1], &self->part_models[1], 11) && whole_frames(self->parts[1].frames.frame) == 9) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222dbac, CafeProps_Part1Anim11AtFrame9)

/* func_ov004_0222dc00: the state, 0 without the props. */
int CafeProps_State(void)
{
    if (data_ov004_02258310 != NULL) {
        return data_ov004_02258310->state;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222dc00, CafeProps_State)

/* The props enter `state` (CafeProps_SetState); whether they did, 0 without them. */
static int enter_current(int state)
{
    if (data_ov004_02258310 != NULL) {
        return CafeProps_SetState(data_ov004_02258310, state);
    }
    return 0;
}

/* func_ov004_0222dc1c */
int CafeProps_EnterState9(void)
{
    return enter_current(9);
}
CLEAN_AS(func_ov004_0222dc1c, CafeProps_EnterState9)

/* func_ov004_0222dc3c */
int CafeProps_EnterState8(void)
{
    return enter_current(8);
}
CLEAN_AS(func_ov004_0222dc3c, CafeProps_EnterState8)

/* func_ov004_0222dc5c */
int CafeProps_EnterState7(void)
{
    return enter_current(7);
}
CLEAN_AS(func_ov004_0222dc5c, CafeProps_EnterState7)

/* func_ov004_0222dc7c */
int CafeProps_EnterState6(void)
{
    return enter_current(6);
}
CLEAN_AS(func_ov004_0222dc7c, CafeProps_EnterState6)

/* func_ov004_0222dc9c */
int CafeProps_EnterState5(void)
{
    return enter_current(5);
}
CLEAN_AS(func_ov004_0222dc9c, CafeProps_EnterState5)

/* func_ov004_0222dcbc */
int CafeProps_EnterState4(void)
{
    return enter_current(4);
}
CLEAN_AS(func_ov004_0222dcbc, CafeProps_EnterState4)

/* func_ov004_0222dcdc */
int CafeProps_EnterState3(void)
{
    return enter_current(3);
}
CLEAN_AS(func_ov004_0222dcdc, CafeProps_EnterState3)

/* func_ov004_0222dcfc */
int CafeProps_EnterState2(void)
{
    return enter_current(2);
}
CLEAN_AS(func_ov004_0222dcfc, CafeProps_EnterState2)

/* func_ov004_0222dd1c */
int CafeProps_EnterState1(void)
{
    return enter_current(1);
}
CLEAN_AS(func_ov004_0222dd1c, CafeProps_EnterState1)

/* func_ov004_0222dd3c */
int CafeProps_EnterState0(void)
{
    return enter_current(0);
}
CLEAN_AS(func_ov004_0222dd3c, CafeProps_EnterState0)

/* When `source` has a first joint animation and `model` gets an animation object from the
 * room's heap, `model` shows that animation's first frame and stands still there. QUIRK: the
 * animation is asked for twice. */
static void start_first_anim(RmoAnimatedModel *model, RmoModel *source)
{
    if (RmoModel_JointAnim(source, 0) != NULL && AnimatedModel_LoadAnim(animated(model), data_021c9b24) != 0) {
        AnimatedModel_Start(animated(model), RmoModel_JointAnim(source, 0), PLAY_ONCE, ONE, 0, 0);
        AnimatedModel_Attach(animated(model));
        model->frames.speed = 0;
    }
}

/* func_ov004_0222dd5c */
void CafeProps_StartPartAnim(CafeProps *self, int part)
{
    start_first_anim(&self->parts[part], &self->part_models[part]);
}
CLEAN_AS(func_ov004_0222dd5c, CafeProps_StartPartAnim)

/* func_ov004_0222dde0: the part's archive and textures released. */
void CafeProps_ReleasePart(CafeProps *self, int part)
{
    RmoModel_Release(&self->part_models[part]);
    RmoTexture_Release(&self->part_textures[part]);
}
CLEAN_AS(func_ov004_0222dde0, CafeProps_ReleasePart)

/* func_ov004_0222de14: the part's archive and textures loaded, its model set up and the
 * textures and palettes bound to the model. */
void CafeProps_LoadPart(CafeProps *self, int part, const char *archive, const char *texture)
{
    RmoModel *source = &self->part_models[part];
    RmoTexture *textures = &self->part_textures[part];
    u8 *model;

    RmoModel_Load(source, archive);
    RmoTexture_Load(textures, texture);
    ModelObject_SetModel(&self->parts[part].object, RmoModel_Model(source), NULL);
    model = RmoModel_Model(source);
    NNS_G3dBindMdlTex(model, RmoTexture_Texture(textures));
    model = RmoModel_Model(source);
    NNS_G3dBindMdlPltt(model, RmoTexture_Texture(textures));
}
CLEAN_AS(func_ov004_0222de14, CafeProps_LoadPart)

/* func_ov004_0222de98: the props placed and drawn (the master's draw calls it). */
void CafeProps_DrawCurrent(void)
{
    if (data_ov004_02258310 != NULL) {
        CafeProps_Draw(data_ov004_02258310);
    }
}
CLEAN_AS(func_ov004_0222de98, CafeProps_DrawCurrent)

/* Parts 1 and 2 play `anim1` and `anim2` once from the start. */
static void play_parts_1_2(CafeProps *self, int anim1, int anim2, u8 flags, u16 start)
{
    CafeProps_PlayAnim(self, anim1, &self->parts[1], &self->part_models[1], flags, ONE, start, 0);
    CafeProps_PlayAnim(self, anim2, &self->parts[2], &self->part_models[2], flags, ONE, start, 0);
}

/* The counter and part 0 play `anim`, looping. */
static void play_body_part_0(CafeProps *self, int anim)
{
    CafeProps_PlayAnim(self, anim, &self->base.body, &self->base.body_model, PLAY_LOOP, ONE, 0, 0);
    CafeProps_PlayAnim(self, anim, &self->parts[0], &self->part_models[0], PLAY_LOOP, ONE, 0, 0);
}

/* func_ov004_0222deb4 */
void CafeProps_UpdateState9(CafeProps *self)
{
    if (played(&self->parts[1], &self->part_models[1], 11)) {
        play_parts_1_2(self, 12, 10, PLAY_ONCE, 0);
    }
}
CLEAN_AS(func_ov004_0222deb4, CafeProps_UpdateState9)

/* func_ov004_0222df3c */
int CafeProps_OnEnterState9(CafeProps *self)
{
    (void) self;
    CameraControl_SetPreviousMode();
    return 1;
}
CLEAN_AS(func_ov004_0222df3c, CafeProps_OnEnterState9)

/* func_ov004_0222df4c */
void CafeProps_UpdateState8(CafeProps *self)
{
    if (played(&self->parts[1], &self->part_models[1], 6)) {
        play_parts_1_2(self, 9, 7, PLAY_ONCE, 0);
    } else if (played(&self->parts[1], &self->part_models[1], 9)) {
        play_parts_1_2(self, 10, 8, PLAY_ONCE, 0);
    } else if (played(&self->parts[1], &self->part_models[1], 10)) {
        CameraControl_MuteSounds();
        CameraControl_SetMode4();
        play_parts_1_2(self, 11, 9, PLAY_ONCE, 0);
    }
}
CLEAN_AS(func_ov004_0222df4c, CafeProps_UpdateState8)

/* func_ov004_0222e0a0: the effect of state 5 ended. QUIRK: its handle is kept, so the update
 * goes on moving the ended effect. */
int CafeProps_OnEnterState8(CafeProps *self)
{
    EffectSystem_EndHandle(self->effect);
    return 1;
}
CLEAN_AS(func_ov004_0222e0a0, CafeProps_OnEnterState8)

/* func_ov004_0222e0b8 */
void CafeProps_UpdateState6(CafeProps *self)
{
    u16 frame = CafeMaster_AnimFrame();
    if (CafeMaster_AnimNumber() == MASTER_ANIM_F8) {
        play_parts_1_2(self, 7, 5, PLAY_BACKWARDS, frame);
    }
}
CLEAN_AS(func_ov004_0222e0b8, CafeProps_UpdateState6)

/* func_ov004_0222e124 */
int CafeProps_OnEnterState6(CafeProps *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222e124, CafeProps_OnEnterState6)

/* func_ov004_0222e128 */
void CafeProps_UpdateState5(CafeProps *self)
{
    u16 frame = CafeMaster_AnimFrame();
    if (CafeMaster_AnimNumber() == MASTER_ANIM_F8) {
        play_parts_1_2(self, 6, 4, PLAY_ONCE, 0);
        if (frame == EFFECT_FRAME) {
            self->effect = EffectSystem_StartKeptSetNumber(EFFECT_SET, &self->effect_point, &self->base.actor.angle[1], NULL);
        }
    }
}
CLEAN_AS(func_ov004_0222e128, CafeProps_UpdateState5)

/* func_ov004_0222e1b4 */
int CafeProps_OnEnterState5(CafeProps *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222e1b4, CafeProps_OnEnterState5)

/* func_ov004_0222e1b8 */
void CafeProps_UpdateState4(CafeProps *self)
{
    CafeMaster_AnimFrame();
    if (CafeMaster_AnimNumber() == MASTER_ANIM_F7) {
        play_parts_1_2(self, 5, 3, PLAY_LOOP, 0);
    }
}
CLEAN_AS(func_ov004_0222e1b8, CafeProps_UpdateState4)

/* func_ov004_0222e220: part 3 plays its first animation once from the start. */
int CafeProps_OnEnterState4(CafeProps *self)
{
    AnimatedModel_Start(animated(&self->parts[3]), RmoModel_JointAnim(&self->part_models[3], 0), PLAY_ONCE, ONE, 0, 0);
    return 1;
}
CLEAN_AS(func_ov004_0222e220, CafeProps_OnEnterState4)

/* func_ov004_0222e25c (states 3 and 7). QUIRK: the master's animation is asked for again for
 * each number it is compared with. */
void CafeProps_UpdateState3(CafeProps *self)
{
    unsigned int frame = CafeMaster_AnimFrame();
    if (CafeMaster_AnimNumber() == MASTER_ANIM_F2) {
        play_body_part_0(self, 0);
    } else if (CafeMaster_AnimNumber() == MASTER_ANIM_F4) {
        play_body_part_0(self, 1);
    } else if (CafeMaster_AnimNumber() == MASTER_ANIM_F6) {
        u8 early = frame <= SHOW_BODY_LAST;
        u8 late = frame >= SHOW_PARTS_FIRST;
        self->body_shown = early;
        self->part_shown[0] = early;
        self->part_shown[1] = late;
        self->part_shown[2] = late;
        play_body_part_0(self, 2);
        CafeProps_PlayAnim(self, 2, &self->parts[1], &self->part_models[1], PLAY_LOOP, ONE, 0, 0);
        CafeProps_PlayAnim(self, 2, &self->parts[2], &self->part_models[2], PLAY_LOOP, ONE, 0, 0);
    } else if (CafeMaster_AnimNumber() == MASTER_ANIM_F3) {
        play_parts_1_2(self, 0, 0, PLAY_LOOP, 0);
    } else if (CafeMaster_AnimNumber() == MASTER_ANIM_F5) {
        play_parts_1_2(self, 1, 1, PLAY_LOOP, 0);
    }
}
CLEAN_AS(func_ov004_0222e25c, CafeProps_UpdateState3)

/* func_ov004_0222e44c (states 3 and 7) */
int CafeProps_OnEnterState3(CafeProps *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222e44c, CafeProps_OnEnterState3)

/* func_ov004_0222e450. QUIRK: the master's animation is asked for again for the second
 * number. */
void CafeProps_UpdateState2(CafeProps *self)
{
    CafeMaster_AnimFrame();
    if (CafeMaster_AnimNumber() == MASTER_ANIM_F3) {
        play_parts_1_2(self, 3, 0, PLAY_LOOP, 0);
    } else if (CafeMaster_AnimNumber() == MASTER_ANIM_F5) {
        play_parts_1_2(self, 4, 1, PLAY_LOOP, 0);
    }
}
CLEAN_AS(func_ov004_0222e450, CafeProps_UpdateState2)

/* func_ov004_0222e4f8 */
int CafeProps_OnEnterState2(CafeProps *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222e4f8, CafeProps_OnEnterState2)

/* func_ov004_0222e4fc. QUIRK: as in state 2. */
void CafeProps_UpdateState1(CafeProps *self)
{
    CafeMaster_AnimFrame();
    if (CafeMaster_AnimNumber() == MASTER_ANIM_F3) {
        play_parts_1_2(self, 0, 0, PLAY_LOOP, 0);
    } else if (CafeMaster_AnimNumber() == MASTER_ANIM_F5) {
        play_parts_1_2(self, 1, 1, PLAY_LOOP, 0);
    }
}
CLEAN_AS(func_ov004_0222e4fc, CafeProps_UpdateState1)

/* func_ov004_0222e5a0 */
int CafeProps_OnEnterState1(CafeProps *self)
{
    (void) self;
    return 1;
}
CLEAN_AS(func_ov004_0222e5a0, CafeProps_OnEnterState1)

/* func_ov004_0222e5a4. QUIRK: as in state 2. */
void CafeProps_UpdateState0(CafeProps *self)
{
    CafeMaster_AnimFrame();
    if (CafeMaster_AnimNumber() == MASTER_ANIM_F2) {
        play_body_part_0(self, 0);
    } else if (CafeMaster_AnimNumber() == MASTER_ANIM_F4) {
        play_body_part_0(self, 1);
    }
}
CLEAN_AS(func_ov004_0222e5a4, CafeProps_UpdateState0)

/* func_ov004_0222e644: the counter and part 0 shown. */
int CafeProps_OnEnterState0(CafeProps *self)
{
    self->body_shown = 1;
    self->part_shown[0] = 1;
    return 1;
}
CLEAN_AS(func_ov004_0222e644, CafeProps_OnEnterState0)

/* _ZN18Obj_ov004_02254fc819func_ov004_0222e65cEv: the state's update, through its table. */
void CafeProps_UpdateState(CafeProps *self)
{
    static const MemberPointer *const updates[CAFE_PROPS_STATES] = {
        &data_ov004_02254f48, /* CafeProps_UpdateState0 */
        &data_ov004_02254f40, /* CafeProps_UpdateState1 */
        &data_ov004_02254f38, /* CafeProps_UpdateState2 */
        &data_ov004_02254f30, /* CafeProps_UpdateState3 */
        &data_ov004_02254f78, /* CafeProps_UpdateState4 */
        &data_ov004_02254f28, /* CafeProps_UpdateState5 */
        &data_ov004_02254f60, /* CafeProps_UpdateState6 */
        &data_ov004_02254f18, /* CafeProps_UpdateState3 */
        &data_ov004_02254f20, /* CafeProps_UpdateState8 */
        &data_ov004_02254f58, /* CafeProps_UpdateState9 */
    };
    MemberTable_InitOnce(&data_ov004_0225830c, data_ov004_022583f8, updates, CAFE_PROPS_STATES);
    /* REQUIRES: state >= 0; the ROM's signed test lets a negative one index before the table */
    if (self->state >= 0 && self->state < CAFE_PROPS_STATES) {
        MemberPointer_CallVoid(&data_ov004_022583f8[self->state], self);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02254fc819func_ov004_0222e65cEv, CafeProps_UpdateState)

/* func_ov004_0222e73c: enters `state` if its entry function (through a table) agrees; whether
 * it did. States 10 and above do not exist. */
int CafeProps_SetState(CafeProps *self, int state)
{
    static const MemberPointer *const entries[CAFE_PROPS_STATES] = {
        &data_ov004_02254f08, /* CafeProps_OnEnterState0 */
        &data_ov004_02254fa0, /* CafeProps_OnEnterState1 */
        &data_ov004_02254f98, /* CafeProps_OnEnterState2 */
        &data_ov004_02254f90, /* CafeProps_OnEnterState3 */
        &data_ov004_02254f88, /* CafeProps_OnEnterState4 */
        &data_ov004_02254f80, /* CafeProps_OnEnterState5 */
        &data_ov004_02254f10, /* CafeProps_OnEnterState6 */
        &data_ov004_02254f68, /* CafeProps_OnEnterState3 */
        &data_ov004_02254f70, /* CafeProps_OnEnterState8 */
        &data_ov004_02254f50, /* CafeProps_OnEnterState9 */
    };
    MemberTable_InitOnce(&data_ov004_02258314, data_ov004_022583a8, entries, CAFE_PROPS_STATES);
    /* REQUIRES: state >= 0 (the game passes 0 to 9); the ROM's signed test lets a negative one
     * index before the table */
    if (state >= 0 && state < CAFE_PROPS_STATES && MemberPointer_CallInt(&data_ov004_022583a8[state], self) != 0) {
        self->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222e73c, CafeProps_SetState)

/* func_ov004_0222e82c (vtable slot 0x0c): the counter's and the parts' archives released; the
 * props are no longer the current ones. */
int CafeProps_Release(CafeProps *self)
{
    RmoObjectSlots_ReleaseBody(&self->base);
    for (int i = 0; i < CAFE_PROPS_PARTS; i++) {
        CafeProps_ReleasePart(self, i);
    }
    data_ov004_02258310 = NULL;
    return 1;
}
CLEAN_AS(func_ov004_0222e82c, CafeProps_Release)

/* The scratch matrix: a translation to `point`. */
static void translate_to(const Vec3 *point)
{
    Mtx43_Translation(&data_021fbe48, point->x, point->y, point->z);
}

/* The scratch matrix: the master's first matrix. */
static void take_master_matrix(void)
{
    data_021fbe48 = *CafeMaster_Matrix748();
}

/* Whether part 1 or 2 is at its fixed point in state 5 or 6 (else at the master's first
 * matrix). */
static int placed(const CafeProps *self, int part)
{
    int frame = whole_frames(self->parts[part].frames.frame);
    if (self->state == 5) {
        return frame >= PLACED_FRAME_STATE_5;
    }
    return frame >= whole_frames(self->parts[part].frames.end) - PLACED_FRAMES_BEFORE_END_STATE_6;
}

/* func_ov004_0222e860: each model's matrix set (built in the scratch matrix data_021fbe48), then
 * the counter and the parts drawn that are shown. Outside states 8 and 9 the effect's point
 * follows part 1: the fixed point while it is placed, else the master's first matrix's
 * translation. */
void CafeProps_Draw(CafeProps *self)
{
    data_021fbe48 = *CafeMaster_Matrix748();
    *model_matrix(&self->base.body) = data_021fbe48;
    data_021fbe48 = *CafeMaster_Matrix718();
    *model_matrix(&self->parts[0]) = data_021fbe48;

    if (self->state == 8 || self->state == 9) {
        translate_to(&data_ov004_0225836c);
    } else if ((self->state == 5 || self->state == 6) && placed(self, 1)) {
        translate_to(&data_ov004_0225836c);
        self->effect_point.x = FIXED_EFFECT_X;
        self->effect_point.y = FIXED_EFFECT_Y;
        self->effect_point.z = FIXED_EFFECT_Z;
    } else {
        /* QUIRK: outside states 8 and 9 the effect's point is set whatever the state */
        take_master_matrix();
        self->effect_point.x = data_021fbe48.m[3][0];
        self->effect_point.y = data_021fbe48.m[3][1];
        self->effect_point.z = data_021fbe48.m[3][2];
    }
    *model_matrix(&self->parts[1]) = data_021fbe48;

    if (self->state == 8 || self->state == 9) {
        translate_to(&data_ov004_0225836c);
    } else if ((self->state == 5 || self->state == 6) && placed(self, 2)) {
        translate_to(&data_ov004_0225836c);
    } else {
        take_master_matrix();
    }
    *model_matrix(&self->parts[2]) = data_021fbe48;

    int frame = whole_frames(self->parts[3].frames.frame);
    if (frame >= PART3_HELD_FIRST && frame <= PART3_HELD_LAST) {
        data_021fbe48 = *CafeMaster_Matrix718();
    } else {
        translate_to(&data_ov004_0225839c);
    }
    *model_matrix(&self->parts[3]) = data_021fbe48;

    translate_to(&data_ov004_02258318);
    *model_matrix(&self->parts[4]) = data_021fbe48;
    *model_matrix(&self->parts[5]) = data_021fbe48;
    translate_to(&data_ov004_02258330);
    *model_matrix(&self->parts[6]) = data_021fbe48;
    *model_matrix(&self->parts[7]) = data_021fbe48;
    translate_to(&data_ov004_02258348);
    *model_matrix(&self->parts[8]) = data_021fbe48;

    if (self->body_shown) {
        AnimatedModel_Draw(animated(&self->base.body), NULL);
    }
    for (int i = 0; i < CAFE_PROPS_PARTS; i++) {
        if (self->part_shown[i]) {
            AnimatedModel_Draw(animated(&self->parts[i]), NULL);
        }
    }
}
CLEAN_AS(func_ov004_0222e860, CafeProps_Draw)

/* func_ov004_0222ec30 (vtable slot 0x24): nothing; the master's draw draws the props. */
int CafeProps_Vfunc24(void)
{
    return 1;
}
CLEAN_AS(func_ov004_0222ec30, CafeProps_Vfunc24)

/* The model's frame set to the sound's beat: one step from frame 0 at `speed`. */
static void step_to_beat(RmoAnimatedModel *model, fx32 speed)
{
    model->frames.frame = 0;
    model->frames.speed = speed;
    AnimatedModel_StepFrames(animated(model));
    model->frames.speed = 0;
}

/* _ZN18Obj_ov004_02254fc819func_ov004_0222ec34Ev (vtable slot 0x18): while one of the musics
 * plays (its sound entry not stopped), the counter and part 0 follow its beat (the entry's word
 * at 0x10); the animations step, the state's update runs, the effect follows its point, and
 * parts 4 and 6 start their effects once shown. */
int CafeProps_Update(CafeProps *self)
{
    if (Math_IsBetween(Music_CurrentMusic(), MUSIC_FIRST, MUSIC_LAST)) {
        const int *record = SoundSys_FirstEntryData();
        if (record != NULL && ((const s8 *) record)[3] != RECORD_STOPPED) {
            step_to_beat(&self->base.body, record[4]);
            step_to_beat(&self->parts[0], record[4]);
        }
    }
    AnimatedModel_StepFrames(animated(&self->base.body));
    for (int i = 0; i < CAFE_PROPS_PARTS; i++) {
        AnimatedModel_StepFrames(animated(&self->parts[i]));
    }
    CafeProps_UpdateState(self);
    if (self->effect != NO_EFFECT) {
        EffectSystem_MoveHandle(self->effect, &self->effect_point, NULL, NULL);
    }
    if (self->part_shown[4] && self->part_effects[0] == NO_EFFECT) {
        self->part_effects[0] =
            EffectSystem_StartKeptSetNumber(EFFECT_SET, &self->part_effect_points[0], &self->part_effect_angles[0], NULL);
    }
    if (self->part_shown[6] && self->part_effects[1] == NO_EFFECT) {
        self->part_effects[1] =
            EffectSystem_StartKeptSetNumber(EFFECT_SET, &self->part_effect_points[1], &self->part_effect_angles[1], NULL);
    }
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02254fc819func_ov004_0222ec34Ev, CafeProps_Update)

/* The last frame of a sequence, as the game computes it from the frame count's whole frames
 * (QUIRK: 16 bits, so a count of 0 gives frame 0xffff). */
static fx32 last_frame(fx32 end)
{
    return (fx32) ((u32) (u16) (whole_frames(end) - 1) << 12);
}

/* func_ov004_0222ed60 (vtable slot 0x00): the props become the current ones; the counter and
 * the parts loaded and shown at their first frames, state 0 entered, part 3 shown, parts 4 to
 * 7 standing at their animations' last frames, the effects' points set and no effect running. */
int CafeProps_Start(CafeProps *self)
{
    data_ov004_02258310 = self;
    RmoObjectSlots_Load(&self->base, data_ov004_02255030, data_ov004_02255048);
    CafeProps_LoadPart(self, 0, data_ov004_02255064, data_ov004_0225507c);
    CafeProps_LoadPart(self, 1, data_ov004_02255098, data_ov004_022550b0);
    CafeProps_LoadPart(self, 2, data_ov004_022550cc, data_ov004_022550e4);
    CafeProps_LoadPart(self, 3, data_ov004_02255100, data_ov004_02255118);
    CafeProps_LoadPart(self, 4, data_ov004_02255098, data_ov004_022550b0);
    CafeProps_LoadPart(self, 5, data_ov004_022550cc, data_ov004_022550e4);
    CafeProps_LoadPart(self, 6, data_ov004_02255098, data_ov004_022550b0);
    CafeProps_LoadPart(self, 7, data_ov004_022550cc, data_ov004_022550e4);
    CafeProps_LoadPart(self, 8, data_ov004_02255134, data_ov004_0225514c);
    start_first_anim(&self->base.body, &self->base.body_model);
    for (int i = 0; i < CAFE_PROPS_PARTS; i++) {
        CafeProps_StartPartAnim(self, i);
    }
    CafeProps_SetState(self, 0);
    self->part_shown[3] = 1;
    for (int i = 4; i < 8; i += 2) {
        CafeProps_PlayAnim(self, 8, &self->parts[i], &self->part_models[i], PLAY_LOOP, ONE, 0, 0);
        CafeProps_PlayAnim(self, 6, &self->parts[i + 1], &self->part_models[i + 1], PLAY_LOOP, ONE, 0, 0);
    }
    self->part_effect_points[0] = data_ov004_02258318;
    self->part_effect_points[1] = data_ov004_02258330;
    self->part_effect_angles[0] = 0;
    self->part_effect_angles[1] = 0;
    for (int i = 4; i < 8; i++) {
        self->parts[i].frames.speed = 0;
        self->parts[i].frames.frame = last_frame(self->parts[i].frames.end);
    }
    self->effect = NO_EFFECT;
    self->part_effects[0] = NO_EFFECT;
    self->part_effects[1] = NO_EFFECT;
    return 1;
}
CLEAN_AS(func_ov004_0222ed60, CafeProps_Start)

/* The parts' holders taken down, then the base class. */
static void destruct(CafeProps *self)
{
    self->base.actor.vtable = data_ov004_02254fc8;
    __cxa_vec_cleanup(self->part_textures, CAFE_PROPS_PARTS, sizeof(RmoTexture), func_ov004_0222c394);
    __cxa_vec_cleanup(self->part_models, CAFE_PROPS_PARTS, sizeof(RmoModel), func_ov004_0222c538);
    __cxa_vec_cleanup(self->parts, CAFE_PROPS_PARTS, sizeof(RmoAnimatedModel), func_020551e0);
    RmoObjectSlots_Destruct(&self->base);
}

/* func_ov004_0222f028 (vtable slot 0x44): taken down and freed. */
CafeProps *CafeProps_Delete(CafeProps *self)
{
    destruct(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0222f028, CafeProps_Delete)

/* func_ov004_0222f08c (vtable slot 0x40) */
CafeProps *CafeProps_Destruct(CafeProps *self)
{
    destruct(self);
    return self;
}
CLEAN_AS(func_ov004_0222f08c, CafeProps_Destruct)

/* func_ov004_0222f0e8 */
CafeProps *CafeProps_Construct(CafeProps *self)
{
    RmoObjectBase_Construct(&self->base);
    self->base.actor.vtable = data_ov004_02254fc8;
    __cxa_vec_ctor(self->parts, CAFE_PROPS_PARTS, sizeof(RmoAnimatedModel), func_02055210, func_020551e0);
    __cxa_vec_ctor(self->part_models, CAFE_PROPS_PARTS, sizeof(RmoModel), func_ov004_0222c548, func_ov004_0222c538);
    __cxa_vec_ctor(self->part_textures, CAFE_PROPS_PARTS, sizeof(RmoTexture), func_ov004_0222c398, func_ov004_0222c394);
    return self;
}
CLEAN_AS(func_ov004_0222f0e8, CafeProps_Construct)

/* func_ov004_0222f160: one made on the auxiliary heap, zeroed. */
void CafeProps_Create(void)
{
    CafeProps *self = Heap_AllocAuxZeroed(sizeof(CafeProps));
    if (self != NULL) {
        CafeProps_Construct(self);
    }
}
CLEAN_AS(func_ov004_0222f160, CafeProps_Create)
