/* The room object of /roomObj/obj_check_in (check_in_gate.h). */
#include "check_in_gate.h"

#include <stdint.h>

#include "autoload_2/approach.h"
#include "autoload_2/heap.h"
#include "clean.h"
#include "main/animated_model.h"
#include "main/bg_models.h"
#include "main/block_021d27ac.h"
#include "main/block_021d27ac_parts.h"
#include "main/calendar.h"
#include "main/frame_ctrl.h"
#include "main/g3d_resource.h"
#include "main/model_object.h"
#include "main/scene_query.h"
#include "main/session.h"
#include "main/sound.h"
#include "main/trivial_object.h"
#include "member_pointer.h"
#include "rmo_object_base.h"

static_assert(sizeof(RmoObject) == 0x290, "RmoObject size");
static_assert(sizeof(ModelAnim) == 0x20, "ModelAnim size");
static_assert(offsetof(CheckInGate, material_anim) == 0x290, "material anim");
static_assert(offsetof(CheckInGate, light_materials) == 0x2b0, "light materials");
static_assert(offsetof(CheckInGate, door_box) == 0x2bc, "door box");
static_assert(offsetof(CheckInGate, boxes) == 0x358, "boxes");
static_assert(offsetof(CheckInGate, door_on) == 0x490, "door on");
static_assert(offsetof(CheckInGate, door_offset) == 0x494, "door offset");
static_assert(sizeof(CheckInGate) == 0x498, "the size CheckInGate_Create allocates");
static_assert(offsetof(CheckInGateHookState, hooks) == 0x0c, "hooks");
static_assert(offsetof(CheckInGateHookState, hook_timings) == 0x8c, "hook timings");
static_assert(offsetof(CheckInGateHookState, material) == 0xb0, "material result");
static_assert(offsetof(CheckInGateMaterialResult, polygon_attr) == 0x0c, "polygon attr");

#define CHECK_IN_GATE_ONE 0x1000 /* normal speed, and 1.0, in 20.12 fixed point */
#define CHECK_IN_GATE_LOOP 0
#define CHECK_IN_GATE_PLAY_ONCE FRAME_CTRL_ONCE

/* The joint and material animation each state plays (the same index of both). */
#define CHECK_IN_GATE_ANIM_CLOSED 0
#define CHECK_IN_GATE_ANIM_OPENING 1
#define CHECK_IN_GATE_ANIM_OPEN 2
#define CHECK_IN_GATE_ANIM_CLOSING 3

#define CHECK_IN_GATE_SOUND_OPENING 0x4eb
#define CHECK_IN_GATE_SOUND_CLOSING 0x4ec
#define CHECK_IN_GATE_SOUND_OPENING_LATE 0x4ed
#define CHECK_IN_GATE_SOUND_CLOSING_LATE 0x4ee
#define CHECK_IN_GATE_LATE_SOUND_FRAME 0x3a

/* The door: its offset closed and open, and how it eases between them each frame. */
#define CHECK_IN_GATE_DOOR_CLOSED 0
#define CHECK_IN_GATE_DOOR_OPEN (-0x2000)
#define CHECK_IN_GATE_DOOR_RATE 0x100
#define CHECK_IN_GATE_DOOR_MAX_STEP 0x1000
#define CHECK_IN_GATE_DOOR_UNSET (-1) /* the offset the start leaves */
/* The door's wall: flat, 0x8000 wide and 0x2000 high at (0x10000, 0, 0x10000 + offset). */
#define CHECK_IN_GATE_DOOR_X 0x10000
#define CHECK_IN_GATE_DOOR_Z 0x10000
#define CHECK_IN_GATE_DOOR_WIDTH 0x8000
#define CHECK_IN_GATE_DOOR_HEIGHT 0x2000

/* The two fixed boxes, at (0xb000, 0, 0x10800) and (0x15000, 0, 0x10800). */
#define CHECK_IN_GATE_BOX_WIDTH 0x2000
#define CHECK_IN_GATE_BOX_DEPTH 0x1c00
#define CHECK_IN_GATE_BOX_HEIGHT 0x2000
#define CHECK_IN_GATE_BOX0_X 0xb000
#define CHECK_IN_GATE_BOX1_X 0x15000
#define CHECK_IN_GATE_BOX_Z 0x10800

/* The scenes the start tests, and the kind of part 0x20 of data_021d27ac that keeps the gate
 * closed in scene 12. */
#define CHECK_IN_GATE_SCENE_11 11
#define CHECK_IN_GATE_SCENE_12 12
#define CHECK_IN_GATE_SCENE_13 13
#define CHECK_IN_GATE_SCENE_14 14
#define CHECK_IN_GATE_SCENE_47 47
#define CHECK_IN_GATE_PART20_KIND_CLOSED 1

