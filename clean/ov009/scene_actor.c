/* Overlay 9's scene actor: its sound emitter, what it tells of itself, its stand point and its
 * talk machine (scene_actor.h). */
#include "scene_actor.h"

#include <stdint.h>

#include "autoload_2/approach.h" /* Math_AbsDiff16 */
#include "autoload_2/fx_math.h"  /* Math_Atan2 */
#include "clean.h"
#include "itcm/vector.h" /* Vec_Add */
#include "ov004/member_pointer.h"
#include "scene_actor_files.h" /* SceneActor_DrawShadows */
#include "scene_actor_life.h"  /* SceneActor_Kind, SceneActor_UpdateModelMatrix, SceneActor_ViewRange* */

static_assert(offsetof(SceneActorSound, state.on) == 0x40, "sound on flag");
static_assert(sizeof(SceneActorSound) == 0x44, "sound size");
static_assert(offsetof(SceneActorLink, unk_10) == 0x10, "link word 0x10");
static_assert(offsetof(SceneActorArea, facing_x) == 0x28, "area facing x");
static_assert(offsetof(SceneActorArea, facing_z) == 0x30, "area facing z");
static_assert(offsetof(SceneActorArea, origin) == 0x3c, "area origin");
static_assert(sizeof(SceneActorArea) == 0x54, "area size");
static_assert(sizeof(SceneActorRecord) == 10, "record size");
static_assert(offsetof(SceneActor, position) == 0x5c, "position");
static_assert(offsetof(SceneActor, yaw) == 0x8e, "yaw");
static_assert(offsetof(SceneActor, receiver_vtable) == 0xec, "receiver");
static_assert(offsetof(SceneActor, message) == 0x10a, "receiver byte 0x1e");
static_assert(offsetof(SceneActor, link) == 0x12c, "link");
static_assert(offsetof(SceneActor, mode) == 0x134, "mode");
static_assert(offsetof(SceneActor, code) == 0x136, "code");
static_assert(offsetof(SceneActor, model_object) == 0x13c, "model object");
static_assert(offsetof(SceneActor, model) == 0x198, "model");
static_assert(offsetof(SceneActor, model_matrix) == 0x1a0, "model matrix");
static_assert(offsetof(SceneActor, member_1f4) == 0x1f4, "member 0x1f4");
static_assert(offsetof(SceneActor, tile_x) == 0x22c, "tile x");
static_assert(offsetof(SceneActor, tile_z) == 0x230, "tile z");
static_assert(offsetof(SceneActor, exit_step) == 0x234, "exit step");
static_assert(offsetof(SceneActor, flags_235) == 0x235, "flags 0x235");
static_assert(offsetof(SceneActor, flags) == 0x236, "flags");
static_assert(offsetof(SceneActor, visit_3) == 0x237, "visit 3");
static_assert(offsetof(SceneActor, sound) == 0x238, "sound");
static_assert(offsetof(SceneActor, state) == 0x27c, "state");
static_assert(offsetof(SceneActor, skip_visit) == 0x280, "skip visit");
static_assert(offsetof(SceneActor, frames) == 0x282, "frames");
static_assert(offsetof(SceneActor, areas) == 0x28c, "areas");
static_assert(offsetof(SceneActor, area_count) == 0x290, "area count");
static_assert(offsetof(SceneActor, talk_point) == 0x2a8, "talk point");
static_assert(sizeof(SceneActor) == 0x2b4, "size");

#define SCENE_ACTOR_RECEIVER_OFFSET 0xec

/* The special characters' codes and main's table of their records. */
#define SCENE_ACTOR_CODE_FIRST 0x5000
#define SCENE_ACTOR_CODE_LAST 0x5021

/* The codes the actor treats apart (what they are is not known yet). */
#define SCENE_ACTOR_CODE_NO_WAIT 0x500a /* no wait is set on the link when its message ends */

/* The scene events of vtable slot 0x4c. */
#define SCENE_ACTOR_EVENT_TALK 0
#define SCENE_ACTOR_EVENT_TALK_AGAIN 1
#define SCENE_ACTOR_EVENT_6 6
#define SCENE_ACTOR_EVENT_IDLE 8

/* Sounds play at this volume. */
#define SCENE_ACTOR_SOUND_VOLUME 0x7f

/* Vtable slots it calls. */
#define SLOT_TALK_POINT 0x50   /* SceneActor_TalkPointAddress */
#define SLOT_SET_MODE 0x6c     /* SceneActor_SetMode */
#define SLOT_PREPARE_TALK 0x78 /* SceneActor_PrepareTalk */
#define SLOT_TALK_OPEN 0x7c    /* SceneActor_OnTalkOpen */
#define SLOT_TALK_WAIT 0x80    /* SceneActor_OnTalkWait */
#define SLOT_TALK_CLOSED 0x84  /* SceneActor_OnTalkClosed */
#define SLOT_8C 0x8c
#define SLOT_STATE_38 0x90 /* SceneActor_WalksWithState38 */
#define SLOT_KEEP_X 0x94   /* SceneActor_KeepsPointX */

/* What SceneActor_GetStandPoint gives: a point 1.0 ahead of the first area, at height 0x200
 * and 0x200 back along z. */
#define SCENE_ACTOR_ONE 0x1000
#define SCENE_ACTOR_STAND_HEIGHT 0x200
#define SCENE_ACTOR_STAND_BACK 0x200

/* What SceneActor_CanTalkTo allows: a facing within 0x1000 of the actor's turned half round,
 * and for kind 0 a distance under 3.0. */
#define SCENE_ACTOR_TALK_ANGLE 0x1000
#define SCENE_ACTOR_TALK_DISTANCE 0x3000

