/* What each of the sky's objects does by its kind (sky_object_kinds.h). */
#include "sky_object_kinds.h"

#include "camera_control.h"
#include "clean.h"
#include "ov004/member_pointer.h"
#include "sky.h"
#include "sky_object_sounds.h"
#include "sky_resources.h"

static_assert(sizeof(SkyObjectBody) == sizeof(SkyObject), "the same object");
static_assert(offsetof(SkyObjectBody, anim) == offsetof(SkyObject, anim), "the animation");
static_assert(offsetof(SkyObjectBody, slot) == offsetof(SkyObject, slot), "the slot");
static_assert(offsetof(SkyObjectBody, distance) == 0x28, "the distance");
static_assert(offsetof(SkyObjectBody, forward) == 0x2e, "the direction");
static_assert(offsetof(SkyObjectBody, hidden) == offsetof(SkyObject, hidden), "hidden");
static_assert(offsetof(SkyObjectBody, position) == offsetof(SkyObject, position), "the position");
static_assert(offsetof(SkyObjectBody, velocity) == 0x40, "the velocity");
static_assert(offsetof(SkyObjectBody, scale_x) == offsetof(SkyObject, scale_x), "the scale");
static_assert(offsetof(SkyObjectBody, priority) == offsetof(SkyObject, priority), "the priority");
static_assert(offsetof(SkyObjectBody, palette) == offsetof(SkyObject, palette), "the palette");
static_assert(offsetof(SkyObjectBody, param) == offsetof(SkyObject, param), "the parameter");
static_assert(offsetof(SkyObjectBody, pull_x) == 0x6c, "the pull");
static_assert(offsetof(SkyObjectBody, shot_flags) == 0x68, "a shot's flags");
static_assert(sizeof(SkyAnimation) == 12, "an animation");

#define SKY_OBJECT_KINDS_FREE_SLOT SKY_SLOTS /* SkyObjectBody.slot of a free entry: none of the five */
#define SKY_OBJECT_KINDS_SCALE_ONE 0x1000
#define SKY_OBJECT_KINDS_SOUND_SOURCE 0 /* the sound source of an object's sounds */
#define SKY_KIND12_ANIMATION 0x2c
#define SKY_KIND12_PRIORITY 2
#define SKY_KIND12_DELAY 20 /* frames before it moves, plus data_020d22c4's */
#define SKY_KIND12_SOUND_SOURCE 7
#define SKY_KIND12_SOUND 0x805
#define SKY_KIND12_DRAG 0xfc3 /* the velocity kept each frame */

extern SkyObjectSounds data_021fbb14; /* the sounds of the sky's objects */
extern SkyObjectSlot data_021fa678[]; /* the objects' slots */
extern const SkyAnimation data_020e7880[];
extern const s8 data_020d22c4[4]; /* kind 12: frames more before it moves, by its parameter */
extern const Vec3 data_021fbee8;  /* the origin */
extern const Vec3 data_021c67d0;  /* the point the camera looks at */
extern CameraControl *data_021c67a4;
extern const fx32 data_020ca0ec; /* an acre's width in world units */
extern const fx32 data_020ca0e8; /* and depth */
extern s32 data_021f6cdc;        /* the path's length: six acres' width */
extern const fx16 FX_SinCosTable_[4096 * 2];

extern u32 data_021f6cc8, data_021f6cd4, data_021f6cd0; /* the tables below were filled */
extern MemberPointer data_021f6d98[SKY_OBJECT_KINDS];   /* take down, by kind */
extern MemberPointer data_021f6e68[SKY_OBJECT_KINDS];   /* run */
extern MemberPointer data_021f6e00[SKY_OBJECT_KINDS];   /* set up */
extern const MemberPointer data_020e5ca0, data_020e5d20, data_020e5a60, data_020e5c88, data_020e5c80, data_020e5c78,
    data_020e5c70, data_020e59b8, data_020e5c60, data_020e5a90, data_020e5c50, data_020e5c48, data_020e5c40;