/* The materials whose lights are set, and their count. */
#define CHECK_IN_GATE_GROUND_MATERIALS 7
/* POLYGON_ATTR's lights (bits 0-3). */
#define CHECK_IN_GATE_POLYGON_LIGHTS 0xfu

/* The material hook: the hours of the colour table, the result's colour and alpha bits, and
 * the render state's flag it clears (bit 8 of NNSG3dRS's flag). */
#define CHECK_IN_GATE_HOURS 24
#define CHECK_IN_GATE_MINUTES 60
#define CHECK_IN_GATE_CHANNEL 31
#define CHECK_IN_GATE_ALPHA_SHIFT 16
#define CHECK_IN_GATE_ALPHA_MASK 0x001f0000u
#define CHECK_IN_GATE_DIFFUSE_MASK 0x7fffu
#define CHECK_IN_GATE_RENDER_FLAG_8 0x100u

/* The model command with the hook, and when it runs (room_object_methods.h). */
#define CHECK_IN_GATE_G3D_MATERIAL 4
#define CHECK_IN_GATE_G3D_AFTER 2

/* The vtable slot that enters a state (CheckInGate_SetState). */
#define CHECK_IN_GATE_SLOT_SET_STATE 0x60

/* An hour of the colour table: the colour's channels (0-31) and the two alpha scales (1.0 is
 * 0x1000) for "m_lt" and for the other two materials. */
typedef struct CheckInGateHour {
    u8 red;
    u8 green;
    u8 blue;
    u8 pad_03;
    fx32 first_alpha; /* 0x04: "m_lt" */
    fx32 other_alpha; /* 0x08: "m_ltdoor" and "m_open" */
} CheckInGateHour;

static_assert(sizeof(CheckInGateHour) == 12, "an hour");

extern const CheckInGateHour data_ov004_02247784[CHECK_IN_GATE_HOURS];
/* The lights the seven materials get (3: lights 0 and 1). */
extern const u32 data_ov004_022478a4;
/* "m_grd_clf", "m_grd_g_s", "m_grd_grs", "m_grd_s_s", "m_grd_soi", "m_grd_clf2", "m_grd_clf3". */
extern const char *const data_ov004_02254e28[CHECK_IN_GATE_GROUND_MATERIALS];

/* The last one started. */
extern CheckInGate *data_ov004_0225827c;

/* The class's vtable. */
extern const u8 data_ov004_02254e4c[];

/* "/roomObj/obj_check_in.arc", "/roomObj/obj_check_in.nsbtx", "m_lt", "m_ltdoor", "m_open". */
extern const char data_ov004_02254eb4[];
extern const char data_ov004_02254ed0[];
extern const char data_ov004_02254eec[];
extern const char data_ov004_02254ef4[];
extern const char data_ov004_02254f00[];

extern Heap *data_021c9b24;
extern NetSession *data_020ccf94;

/* The function-local static points of the two fixed boxes: their guards, the points and their
 * destruction records. */
extern u32 data_ov004_02258298;
extern Vec3 data_ov004_022582a8;
extern u8 data_ov004_0225829c[];
extern u32 data_ov004_02258294;
extern Vec3 data_ov004_022582c0;
extern u8 data_ov004_022582b4[];

/* The state tables (member_pointer.h): their guards, the tables and their constants. */
extern u32 data_ov004_02258270;
extern MemberPointer data_ov004_022582cc[CHECK_IN_GATE_STATE_COUNT];
extern const MemberPointer data_ov004_02254d7c, data_ov004_02254d94, data_ov004_02254d9c, data_ov004_02254dac;
extern u32 data_ov004_02258274;
extern MemberPointer data_ov004_022582ec[CHECK_IN_GATE_STATE_COUNT];
extern const MemberPointer data_ov004_02254d84, data_ov004_02254d8c, data_ov004_02254db4, data_ov004_02254da4;

/* The RMO family's base class and holders (rmo_object.h). */
extern RmoObject *func_ov004_0222c7a0(RmoObject *object);
extern const u8 *func_ov004_0222c3c4(RmoModel *model, int index); /* a joint animation */
extern const u8 *func_ov004_0222c3b4(RmoModel *model, int index); /* a material animation */
extern int func_ov004_0222c3f4(RmoModel *model, const char *path);
extern u8 *func_ov004_0222c3a0(RmoModel *model);
extern void func_ov004_0222c3d4(RmoModel *model);
extern int func_ov004_0222c348(RmoTexture *texture, const char *path);
extern void *func_ov004_0222c33c(RmoTexture *texture);
extern void func_ov004_0222c340(RmoTexture *texture);

extern int NNS_G3dBindMdlTex(u8 *model, void *texture);
extern int NNS_G3dBindMdlPltt(u8 *model, void *texture);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern void __register_global_object(void *object, void *destruct, void *record);