/* The player kind of player state 0x39 SCENE_ACTOR_WALK_AGAIN asks for. */
#define SCENE_ACTOR_PLAYER_KIND 2
/* The player whose x SceneActor_KeepsPointX can ask for. */
#define SCENE_ACTOR_PLAYER 4

/* SCENE_ACTOR_GONE: the frames it waits, more for kind 1; what it registers. */
#define SCENE_ACTOR_GONE_WAIT 20
#define SCENE_ACTOR_GONE_WAIT_KIND_1 12
#define SCENE_ACTOR_GONE_AHEAD 0x1000
#define SCENE_ACTOR_GONE_ARG 0x0f000000

/* The sound emitter's vtable (kind 2). */
extern const u8 data_0213f090[];
/* "obj_etc_error": the receiver's name until a derived class gives it another. */
extern const char data_ov009_02265a18[];
/* The special characters' records, one per code from 0x5000. */
extern const SceneActorRecord data_020d1f24[];
/* The camera, while it exists, and its position. */
extern int data_021c67a4;
extern const Vec3 data_021c67d0;

/* The talk machine's tables (member_pointer.h): their guards, the tables and their
 * constants. */
extern u32 data_ov009_02265b28;
extern MemberPointer data_ov009_02265c6c[SCENE_ACTOR_STATES];
extern const MemberPointer data_ov009_02265810, data_ov009_022657c8, data_ov009_022657d8, data_ov009_022657e0,
    data_ov009_02265840, data_ov009_02265850, data_ov009_022657b8, data_ov009_022657a8, data_ov009_022657d0;
extern u32 data_ov009_02265b2c;
extern MemberPointer data_ov009_02265c24[SCENE_ACTOR_STATES];
extern const MemberPointer data_ov009_022657c0, data_ov009_022657f8, data_ov009_022657f0, data_ov009_02265898,
    data_ov009_02265808, data_ov009_02265820, data_ov009_02265828, data_ov009_02265848, data_ov009_02265888;

extern void func_0205510c(void *model_object, int arg);
/* The field actor asking a player to stand at a point (overlay 3, field_actor.h). */
int FieldActor_PlayerRequestState39(u32 kind, int *x, int *z, int yaw);
int FieldActor_PlayerRequestState38(int *x, int *z, short *yaw);
/* A player's position. */
extern const Vec3 *func_02095794(int player);
/* A record of data_020d1f24 copied out, two of its bytes, and the copy's (empty) destructor. */
extern void func_020b2a68(SceneActorRecord *dst, const SceneActorRecord *src);
extern int func_020b2a4c(SceneActorRecord *record);
extern int func_020b2a50(SceneActorRecord *record);
extern void func_020b2a64(SceneActorRecord *record);
/* Main's member object at 0x1f4: whether its first word is set. */
extern int func_020b3310(void *member);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
/* The point of an area. */
extern const Vec3 *func_02032754(SceneActorArea *area);
/* Copies at most 25 characters of `name` into the receiver's name. */
extern void func_020a8164(void *receiver, const char *name);
/* Whether a code is of the kind func_0204bc64 converts, and the conversion. */
extern int func_0204bcdc(u16 *code);
extern int func_0204bc64(u16 *code);
/* Sets the link's word at 0x10. */
extern void func_020676c4(SceneActorLink *link, int value);
/* The character's visit record: clearing bit `bit` of its flags, asking for it, its answer. */
extern void func_020b23ec(int code, int bit);
extern void func_020b248c(u16 code);
extern int func_020b2470(u16 code);
/* Main's byte at data_021f4b14 cleared; main's table at data_021f69d0 (func_020b5e10 gives
 * it), its neighbour at data_021f69b8 reset (func_020b5e90), whether the table takes `id`, and
 * adding to it; the scene; a height that is always 0x200; main's word at data_021f4b48. */
extern void func_020b23c8(void);
extern void *func_020b5e10(void);
extern void func_020b5e90(void);
extern int func_020b6098(void *table, int id);
extern int func_020b5ea0(void *table, int scene, Vec3 *point, int p3, short angle, int p5, int p6);
extern u8 func_020b65c4(void);
extern int func_020310c8(int value);
extern void func_020b22ac(int value);
/* Hands the receiver back, takes it, lets the scene go on, and what CanTalkTo runs. */
extern void func_0203ee08(SceneActor *actor, void *receiver);
extern void func_0203ee14(SceneActor *actor, void *receiver);
extern int func_0203e020(SceneActor *actor);
extern void func_0203edd0(SceneActor *actor);
extern int func_02096174(void);
extern int func_02096168(void);
extern void func_02095944(unsigned int arg);
extern void func_0203aec4(void);

/* The receiver part as C++ converts a pointer to the actor to it: NULL stays NULL. */
static void *scene_actor_receiver(SceneActor *actor)
{
    return actor != NULL ? (u8 *) actor + SCENE_ACTOR_RECEIVER_OFFSET : NULL;
}

/* The address of the function in vtable slot `offset`. */
static uintptr_t scene_actor_slot(const SceneActor *actor, u32 offset)
{
    return *(const u32 *) ((const u8 *) actor->vtable + offset);
}

typedef int (*SceneActorIntSlot)(SceneActor *actor);
typedef void (*SceneActorVoidSlot)(SceneActor *actor);
typedef int (*SceneActorModeSlot)(SceneActor *actor, int mode);

static int scene_actor_call_int(SceneActor *actor, u32 offset)
{
    return ((SceneActorIntSlot) scene_actor_slot(actor, offset))(actor);
}

static void scene_actor_call_void(SceneActor *actor, u32 offset)
{
    ((SceneActorVoidSlot) scene_actor_slot(actor, offset))(actor);
}