extern const MemberPointer data_020e5c90, data_020e5a80, data_020e5be8, data_020e5ca8, data_020e5cf8, data_020e5d00,
    data_020e5cb0, data_020e5b70, data_020e59f8, data_020e5d68, data_020e5ad8, data_020e5ae0, data_020e5d18;
extern const MemberPointer data_020e5d88, data_020e5b58, data_020e5a50, data_020e5d70, data_020e5bf0, data_020e5a58,
    data_020e5c38, data_020e5a30, data_020e5b48, data_020e5d40, data_020e59c8, data_020e5ae8, data_020e5a78;

extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern fx32 FX_InvA(fx32 x);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *sum);
extern u32 func_020644cc(int bound);       /* a random number below `bound` */
extern u32 func_020644b4(int bound);       /* the same from another generator */
extern void func_0208a1f8(CellAnim *anim); /* an animation's constructor */
extern void func_0208a1f0(CellAnim *anim, const SkyAnimation *data);
extern void func_0208a1ec(CellAnim *anim, int hold);
extern void *func_0208a144(CellAnim *anim); /* started from the first frame */

static const MemberPointer *const sky_object_kinds_take_down_constants[SKY_OBJECT_KINDS] = {
    &data_020e5ca0, &data_020e5d20, &data_020e5a60, &data_020e5c88, &data_020e5c80, &data_020e5c78, &data_020e5c70,
    &data_020e59b8, &data_020e5c60, &data_020e5a90, &data_020e5c50, &data_020e5c48, &data_020e5c40,
};
static const MemberPointer *const sky_object_kinds_run_constants[SKY_OBJECT_KINDS] = {
    &data_020e5c90, &data_020e5a80, &data_020e5be8, &data_020e5ca8, &data_020e5cf8, &data_020e5d00, &data_020e5cb0,
    &data_020e5b70, &data_020e59f8, &data_020e5d68, &data_020e5ad8, &data_020e5ae0, &data_020e5d18,
};
static const MemberPointer *const sky_object_kinds_set_up_constants[SKY_OBJECT_KINDS] = {
    &data_020e5d88, &data_020e5b58, &data_020e5a50, &data_020e5d70, &data_020e5bf0, &data_020e5a58, &data_020e5c38,
    &data_020e5a30, &data_020e5b48, &data_020e5d40, &data_020e59c8, &data_020e5ae8, &data_020e5a78,
};

/* func_020bf220: sound `number` from source `index` of the objects' sounds, kept playing while
 * asked for, heard from the object's point without depth. */
void SkyObjectKinds_PlayHeldAt(SkyObject *object, int index, int number)
{
    Vec3 point;
    SkyObjectKinds_FlatPoint(object, &point);
    SkyObjectSounds_PlayHeld(&data_021fbb14, index, number, &point);
}
CLEAN_AS(func_020bf220, SkyObjectKinds_PlayHeldAt)

/* func_020bf248: sound `number` from the first source, heard from the object's point with its
 * depth. */
void SkyObjectKinds_Play(SkyObject *object, int number)
{
    Vec3 point;
    SkyObjectKinds_DepthPoint(object, &point);
    SkyObjectSounds_Play(&data_021fbb14, SKY_OBJECT_KINDS_SOUND_SOURCE, number, &point);
}
CLEAN_AS(func_020bf248, SkyObjectKinds_Play)

/* func_020bf26c: the same, kept playing while asked for. */
void SkyObjectKinds_PlayHeld(SkyObject *object, int number)
{
    Vec3 point;
    SkyObjectKinds_DepthPoint(object, &point);
    SkyObjectSounds_PlayHeld(&data_021fbb14, SKY_OBJECT_KINDS_SOUND_SOURCE, number, &point);
}
CLEAN_AS(func_020bf26c, SkyObjectKinds_PlayHeld)