/* The hooks are the game's functions: their addresses go into the model and the render state. */
extern void func_ov004_0222da90(CheckInGateHookState *state);
extern void func_ov004_0222daa0(CheckInGateHookState *state);
extern void func_020012dc(void *object); /* TrivialObject_Destruct */

static AnimatedModel *CheckInGate_body(CheckInGate *self)
{
    return (AnimatedModel *) (void *) &self->base.body;
}

static u8 *CheckInGate_state(CheckInGate *self)
{
    return &self->base.unk_24c[0];
}

/* Vtable slot 0x60 (CheckInGate_SetState for this class), called through the vtable. */
static int CheckInGate_call_set_state(CheckInGate *self, unsigned int state)
{
    const u32 *vtable = self->base.actor.vtable;
    return ((int (*)(CheckInGate *, unsigned int))(uintptr_t) vtable[CHECK_IN_GATE_SLOT_SET_STATE / 4])(self, state);
}

/* Joint and material animation `index` from their start, with the same flags. */
static void CheckInGate_play(CheckInGate *self, int index, int flags)
{
    AnimatedModel_Start(CheckInGate_body(self), func_ov004_0222c3c4(&self->base.body_model, index), flags, CHECK_IN_GATE_ONE,
                        0, 0);
    ModelRenderObject *render = ModelObject_RenderObject(&self->base.body.object);
    const u8 *material_anim = func_ov004_0222c3b4(&self->base.body_model, index);
    ModelAnim_Restart(&self->material_anim, render, material_anim, flags, CHECK_IN_GATE_ONE, 0);
}

/* Both animations step, and the material animation's object shows its frame.
 * REQUIRES: the material animation was allocated (its object is not NULL). */
static void CheckInGate_step(CheckInGate *self)
{
    AnimatedModel_StepFrames(CheckInGate_body(self));
    FrameCtrl_Step(&self->material_anim.ctrl);
    self->material_anim.anim->frame = self->material_anim.ctrl.frame;
}

/* The opening's or closing's step: the door eased towards `target`, then `next` once the joint
 * animation has run out, or `late_sound` when it passes frame 0x3a. */
static void CheckInGate_move(CheckInGate *self, fx32 target, unsigned int next, int late_sound)
{
    CheckInGate_step(self);
    int offset = self->door_offset;
    Approach_EaseS32(&offset, target, CHECK_IN_GATE_DOOR_RATE, CHECK_IN_GATE_DOOR_MAX_STEP);
    CheckInGate_SetDoor(self, offset);
    if (FrameCtrl_IsDone(&self->base.body.frames)) {
        CheckInGate_call_set_state(self, next);
    } else if (FrameCtrl_Passed(&self->base.body.frames, CHECK_IN_GATE_LATE_SOUND_FRAME)) {
        SoundSys_PlaySe(late_sound);
    }
}

/* func_ov004_0222ce1c (update of CHECK_IN_GATE_CLOSING) */
void CheckInGate_UpdateClosing(CheckInGate *self)
{
    CheckInGate_move(self, CHECK_IN_GATE_DOOR_CLOSED, CHECK_IN_GATE_CLOSED, CHECK_IN_GATE_SOUND_CLOSING_LATE);
}
CLEAN_AS(func_ov004_0222ce1c, CheckInGate_UpdateClosing)

/* func_ov004_0222cea8 (entry of CHECK_IN_GATE_CLOSING): the closing played once, with its
 * sound. */
int CheckInGate_EnterClosing(CheckInGate *self)
{
    CheckInGate_play(self, CHECK_IN_GATE_ANIM_CLOSING, CHECK_IN_GATE_PLAY_ONCE);
    SoundSys_PlaySe(CHECK_IN_GATE_SOUND_CLOSING);
    return 1;
}
CLEAN_AS(func_ov004_0222cea8, CheckInGate_EnterClosing)

/* func_ov004_0222cf18 (update of CHECK_IN_GATE_OPEN): the door's wall stands open only in
 * scene 11. */
void CheckInGate_UpdateOpen(CheckInGate *self)
{
    CheckInGate_step(self);
    if (SceneQuery_Current() == CHECK_IN_GATE_SCENE_11) {
        CheckInGate_SetDoor(self, CHECK_IN_GATE_DOOR_OPEN);
    }
}
CLEAN_AS(func_ov004_0222cf18, CheckInGate_UpdateOpen)

/* func_ov004_0222cf5c (entry of CHECK_IN_GATE_OPEN): the open animations looped. */
int CheckInGate_EnterOpen(CheckInGate *self)
{
    CheckInGate_play(self, CHECK_IN_GATE_ANIM_OPEN, CHECK_IN_GATE_LOOP);
    return 1;
}
CLEAN_AS(func_ov004_0222cf5c, CheckInGate_EnterOpen)