static int scene_actor_set_mode(SceneActor *actor, int mode)
{
    return ((SceneActorModeSlot) scene_actor_slot(actor, SLOT_SET_MODE))(actor, mode);
}

/* The character's record: the code's, or the first for a code out of range. */
static const SceneActorRecord *scene_actor_record(const SceneActor *actor)
{
    u32 code = actor->code;
    if (code >= SCENE_ACTOR_CODE_FIRST && code <= SCENE_ACTOR_CODE_LAST) {
        return &data_020d1f24[code - SCENE_ACTOR_CODE_FIRST];
    }
    return &data_020d1f24[0];
}

/* Whether `*code` is `value`, through func_0204bc64 when func_0204bcdc says it converts. */
static int scene_actor_code_is(u16 *code, u16 value)
{
    if (func_0204bcdc(code) != 0) {
        u16 other = value;
        int converted = func_0204bc64(code);
        return converted == func_0204bc64(&other);
    }
    return *code == value;
}

/* func_ov009_02262ec0 (vtable slot 0xb8): always 0. */
int SceneActor_SlotB8(SceneActor *actor)
{
    (void) actor;
    return 0;
}
CLEAN_AS(func_ov009_02262ec0, SceneActor_SlotB8)

/* func_ov009_02262ec4 (vtable slot 0xb4, returning a Vec3): its position. */
void SceneActor_Position(Vec3 *out, SceneActor *actor)
{
    out->x = actor->position.x;
    out->y = actor->position.y;
    out->z = actor->position.z;
}
CLEAN_AS(func_ov009_02262ec4, SceneActor_Position)

/* func_ov009_02262ed4: while the emitter is on, plays sound `number` through the sound
 * layer's other entry, at volume 0x7f. */
void SceneActorSound_PlayEx(SceneActorSound *sound, int number)
{
    if (sound->state.on) {
        SoundEmitter_PlayEx(&sound->emitter, number, SCENE_ACTOR_SOUND_VOLUME, 0);
    }
}
CLEAN_AS(func_ov009_02262ed4, SceneActorSound_PlayEx)

/* func_ov009_02262ef0: while the emitter is on, plays sound `number` at volume 0x7f. */
void SceneActorSound_Play(SceneActorSound *sound, int number)
{
    if (sound->state.on) {
        SoundEmitter_PlayB(&sound->emitter, number, SCENE_ACTOR_SOUND_VOLUME, 0);
    }
}
CLEAN_AS(func_ov009_02262ef0, SceneActorSound_Play)

/* func_ov009_02262f0c: turns the emitter off, through its slot 0x10, when it is on. */
void SceneActorSound_TurnOff(SceneActorSound *sound)
{
    if (sound->state.on) {
        SoundEmitter_Vfunc10B(&sound->emitter);
        sound->state.on = 0;
    }
}
CLEAN_AS(func_ov009_02262f0c, SceneActorSound_TurnOff)

/* func_ov009_02262f2c: while the emitter is on, its sounds follow a copy of `pos`. */
void SceneActorSound_UpdateAt(SceneActorSound *sound, const Vec3 *pos)
{
    if (sound->state.on) {
        Vec3 copy = *pos;
        SoundEmitter_UpdateAtB(&sound->emitter, &copy);
    }
}
CLEAN_AS(func_ov009_02262f2c, SceneActorSound_UpdateAt)

/* func_ov009_02262f54: turns the emitter on, through its slot 0x08, when it is off. */
void SceneActorSound_TurnOn(SceneActorSound *sound)
{
    if (!sound->state.on) {
        SoundEmitter_StopB(&sound->emitter);
        sound->state.on = 1;
    }
}
CLEAN_AS(func_ov009_02262f54, SceneActorSound_TurnOn)

/* func_ov009_02262f74: the destructor of the emitter (overlay 9's copy of func_020f59ec): its
 * vtable set back, then the base class's. */
void *SceneActorSound_Destroy(SceneActorSound *sound)
{
    sound->object.vtable = data_0213f090;
    SoundEmitterClass_DestructBase(&sound->object);
    return sound;
}
CLEAN_AS(func_ov009_02262f74, SceneActorSound_Destroy)

/* func_ov009_02262f8c: the emitter built (kind 2), off. */
void *SceneActorSound_Construct(SceneActorSound *sound)
{
    SoundEmitterClass_Construct2(&sound->object);
    sound->state.on = 0;
    return sound;
}
CLEAN_AS(func_ov009_02262f8c, SceneActorSound_Construct)

/* func_ov009_02262fa4: whether the first word of the member object at 0x1f4 is set (1 or 0). */
int SceneActor_Member1F4IsSet(SceneActor *actor)
{
    return func_020b3310(actor->member_1f4);
}
CLEAN_AS(func_ov009_02262fa4, SceneActor_Member1F4IsSet)

/* func_ov009_02262fb4: the tile's z. */
u32 SceneActor_TileZ(SceneActor *actor)
{
    return (u32) actor->tile_z;
}
CLEAN_AS(func_ov009_02262fb4, SceneActor_TileZ)

/* func_ov009_02262fc0: the tile's x. */
int SceneActor_TileX(SceneActor *actor)
{
    return actor->tile_x;
}
CLEAN_AS(func_ov009_02262fc0, SceneActor_TileX)

/* func_ov009_02262fcc: the address of the character's code. */
int SceneActor_CodeAddress(SceneActor *actor)
{
    return (int) (uintptr_t) &actor->code;
}
CLEAN_AS(func_ov009_02262fcc, SceneActor_CodeAddress)