/* func_020bf290: the object's point on the sky, at depth 0; 0. */
int SkyObjectKinds_FlatPoint(const SkyObject *object, Vec3 *point)
{
    point->x = object->position.x;
    point->y = object->position.y;
    point->z = 0;
    return 0;
}
CLEAN_AS(func_020bf290, SkyObjectKinds_FlatPoint)

/* func_020bf2a0: the object's point on the sky, its depth from its scale. */
void SkyObjectKinds_DepthPoint(const SkyObject *object, Vec3 *point)
{
    SkyObjectKinds_SoundPoint(point, object->position.x, object->position.y, object->scale_x);
}
CLEAN_AS(func_020bf2a0, SkyObjectKinds_DepthPoint)

/* func_020bf2b8: a point (x, y) with a depth from 0 to 1.0 by `scale` (the inverse of the
 * object's size, 1.0 to 4.0): (1 - scale / 4) / (scale - scale / 4). */
void SkyObjectKinds_SoundPoint(Vec3 *point, fx32 x, fx32 y, fx32 scale)
{
    fx32 quarter = FX_MulFunc(0x400, scale);
    fx32 whole = FX_MulFunc(0x1000, scale);
    fx32 depth = FX_Div(0x1000 - quarter, whole - quarter);
    if (depth < 0) {
        depth = 0;
    } else if (depth > 0x1000) {
        depth = 0x1000;
    }
    point->x = x;
    point->y = y;
    point->z = depth;
}
CLEAN_AS(func_020bf2b8, SkyObjectKinds_SoundPoint)

/* func_020bf3c8: the object placed at its distance along the path, one acre's depth north of
 * the town's edge. */
void SkyObjectKinds_PlaceOnPath(SkyObject *object, fx32 sway)
{
    Vec3 at = {SkyObject_Body(object)->distance, 0, data_020ca0e8};
    SkyObjectKinds_Place(object, &at, sway);
}
CLEAN_AS(func_020bf3c8, SkyObjectKinds_PlaceOnPath)

/* func_020bf3ec: the object placed on the sky for the world point `at`, from how far it is
 * from the point the camera looks at: `across` acres east and `away` four acres north (eased:
 * away * (2 - away)). Across the screen 256 pixels per acre from the middle, narrowing with
 * the distance north; from y 80 down to 160 at four acres, raised by the camera's value 0x1e8
 * the nearer it is; its size from 1.0 down to 0.25 there (the scale its inverse), bobbing by
 * `sway` times the sine of its phase, by its size.
 * QUIRK: x goes through FX_MulFunc by 1.0 (leaving it as it is) before it is scaled by 256. */
void SkyObjectKinds_Place(SkyObject *object, const Vec3 *at, fx32 sway)
{
    SkyObjectBody *body = SkyObject_Body(object);
    fx32 north = data_021c67d0.z - at->z;
    fx32 east = at->x - data_021c67d0.x;
    fx32 across = FX_Div(east, data_020ca0ec);
    fx32 away = FX_Div(north, (fx32) ((u32) data_020ca0e8 << 2));
    fx32 rest = FX_MulFunc(-0x1000, away - 0x1000);
    fx32 eased = FX_MulFunc(away, rest + 0x1000);
    fx32 width = FX_MulFunc(-0x666, eased) + 0xe66;
    fx32 x = FX_MulFunc(across, width) + 0x800;
    x = (fx32) ((u32) FX_MulFunc(x, 0x1000) << 8);
    fx32 y = FX_MulFunc(0x50000, eased) + 0x50000;
    fx32 nearness = 0x1000 - eased;
    fx32 lift = 0;
    if (data_021c67a4 != NULL) {
        lift = FX_MulFunc((fx32) CameraControl_Value1E8(), nearness);
    }
    lift = FX_MulFunc(lift, 0x10000);
    body->position.x = x;
    body->position.y = y - lift;
    body->position.z = 0;
    fx32 size = FX_MulFunc(-0xc00, eased) + 0x1000;
    if (size < 0x400) {
        size = 0x400;
    } else if (size > 0x1000) {
        size = 0x1000;
    }
    fx32 scale = FX_InvA(size);
    body->scale_x = scale;
    body->scale_y = scale;
    fx32 bob = FX_MulFunc(FX_MulFunc(FX_SinCosTable_[(body->phase >> 4) * 2], sway), size);
    body->position.y = body->position.y + bob;
}
CLEAN_AS(func_020bf3ec, SkyObjectKinds_Place)