/* func_ov004_0222cfbc (update of CHECK_IN_GATE_OPENING) */
void CheckInGate_UpdateOpening(CheckInGate *self)
{
    CheckInGate_move(self, CHECK_IN_GATE_DOOR_OPEN, CHECK_IN_GATE_OPEN, CHECK_IN_GATE_SOUND_OPENING_LATE);
}
CLEAN_AS(func_ov004_0222cfbc, CheckInGate_UpdateOpening)

/* func_ov004_0222d04c (entry of CHECK_IN_GATE_OPENING): the opening played once, with its
 * sound. */
int CheckInGate_EnterOpening(CheckInGate *self)
{
    CheckInGate_play(self, CHECK_IN_GATE_ANIM_OPENING, CHECK_IN_GATE_PLAY_ONCE);
    SoundSys_PlaySe(CHECK_IN_GATE_SOUND_OPENING);
    return 1;
}
CLEAN_AS(func_ov004_0222d04c, CheckInGate_EnterOpening)

/* func_ov004_0222d0bc (update of CHECK_IN_GATE_CLOSED): the door's wall stands closed. */
void CheckInGate_UpdateClosed(CheckInGate *self)
{
    CheckInGate_step(self);
    CheckInGate_SetDoor(self, CHECK_IN_GATE_DOOR_CLOSED);
}
CLEAN_AS(func_ov004_0222d0bc, CheckInGate_UpdateClosed)

/* func_ov004_0222d0f4 (entry of CHECK_IN_GATE_CLOSED): the closed animations looped. */
int CheckInGate_EnterClosed(CheckInGate *self)
{
    CheckInGate_play(self, CHECK_IN_GATE_ANIM_CLOSED, CHECK_IN_GATE_LOOP);
    return 1;
}
CLEAN_AS(func_ov004_0222d0f4, CheckInGate_EnterClosed)

/* _ZN18Obj_ov004_02254e4c19func_ov004_0222d154Ev: the state's update, through its table; a
 * state byte of 4 or more runs none. */
void CheckInGate_UpdateState(CheckInGate *self)
{
    static const MemberPointer *const updates[CHECK_IN_GATE_STATE_COUNT] = {
        &data_ov004_02254d7c, /* CheckInGate_UpdateClosed */
        &data_ov004_02254d94, /* CheckInGate_UpdateOpening */
        &data_ov004_02254d9c, /* CheckInGate_UpdateOpen */
        &data_ov004_02254dac, /* CheckInGate_UpdateClosing */
    };
    MemberTable_InitOnce(&data_ov004_02258270, data_ov004_022582cc, updates, CHECK_IN_GATE_STATE_COUNT);
    u8 state = *CheckInGate_state(self);
    if (state < CHECK_IN_GATE_STATE_COUNT) {
        MemberPointer_CallVoid(&data_ov004_022582cc[state], self);
    }
}
CLEAN_AS(_ZN18Obj_ov004_02254e4c19func_ov004_0222d154Ev, CheckInGate_UpdateState)

/* func_ov004_0222d1e0 (vtable slot 0x60): enters `state` if its entry (through a table)
 * agrees; whether it did. */