/* func_ov009_02262fd8: SceneActor_SetModeByKindA while idle; else 0. */
int SceneActor_IdleSetModeByKindA(SceneActor *actor)
{
    if (actor->state == SCENE_ACTOR_IDLE) {
        return SceneActor_SetModeByKindA(actor);
    }
    return 0;
}
CLEAN_AS(func_ov009_02262fd8, SceneActor_IdleSetModeByKindA)

/* func_ov009_02262ff8: by its kind, sets mode 3 (kind 1), 2 (kind 2) or 6 (kind 3) through
 * vtable slot 0x6c, and gives its answer; 0 for other kinds. */
int SceneActor_SetModeByKindA(SceneActor *actor)
{
    switch (SceneActor_Kind(actor)) {
        case 2:
            return scene_actor_set_mode(actor, 2);
        case 3:
            return scene_actor_set_mode(actor, 6);
        case 1:
            return scene_actor_set_mode(actor, 3);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov009_02262ff8, SceneActor_SetModeByKindA)

/* func_ov009_0226303c: SceneActor_SetModeByKindB while idle; else 0. */
int SceneActor_IdleSetModeByKindB(SceneActor *actor)
{
    if (actor->state == SCENE_ACTOR_IDLE) {
        return SceneActor_SetModeByKindB(actor);
    }
    return 0;
}
CLEAN_AS(func_ov009_0226303c, SceneActor_IdleSetModeByKindB)

/* func_ov009_0226305c: by its kind, sets mode 3 (kind 1), 1 (kind 2) or 5 (kind 3) through
 * vtable slot 0x6c, and gives its answer; 0 for other kinds. */
int SceneActor_SetModeByKindB(SceneActor *actor)
{
    switch (SceneActor_Kind(actor)) {
        case 2:
            return scene_actor_set_mode(actor, 1);
        case 3:
            return scene_actor_set_mode(actor, 5);
        case 1:
            return scene_actor_set_mode(actor, 3);
        default:
            return 0;
    }
}
CLEAN_AS(func_ov009_0226305c, SceneActor_SetModeByKindB)

/* func_ov009_022630a0: whether it is in mode 0. */
int SceneActor_IsInMode0(SceneActor *actor)
{
    return actor->mode == 0;
}
CLEAN_AS(func_ov009_022630a0, SceneActor_IsInMode0)

/* func_ov009_022630b4: SCENE_ACTOR_FLAG_OUT_OF_VIEW cleared, then set again when
 * SceneActor_IsOutOfView says so. */
void SceneActor_UpdateOutOfView(SceneActor *actor)
{
    actor->flags_235 &= ~SCENE_ACTOR_FLAG_OUT_OF_VIEW;
    if (SceneActor_IsOutOfView(actor)) {
        actor->flags_235 |= SCENE_ACTOR_FLAG_OUT_OF_VIEW;
    }
}
CLEAN_AS(func_ov009_022630b4, SceneActor_UpdateOutOfView)

/* func_ov009_022630e4: whether it is outside the camera's box: there is no camera, or along x
 * it is further from the camera than the record's half-width, or along z further ahead or
 * behind than the record's depths. */
int SceneActor_IsOutOfView(SceneActor *actor)
{
    if (data_021c67a4 == 0) {
        return 1;
    }
    int dx = actor->position.x - data_021c67d0.x;
    if (dx < 0) {
        dx = -dx;
    }
    int dz = actor->position.z - data_021c67d0.z;
    if (dx > SceneActor_ViewRangeX(actor)) {
        return 1;
    }
    if (dz > SceneActor_ViewRangeZAhead(actor)) {
        return 1;
    }
    if (dz < -SceneActor_ViewRangeZBehind(actor)) {
        return 1;
    }
    return 0;
}
CLEAN_AS(func_ov009_022630e4, SceneActor_IsOutOfView)

/* func_ov009_0226313c (vtable slot 0x98): always 0. */
int SceneActor_Slot98(SceneActor *actor)
{
    (void) actor;
    return 0;
}
CLEAN_AS(func_ov009_0226313c, SceneActor_Slot98)

/* func_ov009_02263140 (vtable slot 0x94): whether the player is asked to stand at the stand
 * point's x (else at player 4's own x); always 1 here. */
int SceneActor_KeepsPointX(SceneActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_02263140, SceneActor_KeepsPointX)

/* func_ov009_02263144 (vtable slot 0xb0): whether its drawing draws the model; always 1
 * here. */
int SceneActor_DrawsModel(SceneActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_02263144, SceneActor_DrawsModel)

/* func_ov009_02263148 (vtable slot 0x90): whether SCENE_ACTOR_WALK asks for player state 0x38
 * (else 0x39); always 0 here. */
int SceneActor_WalksWithState38(SceneActor *actor)
{
    (void) actor;
    return 0;
}
CLEAN_AS(func_ov009_02263148, SceneActor_WalksWithState38)

/* func_ov009_0226314c (vtable slot 0xa0): byte 5 of the character's record. */
int SceneActor_RecordByte5(SceneActor *actor)
{
    SceneActorRecord record;
    func_020b2a68(&record, scene_actor_record(actor));
    int value = func_020b2a4c(&record);
    func_020b2a64(&record);
    return value;
}
CLEAN_AS(func_ov009_0226314c, SceneActor_RecordByte5)

/* func_ov009_022631b4: the character's id in main's table at data_021f69d0 (byte 4 of its
 * record, signed). */
int SceneActor_RecordId(SceneActor *actor)
{
    SceneActorRecord record;
    func_020b2a68(&record, scene_actor_record(actor));
    int value = func_020b2a50(&record);
    func_020b2a64(&record);
    return value;
}
CLEAN_AS(func_ov009_022631b4, SceneActor_RecordId)

/* func_ov009_0226321c: where a player stands to talk to it, and whether it has a place for
 * that. With areas, the point is 1.0 ahead of the first area's point along the direction it
 * faces, at height 0x200 and 0x200 back along z, and `angle` (when given) faces the area,
 * turned half round from its direction; each is left alone when NULL. Without, the point is
 * its position and the result 0.
 * QUIRK: without areas `point` is written even when NULL. */
int SceneActor_GetStandPoint(SceneActor *actor, Vec3 *point, s16 *angle)
{
    if (actor->areas == NULL || actor->area_count == 0) {
        *point = actor->position;
        return 0;
    }
    SceneActorArea *area = actor->areas;
    s16 facing = Math_Atan2(area->facing_x, area->facing_z);
    Vec3 ahead;
    ahead.z = FX_MulFunc(SCENE_ACTOR_ONE, area->facing_z);
    ahead.x = FX_MulFunc(SCENE_ACTOR_ONE, area->facing_x);
    ahead.y = 0;
    if (angle != NULL) {
        *angle = (s16) (facing + 0x8000);
    }
    if (point != NULL) {
        Vec3 sum;
        Vec_Add(&sum, func_02032754(area), &ahead);
        *point = sum;
        point->y = SCENE_ACTOR_STAND_HEIGHT;
        point->z -= SCENE_ACTOR_STAND_BACK;
    }
    return 1;
}
CLEAN_AS(func_ov009_0226321c, SceneActor_GetStandPoint)

/* func_ov009_022632c8: while it has a model, draws it with a copy of its matrix. */
void SceneActor_DrawModel(SceneActor *actor)
{
    if (actor->model == NULL) {
        return;
    }
    SceneActor_UpdateModelMatrix(actor, NULL);
    func_0205510c(actor->model_object, 0);
    Mtx43 matrix = actor->model_matrix;
    SceneActor_DrawShadows(actor, &matrix);
}
CLEAN_AS(func_ov009_022632c8, SceneActor_DrawModel)

/* func_ov009_02263314 (vtable slot 0x84, once the link has closed in SCENE_ACTOR_TALK_END):
 * nothing. */
void SceneActor_OnTalkClosed(SceneActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov009_02263314, SceneActor_OnTalkClosed)

/* func_ov009_02263318 (vtable slot 0x80, each frame the link stays open in
 * SCENE_ACTOR_TALK_END): nothing. */
void SceneActor_OnTalkWait(SceneActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov009_02263318, SceneActor_OnTalkWait)

/* func_ov009_0226331c (vtable slot 0x7c, once the link has opened in SCENE_ACTOR_TALK):
 * nothing. */
void SceneActor_OnTalkOpen(SceneActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov009_0226331c, SceneActor_OnTalkOpen)

/* func_ov009_02263320 (vtable slot 0x78, entering SCENE_ACTOR_TALK): names the receiver
 * "obj_etc_error" and clears its message. */
void SceneActor_PrepareTalk(SceneActor *actor)
{
    func_020a8164(&actor->receiver_vtable, data_ov009_02265a18);
    actor->message = 0;
}
CLEAN_AS(func_ov009_02263320, SceneActor_PrepareTalk)

/* func_ov009_02263344 (receiver slot 0x14, also vtable slot 0x88: a message ended): sets the
 * link's word at 0x10 to 100, unless the character's code is 0x500a.
 * REQUIRES: the receiver has a link when the code is not 0x500a. */
void SceneActor_OnMessageEnd(SceneActor *actor)
{
    if (!scene_actor_code_is(&actor->code, SCENE_ACTOR_CODE_NO_WAIT)) {
        func_020676c4(actor->link, 100);
    }
}
CLEAN_AS(func_ov009_02263344, SceneActor_OnMessageEnd)

/* _ZN18Obj_ov009_022658dc19func_ov009_022633acEji (vtable slot 0x4c): the scene's events: 0
 * and 1 start a visit, 8 makes it idle; 6 clears bit 0 of the character's visit flags, main's
 * byte at data_021f4b14, asks for main's table at data_021f69d0 (for nothing), resets the one at
 * data_021f69b8 and sets the byte at 0x234 to 1. Others do nothing. */
void SceneActor_OnSceneEvent(SceneActor *actor, unsigned int event, int arg)
{
    (void) arg;
    switch (event) {
        case SCENE_ACTOR_EVENT_6:
            func_020b23ec(actor->code, 0);
            func_020b23c8();
            func_020b5e10();
            func_020b5e90();
            actor->exit_step = 1;
            break;
        case SCENE_ACTOR_EVENT_TALK:
        case SCENE_ACTOR_EVENT_TALK_AGAIN:
            SceneActor_SetState(actor, SCENE_ACTOR_VISIT);
            break;
        case SCENE_ACTOR_EVENT_IDLE:
            SceneActor_SetState(actor, SCENE_ACTOR_IDLE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022633acEji, SceneActor_OnSceneEvent)

/* func_ov009_02263410 (vtable slot 0x48): whether `other` can talk to it. It must face it
 * (within 0x1000 of its direction turned half round). An actor of kind 0 then needs vtable
 * slot 0x8c to say no and `other`'s talk point within 3.0 of its own in the ground plane;
 * any other kind needs SCENE_ACTOR_FLAG_TALKABLE and kind 2, and the talk skips the visit
 * record when slot 0x8c says no. Past those first checks func_0203edd0 runs on it.
 * QUIRK: for kind 0, func_0203edd0 runs and the visit record is skipped even when `other` is
 * too far away. */
int SceneActor_CanTalkTo(SceneActor *actor, SceneActor *other)
{
    if (other == NULL) {
        return 0;
    }
    if (Math_AbsDiff16((s16) (actor->yaw + 0x8000), other->yaw) > SCENE_ACTOR_TALK_ANGLE) {
        return 0;
    }
    if (SceneActor_Kind(actor) != 0) {
        if (!(actor->flags_235 & SCENE_ACTOR_FLAG_TALKABLE) || SceneActor_Kind(actor) != 2) {
            return 0;
        }
        int slot_8c = scene_actor_call_int(actor, SLOT_8C);
        func_0203edd0(actor);
        actor->skip_visit = slot_8c == 0;
        return 1;
    }
    if (scene_actor_call_int(actor, SLOT_8C) != 0) {
        return 0;
    }
    const Vec3 *theirs = (const Vec3 *) (uintptr_t) scene_actor_call_int(other, SLOT_TALK_POINT);
    const Vec3 *mine = (const Vec3 *) (uintptr_t) scene_actor_call_int(actor, SLOT_TALK_POINT);
    fx32 distance = Vec_DistanceXZ(theirs, mine);
    func_0203edd0(actor);
    actor->skip_visit = 1;
    return distance < SCENE_ACTOR_TALK_DISTANCE;
}
CLEAN_AS(func_ov009_02263410, SceneActor_CanTalkTo)

/* func_ov009_022634e4 (vtable slot 0x50): the address of its talk point. */
int SceneActor_TalkPointAddress(SceneActor *actor)
{
    return (int) (uintptr_t) &actor->talk_point;
}
CLEAN_AS(func_ov009_022634e4, SceneActor_TalkPointAddress)

/* _ZN18Obj_ov009_022658dc19func_ov009_022634f0Ev (update of SCENE_ACTOR_WALK_AGAIN): when it
 * has a stand point, asks the player to stand there (player state 0x39, kind 2), at player
 * 4's own x when vtable slot 0x94 says no and that player exists, and moves to
 * SCENE_ACTOR_GONE when the player agrees. */
void SceneActor_UpdateWalkAgain(SceneActor *actor)
{
    Vec3 point;
    s16 angle;
    if (!SceneActor_GetStandPoint(actor, &point, &angle)) {
        return;
    }
    int x = point.x;
    int z = point.z;
    if (scene_actor_call_int(actor, SLOT_KEEP_X) == 0) {
        const Vec3 *player = func_02095794(SCENE_ACTOR_PLAYER);
        if (player != NULL) {
            x = player->x;
        }
    }
    if (FieldActor_PlayerRequestState39(SCENE_ACTOR_PLAYER_KIND, &x, &z, angle)) {
        SceneActor_SetState(actor, SCENE_ACTOR_GONE);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022634f0Ev, SceneActor_UpdateWalkAgain)

/* func_ov009_02263548 (entry of SCENE_ACTOR_WALK_AGAIN) */
int SceneActor_EnterWalkAgain(SceneActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_02263548, SceneActor_EnterWalkAgain)

/* _ZN18Obj_ov009_022658dc19func_ov009_0226354cEv (update of SCENE_ACTOR_LEAVE_AGAIN): on to
 * SCENE_ACTOR_WALK_AGAIN once func_02096174 agrees. */
void SceneActor_UpdateLeaveAgain(SceneActor *actor)
{
    if (func_02096174()) {
        SceneActor_SetState(actor, SCENE_ACTOR_WALK_AGAIN);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_0226354cEv, SceneActor_UpdateLeaveAgain)

/* func_ov009_02263568 (entry of SCENE_ACTOR_LEAVE_AGAIN) */
int SceneActor_EnterLeaveAgain(SceneActor *actor)
{
    (void) actor;
    func_02095944(0);
    return 1;
}
CLEAN_AS(func_ov009_02263568, SceneActor_EnterLeaveAgain)

/* func_ov009_0226357c (update of SCENE_ACTOR_GONE): counts the frames. From 20 of them (32 for
 * kind 1) on, when it has a stand point and main's table takes its id, it adds to the table at
 * that point, one unit further along z and at height func_020310c8 (0x200), turned half round,
 * with its tile; then hands its kind to func_020b22ac and sets SCENE_ACTOR_FLAG_GONE.
 * QUIRK: its kind is asked for once more than used; the counter is 16 bits and wraps, and
 * nothing stops the update after the flag is set. */
void SceneActor_UpdateGone(SceneActor *actor)
{
    actor->frames++;
    SceneActor_Kind(actor);
    int wait = SCENE_ACTOR_GONE_WAIT;
    if (SceneActor_Kind(actor) == 1) {
        wait += SCENE_ACTOR_GONE_WAIT_KIND_1;
    }
    if (actor->frames < wait) {
        return;
    }
    int id = SceneActor_RecordId(actor);
    Vec3 point;
    s16 angle;
    if (!SceneActor_GetStandPoint(actor, &point, &angle)) {
        return;
    }
    if (!func_020b6098(func_020b5e10(), id)) {
        return;
    }
    point.y = func_020310c8(0);
    point.z += SCENE_ACTOR_GONE_AHEAD;
    void *table = func_020b5e10();
    int scene = func_020b65c4();
    func_020b5ea0(table, scene, &point, SCENE_ACTOR_GONE_ARG, (short) (angle + 0x8000), actor->tile_x, actor->tile_z);
    func_020b22ac(SceneActor_Kind(actor));
    actor->flags |= SCENE_ACTOR_FLAG_GONE;
}
CLEAN_AS(func_ov009_0226357c, SceneActor_UpdateGone)

/* func_ov009_02263648 (entry of SCENE_ACTOR_GONE): the frame count starts again. */
int SceneActor_EnterGone(SceneActor *actor)
{
    actor->frames = 0;
    return 1;
}
CLEAN_AS(func_ov009_02263648, SceneActor_EnterGone)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263658Ev (update of SCENE_ACTOR_WALK): once
 * func_02096168 agrees, an actor of kind 2 or 3 calls func_0203aec4 and moves to
 * SCENE_ACTOR_GONE.
 * QUIRK: other kinds stay in SCENE_ACTOR_WALK. */
void SceneActor_UpdateWalk(SceneActor *actor)
{
    if (!func_02096168()) {
        return;
    }
    switch (SceneActor_Kind(actor)) {
        case 2:
        case 3:
            func_0203aec4();
            SceneActor_SetState(actor, SCENE_ACTOR_GONE);
            break;
        default:
            break;
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263658Ev, SceneActor_UpdateWalk)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263694Ev (entry of SCENE_ACTOR_WALK): whether the
 * player agreed to stand at the stand point: at player 4's own x when vtable slot 0x94 says no
 * and that player exists; through player state 0x38 when slot 0x90 says so, else 0x39 (kind 1
 * when its own kind is 2, else 0). 0 without a stand point. */
int SceneActor_EnterWalk(SceneActor *actor)
{
    Vec3 point;
    s16 angle;
    if (!SceneActor_GetStandPoint(actor, &point, &angle)) {
        return 0;
    }
    int x = point.x;
    int z = point.z;
    if (scene_actor_call_int(actor, SLOT_KEEP_X) == 0) {
        const Vec3 *player = func_02095794(SCENE_ACTOR_PLAYER);
        if (player != NULL) {
            x = player->x;
        }
    }
    if (scene_actor_call_int(actor, SLOT_STATE_38) != 0) {
        return FieldActor_PlayerRequestState38(&x, &z, &angle) != 0;
    }
    u32 kind = SceneActor_Kind(actor) == 2;
    return FieldActor_PlayerRequestState39(kind, &x, &z, angle) != 0;
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263694Ev, SceneActor_EnterWalk)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263718Ev (update of SCENE_ACTOR_LEAVE): on to
 * SCENE_ACTOR_WALK once func_02096174 agrees. */
void SceneActor_UpdateLeave(SceneActor *actor)
{
    if (func_02096174()) {
        SceneActor_SetState(actor, SCENE_ACTOR_WALK);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263718Ev, SceneActor_UpdateLeave)

/* func_ov009_02263734 (entry of SCENE_ACTOR_LEAVE) */
int SceneActor_EnterLeave(SceneActor *actor)
{
    (void) actor;
    func_02095944(0);
    return 1;
}
CLEAN_AS(func_ov009_02263734, SceneActor_EnterLeave)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263748Ev (update of SCENE_ACTOR_TALK_END): once the
 * link has closed, vtable slot 0x84, the receiver handed back and the scene goes on; until
 * then (or without a link) slot 0x80. Its state stays SCENE_ACTOR_TALK_END until the scene
 * sets another. */
void SceneActor_UpdateTalkEnd(SceneActor *actor)
{
    if (actor->link != NULL && actor->link->status == 0) {
        scene_actor_call_void(actor, SLOT_TALK_CLOSED);
        func_0203ee08(actor, scene_actor_receiver(actor));
        func_0203e020(actor);
    } else {
        scene_actor_call_void(actor, SLOT_TALK_WAIT);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263748Ev, SceneActor_UpdateTalkEnd)

/* func_ov009_0226378c (entry of SCENE_ACTOR_TALK_END) */
int SceneActor_EnterTalkEnd(SceneActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_0226378c, SceneActor_EnterTalkEnd)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263790Ev (update of SCENE_ACTOR_TALK): once the link
 * is open, vtable slot 0x7c and on to SCENE_ACTOR_TALK_END. */
void SceneActor_UpdateTalk(SceneActor *actor)
{
    if (actor->link != NULL && actor->link->status != 0) {
        scene_actor_call_void(actor, SLOT_TALK_OPEN);
        SceneActor_SetState(actor, SCENE_ACTOR_TALK_END);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263790Ev, SceneActor_UpdateTalk)

/* _ZN18Obj_ov009_022658dc19func_ov009_022637bcEv (entry of SCENE_ACTOR_TALK): takes the
 * receiver, raises the link's request and prepares the talk (vtable slot 0x78).
 * REQUIRES: the receiver has a link once func_0203ee14 has taken it. */
int SceneActor_EnterTalk(SceneActor *actor)
{
    func_0203ee14(actor, scene_actor_receiver(actor));
    actor->link->requested = 1;
    scene_actor_call_void(actor, SLOT_PREPARE_TALK);
    return 1;
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022637bcEv, SceneActor_EnterTalk)

/* _ZN18Obj_ov009_022658dc19func_ov009_022637ecEv (update of SCENE_ACTOR_VISIT): when the talk
 * skips the visit record, on to SCENE_ACTOR_TALK. Else, once main has an answer (nonzero), it
 * keeps whether it is 2 (SCENE_ACTOR_FLAG_VISIT_2) and whether it is 3 (visit_3); either starts
 * the talk, else kind 1 moves to SCENE_ACTOR_LEAVE_AGAIN and others to SCENE_ACTOR_LEAVE. */
void SceneActor_UpdateVisit(SceneActor *actor)
{
    if (actor->skip_visit) {
        SceneActor_SetState(actor, SCENE_ACTOR_TALK);
        return;
    }
    int answer = func_020b2470(actor->code);
    if (answer == 0) {
        return;
    }
    actor->flags = (u8) ((actor->flags & ~SCENE_ACTOR_FLAG_VISIT_2) | (answer == 2 ? SCENE_ACTOR_FLAG_VISIT_2 : 0));
    actor->visit_3 = answer == 3;
    if ((actor->flags & SCENE_ACTOR_FLAG_VISIT_2) || actor->visit_3) {
        SceneActor_SetState(actor, SCENE_ACTOR_TALK);
    } else if (SceneActor_Kind(actor) == 1) {
        SceneActor_SetState(actor, SCENE_ACTOR_LEAVE_AGAIN);
    } else {
        SceneActor_SetState(actor, SCENE_ACTOR_LEAVE);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022637ecEv, SceneActor_UpdateVisit)

/* func_ov009_02263888 (entry of SCENE_ACTOR_VISIT): asks main for the visit record unless the
 * talk skips it, and forgets the last answer. */
int SceneActor_EnterVisit(SceneActor *actor)
{
    if (!actor->skip_visit) {
        func_020b248c(actor->code);
    }
    actor->flags &= ~SCENE_ACTOR_FLAG_VISIT_2;
    actor->visit_3 = 0;
    return 1;
}
CLEAN_AS(func_ov009_02263888, SceneActor_EnterVisit)

/* func_ov009_022638c8 (update of SCENE_ACTOR_IDLE): nothing. */
void SceneActor_UpdateIdle(SceneActor *actor)
{
    (void) actor;
}
CLEAN_AS(func_ov009_022638c8, SceneActor_UpdateIdle)

/* func_ov009_022638cc (entry of SCENE_ACTOR_IDLE) */
int SceneActor_EnterIdle(SceneActor *actor)
{
    (void) actor;
    return 1;
}
CLEAN_AS(func_ov009_022638cc, SceneActor_EnterIdle)

/* _ZN18Obj_ov009_022658dc19func_ov009_022638d0Ev: the state's update, through its table.
 * REQUIRES: the state is not negative (SceneActor_SetState only sets 0 to 8). */
void SceneActor_UpdateState(SceneActor *actor)
{
    static const MemberPointer *const updates[SCENE_ACTOR_STATES] = {
        &data_ov009_02265810, /* SceneActor_UpdateIdle */
        &data_ov009_022657c8, /* SceneActor_UpdateVisit */
        &data_ov009_022657d8, /* SceneActor_UpdateTalk */
        &data_ov009_022657e0, /* SceneActor_UpdateTalkEnd */
        &data_ov009_02265840, /* SceneActor_UpdateLeave */
        &data_ov009_02265850, /* SceneActor_UpdateWalk */
        &data_ov009_022657b8, /* SceneActor_UpdateGone */
        &data_ov009_022657a8, /* SceneActor_UpdateLeaveAgain */
        &data_ov009_022657d0, /* SceneActor_UpdateWalkAgain */
    };
    MemberTable_InitOnce(&data_ov009_02265b28, data_ov009_02265c6c, updates, SCENE_ACTOR_STATES);
    if (actor->state < SCENE_ACTOR_STATES) {
        MemberPointer_CallVoid(&data_ov009_02265c6c[actor->state], actor);
    }
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022638d0Ev, SceneActor_UpdateState)

/* _ZN18Obj_ov009_022658dc19func_ov009_022639a0Ei: enters state `state` if its entry (through a
 * table) agrees; whether it did. States 9 and above do not exist.
 * REQUIRES: `state` is not negative. */
int SceneActor_SetState(SceneActor *actor, int state)
{
    static const MemberPointer *const entries[SCENE_ACTOR_STATES] = {
        &data_ov009_022657c0, /* SceneActor_EnterIdle */
        &data_ov009_022657f8, /* SceneActor_EnterVisit */
        &data_ov009_022657f0, /* SceneActor_EnterTalk */
        &data_ov009_02265898, /* SceneActor_EnterTalkEnd */
        &data_ov009_02265808, /* SceneActor_EnterLeave */
        &data_ov009_02265820, /* SceneActor_EnterWalk */
        &data_ov009_02265828, /* SceneActor_EnterGone */
        &data_ov009_02265848, /* SceneActor_EnterLeaveAgain */
        &data_ov009_02265888, /* SceneActor_EnterWalkAgain */
    };
    MemberTable_InitOnce(&data_ov009_02265b2c, data_ov009_02265c24, entries, SCENE_ACTOR_STATES);
    if (state < SCENE_ACTOR_STATES && MemberPointer_CallInt(&data_ov009_02265c24[state], actor) != 0) {
        actor->state = state;
        return 1;
    }
    return 0;
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_022639a0Ei, SceneActor_SetState)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263a80Ev (run of mode 6): back to mode 0, through
 * vtable slot 0x6c. */
void SceneActor_RunMode6(SceneActor *actor)
{
    scene_actor_set_mode(actor, 0);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263a80Ev, SceneActor_RunMode6)

/* func_ov009_02263a94 (entry of mode 6) */
int SceneActor_EnterMode6(void)
{
    return 1;
}
CLEAN_AS(func_ov009_02263a94, SceneActor_EnterMode6)

/* _ZN18Obj_ov009_022658dc19func_ov009_02263a98Ev (run of mode 5): back to mode 0, through
 * vtable slot 0x6c. */
void SceneActor_RunMode5(SceneActor *actor)
{
    scene_actor_set_mode(actor, 0);
}
CLEAN_AS(_ZN18Obj_ov009_022658dc19func_ov009_02263a98Ev, SceneActor_RunMode5)

/* func_ov009_02263aac (entry of mode 5) */
int SceneActor_EnterMode5(void)
{
    return 1;
}
CLEAN_AS(func_ov009_02263aac, SceneActor_EnterMode5)