/* func_020bf514: the object moved `step` along its path; until it passes an end its phase
 * moves on by `phase_step` and it is placed. Whether it passed the end. */
int SkyObjectKinds_Advance(SkyObject *object, int step, fx32 sway, int phase_step)
{
    SkyObjectBody *body = SkyObject_Body(object);
    int passed = 0;
    if (body->forward) {
        body->distance += step;
        if (body->distance > data_021f6cdc) {
            passed = 1;
        }
    } else {
        body->distance -= step;
        if (body->distance < 0) {
            passed = 1;
        }
    }
    if (!passed) {
        body->phase = (u16) (body->phase + phase_step);
        SkyObjectKinds_PlaceOnPath(object, sway);
    }
    return passed;
}
CLEAN_AS(func_020bf514, SkyObjectKinds_Advance)

/* func_020bf568: the object set at the west end of its path going east, or at the east end
 * going west, and placed. */
void SkyObjectKinds_StartPath(SkyObject *object, u8 forward, fx32 sway)
{
    SkyObjectBody *body = SkyObject_Body(object);
    body->forward = forward;
    body->distance = body->forward != 0 ? 0 : data_021f6cdc;
    SkyObjectKinds_PlaceOnPath(object, sway);
}
CLEAN_AS(func_020bf568, SkyObjectKinds_StartPath)

/* func_020bf590: the object taken down: its slot (when it needs one) has one user less, and
 * the entry is free. */
void SkyObjectKinds_Remove(SkyObject *object)
{
    int slot = object->slot;
    if (slot != SKY_OBJECT_NO_SLOT) {
        SkySlot_Release((SkyObjectSlot *) ((uintptr_t) data_021fa678 + (u32) slot * (u32) sizeof(SkyObjectSlot)));
    }
    SkyObjectKinds_Free(object);
}
CLEAN_AS(func_020bf590, SkyObjectKinds_Remove)

/* func_020bf5b8: the object's cell animation started from its entry of data_020e7880.
 * REQUIRES: the animation is one of the table's (below 0x2e). */
void SkyObjectKinds_StartAnimation(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    const SkyAnimation *animation = &data_020e7880[body->animation];
    func_0208a1f0(&body->anim, animation);
    func_0208a1ec(&body->anim, animation->hold);
    func_0208a144(&body->anim);
}
CLEAN_AS(func_020bf5b8, SkyObjectKinds_StartAnimation)

/* A member of a kind's table called on the object, when the kind has one. */
static void sky_object_kinds_call(const MemberPointer *table, SkyObject *object)
{
    MemberPointer member = table[object->kind];
    if (member.function != 0) {
        MemberPointer_CallVoid(&member, object);
    }
}

/* func_020bf5f0: the object taken down by its kind (data_021f6d98, filled once).
 * REQUIRES: the kind is 0 to 12. */
void SkyObjectKinds_TakeDown(SkyObject *object)
{
    MemberTable_InitOnce(&data_021f6cc8, data_021f6d98, sky_object_kinds_take_down_constants, SKY_OBJECT_KINDS);
    sky_object_kinds_call(data_021f6d98, object);
}
CLEAN_AS(func_020bf5f0, SkyObjectKinds_TakeDown)

/* func_020bf700: a frame of the object by its kind (data_021f6e68, filled once).
 * REQUIRES: the kind is 0 to 12. */
void SkyObjectKinds_Run(SkyObject *object)
{
    MemberTable_InitOnce(&data_021f6cd4, data_021f6e68, sky_object_kinds_run_constants, SKY_OBJECT_KINDS);
    sky_object_kinds_call(data_021f6e68, object);
}
CLEAN_AS(func_020bf700, SkyObjectKinds_Run)