int CheckInGate_SetState(CheckInGate *self, unsigned int state)
{
    static const MemberPointer *const entries[CHECK_IN_GATE_STATE_COUNT] = {
        &data_ov004_02254d84, /* CheckInGate_EnterClosed */
        &data_ov004_02254d8c, /* CheckInGate_EnterOpening */
        &data_ov004_02254db4, /* CheckInGate_EnterOpen */
        &data_ov004_02254da4, /* CheckInGate_EnterClosing */
    };
    MemberTable_InitOnce(&data_ov004_02258274, data_ov004_022582ec, entries, CHECK_IN_GATE_STATE_COUNT);
    if (state < CHECK_IN_GATE_STATE_COUNT && MemberPointer_CallInt(&data_ov004_022582ec[state], self) != 0) {
        *CheckInGate_state(self) = (u8) state;
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov004_0222d1e0, CheckInGate_SetState)

/* func_ov004_0222d280: the door's wall taken off the field when it is on it. */
void CheckInGate_RemoveDoorBox(CheckInGate *self)
{
    if (self->door_box.active != 0) {
        CollisionBox_Remove(&self->door_box);
    }
}
CLEAN_AS(func_ov004_0222d280, CheckInGate_RemoveDoorBox)

/* func_ov004_0222d2a4 (after the state's update): the door's wall taken off the field, then
 * put back at the door's offset when the update set it up. */
void CheckInGate_UpdateDoorBox(CheckInGate *self)
{
    CheckInGate_RemoveDoorBox(self);
    if (self->door_on != 0) {
        Vec3 position;
        position.x = CHECK_IN_GATE_DOOR_X;
        position.y = 0;
        position.z = (fx32) ((u32) self->door_offset + CHECK_IN_GATE_DOOR_Z);
        CollisionBox_Add(&self->door_box, CHECK_IN_GATE_DOOR_WIDTH, 0, CHECK_IN_GATE_DOOR_HEIGHT, &position, 0, NULL);
    }
}
CLEAN_AS(func_ov004_0222d2a4, CheckInGate_UpdateDoorBox)

/* func_ov004_0222d30c: the door's wall stands this frame at `offset`. */
void CheckInGate_SetDoor(CheckInGate *self, fx32 offset)
{
    self->door_on = 1;
    self->door_offset = offset;
}
CLEAN_AS(func_ov004_0222d30c, CheckInGate_SetDoor)

/* func_ov004_0222d320 (before the state's update): no door's wall unless the update sets it. */
CheckInGate *CheckInGate_ClearDoor(CheckInGate *self)
{
    self->door_on = 0;
    return self;
}
CLEAN_AS(func_ov004_0222d320, CheckInGate_ClearDoor)

/* (1.0 - t) * from + t * to, in 20.12 fixed point.
 * QUIRK: the products and the sum wrap at 32 bits, as the ROM's multiplications do. */
static s32 CheckInGate_blend(s32 from, s32 to, fx32 t)
{
    u32 sum = ((u32) CHECK_IN_GATE_ONE - (u32) t) * (u32) from + (u32) t * (u32) to;
    return (s32) sum >> 12;
}

/* func_ov004_0222d32c (the material hook): for "m_lt", "m_ltdoor" and "m_open", the colour of
 * the hour and the next blended by the minute becomes the material's diffuse colour, and its
 * alpha is scaled by the blended alpha scale of "m_lt" or of the other two (31 at most);
 * the render state's flag 8 is cleared.
 * QUIRK: a channel is truncated to 8 bits, not 5, before it is shifted into place, so one over
 * 31 runs into the next (the table's never are); the colour is truncated to 16 bits and its
 * bit 15 still reaches the result's word. */
void CheckInGate_MaterialHook(CheckInGate *self, int material, CheckInGateHookState *state)
{
    Time now;
    Calendar_Now(&now);
    u8 hour = now.hour;
    fx32 t = FX_Div((fx32) now.minute << 12, CHECK_IN_GATE_MINUTES << 12);
    const CheckInGateHour *next = &data_ov004_02247784[(u8) ((hour + 1) % CHECK_IN_GATE_HOURS)];
    const CheckInGateHour *current = &data_ov004_02247784[(u8) (hour % CHECK_IN_GATE_HOURS)];

    u8 red = (u8) CheckInGate_blend(current->red, next->red, t);
    u8 green = (u8) CheckInGate_blend(current->green, next->green, t);
    u8 blue = (u8) CheckInGate_blend(current->blue, next->blue, t);
    u16 colour = (u16) ((u32) red | (u32) green << 5 | (u32) blue << 10);
    fx32 other_alpha = CheckInGate_blend(current->other_alpha, next->other_alpha, t);
    fx32 first_alpha = CheckInGate_blend(current->first_alpha, next->first_alpha, t);

    if (material != self->light_materials[0] && material != self->light_materials[1] && material != self->light_materials[2]) {
        return;
    }
    u32 alpha = (state->material->polygon_attr >> CHECK_IN_GATE_ALPHA_SHIFT) & CHECK_IN_GATE_CHANNEL;
    fx32 scale = material == self->light_materials[0] ? first_alpha : other_alpha;
    alpha = (u32) (FX_MulFunc((fx32) (alpha << 12), scale) >> 12) & CHECK_IN_GATE_CHANNEL;
    state->material->polygon_attr &= ~CHECK_IN_GATE_ALPHA_MASK;
    state->material->polygon_attr |= alpha << CHECK_IN_GATE_ALPHA_SHIFT;
    state->flags &= ~CHECK_IN_GATE_RENDER_FLAG_8;
    state->material->diffuse &= ~CHECK_IN_GATE_DIFFUSE_MASK;
    state->material->diffuse |= colour;
}
CLEAN_AS(func_ov004_0222d32c, CheckInGate_MaterialHook)

/* func_ov004_0222d4d4: whether the last one started is open. */
int CheckInGate_IsOpen(void)
{
    return data_ov004_0225827c != NULL && *CheckInGate_state(data_ov004_0225827c) == CHECK_IN_GATE_OPEN;
}
CLEAN_AS(func_ov004_0222d4d4, CheckInGate_IsOpen)

/* func_ov004_0222d4f4: the last one started closing (vtable slot 0x60); its answer, 0 for
 * none. */
int CheckInGate_Close(void)
{
    CheckInGate *gate = data_ov004_0225827c;
    if (gate != NULL) {
        return CheckInGate_call_set_state(gate, CHECK_IN_GATE_CLOSING);
    }
    return 0;
}
CLEAN_AS(func_ov004_0222d4f4, CheckInGate_Close)

/* func_ov004_0222d518: the last one started opening (vtable slot 0x60); its answer, 0 for
 * none. */
int CheckInGate_Open(void)
{
    CheckInGate *gate = data_ov004_0225827c;
    if (gate != NULL) {
        return CheckInGate_call_set_state(gate, CHECK_IN_GATE_OPENING);
    }
    return 0;
}
CLEAN_AS(func_ov004_0222d518, CheckInGate_Open)

/* func_ov004_0222d53c */
void CheckInGate_SetCurrent(CheckInGate *gate)
{
    data_ov004_0225827c = gate;
}
CLEAN_AS(func_ov004_0222d53c, CheckInGate_SetCurrent)

/* func_ov004_0222d548: when there is a first material animation and the heap has room for its
 * object, it is started looped and attached to the model; whether it was. */
int CheckInGate_StartMaterialAnim(CheckInGate *self)
{
    if (func_ov004_0222c3b4(&self->base.body_model, 0) == NULL ||
        ModelAnim_AllocMaterialAnim(&self->material_anim, self->base.body.object.model, data_021c9b24) == 0) {
        return 0;
    }
    ModelAnim_Start(&self->material_anim, func_ov004_0222c3b4(&self->base.body_model, 0), CHECK_IN_GATE_LOOP,
                    CHECK_IN_GATE_ONE, 0);
    ModelAnim_Attach(&self->material_anim, ModelObject_RenderObject(&self->base.body.object));
    return 1;
}
CLEAN_AS(func_ov004_0222d548, CheckInGate_StartMaterialAnim)

/* func_ov004_0222d5c0: when there is a first joint animation that the model can take, it is
 * started looped and attached; whether it was. */
int CheckInGate_StartJointAnim(CheckInGate *self)
{
    if (func_ov004_0222c3c4(&self->base.body_model, 0) == NULL ||
        AnimatedModel_LoadAnim(CheckInGate_body(self), data_021c9b24) == 0) {
        return 0;
    }
    AnimatedModel_Start(CheckInGate_body(self), func_ov004_0222c3c4(&self->base.body_model, 0), CHECK_IN_GATE_LOOP,
                        CHECK_IN_GATE_ONE, 0, 0);
    AnimatedModel_Attach(CheckInGate_body(self));
    return 1;
}
CLEAN_AS(func_ov004_0222d5c0, CheckInGate_StartJointAnim)

/* func_ov004_0222d624: the seven ground materials take the overlay's lights (bits 0-3 of
 * their polygon attributes and of the mask that says which bits are the material's).
 * BUG: a material the model lacks (index -1) is not skipped: the word before the dictionary's
 * first entry is taken for a record's offset and that address written; the test of the
 * record's address against NULL never fails for a real model. */
void CheckInGate_LightMaterials(CheckInGate *self)
{
    u8 *model = func_ov004_0222c3a0(&self->base.body_model);
    uintptr_t materials = (uintptr_t) model + *(const u32 *) (const void *) (model + 8);
    u32 lights = data_ov004_022478a4;
    for (unsigned int i = 0; i < CHECK_IN_GATE_GROUND_MATERIALS; i++) {
        int index = G3dRes_MaterialIndex(func_ov004_0222c3a0(&self->base.body_model), data_ov004_02254e28[i]);
        /* the dictionary after the 4-byte header: its entries start at its halfword 6 */
        uintptr_t entries = materials + 4 + *(const u16 *) (uintptr_t) (materials + 0x0a);
        u16 unit = *(const u16 *) entries;
        uintptr_t row = entries + (u32) unit * (u32) index;
        uintptr_t record = materials + *(const u32 *) (row + 4);
        if (record != 0) {
            G3dResMaterial *data = (G3dResMaterial *) record;
            data->poly_attr_mask = (data->poly_attr_mask & ~CHECK_IN_GATE_POLYGON_LIGHTS) | lights;
            data->poly_attr = (data->poly_attr & ~CHECK_IN_GATE_POLYGON_LIGHTS) | lights;
        }
    }
}
CLEAN_AS(func_ov004_0222d624, CheckInGate_LightMaterials)

/* func_ov004_0222d69c: the model's textures and palettes bound from the field's ground texture,
 * then from its own (the later binding wins where both have a name). */
int CheckInGate_BindTextures(CheckInGate *self)
{
    u8 *model = func_ov004_0222c3a0(&self->base.body_model);
    NNS_G3dBindMdlTex(model, (void *) (uintptr_t) BgModels_GroundTexture((const BgModels *) (uintptr_t) BgModels_Get()));
    model = func_ov004_0222c3a0(&self->base.body_model);
    NNS_G3dBindMdlPltt(model, (void *) (uintptr_t) BgModels_GroundTexture((const BgModels *) (uintptr_t) BgModels_Get()));
    model = func_ov004_0222c3a0(&self->base.body_model);
    NNS_G3dBindMdlTex(model, func_ov004_0222c33c(&self->base.body_texture));
    model = func_ov004_0222c3a0(&self->base.body_model);
    NNS_G3dBindMdlPltt(model, func_ov004_0222c33c(&self->base.body_texture));
    return 1;
}
CLEAN_AS(func_ov004_0222d69c, CheckInGate_BindTextures)

/* func_ov004_0222d71c (vtable slot 0x0c): the model and texture released and every box taken
 * off the field.
 * QUIRK: it stays the last one started (data_ov004_0225827c is not cleared; nothing but
 * overlay 4's loading clears it). */
int CheckInGate_Release(CheckInGate *self)
{
    func_ov004_0222c3d4(&self->base.body_model);
    func_ov004_0222c340(&self->base.body_texture);
    CheckInGate_RemoveDoorBox(self);
    CollisionBox_Remove(&self->boxes[0]);
    CollisionBox_Remove(&self->boxes[1]);
    return 1;
}
CLEAN_AS(func_ov004_0222d71c, CheckInGate_Release)

/* func_ov004_0222d760 (vtable slot 0x24) */
int CheckInGate_Draw(CheckInGate *self)
{
    AnimatedModel_Draw(CheckInGate_body(self), NULL);
    return 1;
}
CLEAN_AS(func_ov004_0222d760, CheckInGate_Draw)

/* _ZN18Obj_ov004_02254e4c19func_ov004_0222d774Ev (vtable slot 0x18): the state's update
 * between clearing the door's wall and putting it where the update set it. */
int CheckInGate_Update(CheckInGate *self)
{
    CheckInGate_ClearDoor(self);
    CheckInGate_UpdateState(self);
    CheckInGate_UpdateDoorBox(self);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov004_02254e4c19func_ov004_0222d774Ev, CheckInGate_Update)

/* A fixed box's point, built once as a function-local static and registered for destruction
 * (func_020012dc, which does nothing). */
static void CheckInGate_point_once(u32 *guard, Vec3 *point, u8 *record, fx32 x)
{
    if ((*guard & 1) == 0) {
        point->x = x;
        point->y = 0;
        point->z = CHECK_IN_GATE_BOX_Z;
        __register_global_object(point, (void *) (uintptr_t) func_020012dc, record);
        *guard |= 1;
    }
}

/* func_ov004_0222d790 (vtable slot 0x00): the model and texture loaded and set up, the three
 * materials found, the material hook set (CheckInGate_SetModelHooks), the animations started;
 * then the gate's state from the scene: in scene 11 open when this system's slot of the session
 * is taken, else closed; in scene 12 closed when part 0x20 of data_021d27ac has kind 1, else
 * open; in scenes 13, 14 and 47 open; in others the state stays as the allocation zeroed it
 * (closed, its entry not run). It becomes the last one started, and its fixed boxes go on the
 * field. */
int CheckInGate_Start(CheckInGate *self)
{
    Block021d27acPart20 *part = (Block021d27acPart20 *) (void *) Block021d27ac_Part20(Block021d27ac_Get());
    func_ov004_0222c3f4(&self->base.body_model, data_ov004_02254eb4);
    func_ov004_0222c348(&self->base.body_texture, data_ov004_02254ed0);
    ModelObject_SetModel(&self->base.body.object, func_ov004_0222c3a0(&self->base.body_model), NULL);
    self->light_materials[0] = G3dRes_MaterialIndex(func_ov004_0222c3a0(&self->base.body_model), data_ov004_02254eec);
    self->light_materials[1] = G3dRes_MaterialIndex(func_ov004_0222c3a0(&self->base.body_model), data_ov004_02254ef4);
    self->light_materials[2] = G3dRes_MaterialIndex(func_ov004_0222c3a0(&self->base.body_model), data_ov004_02254f00);
    ModelObject_SetInitHook(&self->base.body.object, (void *) (uintptr_t) func_ov004_0222da90, self);
    CheckInGate_BindTextures(self);
    CheckInGate_LightMaterials(self);
    CheckInGate_StartJointAnim(self);
    CheckInGate_StartMaterialAnim(self);

    switch (SceneQuery_Current()) {
        case CHECK_IN_GATE_SCENE_11:
            if (Session_IsSlotTaken(data_020ccf94, data_020ccf94->local_slot)) {
                CheckInGate_call_set_state(self, CHECK_IN_GATE_OPEN);
            } else {
                CheckInGate_call_set_state(self, CHECK_IN_GATE_CLOSED);
            }
            break;
        case CHECK_IN_GATE_SCENE_12:
            if (Block021d27acPart20_Kind(part) == CHECK_IN_GATE_PART20_KIND_CLOSED) {
                CheckInGate_call_set_state(self, CHECK_IN_GATE_CLOSED);
            } else {
                CheckInGate_call_set_state(self, CHECK_IN_GATE_OPEN);
            }
            break;
        case CHECK_IN_GATE_SCENE_13:
        case CHECK_IN_GATE_SCENE_14:
        case CHECK_IN_GATE_SCENE_47:
            CheckInGate_call_set_state(self, CHECK_IN_GATE_OPEN);
            break;
    }

    CheckInGate_SetCurrent(self);
    self->door_offset = CHECK_IN_GATE_DOOR_UNSET;
    CheckInGate_point_once(&data_ov004_02258298, &data_ov004_022582a8, data_ov004_0225829c, CHECK_IN_GATE_BOX0_X);
    CheckInGate_point_once(&data_ov004_02258294, &data_ov004_022582c0, data_ov004_022582b4, CHECK_IN_GATE_BOX1_X);
    CollisionBox_Add(&self->boxes[0], CHECK_IN_GATE_BOX_WIDTH, CHECK_IN_GATE_BOX_DEPTH, CHECK_IN_GATE_BOX_HEIGHT,
                     &data_ov004_022582a8, 0, NULL);
    CollisionBox_Add(&self->boxes[1], CHECK_IN_GATE_BOX_WIDTH, CHECK_IN_GATE_BOX_DEPTH, CHECK_IN_GATE_BOX_HEIGHT,
                     &data_ov004_022582c0, 0, NULL);
    return 1;
}
CLEAN_AS(func_ov004_0222d790, CheckInGate_Start)

/* The parts taken down in the reverse of their construction. */
static void CheckInGate_take_down(CheckInGate *self)
{
    self->base.actor.vtable = data_ov004_02254e4c;
    CollisionBox_Destruct(&self->boxes[1]);
    CollisionBox_Destruct(&self->boxes[0]);
    CollisionBox_Destruct(&self->door_box);
    ModelAnim_DestructComplete(&self->material_anim);
    func_ov004_0222c7a0(&self->base);
}

/* func_ov004_0222d9ac (the deleting destructor, vtable slot 0x44) */
CheckInGate *CheckInGate_Delete(CheckInGate *self)
{
    CheckInGate_take_down(self);
    Heap_FreeAux(self);
    return self;
}
CLEAN_AS(func_ov004_0222d9ac, CheckInGate_Delete)

/* func_ov004_0222d9fc (the destructor, vtable slot 0x40) */
CheckInGate *CheckInGate_Destruct(CheckInGate *self)
{
    CheckInGate_take_down(self);
    return self;
}
CLEAN_AS(func_ov004_0222d9fc, CheckInGate_Destruct)

/* func_ov004_0222da48 (the constructor). Its state and door are left as the allocation zeroed
 * them. */
CheckInGate *CheckInGate_Construct(CheckInGate *self)
{
    RmoObjectBase_Construct(&self->base);
    self->base.actor.vtable = data_ov004_02254e4c;
    ModelAnim_Construct(&self->material_anim);
    CollisionBox_Construct(&self->door_box);
    CollisionBox_Construct(&self->boxes[0]);
    CollisionBox_Construct(&self->boxes[1]);
    return self;
}
CLEAN_AS(func_ov004_0222da48, CheckInGate_Construct)

/* func_ov004_0222da90 (the model's init hook, given by ModelObject_SetInitHook): the material
 * hook, run after each material's command. */
void CheckInGate_SetModelHooks(CheckInGateHookState *state)
{
    state->hooks[CHECK_IN_GATE_G3D_MATERIAL] = (u32) (uintptr_t) func_ov004_0222daa0;
    state->hook_timings[CHECK_IN_GATE_G3D_MATERIAL] = CHECK_IN_GATE_G3D_AFTER;
}
CLEAN_AS(func_ov004_0222da90, CheckInGate_SetModelHooks)

/* func_ov004_0222daa0: a material's hook: CheckInGate_MaterialHook of the model's object with
 * the material (byte 1 of the command); nothing without an object. */
void CheckInGate_RunMaterialHook(CheckInGateHookState *state)
{
    CheckInGate *gate = state->render_object->user;
    if (gate != NULL) {
        CheckInGate_MaterialHook(gate, state->command[1], state);
    }
}
CLEAN_AS(func_ov004_0222daa0, CheckInGate_RunMaterialHook)

/* func_ov004_0222dabc: a new one from the room's heap; nothing when it has no room. */
void CheckInGate_Create(void)
{
    CheckInGate *self = Heap_AllocAuxZeroed(sizeof(CheckInGate));
    if (self != NULL) {
        CheckInGate_Construct(self);
    }
}
CLEAN_AS(func_ov004_0222dabc, CheckInGate_Create)