/* func_020bf810: the object set up by its kind with the parameter it was added with
 * (data_021f6e00, filled once).
 * REQUIRES: the kind is 0 to 12. */
void SkyObjectKinds_SetUp(SkyObject *object, int param)
{
    MemberTable_InitOnce(&data_021f6cd0, data_021f6e00, sky_object_kinds_set_up_constants, SKY_OBJECT_KINDS);
    MemberPointer member = data_021f6e00[object->kind];
    if (member.function != 0) {
        void *self = MemberPointer_Object(&member, object);
        ((void (*)(void *, int))(uintptr_t) MemberPointer_Code(&member, self))(self, param);
    }
}
CLEAN_AS(func_020bf810, SkyObjectKinds_SetUp)

/* func_020bf924: the entry free: of the kind never drawn, no resource, no animation, outside
 * the five slots, at scale 1 unrotated. */
void SkyObjectKinds_Free(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    body->kind = SKY_OBJECT_UNDRAWN;
    body->state = SKY_OBJECT_FREE;
    body->resource = SKY_OBJECT_NO_RESOURCE;
    body->animation = SKY_ANIMATION_NONE;
    body->slot = SKY_OBJECT_KINDS_FREE_SLOT;
    body->scale_x = SKY_OBJECT_KINDS_SCALE_ONE;
    body->scale_y = SKY_OBJECT_KINDS_SCALE_ONE;
    body->rotation = 0;
}
CLEAN_AS(func_020bf924, SkyObjectKinds_Free)

/* func_020bf948: the object's fields reset: at the origin, still, at scale 1, going east, shown,
 * no palette, drawn behind everything (priority -1). */
void SkyObjectKinds_Reset(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    body->scale_x = SKY_OBJECT_KINDS_SCALE_ONE;
    body->scale_y = SKY_OBJECT_KINDS_SCALE_ONE;
    body->position.x = 0;
    body->position.y = 0;
    body->position.z = 0;
    body->velocity.x = 0;
    body->velocity.y = 0;
    body->velocity.z = 0;
    body->rotation = 0;
    body->distance = 0;
    body->phase = 0;
    body->forward = 1;
    body->can_hit = 0;
    body->hit = 0;
    body->hidden = 0;
    body->unk_56 = 0;
    body->unk_57 = 0;
    body->priority = -1;
    body->radius = 0;
    body->palette = -1;
    for (int i = 0; i < 5; i++) {
        body->words[i] = 0;
    }
}
CLEAN_AS(func_020bf948, SkyObjectKinds_Reset)

/* func_020bf9ac: an object's constructor (the entries', by __cxa_vec_ctor): its animation
 * constructed, its fields reset and the entry free. */
SkyObject *SkyObjectKinds_Construct(SkyObject *object)
{
    func_0208a1f8(&object->anim);
    SkyObjectKinds_Reset(object);
    SkyObjectKinds_Free(object);
    return object;
}
CLEAN_AS(func_020bf9ac, SkyObjectKinds_Construct)

/* func_020bf9cc: kind 12 taken down. */
void SkyKind12_TakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020bf9cc, SkyKind12_TakeDown)

/* func_020bf9d4: a frame of kind 12: it waits out its delay (the one of parameter 0 of every
 * four then plays sound 0x805 from source 7, at the origin); then it is pulled, slowed by drag
 * and moved, and done once out of view. */
void SkyKind12_Run(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    if (body->delay > 0) {
        body->delay--;
        if (body->delay > 0 || (body->param & 3) != 0) {
            return;
        }
        SkyObjectSounds_PlayHeld(&data_021fbb14, SKY_KIND12_SOUND_SOURCE, SKY_KIND12_SOUND, &data_021fbee8);
        return;
    }
    body->velocity.x += body->pull_x;
    body->velocity.y += body->pull_y;
    Vec_Scale(&body->velocity, SKY_KIND12_DRAG);
    VEC_Add(&body->position, &body->velocity, &body->position);
    if (SkyObject_OutOfView(&body->position)) {
        body->state = SKY_OBJECT_DONE;
    }
}
CLEAN_AS(func_020bf9d4, SkyKind12_Run)

/* func_020bfa88: kind 12 set up: its delay by the parameter, from x -8 at a random y of 144 to
 * 199, moving right (1.0 plus up to 8.0 at random) and down (2.0 less up to 2.0), pulled right
 * by 0x267 and up by 0x599 each frame. */
void SkyKind12_SetUp(SkyObject *object, int param)
{
    SkyObjectBody *body = SkyObject_Body(object);
    body->param = (u32) param;
    body->delay = data_020d22c4[param & 3] + SKY_KIND12_DELAY;
    body->animation = SKY_KIND12_ANIMATION;
    body->priority = SKY_KIND12_PRIORITY;
    fx32 y = (fx32) ((func_020644cc(0x38) + 0x90) << 12);
    body->position.x = -0x8000;
    body->position.y = y;
    body->position.z = 0;
    body->velocity.x = 0x1000;
    body->velocity.y = 0x2000;
    body->velocity.z = 0;
    body->velocity.x += (fx32) func_020644b4(0x8000);
    body->velocity.y -= (fx32) func_020644b4(0x2000);
    body->pull_x = -0x666 + 0x8cd;
    body->pull_y = 0xcd - 0x666;
}
CLEAN_AS(func_020bfa88, SkyKind12_SetUp)

/* func_020bfcb0: kind 10 taken down. */
void SkyKind10_TakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020bfcb0, SkyKind10_TakeDown)

#define SKY_KIND10_X 0xb0000 /* x 176 */
#define SKY_KIND10_Y 0x67000 /* y 103 */
#define SKY_KIND10_ANIMATION 0x15
#define SKY_KIND10_PRIORITY 3
#define SKY_KIND8_PRIORITY 2

extern int CellAnim_IsDone(CellAnim *anim);

/* func_020bfcb8: a frame of kind 10: nothing (called with the object, which it does not take). */
void SkyKind10_Run(void) {}
CLEAN_AS(func_020bfcb8, SkyKind10_Run)

/* func_020bfcbc: kind 10 set up at (176, 103). */
void SkyKind10_SetUp(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    body->position.x = SKY_KIND10_X;
    body->position.y = SKY_KIND10_Y;
    body->animation = SKY_KIND10_ANIMATION;
    body->priority = SKY_KIND10_PRIORITY;
}
CLEAN_AS(func_020bfcbc, SkyKind10_SetUp)

/* func_020c0420: kind 8 taken down. */
void SkyKind8_TakeDown(SkyObject *object)
{
    SkyObjectKinds_Remove(object);
}
CLEAN_AS(func_020c0420, SkyKind8_TakeDown)

/* func_020c0428: a frame of kind 8: done once its animation is. */
void SkyKind8_Run(SkyObject *object)
{
    if (CellAnim_IsDone(&object->anim)) {
        object->state = SKY_OBJECT_DONE;
    }
}
CLEAN_AS(func_020c0428, SkyKind8_Run)

/* func_020c0440: kind 8 set up at x 128 plus or less up to 127 and y 80 to 159, with one of
 * animations 8 to 15. */
void SkyKind8_SetUp(SkyObject *object)
{
    SkyObjectBody *body = SkyObject_Body(object);
    int across = (int) func_020644cc(0x80);
    across = across * ((int) func_020644cc(2) * 2 - 1) + 0x80;
    fx32 y = (fx32) ((func_020644cc(0x50) + 0x50) << 12);
    body->position.x = (fx32) ((u32) across << 12);
    body->position.y = y;
    body->position.z = 0;
    body->animation = (s32) func_020644cc(8) + 8;
    body->priority = SKY_KIND8_PRIORITY;
}
CLEAN_AS(func_020c0440, SkyKind8_SetUp)
